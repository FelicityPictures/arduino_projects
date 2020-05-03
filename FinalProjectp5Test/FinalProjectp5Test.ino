const int LED[] = {2, 3, 4};
int LEDStatus[] = {true, false, true};
String inputString = "";
bool stringComplete = false;

void setup() {
  Serial.begin(9600);
  for(int i = 0; i < 3; i++){
    pinMode(LED[i], OUTPUT);
  }
  establishContact(); // make sure we're communicating
  delay(16);  // small delay
}

void loop() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    // if the incoming character is a newline, 
    // set a flag so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
      inputString.trim(); // trim off any whitespace
    }
  }

  if (stringComplete) { 
//    Serial.println(inputString);
    // parse the data and save it into an array
    int maxIndex = inputString.length() - 1; // get the number of elements
    int index = 0;
    int next_index;
    String value;
    int counter = 0;
    do {
      // this chunk of code parses a string with comma-separated values
      // and adds the values to an array
      next_index = inputString.indexOf(',', index); // find the next comma
      value = inputString.substring(index, next_index); //get the next number
      value.trim(); // trim any whitespace
      Serial.print(value);
      Serial.print(",");
      if(value == "0" && counter < 3){
        LEDStatus[counter] = false;
      }else{
        LEDStatus[counter] = true;
      }
      
      index = next_index + 1; // this shifts to find the next value
      counter++; // increment the array
    } while ((next_index != -1) && (next_index < maxIndex)); // do the above while we have a string

    inputString = ""; // clear the string for more information
    stringComplete = false; // get ready for another new set of information
    Serial.println("");
    Serial.print('A'); // ask for more

//------------------------------------------------------------------------------------
    for(int i = 0; i < 3; i++){
      if(LEDStatus[i]){
        digitalWrite(LED[i], HIGH);
      }else{
        digitalWrite(LED[i], LOW);
      }
  //    Serial.print(LEDStatus[i]);
  //    if(i < 2){
  //      Serial.print(",");
  //    }
    }
  //  Serial.println(" ");
  }
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println('A');   // send an initial string
    delay(300);
  }
}
