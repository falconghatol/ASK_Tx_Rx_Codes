#include <RH_ASK.h>
#include <Adafruit_AHT10.h>

#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h> // Not actually used but needed to compile
#endif

RH_ASK driver(2000, 4, 14, 0);
Adafruit_AHT10 aht;

void setup() {
#ifdef RH_HAVE_SERIAL
    Serial.begin(115200);    // Debugging only
#endif
    if (!driver.init())
#ifdef RH_HAVE_SERIAL
         Serial.println("init failed");
#else
  ;
#endif

    if (! aht.begin()) {
    Serial.println("Could not find AHT10? Check wiring");
    while (1) delay(10);
    }
    Serial.println("AHT10 found");
}

void loop() {
    sensors_event_t humidity, temp;
    aht.getEvent(&humidity, &temp);

    char dataString[32];
    //sprintf(dataString, "Temperature: %.1f degrees C, Humidity: %.1f% RH", temp.temperature, humidity.relative_humidity);
    sprintf(dataString, "%.2f,%.2f", temp.temperature, humidity.relative_humidity);

    driver.send((uint8_t *)dataString, strlen(dataString));
    driver.waitPacketSent();
    delay(250); // Adjust delay as needed
}
