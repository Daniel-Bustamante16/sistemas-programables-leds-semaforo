// 3 LEDs independientes usando millis()
// Arduino UNO R4 WiFi

const int ROJO = 2;
const int AMARILLO = 3;
const int VERDE = 4;

unsigned long tiempoRojo = 0;
unsigned long tiempoAmarillo = 0;
unsigned long tiempoVerde = 0;

bool estadoRojo = false;
bool estadoAmarillo = false;
bool estadoVerde = false;

void setup() {

  pinMode(ROJO, OUTPUT);
  pinMode(AMARILLO, OUTPUT);
  pinMode(VERDE, OUTPUT);

}

void loop() {

  unsigned long tiempoActual = millis();

  // LED ROJO
  if (tiempoActual - tiempoRojo >= 1000) {
    tiempoRojo = tiempoActual;

    estadoRojo = !estadoRojo;
    digitalWrite(ROJO, estadoRojo);
  }

  // LED AMARILLO
  if (tiempoActual - tiempoAmarillo >= 2000) {
    tiempoAmarillo = tiempoActual;

    estadoAmarillo = !estadoAmarillo;
    digitalWrite(AMARILLO, estadoAmarillo);
  }

  // LED VERDE
  if (tiempoActual - tiempoVerde >= 3000) {
    tiempoVerde = tiempoActual;

    estadoVerde = !estadoVerde;
    digitalWrite(VERDE, estadoVerde);
  }

}
