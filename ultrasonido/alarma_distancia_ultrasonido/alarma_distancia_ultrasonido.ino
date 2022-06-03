/*
 * Alarma de distancia
 * David Guzmán
 * 
 * 13 de julio de 2021
 * 
 * Usando sensor ultrasonido.
 * Usando pantalla OLED I2C
 * 
 * On an arduino UNO:       A4(SDA), A5(SCL)
 * 
 * Conexiones ultrasonido:
 *  D4: VCC
 *  D5: TRIG
 *  D6: ECHO
 *  D7: GND
 * 
 */


//Para OLED
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



const int trigPin = 5;
const int echoPin = 6;

const int chicharraPin = 12;
const int ledPin = 13;

float UMBRAL_CM = 100; //1 metro

bool pantalla_ok = true;



 
void setup() {
  //Salidas
  pinMode(trigPin, OUTPUT); //pin trig de sensor ultrasonido
  pinMode(7, OUTPUT); //pin gnd de sensor ultrasonido
  pinMode(4, OUTPUT); //pin vcc de sensor ultrasonido
  digitalWrite(7, LOW); //asigno 0V
  digitalWrite(4, HIGH); //asigno 5V

  pinMode(chicharraPin, OUTPUT); //pin chicharra
  pinMode(ledPin, OUTPUT); //pin chicharra
  digitalWrite(chicharraPin, LOW); //asigno 0V por defecto
  digitalWrite(ledPin, LOW); //asigno 0V por defecto
  

  //Entradas
  pinMode(echoPin, INPUT);  //pin echo de sensor ultrasonido

  //Config serial
  Serial.begin(9600);
   Serial.println("distancia (cm)");

   //Config OLED
   // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("No ubico pantalla OLED"));
    pantalla_ok = false;  //registrar el error en pantalla
  }
}

void loop() {
  unsigned long tiempo_eco;
  float distancia_en_cm=0;

  //se envía pulso de 10 microsegundos en pin trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  tiempo_eco = pulseIn(echoPin, HIGH); //mide tiempo desde emisión hasta recepción, en microsegundos

  distancia_en_cm = tiempo_eco*0.034/2; //0.034cm/s es la velocidad del sonido en el aire. Se divide por 2 porque la señal va y vuelve.
  
  Serial.println(distancia_en_cm);
  

  if (distancia_en_cm < UMBRAL_CM) {
    //ALARMA!!
    //Encender LED
    digitalWrite(ledPin, HIGH);

    //Enceder chicharra
    
  }
  else {
    //Apagar LED
    digitalWrite(ledPin, LOW);

    //Apagar chicharra
  }

  if (pantalla_ok){ //solo si conectó con pantalla
    display.clearDisplay(); //limpio
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setCursor(0, 0);
//    display.print(F("d="));
//    display.print(distancia_en_cm,0); //redondeo a 0 decimales
//    display.println(F("cm"));

    //barra horizontal de distancia
    display.setTextSize(2);    
    if (distancia_en_cm < UMBRAL_CM*0.25) {
      //display.print(F("|"));
      display.print(F("ALERTA MAX"));
    }
    else if (distancia_en_cm < UMBRAL_CM*0.5) {
      //display.print(F("|"));
      display.print(F("ALERTA ALT"));
    }
    else if (distancia_en_cm < UMBRAL_CM*0.75) {
      //display.print(F("|"));
      display.print(F("  ALERTA"));
    }
    else if (distancia_en_cm < UMBRAL_CM*1.0) {
      //display.print(F("|"));
      display.print(F("  alerta"));
    }
    else if (distancia_en_cm < UMBRAL_CM*1.25) {
      //display.print(F("|"));
      display.print(F("   bien"));
    }
    else if (distancia_en_cm < UMBRAL_CM*1.5) {
      //display.print(F("|"));
      display.print(F("    ok"));
    }
    else if (distancia_en_cm < UMBRAL_CM*1.75) {
      //display.print(F("|"));
    }
    else{
      //display.print(F("|"));
    }

    
    if (distancia_en_cm < 300)
    {
        //imprime la distancia si es menor a 3m; de lo contrario es medida basura o ignorar
        display.setCursor(50, 16);
        display.setTextSize(2);
        display.print(distancia_en_cm,0); //redondeo a 0 decimales
        display.println(F("cm"));
    }
    
    display.display();  //muestro
    
  }
  
  
  delay(1000);
}
