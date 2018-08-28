#include <dht.h>

dht DHT;

#define LED_1A  1
#define LED_1B  0
#define LED_1C  2
#define LED_1D  3
#define LED_1E  4
#define LED_1F  5
#define LED_1G  6

#define LED_2A  7
#define LED_2B  8
#define LED_2C  9
#define LED_2D  10
#define LED_2E  11
#define LED_2F  12
#define LED_2G  13

#define DEC_TOP 15
#define DEC_BOT 16

#define DHT11_PIN 14


void setup() {
  pinMode(LED_1A, OUTPUT);
  pinMode(LED_1B, OUTPUT);
  pinMode(LED_1C, OUTPUT);
  pinMode(LED_1D, OUTPUT);
  pinMode(LED_1E, OUTPUT);
  pinMode(LED_1F, OUTPUT);
  pinMode(LED_1G, OUTPUT);

  pinMode(LED_2A, OUTPUT);
  pinMode(LED_2B, OUTPUT);
  pinMode(LED_2C, OUTPUT);
  pinMode(LED_2D, OUTPUT);
  pinMode(LED_2E, OUTPUT);
  pinMode(LED_2F, OUTPUT);
  pinMode(LED_2G, OUTPUT);

  pinMode(DEC_TOP, OUTPUT);
  pinMode(DEC_BOT, OUTPUT);

  Serial.begin(115200);
  Serial.println("DHT TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT_LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C), \tTemperature (F)");
}


void zero(int disp) {
  if (disp == 0) {
    digitalWrite(LED_1A, LOW);
    digitalWrite(LED_1B, LOW);
    digitalWrite(LED_1C, LOW);
    digitalWrite(LED_1D, LOW);
    digitalWrite(LED_1E, LOW);
    digitalWrite(LED_1F, LOW);
    digitalWrite(LED_1G, HIGH);
  } else {
    if (disp == 1) {
      digitalWrite(LED_2A, LOW);
      digitalWrite(LED_2B, LOW);
      digitalWrite(LED_2C, LOW);
      digitalWrite(LED_2D, LOW);
      digitalWrite(LED_2E, LOW);
      digitalWrite(LED_2F, LOW);
      digitalWrite(LED_2G, HIGH);
    } else {
      digitalWrite(LED_1A, HIGH);
      digitalWrite(LED_1B, HIGH);
      digitalWrite(LED_1C, HIGH);
      digitalWrite(LED_1D, HIGH);
      digitalWrite(LED_1E, HIGH);
      digitalWrite(LED_1F, HIGH);
      digitalWrite(LED_1G, LOW);

      digitalWrite(LED_2A, HIGH);
      digitalWrite(LED_2B, HIGH);
      digitalWrite(LED_2C, HIGH);
      digitalWrite(LED_2D, HIGH);
      digitalWrite(LED_2E, HIGH);
      digitalWrite(LED_2F, HIGH);
      digitalWrite(LED_2G, LOW);
    }
  }
}

void one(int disp) {
  if (disp == 0) {
    digitalWrite(LED_1A, HIGH);
    digitalWrite(LED_1B, LOW);
    digitalWrite(LED_1C, LOW);
    digitalWrite(LED_1D, HIGH);
    digitalWrite(LED_1E, HIGH);
    digitalWrite(LED_1F, HIGH);
    digitalWrite(LED_1G, HIGH);
  } else {
    if (disp == 1) {
      digitalWrite(LED_2A, HIGH);
      digitalWrite(LED_2B, LOW);
      digitalWrite(LED_2C, LOW);
      digitalWrite(LED_2D, HIGH);
      digitalWrite(LED_2E, HIGH);
      digitalWrite(LED_2F, HIGH);
      digitalWrite(LED_2G, HIGH);
    } else {
      digitalWrite(LED_1A, HIGH);
      digitalWrite(LED_1B, HIGH);
      digitalWrite(LED_1C, HIGH);
      digitalWrite(LED_1D, HIGH);
      digitalWrite(LED_1E, HIGH);
      digitalWrite(LED_1F, HIGH);
      digitalWrite(LED_1G, LOW);

      digitalWrite(LED_2A, HIGH);
      digitalWrite(LED_2B, HIGH);
      digitalWrite(LED_2C, HIGH);
      digitalWrite(LED_2D, HIGH);
      digitalWrite(LED_2E, HIGH);
      digitalWrite(LED_2F, HIGH);
      digitalWrite(LED_2G, LOW);
    }
  }
}

