/*
Projet: Epreuve finale
Equipe: P18
Auteurs: Donavan Sirois   sird5280
Description: Programme du robot qui gere la gestion de l'inventaire
Date: 2025-10-30
*/

#include <LibRobus.h>
#include <Arduino.h>

#define NCASIERS 3

bool chercherCaseLibre();

void initCasiers();

int getNumCasier();

void resetCasier();

int scanRFID();