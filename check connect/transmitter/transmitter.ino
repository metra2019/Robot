//_____radio module___________
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define RADIO_CE 9 //CE SP
#define RADIO_SCN 10 //SCN SPI
#define CHANNEL 6
const uint64_t pipe = 0xF0F1F2F3F4L ;  //id
RF24 radio(RADIO_CE, RADIO_SCN); //initialization

byte data = 0;

void setup() {
  Serial.begin(9600);

  //radio settings
  radio.begin();
  radio.setChannel(CHANNEL);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_HIGH);
  //set transmitter mode
  radio.openWritingPipe(pipe);
}

void loop() {
  radio.write(&data, sizeof(data));
}
