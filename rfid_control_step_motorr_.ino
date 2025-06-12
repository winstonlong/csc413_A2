#include <SPI.h>
#include <MFRC522.h>
#include <Stepper.h>

// setup rc522 reader
#define SS_PIN 10
#define RST_PIN 5
MFRC522 rfid(SS_PIN, RST_PIN);

// setup stepper motor
const int stepsPerRevolution = 2048;  // 28BYJ-48 takes 2048 steps per revolution
Stepper myStepper(stepsPerRevolution, 2, 6, 3, 7);  // pin order: IN1, IN3, IN2, IN4

// allowed uids (key fob and card)
const int NUM_CARDS = 2;
byte allowedUIDs[NUM_CARDS][4] = {
  {0x35, 0x51, 0x85, 0x76},  // key fob uid
  {0x67, 0x9C, 0x9F, 0xFA}   // card uid
};

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  myStepper.setSpeed(15);  // set motor speed

  Serial.println("system initialized, please scan your card...");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;

  Serial.print("UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print("0x");
    Serial.print(rfid.uid.uidByte[i], HEX);
    Serial.print(i < rfid.uid.size - 1 ? ", " : "\n");
  }

  if (checkUID(rfid.uid.uidByte)) {
    Serial.println(" auth successful! rotating motor 90 degrees counterclockwise...");
    // negative steps for counterclockwise rotation
    myStepper.step(-stepsPerRevolution / 4);  
    delay(1000);  // simple debounce
  } else {
    Serial.println(" unauthorized card!");
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

// check if uid is allowed
bool checkUID(byte *uid) {
  for (int i = 0; i < NUM_CARDS; i++) {
    bool match = true;
    for (int j = 0; j < 4; j++) {
      if (uid[j] != allowedUIDs[i][j]) {
        match = false;
        break;
      }
    }
    if (match) return true;
  }
  return false;
}
