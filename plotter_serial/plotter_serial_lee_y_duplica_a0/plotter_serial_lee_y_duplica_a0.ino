// C++ code
//
/*
  Basado en ejemplo AnalogReadSerial
  Editado por David Guzmán, junio de 2022.

  Para usar con plotter serial, graficando valor
  leído y su doble.

  Reads an analog input (potentiometer) on pin 0,
  prints the result to the serial monitor.

  Attach the center pin of a potentiometer to pin
  A0, and the outside pins to +5V and ground.

*/

int sensorValue = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT);

  Serial.println("sencillo,doble"); //encabezados (leyendas) de plotter serial
}

void loop()
{
  // read the input on analog pin 0:
  sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.print(sensorValue);
  Serial.print(",");  //columnas separadas por coma
  Serial.println((sensorValue * 2));  //última columna con salto de línea: println
  delay(500); // Wait for 500 millisecond(s)
}
