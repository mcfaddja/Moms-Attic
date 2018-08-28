#include <dht.h>
#include <Ethernet.h>

dht DHT;

#define DHT11_PIN 2

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 250);

EthernetServer server(80);


const char sensorName = "testEthernet1";


double tempC = 0;
double tempF = 0;
double relH = 0;

long lastReadingTime = 0;


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

  // start listening for clients
  server.begin();

  delay(1000);
}

void loop() {
  // check for a reading no more than once a second.
  if (millis() - lastReadingTime > 5001) {
    // if there's a reading ready, read it:
    // don't do anything until the data ready pin is high:
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

    tempC = DHT.temperature;
    tempF = tempC * 9.0 / 5.0 + 32.0;
    relH = DHT.humidity;


  }

  doNetworkStuff();

  delay(99);
}


void doNetworkStuff() {
  int theBuffSize = 640;
  int theMiniBuffSize = 64;
  char buff[theBuffSize];
  char miniBuff[theMiniBuffSize];

  memset(buff, '\0', sizeof(buff));
  memset(miniBuff, '\0', sizeof(miniBuff));

  snprintf(miniBuff, sizeof(miniBuff), "%s\r\n", sensorName);
  strcat(buff, miniBuff);
  
  snprintf(miniBuff, sizeof(miniBuff), "%f\r\n", relH);
  strcat(buff, miniBuff);

  snprintf(miniBuff, sizeof(miniBuff), "%f\r\n", tempC);
  strcat(buff, miniBuff);

  snprintf(miniBuff, sizeof(miniBuff), "%f\r\n", tempF);
  strcat(buff, miniBuff);

  EthernetClient client;

  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    Serial.println("wait 5 sec...");
    delay(2500);
    return;
  }
  
  Serial.print("connected to");
  Serial.println(client.remoteIP());

  client.println(buff);
  Serial.println("data sent, closing connection...");

  client.stop();
  Serial.println("connection closed!!!");
}

