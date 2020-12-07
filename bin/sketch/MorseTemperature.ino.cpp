#include <Arduino.h>
#line 1 "e:\\Source\\Brians Playground\\Microcontrollers\\arduino\\MorseTemperature\\MorseTemperature.ino"
#include <DallasTemperature.h>
#include <string.h>
#include "LowPower.h"

double tempF;
//double tempC;

int LedPin = 9;

#define SLEEP_LOOPS 15 // number of loops for 8 second sleeps:  loops = (minutes * 60) / 8  (37 loops is about 5 minutes)

// Dallas Temperature
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);           // Setup a oneWire instance to communicate with any OneWire device
DallasTemperature tempSensors(&oneWire); // Pass oneWire reference to DallasTemperature library

#line 17 "e:\\Source\\Brians Playground\\Microcontrollers\\arduino\\MorseTemperature\\MorseTemperature.ino"
void setup();
#line 28 "e:\\Source\\Brians Playground\\Microcontrollers\\arduino\\MorseTemperature\\MorseTemperature.ino"
void loop();
#line 43 "e:\\Source\\Brians Playground\\Microcontrollers\\arduino\\MorseTemperature\\MorseTemperature.ino"
void doMorse();
#line 85 "e:\\Source\\Brians Playground\\Microcontrollers\\arduino\\MorseTemperature\\MorseTemperature.ino"
void getTemperature();
#line 94 "e:\\Source\\Brians Playground\\Microcontrollers\\arduino\\MorseTemperature\\MorseTemperature.ino"
void setupTempSensors();
#line 99 "e:\\Source\\Brians Playground\\Microcontrollers\\arduino\\MorseTemperature\\MorseTemperature.ino"
void doSleep();
#line 17 "e:\\Source\\Brians Playground\\Microcontrollers\\arduino\\MorseTemperature\\MorseTemperature.ino"
void setup()
{
  Serial.begin(9600);
  delay(3000);
  Serial.println("starting");

  pinMode(LedPin, OUTPUT);

  setupTempSensors(); // setup 1-wire temperature sensors
}

void loop()
{
  getTemperature();
  for (int c = 0; c < 3; c++)
  {
    // hardcode tempF if you dont have a dallas temp sensor to simulate what you want
    //tempF = 40;
    doMorse();
    delay(3000);
  }

  doSleep();
  Serial.println("Arduino:- Woke up to do work");
}

void doMorse()
{

  String tempString = String(tempF, 0);
  Serial.print("Temperature is: ");
  Serial.println(tempString);

  for (int i = 0; i < tempString.length(); i++)
  {
    Serial.print("Processing Character#: ");
    Serial.println(i);
    int c = (int)(tempString[i] - 48);
    Serial.print("Character: ");
    Serial.println(c);
    if (c == 0)
    {
      delay(500);
      Serial.print("Da ");
      digitalWrite(LedPin, HIGH);
      delay(400);
      digitalWrite(LedPin, LOW);
    }
    else
    {
      for (int x = 0; x < c; x++)
      {
        delay(500);
        Serial.print("Dit ");
        digitalWrite(LedPin, HIGH);
        delay(200);
        digitalWrite(LedPin, LOW);
      }
    }
    Serial.println("");
    if (i < tempString.length() - 1) // if it is not the last number in the string?
    {
      delay(1000);
    }
  }
}

// get the current temperature
void getTemperature()
{

  tempSensors.requestTemperatures();
  //tempC = (tempSensors.getTempCByIndex(0));
  tempF = (tempSensors.getTempCByIndex(0) * 9.0) / 5.0 + 32.0;
}

// setup temperature sensor
void setupTempSensors()
{
  tempSensors.begin();
}

void doSleep()
{
  for (int i = 0; i < SLEEP_LOOPS; i++)
  {
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
}
