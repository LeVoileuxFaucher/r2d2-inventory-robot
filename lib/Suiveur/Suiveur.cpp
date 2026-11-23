/*
Projet: Labyrinthe
Equipe: P18
Auteurs: Tristan Faucher
Description: Programme du robot ROBUS pour résoudre le labyrinthe
Date: 2025-10-02
*/

#include "Suiveur.h"

int derniereDirection = 0;
int16_t TabLectures[3] = {0, 0, 0};
float normG = 0;
float normC = 0;
float normD = 0;
float position = 0;
float somme = 0;
float vitesseGauche = 0;
float vitesseDroite = 0;

void LectureCapteur()
{
  TabLectures[LEFT] = analogRead(SUIVEURGPIN);
  TabLectures[FRONT] = analogRead(SUIVEURCPIN);
  TabLectures[RIGHT] = analogRead(SUIVEURDPIN);
}

void Normalisation()
{
  normG = constrain((float)(TabLectures[LEFT] - BLANCG) / PLAGEG, 0, 1);
  normC = constrain((float)(TabLectures[FRONT] - BLANCC) / PLAGEC, 0, 1);
  normD = constrain((float)(TabLectures[RIGHT] - BLANCD) / PLAGED, 0, 1);
}

void GestionPosition()
{
  somme = normG + normC + normD;
  position = 0; // 0 = centré

  if (somme > 0)
    position = (-1 * normG + 0 * normC + 1 * normD) / somme;
}

void CorrectionVitesse()
{
  float correction = Kp * position;

  // --- Calcul des vitesses des moteurs ---
  vitesseGauche = VITESSE_BASE + correction;
  vitesseDroite = VITESSE_BASE - correction;
}
void SerialFlush()
{
  while(Serial2.available() > 0) {
        char t = Serial2.read();
     }
}

void GestionPerteLigne()
{
  if (derniereDirection < 0)
  {
    vitesseGauche = -0.075;
    vitesseDroite = 0.075;
  }
  else if (derniereDirection > 0)
  {
    vitesseGauche = 0.075;
    vitesseDroite = -0.075;
  }
  else
  {
    vitesseGauche = 0.075;
    vitesseDroite = 0.075;
  }
  MOTOR_SetSpeed(RIGHT, vitesseDroite);
  MOTOR_SetSpeed(LEFT, vitesseGauche);
}

void GestionVitesse()
{
  vitesseGauche = constrain(vitesseGauche, VITESSE_MIN, VITESSE_MAX);
  vitesseDroite = constrain(vitesseDroite, VITESSE_MIN, VITESSE_MAX);

  // --- Appliquer les vitesses ---
  MOTOR_SetSpeed(RIGHT, vitesseDroite);
  MOTOR_SetSpeed(LEFT, vitesseGauche);
}

void SauvegardePosition()
{
  if (position < -0.3)
    derniereDirection = -1;
  else if (position > 0.3)
    derniereDirection = 1;
}

void Sui_Lah_Ling()
{
  LectureCapteur();
  Normalisation();
  SauvegardePosition();
  // --- Gestion de la perte de ligne ---
  if((normG < 0.1)&&(normC < 0.1)&&(normD < 0.1)) // presque tout blanc : ligne perdue (somme < 0.1)
  {
    GestionPerteLigne();
  }
  else
  {
    GestionPosition();
    CorrectionVitesse();
    GestionVitesse();
  }
  //Debug();
}


int16_t GetVCapteur(int n)
{
  return TabLectures[n];
}

bool GetLigneCentre(void)
{
  LectureCapteur();
  Normalisation();
  if((normG < 0.2)&&(normC > 0.8)&&(normD < 0.2))
    return 1; // Ligne détectée au centre
  else
    return 0; // Ligne perdue
}

bool GetIntersection(void)
{
  LectureCapteur();
  Normalisation();
  if((normG > 0.9)&&(normC > 0.9)&&(normD > 0.9))
    return 1; // Intersection détectée
  else
    return 0; // Intersection perdue
}

void MoveToLineGauche(float vitesse)
{
  // Avancer jusqu'à ce qu'au moins un capteur détecte la ligne
  tourneGauche(vitesse);
  while(!GetLigneCentre())
  {
    LectureCapteur();
    Normalisation();
  }
  // Arrêter les moteurs
  arret();
}

void MoveToLineDroit(float vitesse)
{
  // Avancer jusqu'à ce qu'au moins un capteur détecte la ligne
 tourneDroit(vitesse);
  while(!GetLigneCentre())
  {
    LectureCapteur();
    Normalisation();
  }
  // Arrêter les moteurs
  arret();
}

void GaucheIntersection()
{
 // Serial.println("gauche");
  while (!GetIntersection())
  {
    Sui_Lah_Ling();
  }
  Debug();
  ResetEncodeurs();
  AvanceXcm(5, 0.2);
  GaucheXdeg(60, 0.2);
  MoveToLineGauche(0.1);
}

