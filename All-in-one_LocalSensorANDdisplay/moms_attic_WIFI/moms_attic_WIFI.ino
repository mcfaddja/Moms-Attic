#include <Wire.h>
#include "OLED.h"
#include <dht.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

dht DHT;
#define DHT11_PIN 0

//WIFI_Kit_8's OLED connection:
//SDA -- GPIO4 -- D2
//SCL -- GPIO5 -- D1
//RST -- GPIO16 -- D0

#define RST_OLED 16
OLED display(4, 5);


//const char* ssid = "McFaddenAC";
//const char* password = "1MckiD4_mckid4@MSN.com";
const char* ssid = "McFaddenN";
const char* password = "$h()()tING4P()()p$";

ESP8266WebServer server(80);

const int led = 13;





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
  delay(3 * 1000);


  Serial.println("DHT TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT_LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");

  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  char hBuff[16];
  char tBuff[16];

  memset(hBuff, '\0', sizeof(hBuff));
  memset(tBuff, '\0', sizeof(tBuff));

  double myRelH = DHT.humidity;
  double myTemp = ((DHT.temperature * (9.0 / 5.0)) + 32);

  snprintf(hBuff, sizeof(hBuff), "Humidity: %4.2f", myRelH);
  snprintf(tBuff, sizeof(tBuff), "Temp (F): %4.2f", myTemp);

  char netBuff[33];
  memset(netBuff, '\0', sizeof(netBuff));
  snprintf(netBuff, sizeof(netBuff), "%s\n%s", hBuff, tBuff);

//  server.on("/temp", [netBuff]() {
//    server.send(200, "text/plain", netBuff);
//  });

  server.begin();
  Serial.println("HTTP server started");
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
  double myTemp = ((DHT.temperature * (9.0 / 5.0)) + 32);

  snprintf(hBuff, sizeof(hBuff), "Humidity: %4.2f", myRelH);
  snprintf(tBuff, sizeof(tBuff), "Temp (F): %4.2f", myTemp);
  Serial.println(hBuff);
  Serial.println(tBuff);

  //  display.clear();
  display.print(hBuff);
  display.print(tBuff, 2);

  server.handleClient();

  char netBuff[33];
  memset(netBuff, '\0', sizeof(netBuff));
  snprintf(netBuff, sizeof(netBuff), "%s\n%s", hBuff, tBuff);

  server.on("/temp", [netBuff]() {
    server.send(200, "text/plain", netBuff);
  });

  server.begin();

  delay(5000);
}



void handleRoot() {
  //  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp8266!");
  //  digitalWrite(led, 0);
}

void handleRoot2(char textIN[]) {
  //  digitalWrite(led, 1);
  server.send(200, "text/plain", textIN);
  //  digitalWrite(led, 0);
}

void handleNotFound() {
  //  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  //  digitalWrite(led, 0);
}
