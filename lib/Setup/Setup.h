/*
Projet: Labyrinthe
Equipe: P18
Auteurs: Donavan Sirois     sird5280
Description: Programme qui setup le robot
Date: 2025-10-02
*/

#include<LibRobus.h>
#include <LiquidCrystal_I2C.h>
#include "Mouvement.h"

#define VERTPIN 53
#define JAUNEPIN 45
#define BLEUPIN 49  
#define ROUGEPIN 41
#define MICROPIN A1
#define SUIVEURGPIN A7
#define SUIVEURCPIN A6
#define SUIVEURDPIN A5
#define ELECTROAIMANTPIN 53
#define BOUTON1 45
#define BOUTON2 47


void SetupLED(void);

void SetupBoutons(void);

void SetupCapteurCouleur(void);

void SetupMoteurs(void);

void SetupRobot(void);

void setupLCD();

