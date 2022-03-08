// pitches library allows us to use the tone() function
#include "pitches.h"

//-------Initialise variables-----------
// define array of LED ports
int ledArray[] = {12,11,10,9};
// initialise states of LEDs
int ledStateArray[] = {LOW, LOW, LOW, LOW};
// initialise counter
int counter = 0;
// initialise sensor values for reading potentiometer
int sensorValue;
int sensorLow = 1023;
int sensorHigh = 0;
// initialise switch state for button functionality
int switchState = 0;
// push button is defined at this pin
const int buttonPin = 8; 
// initialise this button state variable, high is pressed, low if not pressed
int buttonState = LOW; 
// initialise this circuit state variable: negative if circuit is off, positive if on
int circuitState = -1; 
// debounce technique taken from: https://www.programmingelectronics.com/debouncing-a-button-with-arduino/
// the last time the output pin was toggled
long lastDebounceTime = 0;  
// the debounce time; increase if the output flickers
long debounceDelay = 50;    



unsigned long previousMillis = 0;        // will store last time LED was updated


long interval = 500;           // interval at which to blink (milliseconds)

void setup() {
  Serial.begin(9600);
 //  set the digital pin as output:
   for(int i=0; i<4; i++){
    pinMode(ledArray[i], OUTPUT);
   }
   pinMode(8, INPUT);
  
}

void loop() {
  sensorValue = analogRead(A0);
  switchState = digitalRead(9);

    int tempo = map(sensorValue,sensorLow,sensorHigh, 2000, 100);
    unsigned long currentMillis = millis();
    //sample the state of the button - is it pressed or not?
    buttonState = digitalRead(buttonPin);
  
    //filter out any noise by setting a time buffer
    if ( (millis() - lastDebounceTime) > debounceDelay) {
  
      //if the button has been pressed, lets toggle the LED from "off to on" or "on to off"
      if ( (buttonState == LOW) && (circuitState < 0) ) {
  
         if (currentMillis - previousMillis >= tempo) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;
      // state one
  
        if(counter==0){
          ledStateArray[0] = HIGH;
          ledStateArray[1] = LOW;
          ledStateArray[2] = LOW;
          ledStateArray[3] = LOW;
          digitalWrite(ledArray[0], ledStateArray[0]);  
          digitalWrite(ledArray[1], ledStateArray[1]);  
          digitalWrite(ledArray[2], ledStateArray[2]);  
          digitalWrite(ledArray[3], ledStateArray[3]); 

          tone(13, NOTE_C4, tempo);
          noTone(8);
          counter++;
        }
        //state two
        else if(counter==1){
          ledStateArray[0] = LOW;
          ledStateArray[1] = HIGH;
          ledStateArray[2] = LOW;
          ledStateArray[3] = LOW;
          digitalWrite(ledArray[0], ledStateArray[0]);  
          digitalWrite(ledArray[1], ledStateArray[1]);  
          digitalWrite(ledArray[2], ledStateArray[2]);  
          digitalWrite(ledArray[3], ledStateArray[3]); 

          tone(13, NOTE_F4, tempo);
          noTone(8);          
          counter++;        
        }
        //state three
        else if(counter==2){
          ledStateArray[0] = LOW;
          ledStateArray[1] = LOW;
          ledStateArray[2] = HIGH;
          ledStateArray[3] = LOW;
          digitalWrite(ledArray[0], ledStateArray[0]);  
          digitalWrite(ledArray[1], ledStateArray[1]);  
          digitalWrite(ledArray[2], ledStateArray[2]);  
          digitalWrite(ledArray[3], ledStateArray[3]); 

          tone(13, NOTE_G4, tempo);
          noTone(8);           
          counter++;                                 
        }
        //state four
        else if(counter==3){
          ledStateArray[0] = LOW;
          ledStateArray[1] = LOW;
          ledStateArray[2] = LOW;
          ledStateArray[3] = HIGH;
          digitalWrite(ledArray[0], ledStateArray[0]);  
          digitalWrite(ledArray[1], ledStateArray[1]);  
          digitalWrite(ledArray[2], ledStateArray[2]);  
          digitalWrite(ledArray[3], ledStateArray[3]);  
          
          tone(13, NOTE_B4, tempo);
          noTone(8);
          counter = 0;
          
        }
        else{
          //error
        }
        }
        //now the LED is on, we need to change the state
        circuitState = -circuitState; 
        //set the current time
        lastDebounceTime = millis(); 
      }
      //turn off sequencer
      else if ( (buttonState == LOW) && (circuitState > 0) ) {
        ledStateArray[0] = LOW;
        ledStateArray[1] = LOW;
        ledStateArray[2] = LOW;
        ledStateArray[3] = LOW;
        digitalWrite(ledArray[0], ledStateArray[0]);  
        digitalWrite(ledArray[1], ledStateArray[1]);  
        digitalWrite(ledArray[2], ledStateArray[2]);  
        digitalWrite(ledArray[3], ledStateArray[3]);  
        //now the LED is off, we need to change the state
        circuitState = -circuitState;
        //set the current time 
        lastDebounceTime = millis(); 
      }
  
    }
    


}
