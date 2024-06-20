# Remote Temperature Monitor

Arduino app using NodeMCU ESP8266 with a DHT22 temperature and humidity sensor.
Sensor values are uploaded to [ThingSpeak](https://thingspeak.com/) for viewing.

## Development

Uses [PlatformIO](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide) for development.

### Build

To build this project you first need to create a file called `include/secrets.h`. In this file you need to add `#define` statements with your secrets.
The following secrets must be added. Make sure you add the quotes ("") too:

```
#define WIFI_NAME "<your wifi name>"
#define WIFI_PASSWORD "<your wifi password>"
#define THINGSPEAK_WRITE_API_KEY "<your write API key>"
#define YHINGSPEAK_SENSOR_CHANNEL_ID "<your channel id>"
```
