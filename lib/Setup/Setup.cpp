/*
Projet: Labyrinthe
Equipe: P18
Auteurs: Donavan Sirois     Sird5280
Description: Programme qui setup le robot
Date: 2025-10-02
*/

#include"Setup.h"

LiquidCrystal_I2C lcd(0x27,16,2);

void SetupLED(void)
{
    pinMode(VERTPIN, OUTPUT);
    pinMode(ROUGEPIN, OUTPUT);
    pinMode(BLEUPIN, OUTPUT);
    pinMode(JAUNEPIN, OUTPUT);
    digitalWrite(VERTPIN, 0);
    digitalWrite(ROUGEPIN, 0);
    digitalWrite(BLEUPIN, 0);
    digitalWrite(JAUNEPIN, 0);
}

void SetupBoutons(void)
{
    pinMode(BOUTON1, INPUT);
    pinMode(BOUTON2, INPUT);
    digitalWrite(BOUTON1, 0);
    digitalWrite(BOUTON2, 0);
}


void SetupCapteurCouleur(void)
{
    
    pinMode(SUIVEURGPIN, INPUT);
    pinMode(SUIVEURCPIN, INPUT);
    pinMode(SUIVEURDPIN, INPUT);
   
}

void SetupMoteurs()
{
    ENCODER_ReadReset(RIGHT);
    ENCODER_ReadReset(LEFT);
    arret();
}

void SetupRobot(void)
{
    BoardInit();        // Initialise la carte
    Serial.begin(9600); // Active la communication série
    Serial2.begin(9600);
    pinMode(MICROPIN, INPUT_PULLUP);
    pinMode(ELECTROAIMANTPIN, OUTPUT);
    digitalWrite(ELECTROAIMANTPIN, 0);

    SetupCapteurCouleur();
    SetupMoteurs();
    SetupLED();
    SetupBoutons();
    setupLCD();
    SERVO_SetAngle(0, 90);
    delay(500);
    SERVO_Disable(0);
}

void setupLCD(){
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0,0);
}
