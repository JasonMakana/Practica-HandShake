// CÓDIGO PARA ESP32-WROOM-32

//NRF24L01 PA/LNA Wireless LED Control
//Código Receptor

#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <Adafruit_NeoPixel.h>

#define PIN_RGB 48  // Pin del sensor led
RF24 radio(2, 5);   // CE, CSN
const byte address[6] = "12321";
int datoRecibido = 0;

Adafruit_NeoPixel pixels(1, PIN_RGB, NEO_GRB + NEO_KHZ800);
/*
void setColor(uint8_t r, uint8_t g, uint8_t b) {
  pixels.setPixelColor(0, pixels.Color(r, g, b));
  pixels.show();
}
*/
void setup() {
  Serial.begin(115200);
  //pixels.begin();
  //pixels.setBrightness(30);

  SPI.begin(18, 19, 23, 5);

  Serial.println("\nCircuito Receptor");
  //radio.begin();

  if (!radio.begin()) {
    Serial.println("No se detecta el nRF24L01");
    while (1);
  }

  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_LOW);  // radio. setPALevel
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    radio.read(&datoRecibido, sizeof(datoRecibido));

    Serial.print("\nEstado recibio: ");
    Serial.println(datoRecibido);

    if (datoRecibido > 0) {
      Serial.println("Dato enviado");
    } else { 
      Serial.println("Sin señal");
    }
    delay(1000);
  }
}


/*

#include <RF24.h>
#include <nRF24L01.h>
#include <printf.h>  

#define boton 4
int contador = 0;
RF24 radio(2, 5);  // CE, CSN
const byte address[6] = "12321";

void setup() {
  Serial.begin(115200);
  Serial.println("\nCircuito Transmisor");
  pinMode(boton, INPUT_PULLUP);

  SPI.begin(18, 19, 23, 5);  // SCK, MISO, MOSI, SS (CSN)

  radio.begin();

  if (!radio.begin()) {
    Serial.println("No se detecta el nRF24L01");
    while (1);
  }

  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();
}

void loop() {
  Serial.print("Enviando dato: ");
  Serial.println(contador);

  bool ok = radio.write(&contador, sizeof(contador));

  if (ok) {
    Serial.println(">> ¡Confirmado!");
  } else {
    Serial.println(">> Sin respuesta");
  }  

  contador++;
  delay(1000); // Envía cada 1 segundo
}
*/