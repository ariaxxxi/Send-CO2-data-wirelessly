#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9,10);
const byte address[6] = "00001";

#include <MHZ19_uart.h>
const int rx_pin = 4;	//Serial rx pin no
const int tx_pin = 5;	//Serial tx pin no
MHZ19_uart mhz19;


void setup() {
  Serial.begin(9600);
  mhz19.begin(rx_pin, tx_pin);
  mhz19.setAutoCalibration(false);

 radio.begin();
 radio.openWritingPipe(address);
 radio.setPALevel(RF24_PA_MIN);
 radio.stopListening();
}


void loop() {
  int co2ppm = mhz19.getPPM();
  int temp = mhz19.getTemperature();

  Serial.print("co2: "); Serial.println(co2ppm);
  radio.write(&co2ppm,sizeof(co2ppm));  
  delay(1000);
}
