/*
 * D0 con L3 (led rojo)
 * D1 con P1
 * D2 con L1 (led verde)
 * 
*/

const int buttonPin = D1; // the number of the pushbutton pin
const int ledPinGreen = D0; // the number of the LED pin (Green)
const int ledPinRed =  D2; // the number of the LED pin (Red)

int buttonState = 0; // variable for reading the pushbutton status

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinRed, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT); 
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  if(buttonState == HIGH){
    digitalWrite(ledPinGreen,HIGH);    
    digitalWrite(ledPinRed,LOW);
    delay(1000);                      // Wait for a second
  } else {
    digitalWrite(ledPinGreen,LOW);    
    digitalWrite(ledPinRed,HIGH);
    delay(1000);                      // Wait for a second
  }
  
}
