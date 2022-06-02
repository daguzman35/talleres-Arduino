/*
 * Semáforo doble RGB en proto
 * David Guzmán
 * 12 de julio de 2021
 * 
 * Código generado usando TinkerCad.
 * 
 * 
 */
void setup()
{
  pinMode(6, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop()
{
  analogWrite(6, 255);
  analogWrite(3, 0);
  analogWrite(5, 0);
  analogWrite(11, 51);
  analogWrite(9, 255);
  analogWrite(10, 51);
  delay(3000); // Wait for 3000 millisecond(s)
  analogWrite(6, 255);
  analogWrite(3, 0);
  analogWrite(5, 0);
  analogWrite(11, 255);
  analogWrite(9, 255);
  analogWrite(10, 0);
  delay(1000); // Wait for 1000 millisecond(s)
  analogWrite(6, 255);
  analogWrite(3, 255);
  analogWrite(5, 0);
  analogWrite(11, 255);
  analogWrite(9, 0);
  analogWrite(10, 0);
  delay(1000); // Wait for 1000 millisecond(s)
  analogWrite(6, 51);
  analogWrite(3, 255);
  analogWrite(5, 51);
  analogWrite(11, 255);
  analogWrite(9, 0);
  analogWrite(10, 0);
  delay(3000); // Wait for 3000 millisecond(s)
  analogWrite(6, 255);
  analogWrite(3, 255);
  analogWrite(5, 0);
  analogWrite(11, 255);
  analogWrite(9, 0);
  analogWrite(10, 0);
  delay(1000); // Wait for 1000 millisecond(s)
  analogWrite(6, 255);
  analogWrite(3, 0);
  analogWrite(5, 0);
  analogWrite(11, 255);
  analogWrite(9, 255);
  analogWrite(10, 0);
  delay(1000); // Wait for 1000 millisecond(s)
}
