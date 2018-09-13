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
char clientID[] = "165d2c10-6fec-11e8-9561-9382c8ec42bc";

unsigned long lastMillis = 0;

/*
 * D0 con L1 (led rojo)
 * D1 con P1
 * D2 con L3 (led verde)
 * 
*/

const int buttonPin = D1; // the number of the pushbutton pin
const int ledPinGreen = D0; // the number of the LED pin (Green)
const int ledPinRed =  D2; // the number of the LED pin (Red)

int buttonState = 0; // variable for reading the pushbutton status
int readState = 0;

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinRed, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  Serial.begin(115200);

  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() {
  
  Cayenne.loop();
  
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  //readState = Cayenne.digitalRead(4);
  
  if(buttonState == HIGH || readState == HIGH){
    digitalWrite(ledPinGreen,HIGH);    
    digitalWrite(ledPinRed,LOW);
    delay(1000);                      // Wait for a second
  } else {
    digitalWrite(ledPinGreen,LOW);    
    digitalWrite(ledPinRed,HIGH);
    delay(1000);                      // Wait for a second
  }

  //Publish data every 0,5 seconds (500 milliseconds). Change this value to publish at a different interval.
  if (millis() - lastMillis > 500) {
    lastMillis = millis();
    //Write data to Cayenne here. This example just sends the current uptime in milliseconds.
//    Cayenne.virtualWrite(0, lastMillis);
//    Cayenne.virtualWrite(1, ledPinGreen);//put in chanel 1 LED value
//    Cayenne.virtualWrite(2, ledPinRed);//put in chanel 2 LED value
    Cayenne.virtualWrite(3, buttonState);//put in chanel 3 Button value
//    delay(500);
  }

}

//Default function for processing actuator commands from the Cayenne Dashboard.
//You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
CAYENNE_IN_DEFAULT()
{
CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}

/*
CAYENNE_IN(10)
{
  CAYENNE_LOG("CAYENNE_IN(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
  
  int i = getValue.asInt();
  if (i==1) {
    CAYENNE_LOG("FAN DOWN");
    digitalWrite(ledPinGreen,LOW); //Control GPIO 04(GreenLed)
  }else{
    CAYENNE_LOG("FAN UP");
    digitalWrite(ledPinGreen,HIGH); //Control GPIO 04(GreenLed)
  }
}

CAYENNE_IN(11){
  CAYENNE_LOG("CAYENNE_IN(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
  
  int i = getValue.asInt();
  if(i==1){
    CAYENNE_LOG("FAN ACTIVE");
    digitalWrite(ledPinRed,LOW); //Control GPIO 05(YellowLed)
  }else{
    CAYENNE_LOG("FAN WAIT");
    digitalWrite(ledPinRed,HIGH); //Control GPIO 05(YellowLed)
  }
}
/*
CAYENNE_IN(6){
  CAYENNE_LOG("CAYENNE_IN(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
}
*/


