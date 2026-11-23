
#include "CapteurCouleur.h"

float r, g, b;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

bool inRange(float value, float target, float tol)
{
  return (value >= target - tol) && (value <= target + tol);
}

uint8_t getColorCode()
{
  GetColor();
  if (inRange(r, 85, 3) && inRange(g, 90, 3) && inRange(b, 72, 3))
    return JAUNE; // Jaune
  if (inRange(r, 82, 4) && inRange(g, 76, 4) && inRange(b, 90, 4))
    return ROUGE; // Rouge/magenta
  if (inRange(r, 62, 2) && inRange(g, 87, 2) && inRange(b, 98, 2))
    return BLEU; // Bleu
  if (inRange(r, 65, 4) && inRange(g, 93, 4) && inRange(b, 90, 4))
    return VERT; // Vert

  return 0; // Inconnue
}

void GetColor(void)
{
  uint16_t rRaw, gRaw, bRaw, cRaw;

  tcs.getRawData(&rRaw, &gRaw, &bRaw, &cRaw);

  r = (float)rRaw / cRaw * 255.0;
  g = (float)gRaw / cRaw * 255.0;
  b = (float)bRaw / cRaw * 255.0;
  Serial.print("R: "); Serial.print((int)r);
  Serial.print(" | G: "); Serial.print((int)g);
  Serial.print(" | B: "); Serial.println((int)b);
}