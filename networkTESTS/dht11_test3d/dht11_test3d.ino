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
#include <EthernetUdp.h>
#include <math.h>

dht DHT;

#define DHT11_PIN 2

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 250);

EthernetServer server(80);

unsigned int localPort = 8888;

const char timeServer[] = "time.nist.gov"; // time.nist.gov NTP server

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message

byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
EthernetUDP Udp;



double tempC = 0;
double tempF = 0;
double relH = 0;

long lastReadingTime = 0;

unsigned long theYear = 0L;
unsigned long dayOfTheYear = 0L;
unsigned long theMonth = 0L;
unsigned long theDay = 0L;
unsigned long theHour = 0L;
unsigned long theMinute = 0L;
unsigned long theSecond = 0L;

unsigned long adjUTC = 8L;

char dateStrUTC[27];
char dateStr[27];


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

  Udp.begin(localPort);

  // start listening for clients
  server.begin();

  delay(1000);
}

void loop()
{
  sendNTPpacket(timeServer);
  delay(1000);
  if (Udp.parsePacket()) {
    // We've received a packet, read the data from it
    Udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

    // the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, extract the two words:

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;

    const unsigned long seventyYears = 2208988800UL;
    // subtract seventy years:
    unsigned long epoch = secsSince1900 - seventyYears;

    compDate(secsSince1900);

    //    theYear = compYear(secsSince1900);
    //    dayOfTheYear = compDayOfTheYear(theYear, secsSince1900

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

      // timestamp the last time you got a reading:
      lastReadingTime = millis();
    }


    listenForEthernetClients();

    //  delay(2000);
  }
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
          client.println("This is the first test remote sensor and it is connected via ETHERNET");
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
          client.println(" ");
          client.println("<br />");
          client.println(" ");
          client.println("<br />");
          makeDateStringUTC();
          makeDateString8utc();
          client.println("The Date is: ");
          client.println(dateStrUTC);
          client.println(" UTC time");
          client.println("<br />");
          client.println(" \t \t ");
          client.println(dateStr);
          client.println(" Pacific Coast time");
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
    delay(1);
    // close the connection:
    client.stop();
  }
}


// send an NTP request to the time server at the given address
void sendNTPpacket(const char * address) {
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); // NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}

unsigned long compYear(unsigned long secsSince1900) {
  unsigned long tmpSecs = secsSince1900;
  unsigned long daySecs = 24L * 60L * 60L;

  boolean keepGoing = true;
  unsigned long tmpYear = 1900;
  while (keepGoing) {
    unsigned int numDays = 365;

    if (tmpYear % 4 == 0) {
      unsigned int leapYearTest1 = tmpYear % 100;
      unsigned int leapYearTest2 = tmpYear % 400;

      if (leapYearTest1 == 0 && leapYearTest2 == 0) {
        numDays = 366;
      }
    }

    tmpSecs = tmpSecs - numDays * daySecs;
    tmpYear++;

    if (tmpYear % 4 == 0) {
      unsigned int leapYearTest1 = tmpYear % 100;
      unsigned int leapYearTest2 = tmpYear % 400;

      if (leapYearTest1 == 0 && leapYearTest2 == 0) {
        numDays = 366;
      } else {
        numDays = 365;
      }
    } else {
      numDays = 365;
    }

    long testSecs = tmpSecs - numDays * daySecs;
    if (testSecs <= 0) {
      keepGoing = false;
    }
  }

  return tmpYear;
}


void compDate(unsigned int secsSince1900) {
  unsigned long tmpSecs = secsSince1900;
  unsigned long daySecs = 24L * 60L * 60L;

  boolean keepGoing = true;
  unsigned long tmpYear = 1900;
  long testSecs = 0;
  while (keepGoing) {
    unsigned int numDays = 365;

    if (checkLeapYear(tmpYear)) numDays = 366;

    tmpSecs = tmpSecs - numDays * daySecs;
    tmpYear++;

    numDays = 365;
    if (checkLeapYear(tmpYear)) numDays = 366;

    testSecs = tmpSecs - numDays * daySecs;
    if (testSecs <= 0) {
      keepGoing = false;
    }
  } // END while loop

  theYear = tmpYear;

  double tmpDayOfYear = (double)tmpSecs / (double)daySecs;
  dayOfTheYear = floor(tmpDayOfYear) + 1L;

  theMonth = compMonth(theYear, dayOfTheYear);

  theDay = compDay(theYear, theMonth, dayOfTheYear);

  double tmpHour = ((double)(secsSince1900 % daySecs)) / 3600.0;
  theHour = floor(tmpHour);

  double tmpMinute = ((double)(secsSince1900 % 3600)) / 60.0;
  theMinute = floor(tmpMinute);

  theSecond = secsSince1900 % 60;
}


