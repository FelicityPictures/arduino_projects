#include "DHT.h"

#define DHTPIN A7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int red = 2;
const int green = 3;
const int blue = 5;

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHT11 test!"));

  dht.begin();
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop() {
  float humidity = dht.readHumidity();
  float temperatureinF = dht.readTemperature(true);

  if (isnan(humidity) || isnan(temperatureinF)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

//  float hif = dht.computeHeatIndex(temperatureinF, humidity);
//  float hic = dht.computeHeatIndex(temperatureInC, humidity, false);

  int flashing = map(temperatureinF, 75, 110, 100, 1000);
  flashing = 1000 - flashing; // the faster the flash, the higher the temperature

  int redIntensity = map(humidity, 0, 100, 0, 255);
  analogWrite(red, redIntensity);
  analogWrite(green, 255-redIntensity);
  analogWrite(blue, 255-redIntensity);
  delay(flashing);
  analogWrite(red, 0);
  analogWrite(green, 0);
  analogWrite(blue, 0);
  delay(flashing);

  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(temperatureinF);
  Serial.println(F("°F"));

}
