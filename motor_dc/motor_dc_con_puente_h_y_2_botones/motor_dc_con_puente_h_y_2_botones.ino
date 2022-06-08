// C++ code
//
/*
  Motor DC con puente H y 2 botones
  David Guzmán
  Bogotá, Colombia
  8 de junio de 2022

  Código desarrollado usando Tinkercad.

  Al presionar uno de los botones de las entradas
  D6 o D7, el motor DC gira a la derecha o a la
  izquierda respectivamente. Las señales emitidas
  por Arduino salen de los pines 12 y 13, quienes
  van hacia un puente H.
*/

void setup()
{
  pinMode(6, INPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(7, INPUT);
}

void loop()
{
  if (digitalRead(6) == HIGH) {
    // girar a la derecha
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
  } else {
    if (digitalRead(7) == HIGH) {
      // girar a la izquierda
      digitalWrite(12, LOW);
      digitalWrite(13, HIGH);
    } else {
      // no girar
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
    }
  }
  delay(10); // Delay a little bit to improve simulation performance
}
