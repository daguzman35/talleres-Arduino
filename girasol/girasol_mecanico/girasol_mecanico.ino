/*
 * Girasol mecánico
 * David Guzmán
 * Creado:        12 de julio de 2021
 * Última edición:12 de julio de 2021
 * 
 * Lee medidas de 2 fotoceldas, y gira el motor buscando máxima iluminación.
 * 
 * Usando motor de pasos.
 * 
 * Entradas:
 *  A0: fotocelda 1
 *  A5: fotocelda 2
 *  
 * Salidas:
 *  D8, D10, D9, D11 = IN1, IN2, IN3, IN4 de motor de pasos.
 *  Usando transistores en ULN2003.
 * 
 * Usando motor de pasos 28BYJ-48, de 5V, 2048 pasos por vuelta.
 * Velocidad máxima recomendada: 1 vuelta/ 4 segundos = 0.25 vueltas/seg.
 * 
 */

#include <Stepper.h>
const int stepsPerRevolution = 2048;

//asignación de pines de fotoceldas
const int fotoUnoPin = A0;
const int fotoDosPin = A5;

int fotoUno = 0;
int fotoDos = 0;

int umbral_diferencia = 30; //la diferencia debe superar este umbral para que haga movimiento

//configurar conexiones de motor de pasos
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  myStepper.setSpeed(10);
  Serial.begin(9600);
  Serial.print("Inicio en ");
  for (int i=5; i>0; i--){
    Serial.print(i);
    Serial.print(",");
    delay(1000);
  }
}

void loop() {
  
  fotoUno = analogRead(fotoUnoPin);
  fotoDos = analogRead(fotoDosPin);

  ////factor de correccion manual, para emparejar diferencias entre fotoceldas
  //fotoUno = fotoUno - 50;

  Serial.print(fotoUno);
  Serial.print(",");
  Serial.print(fotoDos);

  if (fotoUno > (fotoDos + umbral_diferencia) ) 
  {
    //girar a la derecha
    Serial.println(",D");
     myStepper.step(10);
  }
  else if (fotoDos > (fotoUno + umbral_diferencia) ) 
  {
    //girar a la izquierda
    Serial.println(",I");
    myStepper.step(-10);
  }
  else
  {
    //quedarse quieto
    Serial.println(",Q");
  }
  //delay(50);
}
