const int numberOfSensors = 3;
const int sensors[] = {A7, A6, A5};
int sensorValues[] = {0, 0, 0};
const int buzzerPin = 2;
int buzzerStatus = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  
  establishContact(); // make sure we're communicating
  delay(16);  // small delay
}

void loop() {
  if (Serial.available() > 0) {
    buzzerStatus = Serial.read();
    digitalWrite(buzzerPin, buzzerStatus);
    
//   ---------------------------------------------------

    for(int i = 0; i < numberOfSensors; i++){
      sensorValues[i] = analogRead(sensors[i]);
      Serial.print(sensorValues[i]);
      if(i < numberOfSensors-1){
        Serial.print(",");
      }
    }
    Serial.println(" ");
  }
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("0,0,0");   // send an initial string
    delay(300);
  }
}
