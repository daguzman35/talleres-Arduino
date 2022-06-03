/*
 * Temporizador start/stop en puerto serial
 * David Guzmán
 * 14 de julio de 2021
 * 
 * Uso 2 botones: uno para arranque, otro para parar.
 * 
 * En puerto serial imprimo el tiempo transcurrido, en segundos, desde que inicia.
 * Enciendo LED de tarjeta cuando está contando.
 * 
 */
int contando = 0;

unsigned long tiempo_inicio = 0;
unsigned long tiempo_fin = 0;
unsigned long tiempo_transcurrido = 0;

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

    //e imprimo el valor en puerto serial
    Serial.println(float(tiempo_transcurrido)/1000,1); //importante pasar a float; imprimo 1 decimal
  }
  
  delay(100); // pausa 100ms; prudente, pero no es necesario.
}
