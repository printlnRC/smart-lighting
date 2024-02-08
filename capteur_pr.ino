//------------------<Librarie>--------------------------------------------------------------------------------------------
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Arduino.h>
#include <Wire.h>
#include <ArtronShop_BH1750.h>

//------------------<Librarie>--------------------------------------------------------------------------------------------

//------------------<declaration>-----------------------------------------------------------------------------------------
const int led = 4;
const int capteur = 2;
int val = 0;
#define TFT_DC 9
#define TFT_CS 10
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
ArtronShop_BH1750 bh1750(0x23, &Wire); // Non Jump ADDR: 0x23, Jump ADDR: 0x5C
//------------------<declaration>-----------------------------------------------------------------------------------------


void setup() {
  pinMode(led, OUTPUT);
  pinMode(capteur, INPUT);
  Serial.begin(9600);
}

void loop() {
  val = digitalRead(capteur);

  if (val == HIGH) {
    if (bh1750.light() < 300 ){
      Serial.println("La LED est allumée.");
    digitalWrite(led, HIGH);
    delay(2000);
    }
    
  } else {
    digitalWrite(led, LOW);
    delay(1000);
  }
}
