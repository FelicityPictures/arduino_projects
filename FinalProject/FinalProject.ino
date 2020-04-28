const int numberOfSensors = 3;
const int sensors[] = {A7, A6, A5};
int sensorValues[] = {0, 0, 0};
// true means there should be pressure on it
int desiredSensorState[numberOfSensors] = {true, false, true};
int maximumValue = 1023;
const int buzzerPin = 2;
int buzzerStatus = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < numberOfSensors; i++){
    sensorValues[i] = analogRead(sensors[i]);
    if(sensorValues[i] <= maximumValue/4){
      sensorValues[i] = 0;
    }else if(sensorValues[i] <= maximumValue/2){
      sensorValues[i] = 1;
    }else if(sensorValues[i] <= (maximumValue*3)/4){
      sensorValues[i] = 2;
    }else if(sensorValues[i] <= maximumValue){
      sensorValues[i] = 3;
    }
    Serial.print(sensorValues[i]);
    if(i < numberOfSensors-1){
      Serial.print(",");
    }
  }
  Serial.println(" ");

  // check if sensors are receiving desired information
  // if not, buzzer sounds
  for(int i = 0; i < numberOfSensors; i++){
    if((desiredSensorState[i] && sensorValues[i] > 1) ||
       (!desiredSensorState[i] && sensorValues[i] <= 1)){
      buzzerStatus = LOW;
    }else{
      buzzerStatus = HIGH;
      break;
    }
  }
  digitalWrite(buzzerPin, buzzerStatus);
}
