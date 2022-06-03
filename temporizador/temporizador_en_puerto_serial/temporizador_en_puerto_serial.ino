/*
 * Temporizador en puerto serial
 * (luego se hará en pantalla OLED)
 * 
 * David Guzmán
 * 14 de julio de 2021
 * 
 * Usa potenciómetro para ajustar el tiempo deseado.
 * 5V --> 10minutos
 * 0V --> 0minutos
 * 
 * Usa botón para dar inicio/fin a temporizador.
 * 
 */

int boton_inicio = 0;
int boton_fin = 0;
int valor_pot = 0;
float voltaje_pot = 0;
float tiempo_deseado_seg = 0; //debe ser float para que pueda dividir sin problema
float tiempo_deseado_min = 0;
unsigned long tiempo_deseado_miliseg = 0; //debe ser unsigned long para comparar con tiempos de millis()

unsigned long hora_actual_miliseg = 0; //debe ser unsigned long para usar con millis()
unsigned long hora_actual_desde_inicio_miliseg = 0; //debe ser unsigned long para usar con millis()
unsigned long hora_inicio_miliseg = 0; //debe ser unsigned long para usar con millis()
unsigned long hora_fin_miliseg = 0; //debe ser unsigned long para usar con millis()

unsigned long conteo_regresivo_miliseg = 0; //debe ser unsigned long para usar con millis()
float conteo_regresivo_seg = 0; //debe ser unsigned long para usar con millis()

float hora_actual_desde_inicio_seg = 0;

bool contando = false;

void setup()
{
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
  
  pinMode(6, INPUT);

  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  
  pinMode(3, INPUT);

  
  Serial.begin(9600);

  pinMode(A0, INPUT);
}

void loop()
{
  //lecturas de entradas
  boton_inicio = digitalRead(6);
  boton_fin = digitalRead(3);
  valor_pot = analogRead(A0);


  //si oprime botón, lee hora de inicio
  if (boton_inicio == 1) {
    Serial.println("oprime boton");
    hora_inicio_miliseg = millis();
    contando = true; //activa contador
  }

  //si oprime botón, lee hora de inicio
  if (boton_fin == 1) {
    Serial.println("oprime boton");
    contando = false; //desactiva contador
  }



  //lee hora actual
  hora_actual_desde_inicio_miliseg = millis() - hora_inicio_miliseg;
  hora_actual_desde_inicio_seg = float(hora_actual_desde_inicio_miliseg) / 1000; //float para poder dividir

  //determina tiempo deseado leyendo potenciómetro
  voltaje_pot = (float(valor_pot)*5)/1024; //¡importante cambiar a float!
  tiempo_deseado_min = voltaje_pot * 2; //5V son 10 minutos
  tiempo_deseado_seg = tiempo_deseado_min * 60;
  tiempo_deseado_miliseg = tiempo_deseado_seg * 1000;

  //calcula hora fin
  //hora_fin_miliseg = hora_fin_miliseg;

  if (contando){
    //conteo_regresivo_miliseg = tiempo_deseado_miliseg - hora_actual_desde_inicio_miliseg;
    conteo_regresivo_seg = float(tiempo_deseado_miliseg - hora_actual_desde_inicio_miliseg)/1000;
  }
  
  //actualizar pantalla y/o puerto serial
  if (millis() % 500 == 0){
    //cada 0.5 segundos
    //Serial.print("valor anAlogo es ");
    Serial.print("A0:");
    Serial.print(valor_pot);

//    Serial.print(" V0:");
//    Serial.print(voltaje_pot);

//    Serial.print(" tm:");
//    Serial.print(tiempo_deseado_min);

    //Serial.print(", tiempo deseado (s): ");
    Serial.print(" D:");
    Serial.print(tiempo_deseado_seg);

    //Serial.print("Hora desde inicio: ");
    Serial.print(" H:");
    Serial.print(hora_actual_desde_inicio_seg);

    Serial.print(" Q: ");
    Serial.println(conteo_regresivo_seg);

    //Deseado: (fijo)
    //Actual cuenta regresiva
    //Contado S/N
    
  }
  

  //delay(1000); // Wait for 1000 millisecond(s)
}
