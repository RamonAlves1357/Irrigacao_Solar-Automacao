/**
 * Autor: Ramon Alves P. de Souza
 * Data: 29/09/2021
 * 
*/

#include <Arduino.h>

// Declaração dos pinos
#define pinSensorUmidadeA A0 // Pino Analogico do SENSOR DE UMIDADE DO SOLO (Higrômetro)
#define pinSensorUmidadeD 8  // Pino Digital do SENSOR DE UMIDADE DO SOLO (Higrômetro)
#define pinRele 3            // Pino do RELE (Solenoide)
#define pinSensorNivel 2     // Pino Digital do SENSOR DE UMIDADE DO SOLO (Nivel d'agua)

// Declaração de variaveis
int cont = 0, umidade, nivel;

// analogRead(pinSensorUmidadeA) > 700 = Seco
// analogRead(pinSensorUmidadeA) < 400 = Molhado

void setup()
{
  // Setup Pinos
  pinMode(pinRele, OUTPUT);          // Valvula Solenoide
  pinMode(pinSensorUmidadeA, INPUT); // Sensor de Umidade Analogico
  pinMode(pinSensorUmidadeD, INPUT); // Sensor de Umidade Digital

  // Inicios
  Serial.begin(2400);
  //digitalWrite(pinRele, LOW);
}

void sensorUmidade()
{
  Serial.print("Medindo Umidade: ");
  Serial.print(analogRead(pinSensorUmidadeA));
  Serial.print("  |  ");

  if (analogRead(pinSensorUmidadeA) > 500)
  {
    Serial.println("Está seco!");
    umidade = 0;

    //return 0;
  }
  else if (analogRead(pinSensorUmidadeA) > 300 && analogRead(pinSensorUmidadeA) < 501)
  {
    Serial.println("Está molhado!");
    umidade = 1;

    //return 1;
  }
  else
  {
    Serial.println("Muita agua!");
    umidade = 1;

    //return 2;
  }
}

void sensorNivel()
{
  Serial.print("Nivel d'agua: ");
  Serial.print(analogRead(pinSensorNivel));
  Serial.print("  |  ");

  if (analogRead(pinSensorUmidadeA) > 500)
  {
    Serial.println("Acabou a agua. Não regar!");
    nivel = 0;

    //return 0;
  }
  else
  {
    Serial.println("Ainda tem agua. Pode regar!");
    nivel = 1;

    //return 1;
  }
}

void Ligar_Valvula(byte pino)
{
  //Serial.println(" Solenoide LIGADO; ");
  digitalWrite(pino, LOW);
}

void Desligar_Valvula(byte pino)
{
  //Serial.println(" Solenoide DESLIGADO; ");
  digitalWrite(pino, HIGH);
}

void loop()
{
  while (umidade == 0 && nivel == 1)
  {
    sensorUmidade();
    sensorNivel();
    Ligar_Valvula(pinRele);
    Serial.print("Status: ");
    Serial.print("  | ");
    Serial.println("Rele LIGADO\n");

    delay(500);
  }

  sensorUmidade();
  sensorNivel();
  delay(500);

  Desligar_Valvula(pinRele);
  Serial.print("Status: ");
  Serial.print("  | ");
  Serial.println("Rele DESLIGADO\n");
}