void two(int disp) {
  if (disp == 0) {
    digitalWrite(LED_1A, LOW);
    digitalWrite(LED_1B, LOW);
    digitalWrite(LED_1C, HIGH);
    digitalWrite(LED_1D, LOW);
    digitalWrite(LED_1E, LOW);
    digitalWrite(LED_1F, HIGH);
    digitalWrite(LED_1G, LOW);
  } else {
    if (disp == 1) {
      digitalWrite(LED_2A, LOW);
      digitalWrite(LED_2B, LOW);
      digitalWrite(LED_2C, HIGH);
      digitalWrite(LED_2D, LOW);
      digitalWrite(LED_2E, LOW);
      digitalWrite(LED_2F, HIGH);
      digitalWrite(LED_2G, LOW);
    } else {
      digitalWrite(LED_1A, HIGH);
      digitalWrite(LED_1B, HIGH);
      digitalWrite(LED_1C, HIGH);
      digitalWrite(LED_1D, HIGH);
      digitalWrite(LED_1E, HIGH);
      digitalWrite(LED_1F, HIGH);
      digitalWrite(LED_1G, LOW);

      digitalWrite(LED_2A, HIGH);
      digitalWrite(LED_2B, HIGH);
      digitalWrite(LED_2C, HIGH);
      digitalWrite(LED_2D, HIGH);
      digitalWrite(LED_2E, HIGH);
      digitalWrite(LED_2F, HIGH);
      digitalWrite(LED_2G, LOW);
    }
  }
}

void three(int disp) {
  if (disp == 0) {
    digitalWrite(LED_1A, LOW);
    digitalWrite(LED_1B, LOW);
    digitalWrite(LED_1C, LOW);
    digitalWrite(LED_1D, LOW);
    digitalWrite(LED_1E, HIGH);
    digitalWrite(LED_1F, HIGH);
    digitalWrite(LED_1G, LOW);
  } else {
    if (disp == 1) {
      digitalWrite(LED_2A, LOW);
      digitalWrite(LED_2B, LOW);
      digitalWrite(LED_2C, LOW);
      digitalWrite(LED_2D, LOW);
      digitalWrite(LED_2E, HIGH);
      digitalWrite(LED_2F, HIGH);
      digitalWrite(LED_2G, LOW);
    } else {
      digitalWrite(LED_1A, HIGH);
      digitalWrite(LED_1B, HIGH);
      digitalWrite(LED_1C, HIGH);
      digitalWrite(LED_1D, HIGH);
      digitalWrite(LED_1E, HIGH);
      digitalWrite(LED_1F, HIGH);
      digitalWrite(LED_1G, LOW);

      digitalWrite(LED_2A, HIGH);
      digitalWrite(LED_2B, HIGH);
      digitalWrite(LED_2C, HIGH);
      digitalWrite(LED_2D, HIGH);
      digitalWrite(LED_2E, HIGH);
      digitalWrite(LED_2F, HIGH);
      digitalWrite(LED_2G, LOW);
    }
  }
}

void four(int disp) {
  if (disp == 0) {
    digitalWrite(LED_1A, HIGH);
    digitalWrite(LED_1B, LOW);
    digitalWrite(LED_1C, LOW);
    digitalWrite(LED_1D, HIGH);
    digitalWrite(LED_1E, HIGH);
    digitalWrite(LED_1F, LOW);
    digitalWrite(LED_1G, LOW);
  } else {
    if (disp == 1) {
      digitalWrite(LED_2A, HIGH);
      digitalWrite(LED_2B, LOW);
      digitalWrite(LED_2C, LOW);
      digitalWrite(LED_2D, HIGH);
      digitalWrite(LED_2E, HIGH);
      digitalWrite(LED_2F, LOW);
      digitalWrite(LED_2G, LOW);
    } else {
      digitalWrite(LED_1A, HIGH);
      digitalWrite(LED_1B, HIGH);
      digitalWrite(LED_1C, HIGH);
      digitalWrite(LED_1D, HIGH);
      digitalWrite(LED_1E, HIGH);
      digitalWrite(LED_1F, HIGH);
      digitalWrite(LED_1G, LOW);

      digitalWrite(LED_2A, HIGH);
      digitalWrite(LED_2B, HIGH);
      digitalWrite(LED_2C, HIGH);
      digitalWrite(LED_2D, HIGH);
      digitalWrite(LED_2E, HIGH);
      digitalWrite(LED_2F, HIGH);
      digitalWrite(LED_2G, LOW);
    }
  }
}

