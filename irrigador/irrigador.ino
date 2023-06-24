/*
 * Sistema de irrigação
 * Pino 6: sempre ligado, usado para testes
 * Pino 7: liga/desliga a bomba
 * LED_BUILTIN: pisca rápido quando a bomba está ligada, pisca mais lento quando a bomba está desligada
 */

// Bomba d'água
#define BOMBA 7 

//  Tempo ligado
#define ON_H (0L)
#define ON_M (1L)
#define ON_S (30L)
#define ON ((ON_H * 60L + ON_M) * 60L + ON_S)

//  Tempo desligado (na verdade, deveria ser tempo do ciclo)
#define OFF_H (24L)
#define OFF_M (0L)
#define OFF_S (0L)
#define OFF ((OFF_H * 60L + OFF_M) * 60L + OFF_S - ON)

//#define TX_LED 1

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);
}

void loop() {
  // liga a bomba
  digitalWrite(BOMBA, HIGH);
  for(unsigned long i=0L; i<ON; i++) {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(500L);                     // wait for a while
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      delay(500L);                     // wait for a while    
  }

  // desliga a bomba
  digitalWrite(BOMBA, LOW);
  for(unsigned long i=0L; i<OFF/2L; i++) {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000L);                    // wait for a while
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      delay(1000L);                    // wait for a while
  }
}
