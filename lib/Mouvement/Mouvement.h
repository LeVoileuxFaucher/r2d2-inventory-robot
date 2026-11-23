/*
Projet: Combatant
Equipe: P18
Auteurs: Tristan Faucher
Description: Programme du robot ROBUS pour se deplacer
Date: 2025-10-24
*/

#include<LibRobus.h>

#define PID_IMPACT 500

void AvanceXcm(int Distance_cm, float vitesse);
void ReculeXcm(int Distance_cm, float vitesse);
void GaucheXdeg(int deg, float vitesse);
void DroitXdeg(int deg, float vitesse);
void arret(void);
void avance(float vitesse);
void tourneDroit(float vitesse);
void tourneGauche(float vitesse); 
void ResetEncodeurs(void);
float GetMoteurspeed(char c);
void SetMoteurspeed(char c, float n);