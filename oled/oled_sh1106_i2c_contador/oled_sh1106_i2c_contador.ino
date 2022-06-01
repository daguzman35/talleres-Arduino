/*  oled_sh1106_i2c_dibuja_contador
 * 
 * Usando pantalla OLED SH1106 I2C 128x64px
 * David Guzmán
 * Junio de 2022
 * 
 * Escribe en pantalla los segundos transcurridos en pantalla OLED.
 * 
 * Basado en ejemplo SH1106_128x64_i2c_QTPY de
 * biblioteca Adafruit SH100X.
 * 
 * Conexiones:
 *    OLED      Arduino UNO
 *    VCC  --   5V
 *    GND  --   GND
 *    SCK  --   A5
 *    SDA  --   A4
 * 
 */
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

/* Uncomment the initialize the I2C address , uncomment only one, If you get a totally blank screen try the other*/
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
//#define i2c_Address 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  delay(250); // wait for the OLED to power up
  display.begin(i2c_Address, true); // Address 0x3C default

  display.clearDisplay(); //limpia contenido de pantalla
  
  display.setTextSize(9); //asigna tamaño de la fuente. Debe ser número entero.
  display.setTextColor(SH110X_WHITE); //color de texto
  
}

int contador=0;  //declaro variable entera

void loop() {  
  contador = contador + 1;
  display.clearDisplay(); //limpia contenido de pantalla
  display.setCursor(0, 0);
  display.print(contador);
  display.display();  //muestra contenido en pantalla. Sin ella, no dibuja.
  delay(1000);

}