boolean checkLeapYear(unsigned long yearIn) {
  boolean theAnswer = false;

  if (yearIn % 4 == 0) {
    unsigned int leapYearTest1 = yearIn % 100;
    unsigned int leapYearTest2 = yearIn % 400;

    if (leapYearTest1 == 0 && leapYearTest2 == 0) {
      theAnswer = true;
    }
  }

  return theAnswer;
}

unsigned long compMonth(unsigned long yearIn, unsigned long dayOfTheYearIn) {
  unsigned long tmpMonth = 0;
  if (checkLeapYear(yearIn)) {
    tmpMonth = compYleapYrMonth(dayOfTheYearIn);
  } else {
    tmpMonth = compNleapYrMonth(dayOfTheYearIn);
  }

  return tmpMonth;
}

unsigned long compYleapYrMonth(unsigned long dayOfTheYearIn) {
  unsigned long tmpMonth = 0;

  switch (dayOfTheYearIn) {
    case 1 ... 31:
      tmpMonth = 1;
    case 32 ... 60:
      tmpMonth = 2;
    case 61 ... 91:
      tmpMonth = 3;
    case 92 ... 121:
      tmpMonth = 4;
    case 122 ... 152:
      tmpMonth = 5;
    case 153 ... 182:
      tmpMonth = 6;
    case 183 ... 213:
      tmpMonth = 7;
    case 214 ... 244:
      tmpMonth = 8;
    case 245 ... 274:
      tmpMonth = 9;
    case 275 ... 305:
      tmpMonth = 10;
    case 306 ... 335:
      tmpMonth = 11;
    case 336 ... 366:
      tmpMonth = 12;
  }

  return tmpMonth;
}

unsigned long compNleapYrMonth(unsigned long dayOfTheYearIn) {
  unsigned long tmpMonth = 0;

  switch (dayOfTheYearIn) {
    case 1 ... 31:
      tmpMonth = 1;
    case 32 ... 59:
      tmpMonth = 2;
    case 60 ... 90:
      tmpMonth = 3;
    case 91 ... 120:
      tmpMonth = 4;
    case 121 ... 151:
      tmpMonth = 5;
    case 152 ... 181:
      tmpMonth = 6;
    case 182 ... 212:
      tmpMonth = 7;
    case 213 ... 243:
      tmpMonth = 8;
    case 244 ... 273:
      tmpMonth = 9;
    case 274 ... 304:
      tmpMonth = 10;
    case 305 ... 334:
      tmpMonth = 11;
    case 335 ... 365:
      tmpMonth = 12;
  }

  return tmpMonth;
}

unsigned long compDay(unsigned long yearIn, unsigned long monthIn, unsigned long dayOfTheYearIn) {
  unsigned long tmpDay = 0;

  unsigned long aTMP = 0;
  if (checkLeapYear(yearIn)) {
    aTMP = compMonthDaysYleapYear(monthIn);
  } else {
    aTMP = compMonthDaysNleapYear(monthIn);
  }

  tmpDay = dayOfTheYearIn - aTMP;

  return tmpDay;
}

unsigned long compMonthDaysYleapYear(unsigned long monthIn) {
  unsigned long tmpDaysToMonth = 0;

  switch (monthIn) {
    case 1:
      tmpDaysToMonth = 0;
    case 2:
      tmpDaysToMonth = 31;
    case 3:
      tmpDaysToMonth = 60;
    case 4:
      tmpDaysToMonth = 91;
    case 5:
      tmpDaysToMonth = 121;
    case 6:
      tmpDaysToMonth = 152;
    case 7:
      tmpDaysToMonth = 182;
    case 8:
      tmpDaysToMonth = 213;
    case 9:
      tmpDaysToMonth = 244;
    case 10:
      tmpDaysToMonth = 274;
    case 11:
      tmpDaysToMonth = 305;
    case 12:
      tmpDaysToMonth = 335;
  }

  return tmpDaysToMonth;
}

unsigned long compMonthDaysNleapYear(unsigned long monthIn) {
  unsigned long tmpDaysToMonth = 0;

  switch (monthIn) {
    case 1:
      tmpDaysToMonth = 0;
    case 2:
      tmpDaysToMonth = 31;
    case 3:
      tmpDaysToMonth = 59;
    case 4:
      tmpDaysToMonth = 90;
    case 5:
      tmpDaysToMonth = 120;
    case 6:
      tmpDaysToMonth = 151;
    case 7:
      tmpDaysToMonth = 181;
    case 8:
      tmpDaysToMonth = 212;
    case 9:
      tmpDaysToMonth = 243;
    case 10:
      tmpDaysToMonth = 273;
    case 11:
      tmpDaysToMonth = 304;
    case 12:
      tmpDaysToMonth = 334;
  }

  return tmpDaysToMonth;
}

