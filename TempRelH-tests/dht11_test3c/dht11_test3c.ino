//
//    FILE: dht11_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.01
// PURPOSE: DHT library test sketch for DHT11 && Arduino
//     URL:
//
// Released to the public domain
//

#include <dht.h>
#include <Ethernet.h>

dht DHT;

#define DHT11_PIN 2

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 250);

EthernetServer server(80);


double tempC = 0;
double tempF = 0;
double relH = 0;

long lastReadingTime = 0;


void setup()
{
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

void loop()
{
  // check for a reading no more than once a second.
  if (millis() - lastReadingTime > 1000) {
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
          client.println("This is the first test remote sensor");
          client.println("<br />");
          client.println("\t This remote device is connected via ETHERNET");
          client.println("<br />");
          client.println("\t The IP Address of this sensor device is 192.168.1.250");
          client.println("<br />");
          client.println("\t The MAC Address of this sensor device is DE:AD:BE:EF:FE:ED");
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
    delay(1);
    // close the connection:
    client.stop();
  }
}
