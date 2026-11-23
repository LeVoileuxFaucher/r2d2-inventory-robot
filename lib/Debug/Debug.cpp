/*
Projet: Combatant
Equipe: P18
Auteurs: Tristan Faucher
Description: Programme pour debugger
Date: 2025-10-24
*/

#include "Debug.h"

void beep(int count)
{
  for (int i = 0; i < count; i++)
  {
    AX_BuzzerON(); // Active le buzzer
    delay(100);
    AX_BuzzerOFF(); // Désactive le buzzer
    delay(100);
  }
  delay(400); // Petite pause avant la suite
}