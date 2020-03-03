const int switchPin = 8;
int outputPin = 4;  // 2 is green, 3 is yellow, 4 is red

int greenInitiated = 0;
unsigned long greenPrevious = 0;
unsigned long greenElapsed = 0;

void setup() {
  pinMode(switchPin, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(outputPin, HIGH);
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(switchPin);
  
  if(reading == LOW){
    outputPin = 4;
  }else{
    if(greenInitiated != 1){
      greenPrevious = millis();
      greenInitiated = 1;
      greenElapsed = 0;
    }
  }

  if(greenInitiated == 1){
    greenElapsed += millis() - greenPrevious;
    greenPrevious = millis();
    if(greenElapsed > 1000){
      if(greenElapsed < 2000){
        outputPin = 3;
      }else if(greenElapsed >= 2000){
        if(greenElapsed < 5000){
          outputPin = 2;
        }else{
          greenInitiated = 0;
        }
      }
    }
  }
  
  if(outputPin == 2){
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  }else if(outputPin == 3){
    digitalWrite(2, LOW);
    digitalWrite(4, LOW);
  }else if(outputPin == 4){
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
  }
  digitalWrite(outputPin, HIGH);
//    // check to see if you just pressed the button
//    // (i.e. the input went from LOW to HIGH), and you've waited long enough
//    // since the last press to ignore any noise:
//    // If the switch changed, due to noise or pressing:
//    if (reading != lastSwitchState) {
//      // reset the debouncing timer
//      lastDebounceTime = millis();
//    }
//    if ((millis() - lastDebounceTime) > debounceDelay) {
////      if (reading != switchState) {
////        switchState = reading;
//        outputState = HIGH;
////      }
//    }
//  }
//
//  digitalWrite(outputPin, outputState);
//
//  // save the reading. Next time through the loop, it'll be the lastButtonState:
//  lastSwitchState = reading;

}
