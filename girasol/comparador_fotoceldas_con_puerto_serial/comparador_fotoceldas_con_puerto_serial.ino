// C++ code
//
/*
  Comparador de iluminación con 2 fotoceldas
  usando puerto serial

  David Guzmán
  17 de junio de 2022
  Creado usando Tinkercad

  Lee valor medido por 2 fotoceldas. Enciende LED
  de Arduino si la luz vista a la 'derecha' es
  mayor que la de la 'izquierda'. A mayor
  iluminación, mayor lectura en el puerto de
  entrada análogo.

  Si desea invertir este comportamiento, puede
  intercambiar lugares entre fotocelda y
  resistencia.

  En puerto serial se emiten las lecturas de cada
  fotocelda, separadas por coma. Apto para usarse
  con plotter serial o con monitor serial de
  Arduino IDE.
*/

int fotoIzq = 0;

int fotoDer = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(A1, INPUT);
  pinMode(A0, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.print("izquierda");
  Serial.print(",");
  Serial.println("derecha");
}

void loop()
{
  fotoIzq = analogRead(A1);
  fotoDer = analogRead(A0);
  Serial.print(fotoIzq);
  Serial.print(",");
  Serial.println(fotoDer);
  if (fotoIzq < fotoDer) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
  delay(10); // Delay a little bit to improve simulation performance
}
