#include <DHT.h>

#define DHTTYPE DHT11
#define DHTPIN 9

DHT dht (DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay (2000);
  float temperature = dht.readTemperature();

  if (isnan(temperature)){
    Serial.println("ERROR EN EL SENSOR");
  }

  Serial.print ("Temperatura:");
  Serial.print (temperature);
  Serial.println ("°C");
}
