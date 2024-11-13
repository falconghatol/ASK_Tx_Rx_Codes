#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h> // Not actually used but needed to compile
#endif

RH_ASK driver(2000, 4, 14, 0);

void setup()
{
#ifdef RH_HAVE_SERIAL
    Serial.begin(115200);	  // Debugging only
#endif
    if (!driver.init())
#ifdef RH_HAVE_SERIAL
         Serial.println("init failed");
#else
	;
#endif

}

void loop()
{
    const char *msg1 = "KCG               ";
    driver.send((uint8_t *)msg1, strlen(msg1));
    driver.waitPacketSent();
    delay(200);

    const char *msg2 = "21BEC0750         ";
    driver.send((uint8_t *)msg2, strlen(msg2));
    driver.waitPacketSent();
    delay(200);

    const char *msg3 = "Text transmission";
    driver.send((uint8_t *)msg3, strlen(msg3));
    driver.waitPacketSent();
    delay(200);

    const char *msg4 = "Test              ";
    driver.send((uint8_t *)msg4, strlen(msg4));
    driver.waitPacketSent();
    delay(200);
    
}
