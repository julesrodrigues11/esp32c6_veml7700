#include "Adafruit_VEML7700.h"

// Baud rate for debug serial
#define SERIAL_DEBUG_BAUD 115200

// Defining constants for SDA and SCL - Can be updated depending on the board's needs
#define SDA 6
#define SCL 7

Adafruit_VEML7700 veml = Adafruit_VEML7700();

float lux;

// Function to set up light sensor - Taken from official repository, can be found at https://learn.adafruit.com/adafruit-veml7700/arduino
void lightSensorSetup()
{
    Serial.println("Adafruit VEML7700 Test");

    if (!veml.begin()) {
        Serial.println("Sensor not found");
        while(1);
    }
    Serial.println("Sensor found");

    Serial.print(F("Gain: "));
    switch (veml.getGain())
    {
        case VEML7700_GAIN_1: Serial.println("1"); break;
        case VEML7700_GAIN_2: Serial.println("2"); break;
        case VEML7700_GAIN_1_4: Serial.println("1/4"); break;
        case VEML7700_GAIN_1_8: Serial.println("1/8"); break;
    }

    Serial.print(F("Integration Time (ms): "));
    switch (veml.getIntegrationTime())
    {
        case VEML7700_IT_25MS: Serial.println("25"); break;
        case VEML7700_IT_50MS: Serial.println("50"); break;
        case VEML7700_IT_100MS: Serial.println("100"); break;
        case VEML7700_IT_200MS: Serial.println("200"); break;
        case VEML7700_IT_400MS: Serial.println("400"); break;
        case VEML7700_IT_800MS: Serial.println("800"); break;
    }

    veml.setLowThreshold(10000);
    veml.setHighThreshold(20000);
    veml.interruptEnable(true);

}

// Function to scan for components attached on the I2C
void Scanner()
{
    Serial.println();
    Serial.println("I2C scanner. Scanning ....");

    byte count = 0;
    Wire.begin(SDA, SCL);
    for (byte i = 8; i < 120; i++)
    {
        Wire.beginTransmission(i);
        if (Wire.endTransmission() == 0)
        {
            Serial.print("Found address: ");
            Serial.print(i, DEC);
            Serial.print(" (0x");
            Serial.print(i, HEX);
            Serial.println(")");
            count++;
        }
    }
    Serial.print("Found ");
    Serial.print(count, DEC);
    Serial.print(" device(s).");
}

// Set up function - For initialisation, Initialises the Serial and Light Sensor
void setup()
{
    do
    {
        Serial.begin(SERIAL_DEBUG_BAUD);
    } while (!Serial);

    delay(2000);
    Serial.println("Initialised!");
    
    Wire.begin(SDA, SCL);
    
    lightSensorSetup();
    
}

// Loop function - Reads lux value from VEML sensor and prints on Serial
void loop()
{
    lux = veml.readLux();
    Serial.println(lux);
}