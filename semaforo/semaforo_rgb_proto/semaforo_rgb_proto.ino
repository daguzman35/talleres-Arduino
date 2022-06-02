/*
 * Semáforo RGB en proto
 * David Guzmán
 * 12 de julio de 2021
 * 
 * Código generado usando TinkerCad.
 * 
 * Usando LED RGB de cátodo común.
 * 
 */
void setup()
{
  pinMode(6, OUTPUT); //rojo
  pinMode(3, OUTPUT); //verde
  pinMode(5, OUTPUT); //azul
}

void loop()
{
  analogWrite(6, 255);
  analogWrite(3, 0);
  analogWrite(5, 0);
  delay(1000); // Wait for 1000 millisecond(s)
  analogWrite(6, 255);
  analogWrite(3, 204);
  analogWrite(5, 0);
  delay(300); // Wait for 300 millisecond(s)
  analogWrite(6, 51);
  analogWrite(3, 255);
  analogWrite(5, 51);
  delay(1000); // Wait for 1000 millisecond(s)
  analogWrite(6, 255);
  analogWrite(3, 204);
  analogWrite(5, 0);
  delay(300); // Wait for 300 millisecond(s)
}
