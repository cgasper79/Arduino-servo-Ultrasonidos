//Robot decision trayecto con placa motores L298N V2
// Se añaden dos sensores de ultrasonidos a cada lado

#include <Servo.h>

Servo servo1;

const int Trigger = 3;   //Pin digital 3 para el Trigger del sensor principal
const int Echo = 4;   //Pin digital 4 para el Echo del sensor principal

const int TriggerDerecha = A3; //Pin digital A3 para el Trigger del sensor Derecha
const int EchoDerecha = A4; // Pin digital A4 para el Echo del sensor Derecha

const int TriggerIzquierda = A1; //Pin digital 1 para el Trigger del sensor Derecha
const int EchoIzquierda = A2; // Pin digital 2 para el Echo del sensor Derecha

// Motor Izquierdo A
int ENA = 11;  // en el pin 10 no funciona correctamente
int IN1 = 9;
int IN2 = 8;

// Motor Derecho B
int ENB = 5;
int IN3 = 7;
int IN4 = 6;

void setup() {
  
  Serial.begin(9600);//iniciailzamos la comunicación
  
  servo1.attach(10); //iniciamos servo en el pin 10

  //Iniciamos pines Ultrasonidos Recto
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0

   //Iniciamos pines Ultrasonidos Derecho
  pinMode(TriggerDerecha, OUTPUT); //pin como salida
  pinMode(EchoDerecha, INPUT);  //pin como entrada
  digitalWrite(TriggerDerecha, LOW);//Inicializamos el pin con 0

 //Iniciamos pines Ultrasonidos Izquierdo
  pinMode(TriggerIzquierda, OUTPUT); //pin como salida
  pinMode(EchoIzquierda, INPUT);  //pin como entrada
  digitalWrite(TriggerIzquierda, LOW);//Inicializamos el pin con 0

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
  long der;
  long izq;
  int obstaculoLateral;

  recto = medirDistancia();
  der = medirDistanciaDerecha();
  izq = medirDistanciaIzquierda();
  
  //Si detecta obstaculo sensor derecha esquiva hacia la izquierda 

  while (der < 30) {
    obstaculoLateral = 1;
    Izquierda(0, random (60,100));
    obstaculoLateral = 0;
    der = medirDistanciaDerecha();
    recto = medirDistancia();
   }  
  
  //Si detecta obstáculo sensor izquierda esquiva hacia la derecha 

  while (izq < 30){
    obstaculoLateral = 1;
    Derecha(random (60,100),0);
    obstaculoLateral = 0;
    izq = medirDistanciaIzquierda();
    recto = medirDistancia();
    
  } 

  //Mientras no hay ostácuos laterales robot hacia adelante y decide si distancia < 30cm
  
  do {
    
    if (recto > 30) {
     Adelante();
     //recto = medirDistancia();
     der = medirDistanciaDerecha();
     izq = medirDistanciaIzquierda();
    
  } else {
     int select = random (1,4);
     delay(1);
     switch (select){
      
      case 1: //decide trayecto una vez
       Serial.println ("Caso 1");
       Decidir(); 
       break;

      case 2: //Media vuelta y decide una vez
       Serial.println ("Caso 2");
       int lado2 = random (1,3);
       delay(1);
       if (lado2 = 1){
        Serial.println ("Izquierda");
        Izquierda(0,80);
        delay (800);
        Decidir();
 
       } else {
        Serial.println ("Derecha");
        Derecha(80,0);
        delay(800);
        Decidir();
       }
       break;

      case 3: //Media vuelta a Izquierda o derecha
       Serial.println ("Caso 3");
       int lado3 = random (1,3);
       delay(1);
       if (lado3 = 1){
        Serial.println ("Izquierda");
        Izquierda(0,80);
        delay (800);
 
       } else {
        Serial.println ("Derecha");
        Derecha(80,0);
        delay(800);
       }
       break;
     }
     
     } 
  
  } while (obstaculoLateral = 0);
  
  delay(1);  

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


long medirDistanciaDerecha(){

  long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros
  
  digitalWrite(TriggerDerecha, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(TriggerDerecha, LOW);
  
  t = pulseIn(EchoDerecha, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm

  return d;
  
  delay(100);          //Hacemos una pausa de 100ms
 
}


long medirDistanciaIzquierda(){

  long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros
  
  digitalWrite(TriggerIzquierda, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(TriggerIzquierda, LOW);
  
  t = pulseIn(EchoIzquierda, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm

  return d;
  
  delay(100);          //Hacemos una pausa de 100ms
 
}



void Decidir() {
  long derecha;
  long izquierda;

  Atras();
  delay(200);  
  Parar();
  
  servo1.write(10);  //Mirar derecha
  delay(1000);
  derecha = medirDistancia();

  servo1.write(255);  //Mirar izquierda
  delay(1000);
  izquierda = medirDistancia();
  
  
  servo1.write(95); //Mirar recto
  

  if (derecha > izquierda) {
    Derecha(80,70);
    delay(500);
    Parar();
    delay(500);
  }
  else {
    Izquierda(70,80);
    delay(500);
    Parar();
    delay(500);
  }
  
}


void Adelante()
{
 //Direccion motor Izquierdo A
 digitalWrite (IN1, HIGH);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 80); //Velocidad motor A *
 
 //Direccion motor Derecho B
 digitalWrite (IN3, HIGH);
 digitalWrite (IN4, LOW);
 analogWrite (ENB, 90); //Velocidad motor B
}



void Atras()
{
 //Direccion motor Izquierdo A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, HIGH);
 analogWrite (ENA, 80); //Velocidad motor A
 //Direccion motor Derecho B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, HIGH);
 analogWrite (ENB, 80); //Velocidad motor B
}



int Derecha(int velA, int velB)
{
 //Direccion Izquierdo A
 digitalWrite (IN1, HIGH);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, velA); //Velocidad motor A
 //Direccion Derecho B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, HIGH);
 analogWrite (ENB, velB); //Velocidad motor A
}



int Izquierda(int velA, int velB)
{
 //Direccion motor Izquierdo A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, HIGH);
 analogWrite (ENA, velA); //Velocidad motor A
 //Direccion motor Derecho B
 digitalWrite (IN3, HIGH);
 digitalWrite (IN4, LOW);
 analogWrite (ENB, velB); //Velocidad motor A
}

void Parar()
{
 //Direccion motor Izquierdo A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 0); //Velocidad motor A
 
 //Direccion motor Derecho B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, LOW);
 analogWrite (ENB, 0); //Velocidad motor A
}
