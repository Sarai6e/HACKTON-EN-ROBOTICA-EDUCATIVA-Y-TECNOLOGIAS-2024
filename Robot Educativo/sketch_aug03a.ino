#include <SoftwareSerial.h>  // libreria que permite establecer pines digitales
#include <Wire.h>
#include <Servo.h>

// Crea un objeto Servo
Servo myServo;

SoftwareSerial miBT(3, 4);  // pin 3 como RX, pin 4 como TX


int ENA, IN1, IN2, IN3, IN4, ENB;
int ruedaA, ruedaB;
int tavance, tgiro;

char DATO = "0";

void setup() {
//configuraciones

Serial.println("configurando");
Serial.begin(9600);

int opcion = 4; // Cambia esto para probar diferentes configuraciones

  // Configuración de acuerdo a la opción seleccionada
  switch (opcion) {
    case 1:
      // PALA + SUMO
      // 98:03:02:96:81:53
      // 98:D3:02:96:73:8F
      ENA = 8;
      IN1 = 9;
      IN2 = 10;
      IN3 = 7;
      IN4 = 6;
      ENB = 5;
     
      ruedaA = 50;
      ruedaB = 60;
      
      tavance = 100;  // Ejemplo de valor para tavance
      tgiro = 50;     // Ejemplo de valor para tgiro
    
      break;

    case 2:
      // Soccer
      // 00:22:06:01:63:DA
      ENA = 8;
      IN1 = 9;
      IN2 = 12;
      IN3 = 7;
      IN4 = 6;
      ENB = 5;
      ruedaA = 70;
      ruedaB = 80;
      
      tavance = 120;  // Ejemplo de valor para tavance
      tgiro = 60;     // Ejemplo de valor para tgiro

      break;
     case 3:
      // Pala reparadD
      // 98:D3:02:96:81:98
      ENA = 8;
      IN1 = 9;
      IN2 = 13;
      IN3 = 7;
      IN4 = 6;
      ENB = 5;
      ruedaA = 90;
      ruedaB = 100;
      tavance = 140;  // Ejemplo de valor para tavance
      tgiro = 70;     // Ejemplo de valor para tgiro
      
      break;
      
    case 4:
      //PALA AMARILLA
      // 98:D3:02:96:C3:12
      // colocar los mismo tipos de motores para mejorar
      
      ENA = 8;  
      IN1 = 9;
      IN2 = 10;
      IN3 = 7;
      IN4 = 5;
      ENB = 6;
      
      ruedaA = 180;
      ruedaB = 255;
      
      tavance = 70;  // Ejemplo de valor para tavance
      tgiro = 30;     // Ejemplo de valor para tgiro
      
      break;
   
       case 5:
      //PALA NARANJA
      // 98:D3:11:FC:34:1D
      // colocar los mismo tipos de motores para mejorar
      
      ENA = 8;
      IN1 = 9;
      IN2 = 12;
      IN3 = 7;
      IN4 = 6;
      ENB = 5;
      
      ruedaA = 250;
      ruedaB = 190;
      
      tavance = 100;  // Ejemplo de valor para tavance
      tgiro = 30;     // Ejemplo de valor para tgiro
      
      break;

       case 6:
      //PALA ROJA
      // 98:D3:41:FD:68:C7
      // colocar los mismo tipos de motores para mejorar
      
      ENA = 8;
      IN1 = 9;
      IN2 = 10;
      IN3 = 7;
      IN4 = 5;
      ENB = 6;
      
      ruedaA = 160;
      ruedaB = 250;
      
      tavance = 80;  // Ejemplo de valor para tavance
      tgiro = 30;     // Ejemplo de valor para tgiro
      
      break;
    default:
      // General
      ENA = 8;
      IN1 = 9;
      IN2 = 10;
      IN3 = 7;
      IN4 = 6;
      ENB = 5;
      ruedaA = 110;
      ruedaB = 120;
      tavance = 160;  // Ejemplo de valor para tavance
      tgiro = 80;     // Ejemplo de valor para tgiro

      break;
  }
  

//configuracion PUENTE H
pinMode(IN1,OUTPUT);
pinMode(IN2,OUTPUT);
pinMode(ENA,OUTPUT);

pinMode(IN3,OUTPUT);
pinMode(IN4,OUTPUT);
pinMode(ENB,OUTPUT);

//configuracion servo
myServo.attach(11);
moveServo(0);


// Configuración del nombre del dispositivo Bluetooth
  miBT.begin(9600);
  miBT.print("AT+NAME=KingBot\r\n");
  delay(100);
  miBT.print("AT+RESET\r\n");
  delay(1000);
  
}



void loop() {



if (miBT.available()){      // si hay informacion disponible desde modulo
  DATO = miBT.read();   // almacena en DATO el caracter recibido desde modulo
  
if(DATO=='A')
{
    Serial.println("* Hacia Adelante *");
    movimientos();
        
    analogWrite(ENA,ruedaA); 
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    
    //adelante motor2
    
    analogWrite(ENB,ruedaB); 
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    
    delay(tavance);
    detener();

}


if(DATO=='B')
{
  Serial.println("* Giro Izquierda // 1 rueda*");
  movimientos();
    
  analogWrite(ENB,ruedaB); 
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);

  delay(tgiro*2);
    
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);  

}


if(DATO=='C')
  {
     Serial.println("* Detener *");
     movimientos();
     detener();
 }

if(DATO=='D')
{
    Serial.println("* Giro Derecha // 1 rueda*");
    movimientos();
    
    analogWrite(ENA,ruedaA); 
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);

    delay(tgiro*2);
    
    digitalWrite(ENA,LOW);
    digitalWrite(ENB,LOW);  
  
}

if(DATO=='E')
{
 Serial.println("* Hacia Atras *");
 movimientos();
    
  detener();
  
  delay(50);
  
  analogWrite(ENA,ruedaA); 
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  
  analogWrite(ENB,ruedaB); 
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  
  delay(tavance);
  detener();  
}


if(DATO=='F')
{

  

}

if(DATO=='G')
{
 
}
if(DATO=='H')
{

}

if(DATO=='I')
{
  
}
if(DATO=='J')
{
//Y

 Serial.println("Giro hacia Izquierda // 2 ruedas");
    movimientos();
           
    analogWrite(ENA,ruedaA);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    
    //adelante motor2
    
    analogWrite(ENB,ruedaB); 
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    
    //duracion del movimiento
    delay(tgiro);
    detener();
  
}
if(DATO=='K')
{
//A

 Serial.println("Giro hacia Derecha // 2 ruedas");
    movimientos();
           
    analogWrite(ENA,ruedaA);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    
    //adelante motor2
    
    analogWrite(ENB,ruedaB); 
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    
    //duracion del movimiento
    delay(tgiro);
    detener();
 
}

if(DATO=='L')
{
// B
 moveServo(0);
}
if(DATO=='M')
{
 
}
if(DATO=='N')
{
 
}
if(DATO=='O')
{

}
if(DATO=='P')
{
  //X
 moveServo(120);
  
}

}

 

 





  
}

void movimientos()
{
  //   Serial.print(" fuerza:");
  

}

void detener()
{
 
digitalWrite(ENA,LOW);
digitalWrite(ENB,LOW); 
digitalWrite(IN3,LOW);
digitalWrite(IN4,LOW);
digitalWrite(IN1,LOW);
digitalWrite(IN2,LOW);
  }

  void moveServo(int degrees) {
  // Ajusta el ángulo del servo
  myServo.write(degrees);
}
