/*
 * Dispensador ultrasonido servomotor
 * David Guzmán
 * 14 de juliio de 2021
 * 
 * Código creado y simulado usando TinkerCad.
 * 
 * Uso sensor ultrasonido HC-SR04
 * Uso servomotor 
 * 
 * Conexiones:
 *  D3: servomotor, señal PWM
 *  D4: pulsador (no usado)
 *  D5: ultrasonido, echo
 *  D6: ultrasonido, trig
 *  
 *  D8: TIERRA (ultrasonido)
 *  D9: 5V (ultrasonido)
 *  
 *  D13: LED indicador cercanía
 * 
 */
#include <Servo.h>

int girar_motor = 0;

int distancia_cm = 0;

int boton_presionado = 0;

int dispensado = 0;

//cuando medida este por debajo de umbral cerca, mover; permitir nuevo movimiento cuando se supere umbral lejos.
int UMBRAL_CERCA_CM = 20;
int UMBRAL_LEJOS_CM = 30;

Servo servo_3;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{


  pinMode(4, INPUT);  //boton
  pinMode(13, OUTPUT);  //led

  //D8: TIERRA (ultrasonido)
  //D9: 5V (ultrasonido)
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(8,LOW);
  digitalWrite(9,HIGH);

  //Configura serial, para pruebas
  Serial.begin(9600);

  //hago lectura inicial de distncia
  delay(500); //espero un rato a que ultrasonido se active antes de hacer la primera medida
  distancia_cm = 0.01723 * readUltrasonicDistance(6, 5);
  
  //imprimo en serial la distancia, para pruebas
  Serial.print("D0:");
  Serial.println(distancia_cm);
}

void loop()
{
  //No es necesario estar midiendo constantemente. Cada 0.5s está bien.
  delay(500);

  //Mido señal de ultrasonido
  distancia_cm = 0.01723 * readUltrasonicDistance(6, 5);

  //imprimo en serial la distancia, para pruebas
  Serial.println(distancia_cm);

  
  //boton_presionado = digitalRead(4);
  if (distancia_cm < UMBRAL_CERCA_CM) {
    if (dispensado == LOW) {
      // si no ha dispensado, dispensar (i.e. mover motor
      // por 1s y volver)
      digitalWrite(13, HIGH);

      servo_3.attach(3, 500, 2500); //solo conectarlo si voy a moverlo
      delay(1000); // Wait for 1000 millisecond(s)
      //servo_3.write(90); //mejor iniciarlo en 0
      
      servo_3.write(50);  //muevo para dispensar
      delay(1000); // Wait for 1000 millisecond(s)
      // importante llevar registro si ya dispensó o no
      dispensado = HIGH;
      servo_3.write(0); //muevo para dejar de dispensar

      servo_3.detach(); //mejor desconectarlo si no voy a moverlo
      delay(1000); // Wait for 1000 millisecond(s)
    }
    // si está cerca, pero ya dispensó, no dispensar de
    // nuevo
  } else {
    if (distancia_cm > UMBRAL_LEJOS_CM) {
      // si se alejó lo suficiente, limpiar registro de
      // dispensación pasada
      dispensado = LOW;
      digitalWrite(13, LOW);
    }
  }
}
