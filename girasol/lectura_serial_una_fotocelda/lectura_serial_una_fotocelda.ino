/* Lectura serial una fotocelda
 *  
 *  David Guzmán
 *  14 de julio de 2021
 *  
 *  Creado usando Tinkercad
 *  
 *  Lee valor medido por una fotocelda, y lo emite en puerto serial.
 *  
 *  A mayor iluminación, mayor lectura en el puerto de entrada análogo.
 *  Si desea invertir este comportamiento, puede intercambiar lugares
 *  entre fotocelda y resistencia.
 * 
 *  Conexiones:
 *    5V --- fotocelda ---- R=10kohm --- GND
 *                       |
 *                       ---- A0
 *
 */
int fotocelda = 0;

void setup()
{
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop()
{
  fotocelda = analogRead(A0);
  Serial.println(fotocelda);
  delay(10); // Delay a little bit to improve simulation performance
}
