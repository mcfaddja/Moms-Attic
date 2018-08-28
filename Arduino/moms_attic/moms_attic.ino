#include <Wire.h>
#include "OLED.h"
#include <dht.h>

dht DHT;
#define DHT11_PIN 0

//WIFI_Kit_8's OLED connection:
//SDA -- GPIO4 -- D2
//SCL -- GPIO5 -- D1
//RST -- GPIO16 -- D0

#define RST_OLED 16
OLED display(4, 5);

// If you bought WIFI Kit 8 before 2017-8-20, you may try this initial
//#define RST_OLED D2
//OLED display(SDA, SCL);

void setup() {
  pinMode(RST_OLED, OUTPUT);
  digitalWrite(RST_OLED, LOW);   // turn D2 low to reset OLED
  delay(50);
  digitalWrite(RST_OLED, HIGH);    // while OLED is running, must set D2 in high
  
  Serial.begin(115200);
  Serial.println("OLED test!");

  // Initialize display
  display.begin();

  // Test message
  display.print("Hello World");
  delay(3*1000);


  Serial.println("DHT TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT_LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");
}

int r = 0, c = 0;

void loop() {

  int chk = DHT.read11(DHT11_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
    Serial.print("OK,\t"); 
    break;
    case DHTLIB_ERROR_CHECKSUM: 
    Serial.print("Checksum error,\t"); 
    break;
    case DHTLIB_ERROR_TIMEOUT: 
    Serial.print("Time out error,\t"); 
    break;
    default: 
    Serial.print("Unknown error,\t"); 
    break;
  }
  // DISPLAY DATA

  char hBuff[16];
  char tBuff[16];

  memset(hBuff, '\0', sizeof(hBuff));
  memset(tBuff, '\0', sizeof(tBuff));

  Serial.println(DHT.humidity);
  Serial.println(DHT.temperature);

  double myRelH = DHT.humidity;
  double myTemp = ((DHT.temperature*(9.0/5.0))+32);

  snprintf(hBuff, sizeof(hBuff), "Humidity: %4.2f", myRelH);
  snprintf(tBuff, sizeof(tBuff), "Temp (F): %4.2f", myTemp);
  Serial.println(hBuff);
  Serial.println(tBuff);

//  display.clear();
  display.print(hBuff);
  display.print(tBuff, 1);

  delay(2000);
  
//    r = r % 4;
//    c = micros() % 6;
//    if (r == 0) display.clear();
//    display.print("Hello World", r++, c++);
//    delay(500);
}