void five(int disp) {
  if (disp == 0) {
    digitalWrite(LED_1A, LOW);
    digitalWrite(LED_1B, HIGH);
    digitalWrite(LED_1C, LOW);
    digitalWrite(LED_1D, LOW);
    digitalWrite(LED_1E, HIGH);
    digitalWrite(LED_1F, LOW);
    digitalWrite(LED_1G, LOW);
  } else {
    if (disp == 1) {
      digitalWrite(LED_2A, LOW);
      digitalWrite(LED_2B, HIGH);
      digitalWrite(LED_2C, LOW);
      digitalWrite(LED_2D, LOW);
      digitalWrite(LED_2E, HIGH);
      digitalWrite(LED_2F, LOW);
      digitalWrite(LED_2G, LOW);
    } else {
      digitalWrite(LED_1A, HIGH);
      digitalWrite(LED_1B, HIGH);
      digitalWrite(LED_1C, HIGH);
      digitalWrite(LED_1D, HIGH);
      digitalWrite(LED_1E, HIGH);
      digitalWrite(LED_1F, HIGH);
      digitalWrite(LED_1G, LOW);

      digitalWrite(LED_2A, HIGH);
      digitalWrite(LED_2B, HIGH);
      digitalWrite(LED_2C, HIGH);
      digitalWrite(LED_2D, HIGH);
      digitalWrite(LED_2E, HIGH);
      digitalWrite(LED_2F, HIGH);
      digitalWrite(LED_2G, LOW);
    }
  }
}

void six(int disp) {
  if (disp == 0) {
    digitalWrite(LED_1A, LOW);
    digitalWrite(LED_1B, HIGH);
    digitalWrite(LED_1C, LOW);
    digitalWrite(LED_1D, LOW);
    digitalWrite(LED_1E, LOW);
    digitalWrite(LED_1F, LOW);
    digitalWrite(LED_1G, LOW);
  } else {
    if (disp == 1) {
      digitalWrite(LED_2A, LOW);
      digitalWrite(LED_2B, HIGH);
      digitalWrite(LED_2C, LOW);
      digitalWrite(LED_2D, LOW);
      digitalWrite(LED_2E, LOW);
      digitalWrite(LED_2F, LOW);
      digitalWrite(LED_2G, LOW);
    } else {
      digitalWrite(LED_1A, HIGH);
      digitalWrite(LED_1B, HIGH);
      digitalWrite(LED_1C, HIGH);
      digitalWrite(LED_1D, HIGH);
      digitalWrite(LED_1E, HIGH);
      digitalWrite(LED_1F, HIGH);
      digitalWrite(LED_1G, LOW);

      digitalWrite(LED_2A, HIGH);
      digitalWrite(LED_2B, HIGH);
      digitalWrite(LED_2C, HIGH);
      digitalWrite(LED_2D, HIGH);
      digitalWrite(LED_2E, HIGH);
      digitalWrite(LED_2F, HIGH);
      digitalWrite(LED_2G, LOW);
    }
  }
}

void seven(int disp) {
  if (disp == 0) {
    digitalWrite(LED_1A, LOW);
    digitalWrite(LED_1B, LOW);
    digitalWrite(LED_1C, LOW);
    digitalWrite(LED_1D, HIGH);
    digitalWrite(LED_1E, HIGH);
    digitalWrite(LED_1F, HIGH);
    digitalWrite(LED_1G, HIGH);
  } else {
    if (disp == 1) {
      digitalWrite(LED_2A, LOW);
      digitalWrite(LED_2B, LOW);
      digitalWrite(LED_2C, LOW);
      digitalWrite(LED_2D, HIGH);
      digitalWrite(LED_2E, HIGH);
      digitalWrite(LED_2F, HIGH);
      digitalWrite(LED_2G, HIGH);
    } else {
      digitalWrite(LED_1A, HIGH);
      digitalWrite(LED_1B, HIGH);
      digitalWrite(LED_1C, HIGH);
      digitalWrite(LED_1D, HIGH);
      digitalWrite(LED_1E, HIGH);
      digitalWrite(LED_1F, HIGH);
      digitalWrite(LED_1G, LOW);

      digitalWrite(LED_2A, HIGH);
      digitalWrite(LED_2B, HIGH);
      digitalWrite(LED_2C, HIGH);
      digitalWrite(LED_2D, HIGH);
      digitalWrite(LED_2E, HIGH);
      digitalWrite(LED_2F, HIGH);
      digitalWrite(LED_2G, LOW);
    }
  }
}

