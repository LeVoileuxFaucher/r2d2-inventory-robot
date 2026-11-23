/*
Projet: Danse en losange
Équipe: P18
Auteur: Tristan Faucher
Description: Programme du robot ROBUS pour lire une couleur XD
Date: 2025-10-24
*/
#include <Arduino.h>
#include <Adafruit_TCS34725.h>

#define JAUNE 4
#define ROUGE 6
#define BLEU 5
#define VERT 1
#define INCONNU 0

uint8_t getColorCode();
bool inRange(float v, float target, float tool);
void GetColor(void);
