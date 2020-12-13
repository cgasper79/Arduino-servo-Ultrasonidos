//Robot decision trayecto con placa motores L298N

#include <Servo.h>

Servo servo1;

const int Trigger = 2;   //Pin digital 2 para el Trigger del sensor principal
const int Echo = 3;   //Pin digital 3 para el Echo del sensor principal

// Motor A
int ENA = 11;  // en el pin 10 no funciona correctamente
int IN1 = 9;
int IN2 = 8;

// Motor B
int ENB = 5;
int IN3 = 7;
int IN4 = 6;

void setup() {
  
  Serial.begin(9600);//iniciailzamos la comunicación
  
  servo1.attach(10); //iniciamos servo en el pin 10

  //Iniciamos pines Ultrasonidos
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0

 // Declaramos todos los pines como salidas L298N
 pinMode (ENA, OUTPUT);
 pinMode (ENB, OUTPUT);
 pinMode (IN1, OUTPUT);
 pinMode (IN2, OUTPUT);
 pinMode (IN3, OUTPUT);
 pinMode (IN4, OUTPUT);
  

}

void loop() {

 long recto;

 recto = medirDistancia();
  
  while (recto > 40) {
    recto = medirDistancia();
    Adelante();
  }
  
  Atras();
  delay(500);  
  
  Parar();
  delay(1000);

  Decidir();
  recto = medirDistancia();
   
  while (recto < 40){
    Decidir(); 
    recto = medirDistancia();
    }
         
}

long medirDistancia(){

  long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros
  
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm

  return d;
  
  delay(100);          //Hacemos una pausa de 100ms
 
}


void Decidir() {
  long derecha;
  long izquierda;
  
  servo1.write(0);  //Mirar derecha
  delay(1000);
  derecha = medirDistancia();
  delay(1000);

  servo1.write(255);  //Mirar izquierda
  delay(1000);
  izquierda = medirDistancia();
  delay(1000);
  
  servo1.write(90); //Mirar recto
  delay(500);

  if (derecha > izquierda) {
    Serial.print("Voy a la derecha ");
    Serial.println();
    Derecha();
    delay(300);
    Parar();
    delay(500);
  }
  else {
    Serial.print("Voy a la Izquierda ");
    Serial.println();
    Izquierda();
    delay(300);
    Parar();
    delay(500);
  }
  
}


void Adelante()
{
 //Direccion motor A
 digitalWrite (IN1, HIGH);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 80); //Velocidad motor A
 
 //Direccion motor B
 digitalWrite (IN3, HIGH);
 digitalWrite (IN4, LOW);
 analogWrite (ENB, 80); //Velocidad motor B
}



void Atras()
{
 //Direccion motor A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, HIGH);
 analogWrite (ENA, 100); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, HIGH);
 analogWrite (ENB, 100); //Velocidad motor B
}


void Derecha()
{
 //Direccion motor A
 digitalWrite (IN1, HIGH);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 150); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, HIGH);
 analogWrite (ENB, 80); //Velocidad motor A
}

void Izquierda()
{
 //Direccion motor A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, HIGH);
 analogWrite (ENA, 80); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, HIGH);
 digitalWrite (IN4, LOW);
 analogWrite (ENB, 150); //Velocidad motor A
}


void Parar()
{
 //Direccion motor A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 0); //Velocidad motor A
 
 //Direccion motor B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, LOW);
 analogWrite (ENB, 0); //Velocidad motor A
}
