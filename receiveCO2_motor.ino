#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9,10);
#define ENA 6
const byte address[6] = "00001";
int motor1pin1 = 2;
int motor1pin2 = 3;
void setup() {
   Serial.begin(9600);
   pinMode(motor1pin1,OUTPUT);
   pinMode(motor1pin2,OUTPUT);
  
   radio.begin();
   radio.openReadingPipe(0,address);
   radio.setPALevel(RF24_PA_MIN);
   radio.startListening();
}

void loop() {

   analogWrite(ENA,80);
     digitalWrite(motor1pin1, HIGH);
     digitalWrite(motor1pin2, LOW);
     delay(1500);

     digitalWrite(motor1pin1, LOW);
     digitalWrite(motor1pin2, HIGH);
     delay(1500);
     
     
  if(radio.available()){
    int data = 0;
    radio.read(&data,sizeof(data));

    int spee = map(data,1,1000,100,240);
    Serial.println(data);
    Serial.println(spee);
     analogWrite(ENA,spee);

     digitalWrite(motor1pin1, HIGH);
     digitalWrite(motor1pin2, LOW);
     delay(2000);

     digitalWrite(motor1pin1, LOW);
     digitalWrite(motor1pin2, HIGH);
     delay(2000);
  }
}
