/*
 * Piano digital
 * David Guzmán
 * 13 de julio de 2021
 * 
 * Basado en ejemplos toneKeyboard y CapacitiveSensorSketch.
 * 
 * Toca notas musicales Do,Re,Mi,Fa,Sol,La,Si usando 3 botones
 * pulsadores, y 4 botones tactiles (capacitivos).
 *
 * Usa la biblioteca 'CapacitiveSensor'
 * https://reference.arduino.cc/reference/en/libraries/capacitivesensor/
 *
 * Conexiones:
	Entradas	
	Pulsadores:
		A0:		Do (262Hz)
		A1:		Re (294Hz)
		A2:		Mi (330Hz)
	Capacitivos:
		D2:		Fa (350Hz)
		D6:		Sol (392Hz)
		D7:		La (440Hz)
		D10:	Si (494Hz)
		
	Salida
		D12:	chicharra (buzzer).

*/

int pos = 0;

//para salida de audio
int PIN_CHICHARRA = 12;

//para entradas capacitivas
int PIN_CAP_COMUN = 4;
int PIN_CAP_A = 2;  //es mejor que no sean consecutivas
int PIN_CAP_B = 6;
int PIN_CAP_C = 7;
int PIN_CAP_D = 10;

//umbrales para activar las notas, esto se debe escoger midiendo.
//depende de las resistencias usadas, de los pines, y del mecanismo
//además de la alimentación.
int UMBRAL_A = 40;
int UMBRAL_B = 70;
int UMBRAL_C = 70;
int UMBRAL_D = 50;

//Notas a tocar (frecuencias)
unsigned int NOTA_BOT_A0 = 262; //Do
unsigned int NOTA_BOT_A1 = 294; //Re
unsigned int NOTA_BOT_A2 = 330; //Mi
unsigned int NOTA_CAP_A = 350;  //Fa
unsigned int NOTA_CAP_B = 392;  //Sol
unsigned int NOTA_CAP_C = 440;  //La
unsigned int NOTA_CAP_D = 494;  //Si


#include <CapacitiveSensor.h>

//definición botones capacitivos, usando pines digitales 2,3,4,5,6
CapacitiveSensor   cs_A = CapacitiveSensor(PIN_CAP_COMUN,PIN_CAP_A);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_B = CapacitiveSensor(PIN_CAP_COMUN,PIN_CAP_B);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil
CapacitiveSensor   cs_C = CapacitiveSensor(PIN_CAP_COMUN,PIN_CAP_C);
CapacitiveSensor   cs_D = CapacitiveSensor(PIN_CAP_COMUN,PIN_CAP_D);
//CapacitiveSensor   cs_4_8 = CapacitiveSensor(4,8);        // 10M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil

void setup()
{
  //salida audio
  pinMode(PIN_CHICHARRA, OUTPUT);

  //entradas de botones pulsadores
  pinMode(A0, INPUT);  
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  
  //cofngiurar serial
  Serial.begin(9600);
}

void loop()
{

  //Lecturas pines capacitivos
  long teclado_cap_a = cs_A.capacitiveSensor(30);
  long teclado_cap_b = cs_B.capacitiveSensor(30);
  long teclado_cap_c = cs_C.capacitiveSensor(30);
  long teclado_cap_d = cs_D.capacitiveSensor(30);

  //Para calibrar umbrales, se imprimen en puerto serial
  Serial.print(teclado_cap_a);  // imprime lectura sensor capacitivo 1
  Serial.print("\t");
  Serial.print(teclado_cap_b);  // imprime lectura sensor capacitivo 2
  Serial.print("\t");
  Serial.print(teclado_cap_c);  // imprime lectura sensor capacitivo 3
  Serial.print("\t");
  Serial.println(teclado_cap_d);// imprime lectura sensor capacitivo 4

  if (teclado_cap_a > UMBRAL_A) {
    //si supera umbral, tocar nota
    tone(PIN_CHICHARRA, NOTA_CAP_A, 100); //dura 100ms
  }
  if (teclado_cap_b > UMBRAL_B) {
    //si supera umbral, tocar nota
    tone(PIN_CHICHARRA, NOTA_CAP_B, 100); //dura 100ms
  }
  if (teclado_cap_c > UMBRAL_C) {
    //si supera umbral, tocar nota
    tone(PIN_CHICHARRA, NOTA_CAP_C, 100); //dura 100ms
  }
  if (teclado_cap_d > UMBRAL_D) {
    //si supera umbral, tocar nota
    tone(PIN_CHICHARRA, NOTA_CAP_D, 100); //dura 100ms
  }
  
  // si se oprime botón conectado a entrada A0
  if (digitalRead(A0) == HIGH) {
    tone(PIN_CHICHARRA, NOTA_BOT_A0, 100);  //dura 100ms
  }
  // si se oprime botón conectado a entrada A1
  if (digitalRead(A1) == HIGH) {
    tone(PIN_CHICHARRA, NOTA_BOT_A1, 100);  //dura 100ms
  }
  // si se oprime botón conectado a entrada A2
  if (digitalRead(A2) == HIGH) {
    tone(PIN_CHICHARRA, NOTA_BOT_A2, 100);  //dura 100ms
  }
  
}
