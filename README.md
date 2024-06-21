# Remote Temperature Monitor

Arduino app using NodeMCU ESP8266 with a DHT22 temperature and humidity sensor.
Sensor values are uploaded to [ThingSpeak](https://thingspeak.com/) for viewing.

## Development

Uses [PlatformIO](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide) for development.

### Build

To build this project you first need to create a file called `include/secrets.h`. In this file you need to add `const` values with your secrets.
This is the template for the `include/secrets.h` file:

```
const String wifi_ssid = "<YOUR WIFI SSID>";
const String wifi_password = "<YOUR WIFI PASSWORD>";

const char thingspeak_write_api_key[] = "<YOUR THINGSPEAK WRITE API KEY>";
const char thingspeak_read_api_key[] = "<YOUR THINGSPEAK READ API KEY>";
const unsigned long thingspeak_channel_id = YOUR_THINGSPEAK CHANNEL ID;
```
