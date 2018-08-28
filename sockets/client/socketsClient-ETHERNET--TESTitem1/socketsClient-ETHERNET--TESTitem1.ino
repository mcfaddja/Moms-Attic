#include <dht.h>
#include <Ethernet.h>
#include <string.h>

dht DHT;

#define DHT11_PIN 2

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 250);

//EthernetServer server(80);

//EthernetClient client;

const char theSensorName[] = "testEthernet1";


typedef struct temp_datapoint {
  char* sensorName;
  float relH;
  float tempC;
  float tempF;
};

//
//float tempC = 0.0f;
//float tempF = 0.0f;
//float relH = 0.0f;

//unsigned int theBuffSize = 640;
//unsigned int theMiniBuffSize = 128;
//char buff[320];
//char miniBuff1[64];
//char miniBuff2[64];
//char miniBuff3[64];
//char miniBuff4[64];

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
  //  server.begin();

  delay(1000);
}

void loop() {
  //  struct temp_datapoint theData;
  //  theData.sensorName = theSensorName;

  char buff[80];
  char miniBuff1[32];
  char miniBuff2[6];
  char miniBuff3[6];
  char miniBuff4[6];
  //  float tempC = 0.0;
  //  float tempF = 0.0;
  //  float relH = 0.0;
  //
  //  int theBuffSize = 640;
  //  int theMiniBuffSize = 128;
  //  char buff[theBuffSize];
  //  char miniBuff1[theMiniBuffSize];
  //  char miniBuff2[theMiniBuffSize];
  //  char miniBuff3[theMiniBuffSize];
  //  char miniBuff4[theMiniBuffSize];
  //
  memset(buff, '\0', sizeof(buff));
  memset(miniBuff1, '\0', sizeof(miniBuff1));
  memset(miniBuff2, '\0', sizeof(miniBuff2));
  memset(miniBuff3, '\0', sizeof(miniBuff3));
  memset(miniBuff4, '\0', sizeof(miniBuff4));

  // check for a reading no more than once a second.
  //  if (millis() - lastReadingTime > 5001) {
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

  //  theData.tempC = DHT.temperature;
  //  theData.tempF = (theData.tempC * 9.0f / 5.0f + 32.0f);
  //  theData.relH = DHT.humidity;
//  double tempC = DHT.temperature;
//  double tempF = (tempC * 9.0f / 5.0f + 32.0f);
//  double relH = DHT.humidity;

  //  unsigned int aTempC = round(theData.tempC);
  //  unsigned int aTempF = round(theData.tempF);
  //  unsigned int aRelH = round(theData.relH);
//  unsigned int aTempC = round(tempC);
//  unsigned int aTempF = round(tempF);
//  unsigned int aRelH = round(relH);

  //  Serial.println(theData.tempC);
  //  Serial.println(theData.tempF);
  //  Serial.println(theData.relH);
//  Serial.println(tempC);
//  Serial.println(tempF);
//  Serial.println(relH);

  double myRelH = DHT.humidity;
  double myTempC = DHT.temperature;
  double myTempF = ((DHT.temperature*(9.0/5.0))+32);

  Serial.println(myRelH);
  Serial.println(myTempC);
  Serial.println(myTempF);



    snprintf(miniBuff1, sizeof(miniBuff1), "%s\r\n", theSensorName);
  strcat(buff, miniBuff1);

//  snprintf(miniBuff2, sizeof(miniBuff2), "%u\r\n", aRelH);
  //  snprintf(miniBuff2, sizeof(miniBuff2), "%G\r\n", theData.relH);
  snprintf(miniBuff2, sizeof(miniBuff2), " %4.2f", myRelH);
  //  snprintf(miniBuff2, sizeof(miniBuff2), "%f\n", DHT.humidity);
  strcat(buff, miniBuff2);

//  snprintf(miniBuff3, sizeof(miniBuff3), "%u\r\n", aTempC);
  //  snprintf(miniBuff3, sizeof(miniBuff3), "%G\r\n", theData.tempC);
  snprintf(miniBuff3, sizeof(miniBuff3), " %4.2f", myTempC);
  //  snprintf(miniBuff3, sizeof(miniBuff3), "%f\n", DHT.temperature);
  strcat(buff, miniBuff3);

//  snprintf(miniBuff4, sizeof(miniBuff4), "%u\r\n", aTempF);
  //  snprintf(miniBuff4, sizeof(miniBuff4), "%G\r\n", theData.tempF);
  snprintf(miniBuff4, sizeof(miniBuff4), " %4.2f", myTempF);
  //  snprintf(miniBuff4, sizeof(miniBuff4), "%f\n", (DHT.temperature * 9.0 / 5.0 + 32));
  strcat(buff, miniBuff4);

  //  snprintf(buff, sizeof(buff), "%s\r\n%f\r\n%f\r\n%f\r\n", theSensorName, relH, tempC, tempF);

  Serial.println(miniBuff2);
  Serial.println(miniBuff3);
  Serial.println(miniBuff4);
  Serial.println(buff);

  EthernetClient client;

  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    Serial.println("wait 5 sec...");
    delay(2500);
    return;
  }

  Serial.print("connected to ");
  Serial.println(client.remoteIP());

  //  if (client.connect(host, port)) {
//  client.println(buff);
  client.println(theSensorName);
  client.println(myRelH);
  client.println(myTempC);
  client.println(myTempF);
  Serial.println("data sent, closing connection...");
  //  }

  client.stop();
  Serial.println("connection closed!!!");

  //    doNetworkStuff();
  //  }



  //  int len = client.available();

  //  if (len > 0) {
  //    client.write(buff, theBuffSize);
  //    Serial.println("data sent, closing connection...");
  //
  //    client.stop();
  //    Serial.println("connection closed!!!");
  //  }


  delay(2000);
}


//void doNetworkStuff() {
//  int theBuffSize = 640;
//  int theMiniBuffSize = 64;
//  char buff[theBuffSize];
//  char miniBuff[theMiniBuffSize];
//
//  memset(buff, '\0', sizeof(buff));
//  memset(miniBuff, '\0', sizeof(miniBuff));
//
//  snprintf(miniBuff, sizeof(miniBuff), "%s\r\n", sensorName);
//  strcat(buff, miniBuff);
//
//  snprintf(miniBuff, sizeof(miniBuff), "%f\r\n", relH);
//  strcat(buff, miniBuff);
//
//  snprintf(miniBuff, sizeof(miniBuff), "%f\r\n", tempC);
//  strcat(buff, miniBuff);
//
//  snprintf(miniBuff, sizeof(miniBuff), "%f\r\n", tempF);
//  strcat(buff, miniBuff);
//
//
//  EthernetClient client;
//
//  if (!client.connect(host, port)) {
//    Serial.println("connection failed");
//    Serial.println("wait 5 sec...");
//    delay(2500);
//    return;
//  }
//
//  Serial.print("connected to");
//  Serial.println(client.remoteIP());
//
//  //  int len = client.available();
//  //
//  //  if (len > 0) {
//  //    client.write(buff, theBuffSize);
//  //    Serial.println("data sent, closing connection...");
//  //
//  //    client.stop();
//  //    Serial.println("connection closed!!!");
//  //  }
//
//}

