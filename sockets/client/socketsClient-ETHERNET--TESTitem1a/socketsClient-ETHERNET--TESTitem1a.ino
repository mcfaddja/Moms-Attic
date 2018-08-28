#include <dht.h>
#include <Ethernet.h>
#include <string.h>

dht DHT;

#define DHT11_PIN 2

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 251);

EthernetServer server(80);

const char theSensorName[] = "testEthernet1";

const uint16_t port = 5000;
const char * host = "192.168.1.238";


double tempC = 0;
double tempF = 0;
double relH = 0;

long lastReadingTime = 0;


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

  server.begin();

  delay(1000);
}

void loop() {
  // check for a reading no more than once a second.
  if (millis() - lastReadingTime > 5001) {
    Serial.println(ip);
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

    double myRelH = DHT.humidity;
    double myTempC = DHT.temperature;
    double myTempF = ((DHT.temperature * (9.0 / 5.0)) + 32);

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

    tempC = DHT.temperature;
    tempF = tempC * 9.0 / 5.0 + 32.0;
    relH = DHT.humidity;

    // timestamp the last time you got a reading:
    lastReadingTime = millis();
  }

  listenForEthernetClients();
  //  delay(2000);
}


void listenForEthernetClients() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("Got a client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          // print the current readings, in HTML format:
          client.println("This is the remote sensor ");
          client.println(theSensorName);
          client.println("<br />");
          client.println(" ");
          client.println("<br />");
          client.println("\t The IP Address of this sensor device is: ");
          client.println("<br />");
          //          client.println("192.168.1.250");
          client.println(String(host));
          client.println("<br />");
          client.println(" ");
          client.println("<br />");
          client.println("\t The MAC Address of this sensor device is: ");
          client.println("<br />");
          //          client.println("ne  DE:AD:BE:EF:FE:EE");
          char macBuff[4];
          memset(macBuff, '\0', sizeof(macBuff));
          for (int i = 0; i < 5; i++) {
            snprintf(macBuff, sizeof(macBuff), "%x", mac[i]);
//            client.println(mac[i]);
            client.println(macBuff);
            client.println(":");
          }
          snprintf(macBuff, sizeof(macBuff), "%x", mac[5]);
          client.println(macBuff);
          //          client.println(mac[6]);
          client.println("<br />");
          client.println(" ");
          client.println("<br />");
          client.println(" ");
          client.println("<br />");
          client.print("Temperature (F): ");
          client.print(tempF);
          client.print(" degrees F");
          client.println("<br />");
          client.print("Temperature (C): ");
          client.print(tempC);
          client.print(" degrees C");
          client.println("<br />");
          client.print("Relative Humidity: " + String(relH));
          client.print(" percent");
          client.println("<br />");
          client.println(" ");
          client.println("<br />");
          client.println(" ");
          client.println("<br />");
          client.println("Time until next measurement: ");
          client.println((5000 - (millis() - lastReadingTime)));
          client.println(" milliseconds");
          client.println("<br />");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(5);
    // close the connection:
    client.stop();
  }
}
