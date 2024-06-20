#include "Arduino.h"
#include "ESP8266WiFi.h"

#include "DHT.h"
#include "ThingSpeak.h"

// You need to create this header file for yourself, see README
#include "secrets.h"

const uint8_t       DHT_PIN = 5;
const uint8_t       DHT_TYPE = DHT22;
const unsigned long DHT_READ_INTERVAL_MS = 20000;
const unsigned int  FIELD_TEMPERATURE = 1;
const unsigned int  FIELD_HUMIDITY = 2;

unsigned int        previous_dht_update_time_ms = 0;
WiFiClient          wifi_client;
DHT                 dht(DHT_PIN, DHT_TYPE);

void connect_to_wifi();
void update_temperature();
void update_humidity();
void send_to_thingspeak();

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
  if (previous_dht_update_time_ms == 0 || current_time_ms - previous_dht_update_time_ms >= DHT_READ_INTERVAL_MS) {
    previous_dht_update_time_ms = current_time_ms;

    update_temperature();
    update_humidity();
    send_to_thingspeak();
  }
}

void connect_to_wifi() {
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  Serial.print("Connecting to wifi \"");
  Serial.print(WIFI_NAME);
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

void update_temperature() {
  float temperature_c = dht.readTemperature();
  if (isnan(temperature_c)) {
    Serial.println("Failed to read temperature from DHT sensor!");
    return;
  }

  ThingSpeak.setField(FIELD_TEMPERATURE, temperature_c);
}

void update_humidity() {
  float humidity = dht.readHumidity();
  if (isnan(humidity)) {
    Serial.println("Failed to read humidity from DHT sensor!");
    return;
  }

  ThingSpeak.setField(FIELD_HUMIDITY, humidity);
}

void send_to_thingspeak() {
  int write_success = ThingSpeak.writeFields(THINGSPEAK_SENSOR_CHANNEL_ID, THINGSPEAK_WRITE_API_KEY);
  if (!write_success) {
    Serial.println("Failed to send data to ThingSpeak!");
    return;
  }

  Serial.println("Data sent to ThingSpeak"); 
}
