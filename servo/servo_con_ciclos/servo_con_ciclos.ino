// C++ code
//
/*
  Servomotor con ciclos

  Ejemplo de servomotor girando a 0° a 180° en
  pasos de 5°. Al llegar a 180°, vuelve a 0°.
  Creado en Tinkercad.

  David Guzmán.
  Bogotá, Colombia.
  Junio de 2022

  Conexiones:
    Servomotor     Arduino
      café     --    GND
      rojo     --    5V
      naranja  --    D9
*/

#include <Servo.h>

int angulo = 0;

Servo servo_9;

int counter;

void setup()
{
  servo_9.attach(9, 500, 2500);
}

void loop()
{
  angulo = 0;
  for (counter = 0; counter < 36; ++counter) {
    // incrementando 5°
    angulo += 5;
    servo_9.write(angulo);
    delay(200); // Wait for 200 millisecond(s)
  }
  delay(1000); // Wait for 1000 millisecond(s)
}