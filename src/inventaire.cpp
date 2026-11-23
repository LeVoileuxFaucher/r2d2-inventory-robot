/*
Projet: Epreuve finale
Equipe: P18
Auteurs: Donavan Sirois   sird5280
Description: Programme du robot qui gere la gestion de l'inventaire
Date: 2025-10-30
*/

#include "inventaire.h"
#include "Debug.h"

int caseActive = -1;

struct Casier
{
    char id[20];
    bool CasierUtiliser;
};

struct Casier c[NCASIERS];

void initCasiers()
{
    for (int i = 0; i < NCASIERS; i++)
    {
        c[i] = {' ', false};
    }
}

int scanRFID()
{
    char id_tag[20];
    char scanc;
    bool firstChar = true;

    if (Serial2.available() > 0)
    {
        // Serial.println(Serial2.available());
        delay(500);
        // Pour savoir si on affiche la première fois
        for (int i = 0; i < 16; i++)
        {
            int r = Serial2.read();
            if (r == -1)
                break;

            scanc = char(r);

            // Si c'est un caractère valide RFID (chiffre ou lettre)
            if ((scanc >= '0' && scanc <= '9') ||
                (scanc >= 'A' && scanc <= 'Z'))
            {
                // Serial.print(scanc);
                //  --- CLEAR SEULEMENT AU PREMIER CARACTÈRE VALIDE ---
                if (firstChar)
                {
                    beep(1);
                    // Serial.println("Lecture RFID: ");
                    Serial2.flush();
                    for (int i = 0; i < 16; i++)
                    {
                        id_tag[i] = 0;
                    }
                    firstChar = false;
                }
                id_tag[i] = scanc;
                Serial.print(id_tag[i]);
                Serial.println(scanc);
            }
           //Serial.println(scanc);
        }

        Serial.println(caseActive);

        for (int i = 0; i < NCASIERS; i++)
        {
            bool id_same = true;
            for (int j = 1; j < 13; j++)
            {
                if (c[i].id[j - 1] != id_tag[j - 1])
                {
                    id_same = false;
                    break;
                }
            }
            if (id_same == true)
            {
                caseActive = i;
                return 2;
            }
        }

        for (int i = 0; i < NCASIERS; i++)
        {
            if (c[i].CasierUtiliser == false)
            {
                caseActive = i;
                for (int j = 1; j < 13; j++)
                    {
                        c[caseActive].id[j - 1] = id_tag[j - 1];
                    }
                c[caseActive].CasierUtiliser = true;
                return 1;
            }
        }
        return 3;
    }
    return 0;
}

int getNumCasier()
{
    return caseActive;
}

void resetCasier()
{
    Serial.println(caseActive);
    for (int i = 0; i < 20; i++)
    {
        c[caseActive].id[i] = '0';
        Serial.print(char(c[caseActive].id[i]));
    }
    c[caseActive].CasierUtiliser = false;
    caseActive = -1;
}