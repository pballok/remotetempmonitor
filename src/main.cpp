#include "Arduino.h"
#include "ESP8266WiFi.h"

#include "DHT.h"
#include "ThingSpeak.h"

// You need to create this header file for yourself, see README
#include "secrets.h"

const uint8_t       dht_pin = 5;
const uint8_t       dht_type = DHT22;
const unsigned long dht_read_interval_ms = 20000;
const unsigned int  temperature_field_id = 1;
const unsigned int  humidity_field_id = 2;

unsigned int        previous_dht_update_time_ms = 0;
WiFiClient          wifi_client;
DHT                 dht(dht_pin, dht_type);

void connect_to_wifi();
float read_temperature_in_celsius();
float read_relative_humidity();
void write_to_thingspeak(float temperature_c, float humidity);

void setup()
{
  Serial.begin(115200);
  dht.begin();

  delay(5000);  // give time to Serial Monitor to launch

  connect_to_wifi();
  ThingSpeak.begin(wifi_client);
}

void loop()
{
  unsigned long current_time_ms = millis();
  if (previous_dht_update_time_ms == 0 || current_time_ms - previous_dht_update_time_ms >= dht_read_interval_ms) {
    previous_dht_update_time_ms = current_time_ms;

    float temperature_c = read_temperature_in_celsius();
    float humidity = read_relative_humidity();

    write_to_thingspeak(temperature_c, humidity);
  }
}

void connect_to_wifi() {
  WiFi.begin(wifi_ssid, wifi_password);
  Serial.print("Connecting to wifi \"");
  Serial.print(wifi_ssid);
  Serial.print("\" ");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }

  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
}

float read_temperature_in_celsius() {
  float temp = dht.readTemperature();
  if (isnan(temp)) {
    Serial.println("Failed to read temperature from DHT sensor!");
  }

  return temp;
}

float read_relative_humidity() {
  float hum = dht.readHumidity();
  if (isnan(hum)) {
    Serial.println("Failed to read humidity from DHT sensor!");
  }

  return hum;
}

void write_to_thingspeak(float temperature_c, float humidity) {
  ThingSpeak.setField(temperature_field_id, temperature_c);
  ThingSpeak.setField(humidity_field_id, humidity);
  int write_success = ThingSpeak.writeFields(thingspeak_channel_id, thingspeak_write_api_key);
  if (!write_success) {
    Serial.println("Failed to write sensor values to ThingSpeak!");
    return;
  }
}
