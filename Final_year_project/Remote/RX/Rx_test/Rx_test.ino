#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN pins

const uint64_t pipe = 0xE8E8F0F0E1LL; // Radio pipe address (must be the same as transmitter)

byte receivedValue; // Variable to store received value

void setup() {
  Serial.begin(9600); // Initialize serial communication
  radio.begin(); // Initialize the radio module
  radio.openReadingPipe(1, pipe); // Set up pipe 1 with the specified address
  radio.setAutoAck(false); // Disable auto acknowledgment
  radio.setCRCLength(RF24_CRC_8); // Set CRC length to 8 bits
  radio.setDataRate(RF24_250KBPS); // Set data rate to 250 kbps
  radio.setPALevel(RF24_PA_MAX); // Set power amplifier level to maximum
  radio.setChannel(108); // Set the radio channel
  radio.startListening(); // Start listening for incoming data
}

void loop() {
  if (radio.available()) {
    // If data is available, read it into receivedValue
    radio.read(&receivedValue, sizeof(receivedValue));
    
    // Print received value to serial monitor
    Serial.print("Received Value: ");
    Serial.println(receivedValue);
  }  
}
