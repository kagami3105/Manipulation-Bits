/*
  Titre      : Système de déclenchement d'arlarme d'incendie
  Auteur     : Boladji ODELOUI
  Date       : 19/02/2025
  Description: Détecte le son et une flamme à l'aide d'un buzzer en manipulant les bits
  Version    : 0.0.1
*/

#include <Arduino.h>

// Définition des pins pour les différents capteurs

#define SOUND_SENSOR 2 // Entrée numérique capteur de son
#define FLAM_SENSOR 3  // Entrée numérique capteur de flamme
#define PIN_LED 4      // Entrée numérique de la LED
#define PIN_BUZZER 5   // Entrée numérique buzzer

// Définition des états des différents capteurs en bit
#define BIT_SOUND (1 << 0)  // Mettre 1 à la position 0 pour l'état du capteur de son
#define BIT_FLAM (1 << 1)   // Mettre 1 à la position 1 pour l'état du capteur de flamme
#define BIT_LED (1 << 7)    // Mettre 1 à la position 7 pour l'état de led
#define BIT_BUZZER (1 << 6) // Mettre 1 à la position 6 pour l'état du buzzer
// Déclaration de l'état de tous les capteurs à 0
uint8_t bitVar = 0x00; // Tous les bits sont à 0

void setup()
{
  // Configuration des broches
  pinMode(SOUND_SENSOR, INPUT);
  pinMode(FLAM_SENSOR, INPUT);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
}

void loop()
{
  // Si le son est détecter mettre le bit à 1 et 0 si le son n'Est pas détecté
  digitalRead(SOUND_SENSOR) ? bitVar |= BIT_SOUND : bitVar &= ~BIT_SOUND;

  // Si une flamme est détecter mettre le bit à 1 et 0 si le son n'Est pas détecté
  digitalRead(FLAM_SENSOR) ? bitVar |= FLAM_SENSOR : bitVar &= ~FLAM_SENSOR;

  // Si le capteur de son détecte un bruit ou le capteur de flamme détecte une flamme on active l'état de du buzzer et de la led puis on allume la led
  if ((bitVar & BIT_SOUND) || (bitVar & BIT_FLAM))
  {
    bitVar = bitVar | BIT_BUZZER | BIT_LED;
    digitalWrite(PIN_LED, HIGH); // LED allumé
    for (int j = 0; j < 5; j++)
    {
      digitalWrite(PIN_BUZZER, HIGH);
      delay(300);
      digitalWrite(PIN_BUZZER, LOW);
      delay(300);
    }
  }
  // Dans le cas où aucun danger n'est pas déterminer on allume pas la led ni le buzzer 
  else
  {
    bitVar = bitVar & ~(BIT_LED | BIT_BUZZER);
    digitalWrite(PIN_LED, LOW);
    digitalWrite(PIN_BUZZER, LOW);
  }
  Serial.print("Etat des bits : ");
  for (int i = 7; i >= 0; i--) {
    // On affiche dans le moniteur série bit à bit en fonction de l'état du capteur détectecté
    Serial.print((bitVar >> i) & 1);
  }
  Serial.println(" ");
  delay(200);
}