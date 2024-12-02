#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN pins

const uint64_t pipe = 0xE8E8F0F0E1LL; // Radio pipe address (must be the same as transmitter)

struct Received_data {
  byte ch1;
  byte ch2;
  byte ch3;
  byte ch4;
  byte ch5;
  byte ch6;
};

Received_data received_data;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    radio.read(&received_data, sizeof(received_data));
    
    // Print received data to serial monitor
    Serial.print("Channel 1: ");
    Serial.print(received_data.ch1);
    Serial.print("\tChannel 2: ");
    Serial.print(received_data.ch2);
    Serial.print("\tChannel 3: ");
    Serial.print(received_data.ch3);
    Serial.print("\tChannel 4: ");
    Serial.print(received_data.ch4);
    Serial.print("\tChannel 5: ");
    Serial.print(received_data.ch5);
    Serial.print("\tChannel 6: ");
    Serial.println(received_data.ch6);
  }
}
