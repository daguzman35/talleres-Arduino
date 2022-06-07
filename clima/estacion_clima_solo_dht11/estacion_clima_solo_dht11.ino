/*
 * Estación clima - solo DHT11
 * Creado por: David Guzmán
 * 
 * 13 de julio de 2021
 * Última edición: 2021-07-13
 * 
 * Siguiendo guía de https://learn.adafruit.com/dht
 * 
 * Librería usada: https://github.com/adafruit/DHT-sensor-library
 * 
 * Esta basado en código del ejemplo DHT-->DHTtester; casi idéntico.
 * 
 */

#include "DHT.h"

#define DHTPIN 2     // Digital pin connected to the DHT sensor

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT misensordht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("Prueba solo DHT11"));

  misensordht.begin();  //inicia conexión con sensor dht
}

void loop() {
  delay(2000); //espera 2s
  
  float humedad = misensordht.readHumidity(); //lee humedad de DHT11
  float temp_celsius = misensordht.readTemperature(); //lee temperatura en centígrados de DHT11
  //float temp_fahrenheit = misensordht.readTemperature(true); //lee temperatura en fahrenheit de DHT11

  bool error_en_lectura = (isnan(humedad) || isnan(temp_celsius));
  if (error_en_lectura) {
    Serial.println(F("Error leyendo datos de sensor DHT11"));
    return; //esto termina la ejecución de la función 'loop'
  }

//    // Compute heat index in Fahrenheit (the default)
//  float hif = misensordht.computeHeatIndex(f, h);
//  // Compute heat index in Celsius (isFahreheit = false)
//  float hic = misensordht.computeHeatIndex(t, h, false);

  Serial.print(F("Humedad: "));
  Serial.print(humedad);
  Serial.print(F("%  Temperatura: "));
  Serial.print(temp_celsius);
  Serial.println(F("°C "));
  
}
