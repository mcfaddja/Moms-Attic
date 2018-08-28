#include <dht.h>
#include <Ethernet.h>
#include <string.h>

dht DHT;

#define DHT11_PIN 2

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE
};
IPAddress ip(192, 168, 1, 252);

const char theSensorName[] = "testEthernet2";

const uint16_t port = 5000;
const char * host = "192.168.1.238";


void setup() {
  Serial.begin(115200);
  Serial.println("DHT TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT_LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");

  Ethernet.init(10);
  Ethernet.begin(mac, ip);

  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  delay(1000);
}

void loop() {
  // READ DATA
  Serial.print("DHT11, \t");
  int chk = DHT.read11(DHT11_PIN);
  switch (chk)
  {
    case DHTLIB_OK:
      Serial.println("OK,\t");
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

  double myRelH = DHT.humidity;
  double myTempC = DHT.temperature;
  double myTempF = ((DHT.temperature*(9.0/5.0))+32);

  Serial.println(myRelH);
  Serial.println(myTempC);
  Serial.println(myTempF);


  EthernetClient client;

  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    Serial.println("wait 5 sec...");
    delay(2500);
    return;
  }

  Serial.print("connected to ");
  Serial.println(client.remoteIP());

  client.println(theSensorName);
  client.println(myRelH);
  client.println(myTempC);
  client.println(myTempF);
  Serial.println("data sent, closing connection...");

  client.stop();
  Serial.println("connection closed!!!");

  delay(2000);
}
