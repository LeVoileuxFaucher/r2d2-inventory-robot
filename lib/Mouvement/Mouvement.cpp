/*
Projet: Combatant
Equipe: P18
Auteurs: Tristan Faucher
Description: Programme du robot ROBUS pour se deplacer
Date: 2025-10-24
*/

#include "Mouvement.h"

float MoteurspeedDroit = 0.0;  // Dernière vitesse du moteur droit (utile pour savoir si le moteur tourne encore)
float MoteurspeedGauche = 0.0; // Dernière vitesse du moteur gauche


float GetMoteurspeed(char c)
{
  if (c == 'D')
  {
    return MoteurspeedDroit;
  }
  else
  {
    return MoteurspeedGauche;
  }
}

void SetMoteurspeed(char c, float n)
{
  if (c == 'D')
  {
    MoteurspeedDroit = n;
  }
  else
  {
    MoteurspeedGauche = n;
  }
}

void ResetEncodeurs(void)
{
  ENCODER_ReadReset(RIGHT);
  ENCODER_ReadReset(LEFT);
}

/*
Arrête complètement les moteurs
 -> Le robot s’immobilise
*/
void arret(void)
{
  MOTOR_SetSpeed(RIGHT, 0);
  MOTOR_SetSpeed(LEFT, 0);
  MoteurspeedDroit = 0;
  MoteurspeedGauche = 0;
}

/*
Fait avancer le robot tout droit
 -> Les deux moteurs tournent à la même vitesse positive
*/
void avance(float vitesse)
{
  MOTOR_SetSpeed(RIGHT, vitesse);
  MOTOR_SetSpeed(LEFT, vitesse);
  MoteurspeedDroit = vitesse;
  MoteurspeedGauche = vitesse;
}

/*
Rotation sur place vers la droite
 -> Le moteur gauche avance, le droit recule
*/
void tourneDroit(float vitesse)
{
  MOTOR_SetSpeed(RIGHT, -vitesse);
  MOTOR_SetSpeed(LEFT, vitesse);
  MoteurspeedDroit = -vitesse;
  MoteurspeedGauche = vitesse;
}

/*
Rotation sur place vers la gauche
 -> Le moteur droit avance, le gauche recule
*/
void tourneGauche(float vitesse)
{
  MOTOR_SetSpeed(RIGHT, vitesse);
  MOTOR_SetSpeed(LEFT, -vitesse);
  MoteurspeedDroit = vitesse;
  MoteurspeedGauche = -vitesse;
}

/*
Tourne le robot de 180° vers la droite
 -> Utilise les codeurs pour mesurer l’angle parcouru
*/
void DroitXdeg(int deg, float vitesse)
{
  tourneDroit(vitesse);
  while (!((MoteurspeedDroit == 0) && (MoteurspeedGauche == 0)))
  {
    if ((long)deg*7600/360 <= ENCODER_Read(LEFT)) // Codeur gauche atteint la distance équivalente à 180°
    {
      MOTOR_SetSpeed(LEFT, 0);
      MoteurspeedGauche = 0;
    }
    if ((long)-deg*7600/360 >= ENCODER_Read(RIGHT)) // Codeur droit aussi
    {
      MOTOR_SetSpeed(RIGHT, 0);
      MoteurspeedDroit = 0;
    }
  }
  ResetEncodeurs();
}

/*
Tourne le robot de 180° vers la gauche
*/
void GaucheXdeg(int deg, float vitesse)
{
  
  tourneGauche(vitesse);
  while (!((MoteurspeedDroit == 0) && (MoteurspeedGauche == 0)))
  {
    if ((long)-deg*7600/360 >= ENCODER_Read(LEFT)) // Codeur gauche atteint la valeur de rotation
    {
      MOTOR_SetSpeed(LEFT, 0);
      MoteurspeedGauche = 0;
    }
    if ((long)deg*7600/360 <= ENCODER_Read(RIGHT)) // Codeur droit aussi
    {
      MOTOR_SetSpeed(RIGHT, 0);
      MoteurspeedDroit = 0;
    }
  }
  ResetEncodeurs();
}

/*
Avance le robot de 50 cm ou jusqu’à un obstacle
 -> Vérifie en continu les capteurs
 -> S’arrête si distance atteinte ou mur détecté
*/
void AvanceXcm(int Distance_cm, float vitesse)
{
  
  int Diff;
  float ratio = 3200.0 / 23.938936;
  int Distance_Encodeur = (int)(Distance_cm * ratio);

  avance(vitesse);
   
  while (!((MoteurspeedDroit == 0) && (MoteurspeedGauche == 0)))
  {
    
    if (Distance_Encodeur <= ENCODER_Read(RIGHT)) // ≈ X cm roue droite
    {
      MOTOR_SetSpeed(RIGHT, 0);
      MoteurspeedDroit = 0;
    }
    if ((Distance_Encodeur <= ENCODER_Read(LEFT))) // ≈ X cm roue gauche
    {
      MOTOR_SetSpeed(LEFT, 0);
      MoteurspeedGauche = 0;
    }
    if (ENCODER_Read(RIGHT) > ENCODER_Read(LEFT))
    {
      Diff = ENCODER_Read(RIGHT) - ENCODER_Read(LEFT);
      MOTOR_SetSpeed(RIGHT, vitesse + -(Diff / PID_IMPACT));
      MOTOR_SetSpeed(LEFT, vitesse + (Diff / PID_IMPACT));
    }
    else if (ENCODER_Read(RIGHT) < ENCODER_Read(LEFT))
    {
      Diff = ENCODER_Read(LEFT) - ENCODER_Read(RIGHT);
      MOTOR_SetSpeed(RIGHT, vitesse + (Diff / PID_IMPACT));
      MOTOR_SetSpeed(LEFT, vitesse + -(Diff / PID_IMPACT));
    } 
  }
    arret();
    delay(50);
  // Reset des codeurs pour prochaine mesure
  ResetEncodeurs();
}

void ReculeXcm(int Distance_cm, float vitesse)
{
  
  int Diff;
  float ratio = 3200.0 / 23.938936;
  int Distance_Encodeur = (int)(Distance_cm * ratio);
  avance(-vitesse);
   
  while (!((MoteurspeedDroit == 0) && (MoteurspeedGauche == 0)))
  {
    if (-Distance_Encodeur >= ENCODER_Read(RIGHT)) 
    {
      MOTOR_SetSpeed(RIGHT, 0);
      MoteurspeedDroit = 0;
    }
    if (-Distance_Encodeur >= ENCODER_Read(LEFT)) 
    {
      MOTOR_SetSpeed(LEFT, 0);
      MoteurspeedGauche = 0;
    }
    if (ENCODER_Read(RIGHT) > ENCODER_Read(LEFT))
    {
      Diff = ENCODER_Read(RIGHT) - ENCODER_Read(LEFT);
      MOTOR_SetSpeed(RIGHT, -vitesse + -(Diff / PID_IMPACT));
      MOTOR_SetSpeed(LEFT, -vitesse + (Diff / PID_IMPACT));
    }
    else if (ENCODER_Read(RIGHT) < ENCODER_Read(LEFT))
    {
      Diff = ENCODER_Read(LEFT) - ENCODER_Read(RIGHT);
      MOTOR_SetSpeed(RIGHT, -vitesse + (Diff / PID_IMPACT));
      MOTOR_SetSpeed(LEFT, -vitesse + -(Diff / PID_IMPACT));
    } 
  }
    arret();
  ResetEncodeurs();
}