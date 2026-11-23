/*
Projet: Epreuve finale
Equipe: P18
Auteurs: Donavan Sirois   sird5280
Description: Programme du robot qui gere la gestion de l'inventaire
Date: 2025-10-30
*/

#include "Setup.h"
#include "inventaire.h"
#include "suiveur.h"
#include "debug.h"


LiquidCrystal_I2C lcd2(0x27,16,2);

int Etat = 0;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;


void setup()
{
  SetupRobot();
}

void loop()
{ 
 
   ArretIntersection();
  digitalWrite(ELECTROAIMANTPIN, 0);
  initCasiers();
  
  
  while (1)
  {
      lcd2.clear();
      lcd2.backlight();
      lcd2.print("Veuillez scanner");
      lcd2.print("                        ");
      lcd2.print("votre carte");
    while (Etat == 0)
    {
      
      Etat = scanRFID();
      // Serial.println(Etat);
      if (Etat == 3)
      {
        Etat = 0;
        lcd2.clear();
        lcd2.backlight();
        lcd2.print("Aucune case     ");
        lcd2.print("                        ");
        lcd2.print("de libre!");
        delay(1000);
        resetCasier();
        SerialFlush();
        lcd2.clear();
        lcd2.backlight();
        lcd2.print("Veuillez scanner");
        lcd2.print("                        ");
        lcd2.print("votre carte");
      }
    }
    digitalWrite(ELECTROAIMANTPIN, 1);
    lcd2.clear();
    lcd2.backlight();
    lcd2.print("Appuyez Vert    ");
    lcd2.print("                        ");
    lcd2.print("lorsque pret");
    
    previousMillis = millis();
    while (Etat == 1)
    {
      currentMillis = millis();
      if (currentMillis - previousMillis >= 15000)
      {
        previousMillis = currentMillis;
        Etat = 0; 
        lcd2.clear();
        lcd2.backlight();
        lcd2.print("Timeout!");
        resetCasier();
        SerialFlush();
        digitalWrite(ELECTROAIMANTPIN, 0);
        beep(2);
        delay(1000);
      }
      if (digitalRead(BOUTON1) != 0) 
      {
        Etat = 3; 
        beep(1);
      }
    } 

    switch (Etat)
    {
      case 3:
        lcd2.clear();
        lcd2.backlight();
        lcd2.print("Livraison en    ");
        lcd2.print("                        ");
        lcd2.print("cours...");
        VaAuCasier(getNumCasier());
        DropCle();
        RetourneDuCasier(getNumCasier());
        SERVO_SetAngle(0, 90);  
        delay(500);
        SERVO_Disable(0);
        lcd2.clear();
        lcd2.backlight();
        lcd2.print("SUCCES!");
        delay(3000);
        digitalWrite(ELECTROAIMANTPIN, 0);
        SerialFlush();
      break;
      case 2:
        digitalWrite(ELECTROAIMANTPIN, 0);
        lcd2.clear();
        lcd2.backlight();
        lcd2.print("Retour en cours");
        VaAuCasier(getNumCasier());
        PrendCle();
        RetourneDuCasier(getNumCasier());
        SERVO_SetAngle(0, 90);  
        delay(500);
        SERVO_Disable(0);
        resetCasier();
        lcd2.clear();
        lcd2.backlight();
        lcd2.print("Case liberee!   ");
        lcd2.print("                        ");
        lcd2.print("veuillez prendre");
        delay(3000);
        digitalWrite(ELECTROAIMANTPIN, 0);
       SerialFlush();
      break;
    }
  Etat = 0;
  }  
}
