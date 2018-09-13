#include <CayenneMessage.h>
#include <CayenneArduinoDefines.h>
#include <CayenneMQTTESP8266.h>
#include <CayenneMQTTWiFiClient.h>
#include <CayenneArduinoMQTTClient.h>
#include <CayenneHandlers.h>
#include <DetectDevice.h>

// This example shows how to connect to Cayenne using an ESP8266 and send/receive sample data.
// Make sure you install the ESP8266 Board Package via the Arduino IDE Board Manager and select the correct ESP8266 board before compiling. 

//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>

// WiFi network info.
char ssid[] = "MiFibra-16CD";
char wifiPassword[] = "gxvK63Xb";
//char ssid[] = "iPhone INGCAG";
//char wifiPassword[] = "m68bzrr2we5dz";


// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "8fdf28e0-4a77-11e7-afce-8d5fd2a310a7";
char password[] = "59a6896aa117db561f9f2990378f2f6c038e3149";
char clientID[] = "da0bbf70-6fef-11e8-84d1-4d9372e87a68";

unsigned long lastMillis = 0;

/*
 * D0 con L2 (led amarillo)
 * A0 con Pot
 * 
*/
const int sensorTerPin = A0;    // select the input pin for the termometer
const int greenLedPin = D0;      // select the pin for the LED
int sensorTerValue = 0;  // variable to store the value coming from the sensor

const int sensorLigPin = D1;    // select the input pin for the light resistor
const int yellowLedPin = D2;      // select the pin for the LED
int sensorLigValue = 0;  // variable to store the value coming from the sensor


void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(greenLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);

  Serial.begin(9600);

  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() {
  // read the value from the sensor:
  sensorTerValue = analogRead(sensorTerPin);
  sensorTerValue = sensorTerValue * 10;
  digitalWrite(greenLedPin, sensorTerValue);
  // turn the ledPin on
  sensorLigValue = analogRead(sensorLigPin);
  sensorLigValue = sensorLigValue / 10;
  digitalWrite(yellowLedPin, sensorLigValue);
  delay(30);

  //Publish data every 0,1 seconds (100 milliseconds). Change this value to publish at a different interval.
  //if (millis() - lastMillis > 100) {
    //lastMillis = millis();
    //Write data to Cayenne here. This example just sends the current uptime in milliseconds.
//    Cayenne.virtualWrite(0, lastMillis);
//    Cayenne.virtualWrite(1, digitalRead(ledPin) );//put in chanel 1 LED value
    Cayenne.virtualWrite(2, sensorTerValue);//put in chanel 2 TEMP value 
    Cayenne.virtualWrite(3, sensorLigValue);//put in chanel 3 LDR value   
  //}
}

//Default function for processing actuator commands from the Cayenne Dashboard.
//You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
CAYENNE_IN_DEFAULT()
{
  CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}

CAYENNE_OUT()
