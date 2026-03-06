// CÓDIGO PARA ESP32-WROOM-32

//NRF24L01 PA/LNA Wireless LED Control
//Código Receptor

#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

RF24 radio(2, 5);   // CE, CSN
const byte address[6] = "12321"; // Canal de comunicación
int datoRecibido = 0; // Variable receptora


void setup() {
  Serial.begin(115200);

  // Inicializacion de pines del módulo NRF24L01
  SPI.begin(18, 19, 23, 5);

  Serial.println("\nCircuito Receptor");

  //Verificación del modulo NRF24L01, si es que la detecta
  if (!radio.begin()) {
    Serial.println("No se detecta el nRF24L01");
    while (1);
  }

  radio.openReadingPipe(1, address); // Abre el canal y usa la dirección
  radio.setPALevel(RF24_PA_LOW);  // Ajusta el nivel de potencia
  radio.startListening(); // Activa el modo recepción
}

void loop() {
  // Verifica si hay datos del transmisor
  if (radio.available()) {
    // Lee el dato y lo guarda
    radio.read(&datoRecibido, sizeof(datoRecibido));

    // Muestra el dato recibido
    Serial.print("\nDato actual: ");
    Serial.println(datoRecibido);

    // Valida si se recibió
    if (datoRecibido > 0) {
      Serial.println("Dato recibido");
    } else { 
      Serial.println("Sin señal");
    }
    delay(1000); // Espera un 1 segundo
  }
}
