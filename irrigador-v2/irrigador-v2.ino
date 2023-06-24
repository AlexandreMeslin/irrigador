/*
 * Sistema de irrigação
 * Pino 6: sempre ligado, usado para testes
 * Pino 7: liga/desliga a bomba
 * LED_BUILTIN: pisca rápido quando a bomba está ligada, pisca mais lento quando a bomba está desligada
 *
 * Versão 1:
 * - temporização usando delay
 * Versão 2:
 * - temporização usando RTC
 *
 * Bibliografia:
 * - https://lastminuteengineers.com/ds1307-rtc-arduino-tutorial/
 */
#include "uRTCLib.h"

// Bomba d'água
#define BOMBA 7

// uRTCLib rtc;
uRTCLib rtc(0x68);

//  Tempo ligado
#define ON_H (0L)
#define ON_M (0L)
#define ON_S (30L)
#define ON ((ON_H * 60L + ON_M) * 60L + ON_S)

//  Tempo desligado (na verdade, deveria ser tempo do ciclo)
#define OFF_H (24L)
#define OFF_M (0L)
#define OFF_S (0L)
#define OFF ((OFF_H * 60L + OFF_M) * 60L + OFF_S - ON)

//#define TX_LED 1

bool statusBomba;
unsigned long int tempoInicial;

void setup() {
  Serial.begin(9600);
  delay(3000); // wait for console opening

  URTCLIB_WIRE.begin();

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BOMBA, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);

  statusBomba = false;  // a bomba inicialmente está desligada
  tempoInicial = millis();  // tempo inicial quando a bomba foi ligada
}

void loop() {
  rtc.refresh();

  if(statusBomba) {
    digitalWrite(BOMBA, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000L);                     // wait for a while
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(3000L);                     // wait for a while    

    unsigned long int tempoAtual = millis();
    if(tempoAtual - tempoInicial > ON * 1000) {
      Serial.print("Acabou o tempo: "); Serial.print(tempoAtual); Serial.print(" - "); Serial.print(tempoInicial); Serial.print(" > "); Serial.println(ON * 1000);
      // desliga a bomba
      statusBomba = false;
      mostraHorario();
      Serial.println("Desligando a bomba");
      digitalWrite(BOMBA, LOW);
    } else {
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(3000L);                    // wait for a while
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      delay(1000L);                    // wait for a while
    }
  }

  if(!statusBomba && rtc.minute() % 2 == 0 && rtc.second() == 0) {
    // liga a bomba
    mostraHorario();
    Serial.println("Ligando a bomba");
    statusBomba = true;
    tempoInicial = millis();  // tempo inicial quando a bomba foi ligada
  } 
}

void mostraHorario() {
  Serial.print(rtc.hour());
  Serial.print(":");
  Serial.print(rtc.minute());
  Serial.print(":");
  Serial.print(rtc.second());
  Serial.print(" - ");
}