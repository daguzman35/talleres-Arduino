/*
 * Temporizador start/stop en pantalla OLED
 * David Guzmán
 * 14 de julio de 2021
 * 
 * Basado en temporizador_start_stop_puerto_serial, agregando ahora pantalla OLED.
 * 
 * Uso 2 botones: uno para arranque, otro para parar.
 * 
 * En puerto serial imprimo el tiempo transcurrido, en segundos, desde que inicia.
 * Enciendo LED de tarjeta cuando está contando.
 * 
 * Para pantalla OLED, uso como base ejemplo ssd1306_128x32_i2c de biblioteca 
 * Adafruit SSD1306.
 * 
 */

//Tomado de 

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

 
int contando = 0;

unsigned long tiempo_inicio = 0;
unsigned long tiempo_fin = 0;
unsigned long tiempo_transcurrido = 0;

bool pantalla_ok = true;

void setup()
{
  //para ayudar conexiones de botones; no es necesario
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW); 
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);

  //Pines de entrada de botones
  pinMode(3, INPUT);
  pinMode(6, INPUT);
  //Pin LED como salida
  pinMode(13, OUTPUT);

  //Configuro puerto serial
  Serial.begin(9600);

  //Configuro pantalla OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Error en OLED: SSD1306 allocation failed"));
    pantalla_ok = false;
    //for(;;); // Don't proceed, loop forever
  }

  if (pantalla_ok){
    display.display();
    delay(2); // Pause for 2 milliseconds
    // Clear the buffer
    display.clearDisplay();  

    display.setTextSize(1);      // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setCursor(0, 0);     // Start at top-left corner
    display.cp437(true);         // Use full 256 char 'Code Page 437' font

    display.println("Temporizador");
    display.println("start/stop");
    display.println("");
    display.println("    DG 2021-07-14");
    display.display();
    
    delay(2000);
    
    display.clearDisplay();  
    display.setTextSize(2);
    display.setCursor(0, 0);     // Start at top-left corner
    display.println("0"); //imprime el número 0
    display.println(" 00:00.000"); //imprime el número 0
    display.display();
  }
  
}

void loop()
{
  int bot_start = digitalRead(3);
  int bot_stop = digitalRead(6);
  if (bot_start == 1) {
    contando = 1;
    digitalWrite(13, HIGH);
    //Serial.println("on");
    tiempo_inicio = millis();
  }
  if (bot_stop == 1) {
    contando = 0;
    digitalWrite(13, LOW);
    //Serial.println("off");
    tiempo_fin = millis();
  }

  if(contando) {
    //si está contando, calculo tiempo transcurrido
    tiempo_transcurrido = millis() - tiempo_inicio;

    float tiempo_transcurrido_seg = float(tiempo_transcurrido)/1000;

    
    int tiempo_transcurrido_mm = int(tiempo_transcurrido_seg / 60);
    int tiempo_transcurrido_ss = int(tiempo_transcurrido_seg) % 60;
    int tiempo_transcurrido_ssss = int(tiempo_transcurrido % 1000);

    //e imprimo el valor en puerto serial
    Serial.println(tiempo_transcurrido_seg,1); //importante pasar a float; imprimo 1 decimal

    if(pantalla_ok){
      display.clearDisplay();  

      display.setTextSize(2);
      display.setCursor(0, 0);     // Start at top-left corner
      display.println(tiempo_transcurrido_seg);
      if (tiempo_transcurrido_mm<100){
        display.print(" "); //imprimir un espacio a la izquierda
      }
      if (tiempo_transcurrido_mm<10){
        display.print("0"); //imprimir otro 0 a la izquierda
      }
      display.print(tiempo_transcurrido_mm);
      display.print(":");
      if (tiempo_transcurrido_ss<10){
        display.print("0"); //imprimir un 0 a la izquierda
      }
      display.print(tiempo_transcurrido_ss);
      display.print(".");
      if (tiempo_transcurrido_ssss<100){
        display.print("0"); //imprimir un 0 a la izquierda
      }
      if (tiempo_transcurrido_ssss<10){
        display.print("0"); //imprimir otro 0 a la izquierda
      }
      display.print(tiempo_transcurrido_ssss);
      display.display();
    }
  }
  
  delay(100); // pausa 100ms; prudente, pero no es necesario.
}
