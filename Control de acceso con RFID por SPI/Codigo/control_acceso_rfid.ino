/*
  Control de acceso con RFID (MRC522) - Arduino UNO
  Librería: "MFRC522" (Miguel Balboa) -> Library Manager

  Conexiones:
    SDA/SS -> D10
    SCK    -> D13
    MOSI   -> D11
    MISO   -> D12
    RST    -> D9
    3.3V   -> 3.3V   (¡NO usar 5V!)
    GND    -> GND
    LED    -> D7 (con resistencia de 220 ohm a GND)
*/

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN  10
#define RST_PIN 9
#define LED_PIN 7

const unsigned long TIEMPO_LED = 2000;  // 2000 ms

MFRC522 lector(SS_PIN, RST_PIN);

// >>> CAMBIA ESTOS BYTES por el UID de tu tarjeta autorizada <<<
byte uidAutorizado[] = {0x3A, 0xF2, 0x1C, 0x7B};
const byte TAM_UID_AUT = sizeof(uidAutorizado);

bool ledEncendido = false;
unsigned long inicioLed = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial) { ; }

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  SPI.begin();
  lector.PCD_Init();
  delay(50);

  // Verificar comunicación leyendo el registro de versión del chip
  byte version = lector.PCD_ReadRegister(MFRC522::VersionReg);
  if (version == 0x00 || version == 0xFF) {
    Serial.println("ERROR: sin comunicacion con el lector (revisa el cableado, MISO/D12).");
  } else {
    Serial.print("Lector detectado. Version del chip: 0x");
    Serial.println(version, HEX);
    Serial.println("Comunicacion con el lector OK.");
  }
  Serial.println("Acerca una tarjeta...");
}

void loop() {
  // Apagar el LED solo si estaba encendido y ya pasaron 2000 ms (sin delay)
  if (ledEncendido && (millis() - inicioLed >= TIEMPO_LED)) {
    digitalWrite(LED_PIN, LOW);
    ledEncendido = false;
  }

  // Seguir leyendo tarjetas (no bloquea)
  if (!lector.PICC_IsNewCardPresent()) return;
  if (!lector.PICC_ReadCardSerial()) return;

  // Mostrar UID con cada byte separado por espacio
  Serial.print("UID:");
  for (byte i = 0; i < lector.uid.size; i++) {
    Serial.print(' ');
    if (lector.uid.uidByte[i] < 0x10) Serial.print('0');
    Serial.print(lector.uid.uidByte[i], HEX);
  }
  Serial.println();

  if (uidCoincide()) {
    Serial.println("ACCESO PERMITIDO");
    digitalWrite(LED_PIN, HIGH);
    ledEncendido = true;
    inicioLed = millis();   // reinicia el conteo de 2 s
  } else {
    Serial.println("ACCESO DENEGADO");
    // El LED no se toca: si estaba encendido sigue su cuenta; si no, queda apagado
  }

  lector.PICC_HaltA();       // detiene la tarjeta actual
  lector.PCD_StopCrypto1();
}

bool uidCoincide() {
  if (lector.uid.size != TAM_UID_AUT) return false;
  for (byte i = 0; i < TAM_UID_AUT; i++) {
    if (lector.uid.uidByte[i] != uidAutorizado[i]) return false;
  }
  return true;
}