void eight(int disp) {
  if (disp == 0) {
    digitalWrite(LED_1A, LOW);
    digitalWrite(LED_1B, LOW);
    digitalWrite(LED_1C, LOW);
    digitalWrite(LED_1D, LOW);
    digitalWrite(LED_1E, LOW);
    digitalWrite(LED_1F, LOW);
    digitalWrite(LED_1G, LOW);
  } else {
    if (disp == 1) {
      digitalWrite(LED_2A, LOW);
      digitalWrite(LED_2B, LOW);
      digitalWrite(LED_2C, LOW);
      digitalWrite(LED_2D, LOW);
      digitalWrite(LED_2E, LOW);
      digitalWrite(LED_2F, LOW);
      digitalWrite(LED_2G, LOW);
    } else {
      digitalWrite(LED_1A, HIGH);
      digitalWrite(LED_1B, HIGH);
      digitalWrite(LED_1C, HIGH);
      digitalWrite(LED_1D, HIGH);
      digitalWrite(LED_1E, HIGH);
      digitalWrite(LED_1F, HIGH);
      digitalWrite(LED_1G, LOW);

      digitalWrite(LED_2A, HIGH);
      digitalWrite(LED_2B, HIGH);
      digitalWrite(LED_2C, HIGH);
      digitalWrite(LED_2D, HIGH);
      digitalWrite(LED_2E, HIGH);
      digitalWrite(LED_2F, HIGH);
      digitalWrite(LED_2G, LOW);
    }
  }
}

void nine(int disp) {
  if (disp == 0) {
    digitalWrite(LED_1A, LOW);
    digitalWrite(LED_1B, LOW);
    digitalWrite(LED_1C, LOW);
    digitalWrite(LED_1D, HIGH);
    digitalWrite(LED_1E, HIGH);
    digitalWrite(LED_1F, LOW);
    digitalWrite(LED_1G, LOW);
  } else {
    if (disp == 1) {
      digitalWrite(LED_2A, LOW);
      digitalWrite(LED_2B, LOW);
      digitalWrite(LED_2C, LOW);
      digitalWrite(LED_2D, HIGH);
      digitalWrite(LED_2E, HIGH);
      digitalWrite(LED_2F, LOW);
      digitalWrite(LED_2G, LOW);
    } else {
      digitalWrite(LED_1A, HIGH);
      digitalWrite(LED_1B, HIGH);
      digitalWrite(LED_1C, HIGH);
      digitalWrite(LED_1D, HIGH);
      digitalWrite(LED_1E, HIGH);
      digitalWrite(LED_1F, HIGH);
      digitalWrite(LED_1G, LOW);

      digitalWrite(LED_2A, HIGH);
      digitalWrite(LED_2B, HIGH);
      digitalWrite(LED_2C, HIGH);
      digitalWrite(LED_2D, HIGH);
      digitalWrite(LED_2E, HIGH);
      digitalWrite(LED_2F, HIGH);
      digitalWrite(LED_2G, LOW);
    }
  }
}

void dec(int disp) {
  if (disp == 0) {
    digitalWrite(DEC_TOP, HIGH);
    digitalWrite(DEC_BOT, HIGH);
  } else {
    if (disp == 1) {
      digitalWrite(DEC_TOP, HIGH);
      digitalWrite(DEC_BOT, LOW);
    } else {
      if (disp == 2) {
        digitalWrite(DEC_TOP, LOW);
        digitalWrite(DEC_BOT, HIGH);
      } else {
        if (disp == 3) {
          digitalWrite(DEC_TOP, LOW);
          digitalWrite(DEC_BOT, LOW);
        } else {
          dec(0);
        }
      }
    }
  }
}







void loop() {
  
}

