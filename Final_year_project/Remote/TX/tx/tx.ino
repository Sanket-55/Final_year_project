#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN pins

const uint64_t pipe = 0xE8E8F0F0E1LL; // Radio pipe address (must be the same as receiver)

struct Data_to_be_sent {
  byte ch1;
  byte ch2;
  byte ch3;
  byte ch4;
  byte ch5;
  byte ch6;
};

Data_to_be_sent sent_data;

void setup() {
  radio.begin();
  radio.openWritingPipe(pipe);
}

void loop() {
  // Read analog values
  sent_data.ch1 = map(analogRead(A0), 0, 1023, 0, 255);
  sent_data.ch2 = map(analogRead(A1), 0, 1023, 0, 255);
  sent_data.ch3 = map(analogRead(A2), 0, 1023, 0, 255);
  
  // Read digital values
  sent_data.ch4 = digitalRead(2);
  sent_data.ch5 = digitalRead(3);
  sent_data.ch6 = digitalRead(4);
  
  // Transmit data wirelessly
  radio.write(&sent_data, sizeof(sent_data));
  
  delay(100); // Adjust delay as needed
}
