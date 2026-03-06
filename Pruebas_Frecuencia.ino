//Código para ESP32S3 con Led integrado

//NRF24L01 PA/LNA Wireless LED Control
//Código Transmisor 


#include <RF24.h>
#include <nRF24L01.h>
#include <printf.h>  

//#define boton 4
int contador = 0;  // Contador que enviara 
RF24 radio(4, 5);  // CE, CSN
const byte address[6] = "12321"; // Canal de comunicación

void setup() {
  Serial.begin(115200);
  Serial.println("\nCircuito Transmisor");
  //pinMode(boton, INPUT_PULLUP);

  // Inicializacion de pines del módulo NRF24L01
  SPI.begin(12, 13, 11, 5);  // SCK, MISO, MOSI, SS (CSN)

  // Verificación del modulo NRF24L01, si es que la detecta
  if (!radio.begin()) {
    //Si no la encuentra muestra mensaje y se detiene
    Serial.println("No se detecta el nRF24L01");
    while (1);
  }

  radio.openWritingPipe(address); // Direcciona los mensajes
  radio.setPALevel(RF24_PA_LOW);  // Ajusta el nivel de potencia
  radio.stopListening();  // Desactiva el modo Recepcion y queda como transmisor
}

void loop() {
  Serial.print("Enviando dato: "); // Se muestra en pantalla
  Serial.println(contador);        // los números que se envian

  // Envía el dato por el módulo
  bool ok = radio.write(&contador, sizeof(contador));

  // Verifica si llego al receptor
  if (ok) {
    Serial.println(">> ¡Confirmado!");
  } else {
    Serial.println(">> Sin respuesta");
  }  

  contador++;   // Incrementa valor y
  delay(1000);  // se envia cada segundo
}
