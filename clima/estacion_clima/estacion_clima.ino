/*
 * Estación clima
 * 
 * Creado por: David Guzmán
 * 
 * 13 de julio de 2021
 * Última edición: 2021-07-13
 * 
 * Sensor de humedad y temperatura: DHT11
 * Siguiendo guía de https://learn.adafruit.com/dht
 * Librería usada: https://github.com/adafruit/DHT-sensor-library
 * Esta basado en código del ejemplo DHT-->DHTtester; casi idéntico.
 * 
 * Pantalla OLED
 * 
 * Imprime datos en pantalla, y en puerto serial para serial plotter
 */

//Para DHT
#include "DHT.h"
#define DHTPIN 2     // Digital pin connected to the DHT sensor

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT misensordht(DHTPIN, DHTTYPE);


//Para OLED
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels

//ATENCION!! Cambiar alto a 64, si aplica.
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // si se desea incluir pin reset, incluirlo aquí; si no, dejar en -1
//ATENCION!! Cambiar SCREEN_ADDRESS a 0x3D si es de 128x64
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  Serial.println(F("Estacion clima"));

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Falla pantalla OLED"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(1); // Pausa ultracorta, para que no muestre 'splash'

  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(2); // Tamaño texto
  display.setTextColor(SSD1306_WHITE);
  display.println("Estacion");
  display.println("clima");
  display.setCursor(64,24);
  display.setTextSize(1); // Tamaño texto
  display.println("2021-07-13");
  display.display();
  delay(5000);
  
  //Títulos que saldrán en plotter serial
  Serial.println(F("Humedad(%), Temperatura(°C)"));

  misensordht.begin();  //inicia conexión con sensor dht

  
}

void loop() {
  
  
  float humedad = misensordht.readHumidity(); //lee humedad de DHT11
  float temp_celsius = misensordht.readTemperature(); //lee temperatura en centígrados de DHT11

  bool error_en_lectura = (isnan(humedad) || isnan(temp_celsius));
  if (error_en_lectura) {
    Serial.println(F("Error leyendo datos de sensor DHT11"));
    return; //esto termina la ejecución de la función 'loop'
  }

  //Imprimir datos en formato para plotter serial
  Serial.print(humedad);
  Serial.print(F(","));
  Serial.println(temp_celsius);

  //Imprimir datos en pantalla OLED
  display.clearDisplay(); //limpia pantalla
  display.setTextSize(2);             // Tamaño texto
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0,0); //coordenada donde inicia
  display.print("T:");
  if ((temp_celsius > 0) && (temp_celsius < 10)){
    //si es número entre 0 y 10, poner un espacio adicional
    display.print(" ");  
  }
  display.print(temp_celsius,1); //con 1 decimal
  display.print(" C");
  display.drawCircle(78,3,3,SSD1306_WHITE); //x0=85, y0=4, r=3 (el círculo de grados: °)

  display.setCursor(32,16); //coordenada donde inicia
  display.print("h:");
  display.print(humedad,1); //con 1 decimal
  display.print("%");
  display.display();  //imprime en pantalla

  //delay(2000); //espera 2s
  delay(200); //espera 0.2s
}
