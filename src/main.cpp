#include "Arduino.h"
#include "DHT.h"

#define DHTPIN 5
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

unsigned int previous_dht_update_time_ms = 0;
const unsigned int dht_read_interval_ms = 10000;
float current_temperature_c = 0.0;
float current_humidity = 0.0;

void setup()
{
  Serial.begin(115200);
  dht.begin();
}

void loop()
{
  unsigned long current_time_ms = millis();
  if (current_time_ms - previous_dht_update_time_ms >= dht_read_interval_ms) {
    previous_dht_update_time_ms = current_time_ms;

    float new_temperature_c = dht.readTemperature();
    if (isnan(new_temperature_c)) {
      Serial.println("Failed to read temperature from DHT sensor!");
    }
    else {
      current_temperature_c = new_temperature_c;
      Serial.print("Temperature: ");
      Serial.print(current_temperature_c);
      Serial.println(" C");
    }

    float new_humidity = dht.readHumidity();
    if (isnan(new_humidity)) {
      Serial.println("Failed to read humidity from DHT sensor!");
    }
    else {
      current_humidity = new_humidity;
      Serial.print("Humidity: ");
      Serial.print(current_humidity);
      Serial.println(" %");
    }
  }
}
