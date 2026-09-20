// Semáforo de 3 LEDs
// Arduino UNO R4 WiFi
// Usa delay()

const int ROJO = 2;
const int AMARILLO = 3;
const int VERDE = 4;

void setup() {

  pinMode(ROJO, OUTPUT);
  pinMode(AMARILLO, OUTPUT);
  pinMode(VERDE, OUTPUT);

}

void loop() {

  // =========================
  // VERDE
  // =========================

  digitalWrite(VERDE, HIGH);
  digitalWrite(AMARILLO, LOW);
  digitalWrite(ROJO, LOW);

  delay(500);


  // =========================
  // AMARILLO
  // =========================

  digitalWrite(VERDE, LOW);
  digitalWrite(AMARILLO, HIGH);
  digitalWrite(ROJO, LOW);

  delay(1000);


  // =========================
  // ROJO
  // =========================

  digitalWrite(VERDE, LOW);
  digitalWrite(AMARILLO, LOW);
  digitalWrite(ROJO, HIGH);

  delay(1500);

}