void makeDateStringUTC() {
  memset(dateStrUTC, '\0', sizeof(dateStrUTC));

  char monthName[9];
  memset(monthName, '\0', sizeof(monthName));
  switch (theMonth) {
    case 1:
      snprintf(monthName, sizeof(monthName), "%s", "January");
    case 2:
      snprintf(monthName, sizeof(monthName), "%s", "February");
    case 3:
      snprintf(monthName, sizeof(monthName), "%s", "March");
    case 4:
      snprintf(monthName, sizeof(monthName), "%s", "April");
    case 5:
      snprintf(monthName, sizeof(monthName), "%s", "May");
    case 6:
      snprintf(monthName, sizeof(monthName), "%s", "June");
    case 7:
      snprintf(monthName, sizeof(monthName), "%s", "July");
    case 8:
      snprintf(monthName, sizeof(monthName), "%s", "August");
    case 9:
      snprintf(monthName, sizeof(monthName), "%s", "September");
    case 10:
      snprintf(monthName, sizeof(monthName), "%s", "October");
    case 11:
      snprintf(monthName, sizeof(monthName), "%s", "November");
    case 12:
      snprintf(monthName, sizeof(monthName), "%s", "December");
  }

  char hourStr[2];
  memset(hourStr, '\0', sizeof(hourStr));
  if(theHour < 10) {
    snprintf(hourStr, sizeof(hourStr), "0%d", theHour);
  } else {
    snprintf(hourStr, sizeof(hourStr), "%d", theHour);
  }
    
  char minuteStr[2];
  memset(minuteStr, '\0', sizeof(minuteStr));
  if(theMinute < 10) {
    snprintf(minuteStr, sizeof(minuteStr), "0%d", theMinute);
  } else {
    snprintf(minuteStr, sizeof(minuteStr), "%d", theMinute);
  }
  
  char secondStr[2];
  memset(secondStr, '\0', sizeof(secondStr));
  if(theSecond < 10) {
    snprintf(secondStr, sizeof(secondStr), "0%d", theSecond);
  } else {
    snprintf(secondStr, sizeof(secondStr), "%d", theSecond);
  }

  
  snprintf(dateStrUTC, sizeof(dateStrUTC), "%s %d, %d %s:%s:%s", monthName, theDay, theYear, hourStr, minuteStr, secondStr);
}

void makeDateString8utc() {
  memset(dateStr, '\0', sizeof(dateStr));

  char monthName[9];
  memset(monthName, '\0', sizeof(monthName));
  switch (theMonth) {
    case 1:
      snprintf(monthName, sizeof(monthName), "%s", "January");
    case 2:
      snprintf(monthName, sizeof(monthName), "%s", "February");
    case 3:
      snprintf(monthName, sizeof(monthName), "%s", "March");
    case 4:
      snprintf(monthName, sizeof(monthName), "%s", "April");
    case 5:
      snprintf(monthName, sizeof(monthName), "%s", "May");
    case 6:
      snprintf(monthName, sizeof(monthName), "%s", "June");
    case 7:
      snprintf(monthName, sizeof(monthName), "%s", "July");
    case 8:
      snprintf(monthName, sizeof(monthName), "%s", "August");
    case 9:
      snprintf(monthName, sizeof(monthName), "%s", "September");
    case 10:
      snprintf(monthName, sizeof(monthName), "%s", "October");
    case 11:
      snprintf(monthName, sizeof(monthName), "%s", "November");
    case 12:
      snprintf(monthName, sizeof(monthName), "%s", "December");
  }

  unsigned long tmpHour = theHour - 8L;
  if(tmpHour < 0) tmpHour = tmpHour + 24L;
  
  char hourStr[2];
  memset(hourStr, '\0', sizeof(hourStr));
  if(tmpHour < 10) {
    snprintf(hourStr, sizeof(hourStr), "0%d", tmpHour);
  } else {
    snprintf(hourStr, sizeof(hourStr), "%d", tmpHour);
  }
    
  char minuteStr[2];
  memset(minuteStr, '\0', sizeof(minuteStr));
  if(theMinute < 10) {
    snprintf(minuteStr, sizeof(minuteStr), "0%d", theMinute);
  } else {
    snprintf(minuteStr, sizeof(minuteStr), "%d", theMinute);
  }
  
  char secondStr[2];
  memset(secondStr, '\0', sizeof(secondStr));
  if(theSecond < 10) {
    snprintf(secondStr, sizeof(secondStr), "0%d", theSecond);
  } else {
    snprintf(secondStr, sizeof(secondStr), "%d", theSecond);
  }

  
  snprintf(dateStr, sizeof(dateStr), "%s %d, %d %s:%s:%s", monthName, theDay, theYear, hourStr, minuteStr, secondStr);
}