void DroitIntersection()
{
  //Serial.println("droit");
  while (!GetIntersection())
  {
    Sui_Lah_Ling();
  }
  ResetEncodeurs();
  AvanceXcm(5, 0.2);
  DroitXdeg(60, 0.2);
  MoveToLineDroit(0.1);
}

void ContinueIntersection()
{
  //Serial.println("continue");
  while (!GetIntersection())
  {
    Sui_Lah_Ling();
  }
  ResetEncodeurs();
  AvanceXcm(10, 0.2);
}

void ArretIntersection ()
{
 // Serial.println("arret");
  while (!GetIntersection())
  {
    Sui_Lah_Ling();
  }
  ResetEncodeurs();
  AvanceXcm(2, 0.2);
  arret();
}
void DemiTourLigne()
{
  //Serial.println("demi-tour");
  ResetEncodeurs();
  ReculeXcm(15, 0.2);
  ResetEncodeurs();
  GaucheXdeg(150, 0.2);
  MoveToLineGauche(0.1);
}
void DropCle()
{
  SERVO_Enable(0);
  for (int i = 0; 90 - i * 5 > 85; i++)
  {
    SERVO_SetAngle(0, 90 - i * 5);  
    delay(60);
  }
    ArretIntersection();
    SERVO_SetAngle(0, 128);  
    delay(1000); 
    digitalWrite(ELECTROAIMANTPIN, 0);
    delay(1000);
    SERVO_SetAngle(0, 85);  
    delay(1000); 
}
void PrendCle()
{
  SERVO_Enable(0); 
  for (int i = 0; 90 - i * 5 > 85; i++)
  {
    SERVO_SetAngle(0, 90 - i * 5);  
    delay(60);
  }
  ArretIntersection();
  digitalWrite(ELECTROAIMANTPIN, 1);
  SERVO_SetAngle(0, 135);  
    delay(1000);
    GaucheXdeg(2, 0.1); 
    AvanceXcm(1, 0.1);
    delay(500); 
  
  ReculeXcm(1, 0.1);
  SERVO_SetAngle(0, 128); 
  delay(1000);
  for (int i = 0; 125 - i * 5 > 90; i++)
  {
    SERVO_SetAngle(0, 125 - i * 5);  
    delay(60);
  }
  ReculeXcm(1, 0.1);
    delay(500);
  
  
  DroitXdeg(3, 0.1);
  delay(500);
  
  delay(500);
  for (int i = 0; 90 - i * 5 > 85; i++)
  {
    SERVO_SetAngle(0, 90 - i * 5);  
    delay(60);
  }
}



void RetourneDuCasier(uint8_t NumDuCasier)
{
  switch (NumDuCasier)
  {
  case 0:
    DemiTourLigne();
    GaucheIntersection();
    DroitIntersection();
    ArretIntersection();
    break;

  case 1:
    DemiTourLigne();
    ContinueIntersection();
    ArretIntersection();
    break;

  case 2:
    DemiTourLigne();
    DroitIntersection();
    GaucheIntersection();
    ArretIntersection();
    break;

  

  default:
   //Serial.println("Casier inconnu");
    break;
  }
}

void VaAuCasier(uint8_t NumDuCasier)
{
  switch (NumDuCasier)
  {
  case 0:
    DemiTourLigne();
    GaucheIntersection();
    DroitIntersection();
    break;

    case 1:
    DemiTourLigne();
    ContinueIntersection();
    break;

    case 2:
    DemiTourLigne();
    DroitIntersection();
    GaucheIntersection();
    break;

    
  
  default:
   //Serial.println("Casier inconnu");
    break;
  }
}

void Debug()
{
  Serial.print("G:");
  Serial.print(TabLectures[LEFT]);
  Serial.print(" C:");
  Serial.print(TabLectures[FRONT]);
  Serial.print(" D:");
  Serial.print(TabLectures[RIGHT]);
  Serial.print(" | G:");
  Serial.print(normG);
  Serial.print(" C:");
  Serial.print(normC);
  Serial.print(" D:");
  Serial.print(normD);
  Serial.print(" | Somme:");
  Serial.print(somme, 2);
  if (position < -0.2)
    Serial.print (" Gauche ");
  else if (position > 0.2)
    Serial.print (" Droite ");
  else
    Serial.print (" Centre ");
  Serial.print(" | Ligne:");
  Serial.print(GetLigneCentre());
  Serial.print(" | Int:");
  Serial.print(GetIntersection());
  Serial.print(" | VL:");
  Serial.print(vitesseGauche, 2);
  Serial.print(" VR:");
  Serial.println(vitesseDroite, 2);
}