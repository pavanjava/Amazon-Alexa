#include <SPI.h>
#include <IRremote.h>

IRsend irsend;

char buff [100];
volatile byte index;
volatile bool receivedone;  /* use reception complete flag */

void setup (void)
{
  Serial.begin (9600);
  SPCR |= bit(SPE);         /* Enable SPI */
  pinMode(MISO, OUTPUT);    /* Make MISO pin as OUTPUT */
  index = 0;
  receivedone = false;
  SPI.attachInterrupt();    /* Attach SPI interrupt */
}

void loop (void)
{
  if (receivedone)          /* Check and print received buffer if any */
  {
    buff[index] = 0;

    if (strcmp(buff, "TV ON") == 0) {
      for (int i = 0; i < 3; i++) {
        Serial.println("SONY ON");
        irsend.sendSony(0xa90, 12);
        delay(40);
      }
    } else if (strcmp(buff, "TV OFF") == 0) {
      for (int i = 0; i < 3; i++) {
        Serial.println("SONY OFF");
        irsend.sendSony(0xa90, 12);
        delay(40);
      }
    } else if (strcmp(buff, "TV OFF") == 0) {
      for (int i = 0; i < 3; i++) {
        Serial.println("SONY OFF");
        irsend.sendSony(0xa90, 12);
        delay(40);
      }
    } else if (strcmp(buff, "VOLUME UP") == 0) {
      for (int i = 0; i < 3; i++) {
        Serial.println("VOLUME UP");
        irsend.sendSony(0x490, 12);
        delay(40);
      }
    } else if (strcmp(buff, "VOLUME DOWN") == 0) {
      for (int i = 0; i < 3; i++) {
        Serial.println("VOLUME DOWN");
        irsend.sendSony(0xc90, 12);
        delay(40);
      }
    } else if (strcmp(buff, "HOME") == 0) {
      for (int i = 0; i < 3; i++) {
        Serial.println("HOME");
        irsend.sendSony(0x070, 12);
        delay(40);
      }
    }else if (strcmp(buff, "RIGHT") == 0) {
      for (int i = 0; i < 3; i++) {
        Serial.println("RIGHT");
        irsend.sendSony(0xcd0, 12);
        delay(40);
      }
    }else if (strcmp(buff, "LEFT") == 0) {
      for (int i = 0; i < 3; i++) {
        Serial.println("LEFT");
        irsend.sendSony(0x2d0, 12);
        delay(40);
      }
    }else if (strcmp(buff, "UP") == 0) {
      for (int i = 0; i < 3; i++) {
        Serial.println("UP");
        irsend.sendSony(0x2f0, 12);
        delay(40);
      }
    }else if (strcmp(buff, "DOWN") == 0) {
      for (int i = 0; i < 3; i++) {
        Serial.println("DOWN");
        irsend.sendSony(0xaf0, 12);
        delay(40);
      }
    }else if (strcmp(buff, "ENTER") == 0) {
      for (int i = 0; i < 3; i++) {
        Serial.println("ENTER");
        irsend.sendSony(0xa70, 12);
        delay(40);
      }
    }else if (strcmp(buff, "MUTE") == 0) {
      for (int i = 0; i < 3; i++) {
        Serial.println("MUTE");
        irsend.sendSony(0x290, 12);
        delay(40);
      }
    }
    index = 0;
    receivedone = false;
  }
}

// SPI interrupt routine
ISR (SPI_STC_vect)
{
  uint8_t oldsrg = SREG;
  cli();
  char c = SPDR;
  if (index < sizeof buff)
  {
    if (c != '\n')
      buff [index++] = c;
    if (c == '\n') {    /* Check for newline character as end of msg */
      receivedone = true;
    }
  }
  SREG = oldsrg;
}
