// C++ code
//
/*
  Servomotor básico

  Prueba de servomotor girando a 0°, 45°, 90° y
  180°.
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

Servo servo_9;

void setup()
{
  servo_9.attach(9, 500, 2500);
}

void loop()
{
  servo_9.write(0);
  delay(1000); // Wait for 1000 millisecond(s)
  servo_9.write(45);
  delay(1000); // Wait for 1000 millisecond(s)
  servo_9.write(90);
  delay(1000); // Wait for 1000 millisecond(s)
  servo_9.write(180);
  delay(1000); // Wait for 1000 millisecond(s)
}