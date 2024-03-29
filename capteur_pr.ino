#include "SPI.h"

#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#include <Wire.h>
#include <BH1750.h>²
#include <SoftwareSerial.h>


// Déclaration des broches TFT
#define TFT_DC 9
#define TFT_CS 10

//------------------<declaration>-----------------------------------------------------------------------------------------

// Initialisation de l'écran TFT
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

// Constantes pour les broches
const int led = 6;
const int capteur = 2;

// Initialisation du capteur de lumière
BH1750 lightMeter;

// Initialisation de la communication série
SoftwareSerial BT(4,6);//(RX,TX)    ATTENTION : relier le RX au TX de l'arduino !!!


// Variables globales
int val = 0;
int IntensiteLed = 0;
int lux = 0;
int cible = 300;
int a = 0;

// Position des textes sur l'écran TFT
int luxTextX = 10;
int luxTextY = 10;
int ledTextX = 10;
int ledTextY = 30;

//------------------<declaration>-----------------------------------------------------------------------------------------


void setup() {
  // Initialisation de l'écran TFT
  tft.begin();
  tft.setRotation(3); // Rotation de l'écran si nécessaire
  tft.fillScreen(ILI9341_BLACK); // Effacer l'écran

  // Initialisation du capteur de lumière
  lightMeter.begin();

  // Initialisation de la communication série
  BT.begin(9600);
  Serial.begin(9600);
}
void affichBT()
{
          a = (BT.read());
        
          Serial.println(a);
            switch (a) 
              {
                case 0 :
                        {
                        
                        BT.println(lux);
                        //delay(200);
                        
                        }
                break ;
                
                case 1 :
                        {
                        BT.println(IntensiteLed);
                        //delay(200);
                        } 
                break ;

               
              }
 }
void loop() {
  // Lire la valeur de luminosité
  lux = lightMeter.readLightLevel();
  Serial.print("lux=");
  Serial.println(lux);
  
  // Lire la valeur du capteur
  val = digitalRead(capteur);

  // Vérifier si le capteur est actif
  if (val == HIGH) {
    // Si la luminosité est inférieure à la cible
    Serial.print("IntensiteLed=");
    if (lux < cible) {
      analogWrite(led, IntensiteLed);
      delay(10);
      IntensiteLed = IntensiteLed + 1;
      Serial.print("IntensiteLed=");
      Serial.println(IntensiteLed);
      delay(20);
    }
    // Si la luminosité est supérieure à la cible
    else if (lux > cible) {
      analogWrite(led, IntensiteLed);
      delay(10);
      // Empêcher IntensiteLed de descendre en dessous de 0
      IntensiteLed = max(0, IntensiteLed - 1);
      Serial.print("IntensiteLed=");
      Serial.println(IntensiteLed);
      delay(20);
    }
    // Si la luminosité est égale à la cible
    else  {
      Serial.print("IntensiteLed=");
      Serial.println(IntensiteLed);
      delay(20);
    }
    
  }
  else {
      analogWrite(led, LOW);
      IntensiteLed = 0 ;
      }

  // Supprimer la valeur précédente d'IntensiteLed sur l'écran TFT
  tft.fillRect(ledTextX, ledTextY, 100, 20, ILI9341_BLACK);

  // Afficher la nouvelle valeur d'IntensiteLed sur l'écran TFT
  tft.setCursor(ledTextX, ledTextY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.print("Led: ");
  tft.print(IntensiteLed);
  
  // Supprimer la valeur précédente de lux sur l'écran TFT
 tft.fillRect(luxTextX, luxTextY, 200, 20, ILI9341_BLACK);


  // Afficher la nouvelle valeur de lux sur l'écran TFT
  tft.setCursor(luxTextX, luxTextY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.print("Lumiere: ");
  tft.print(lux);

  // Ajouter un court délai pour éviter les rafraîchissements trop rapides de l'écran
  delay(200);
  //metre a 300 direct
  affichBT();
  delay(100);


}
