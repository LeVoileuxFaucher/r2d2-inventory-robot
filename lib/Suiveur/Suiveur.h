/*
Projet: Labyrinthe
Equipe: P18
Auteurs: Tristan Faucher
Description: Programme du robot ROBUS pour résoudre le labyrinthe
Date: 2025-10-02
*/

#include <LibRobus.h>
#include <Arduino.h>
#include "Setup.h"
#include "Mouvement.h"

#define BLANCG 30
#define NOIRG 500
#define PLAGEG (NOIRG - BLANCG)

#define BLANCC 20
#define NOIRC 460
#define PLAGEC (NOIRC - BLANCC)

#define BLANCD 20
#define NOIRD 440
#define PLAGED (NOIRD - BLANCD)

#define VITESSE_BASE 0.2
#define VITESSE_MAX 0.3
#define VITESSE_MIN 0.1

#define Kp 0.1

#define FREQMIN 770
#define FREQMAX 800



void Sui_Lah_Ling(void);
void LectureCapteur(void);
int16_t GetVCapteur(int n);
void MoveToLineGauche(float vitesse);
void MoveToLineDroit(float vitesse);
bool GetLigneCentre(void);
bool GetIntersection(void);
void Normalisation(void);
void GestionPosition(void);
void CorrectionVitesse(void);
void GestionPerteLigne(void);
void GestionVitesse(void);
void SauvegardePosition(void);
void Debug(void);
void VaAuCasier(uint8_t NumDuCasier);
void RetourneDuCasier(uint8_t NumDuCasier);
void GaucheIntersection(void);
void DroitIntersection(void);
void ContinueIntersection(void);
void ArretIntersection(void);
void DemiTourLigne(void);
void DropCle(void);
void PrendCle(void);
void SerialFlush(void);