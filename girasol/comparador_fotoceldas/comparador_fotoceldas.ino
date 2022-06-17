/* Comparador de iluminación con 2 fotoceldas
 *  
 *  David Guzmán
 *  14 de julio de 2021
 *  
 *  Creado usando Tinkercad
 *  
 *  Lee valor medido por 2 fotoceldas. Enciende LED de Arduino si la 
 *  luz vista a la 'derecha' es mayor que la de la 'izquierda'.
 *  
 *  A mayor iluminación, mayor lectura en el puerto de entrada análogo.
 *  Si desea invertir este comportamiento, puede intercambiar lugares
 *  entre fotocelda y resistencia.
 * 
 *  Conexiones:
 *  
 * Fotocelda derecha:
 *    5V --- fotocelda ---- R=10kohm --- GND
 *                       |
 *                       ---- A0
 *  
 *  Fotocelda izquierda:
 *    5V --- fotocelda ---- R=10kohm --- GND
 *                       |
 *                       ---- A1
 *
 */
int fotoIzq = 0;

int fotoDer = 0;

void setup()
{
  pinMode(A1, INPUT);
  pinMode(A0, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  fotoIzq = analogRead(A1);
  fotoDer = analogRead(A0);
  if (fotoIzq < fotoDer) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
  delay(10); // Delay a little bit to improve simulation performance
}
