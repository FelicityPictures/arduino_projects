#include <Servo.h>

const int outputPin = A7;
const int piezoInputPin = 2;
const int redPin = A0;
const int greenPin = A1;
const int bluePin = A2;

int piezoRead;
int piezoMaximum = 0;
int val, mappedVal;
unsigned long previousTime, elapsedTime;
int knockCounter;
unsigned long initialDelay;

//for debounce
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

Servo myservo;

void setup() {
  Serial.begin(9600);
  Serial.println(F("Starting"));
  
  myservo.attach(outputPin);
  myservo.write(0);
  pinMode(piezoInputPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  knockCounter = 0;
  previousTime = millis();
  analogWrite(redPin, 255);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
  
//  piezoRead = analogRead(piezoInputPin);
//  while(millis() < 5000){
//    Serial.println("Calibrating...");
//    if(piezoMaximum < piezoRead){
//      piezoMaximum = piezoRead;
//    }
//  }
}

void loop() {
  // Read piezo
//  piezoRead = analogRead(piezoInputPin);
//  Serial.print(F("piezoRead: "));
//  Serial.println(piezoRead);
//  if(piezoRead > piezoMaximum+5){
//    Serial.println("Knock!");
//    delay(1000);
//  }

  int reading = digitalRead(piezoInputPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      
      // button is actually on
      if (buttonState == HIGH) {        
        knockCounter++;
        elapsedTime = millis() - previousTime;
        previousTime = millis();
        if(knockCounter <= 2){
          initialDelay = elapsedTime;
        }else{
          if(knockCounter == 3 || knockCounter == 4){
            // check that elapsedTime is half of initialDelay. If it isn't, reset the knock progress
            if(elapsedTime < (initialDelay/2) - (initialDelay/4) or elapsedTime > (initialDelay/2) + (initialDelay/4)){
              knockCounter = 0;
            }
          }else if(knockCounter == 5 || knockCounter == 7){
            // check that elapsedTime is equal to initialDelay. If it isn't, reset the knock progress
            if(elapsedTime < initialDelay - (initialDelay/4) or elapsedTime > initialDelay + (initialDelay/4)){
              knockCounter = 0;
            }else if(knockCounter == 7){
              //open door
              delay(500);
//              myservo.write(90);
              for (int pos = 0; pos < 90; pos++) { // goes from 0 degrees to 180 degrees
                // in steps of 1 degree
                myservo.write(pos);              // tell servo to go to position in variable 'pos'
                delay(15);                       // waits 15ms for the servo to reach the position
              }
              analogWrite(redPin, 0);
              analogWrite(greenPin, 255);
              analogWrite(bluePin, 0);
              delay(5000);
//              myservo.write(0);
              for (int pos = 90; pos > 0; pos--) { // goes from 0 degrees to 180 degrees
                // in steps of 1 degree
                myservo.write(pos);              // tell servo to go to position in variable 'pos'
                delay(15);                       // waits 15ms for the servo to reach the position
              }
              //reset
              knockCounter = 0;
            }
          }else if(knockCounter == 6){
            // check that elapsedTime is two times initialDelay. If it isn't, reset the knock progress
            if(elapsedTime < (initialDelay*2) - (initialDelay/4) or elapsedTime > (initialDelay*2) + (initialDelay/4)){
              knockCounter = 0;
            }
          }
        }
        
        Serial.print("pressed counter: ");
        Serial.print(knockCounter);
        Serial.print(" elapsed time since last one: ");
        Serial.println(elapsedTime);
      }
    }
  }
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;

  if(knockCounter < 1){
    analogWrite(redPin, 255);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
  }else if(knockCounter >= 1 && knockCounter <= 7){
    analogWrite(redPin, 255);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 0);
  }
  
}


// Moves servo
// 1023 is open
// 0 is close
//    mappedVal = map(val, 0, 1023, 0, 90);     // scale it to use it with the servo (value between 0 and 180)
//    myservo.write(mappedVal);                  // sets the servo position according to the scaled value
//    delay(1000);
