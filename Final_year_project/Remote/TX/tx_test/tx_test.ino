#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN pins

const uint64_t pipe = 0xE8E8F0F0E1LL; // Radio pipe address (must be the same on the receiver)

void setup() {
  radio.begin();
  radio.openWritingPipe(pipe);
}

void loop() {
  // Read analog value from potentiometer
  int potValue = analogRead(A1);

  // Map the potentiometer value to a range of 0-255 (8-bit)
  byte mappedValue = map(potValue, 0, 1023, 0, 255);

  // Transmit the mapped value wirelessly
  radio.write(&mappedValue, sizeof(mappedValue));

  delay(100); // Adjust delay as needed
}
