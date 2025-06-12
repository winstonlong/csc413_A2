// ✅ project logic: combine 4 ingredients + 4 methods to light up the unique led for a dish (invalid combos light up nothing)

const int yellowLEDs[] = {10, 11, 12};     // steam
const int greenLEDs[]  = {A0, A1, A2};     // fry
const int blueLEDs[]   = {A3, A4, A5, 13}; // boil
const int redLEDs[]    = {8, 9};           // roast

const int leftButtons[] = {2, 3, 4, 5};     // left switches: rice, flour, wheat, potato
const int rightButtons[] = {6, 7, A6, A7};  // right switches: steam, fry, boil, roast

String leftNames[]  = {"rice", "flour", "wheat", "potato"};
String rightNames[] = {"steam", "fry", "boil", "roast"};

struct Recipe {
  String ingredient;
  String method;
  int ledPin;
};

Recipe recipes[] = {
  {"rice",  "steam", 10},    // steamed rice
  {"rice",  "boil", 13},    // congee
  {"rice",  "fry",   A0},    // fried rice
  {"potato","boil", A4},  // mashed potato
  {"potato","roast", 8},   // baked potato
  {"potato","fry",   A1},  // french fries
  {"potato","steam", 11},  // steamed potato
  {"wheat", "boil",  A5},  // porridge
  {"flour","steam", 12},   // steamed bun
  {"flour","boil",  A3},  // noodle
  {"flour","roast", 9},   // bread
  {"flour","fry",   A2}    // pancake
};

void setup() {
  Serial.begin(9600);
  for (int pin : yellowLEDs) pinMode(pin, OUTPUT);
  for (int pin : greenLEDs)  pinMode(pin, OUTPUT);
  for (int pin : blueLEDs)   pinMode(pin, OUTPUT);
  for (int pin : redLEDs)    pinMode(pin, OUTPUT);
  for (int pin : leftButtons)  pinMode(pin, INPUT_PULLUP);
  for (int pin : rightButtons) pinMode(pin, INPUT_PULLUP);

  Serial.println(" ingredient + method = recipe logic mode started");
}

void loop() {
  String leftInput  = "";
  String rightInput = "";

  for (int i = 0; i < 4; i++) {
    if (digitalRead(leftButtons[i]) == LOW)  leftInput  = leftNames[i];
    if (digitalRead(rightButtons[i]) == LOW) rightInput = rightNames[i];
  }

  turnOffAllLEDs();

  if (leftInput != "" && rightInput != "") {
    bool found = false;
    for (Recipe r : recipes) {
      if (r.ingredient == leftInput && r.method == rightInput) {
        digitalWrite(r.ledPin, HIGH);
        found = true;
      }
    }
    if (found) {
      Serial.print(" combo success: ");
      Serial.print(leftInput); Serial.print(" + "); Serial.print(rightInput);
      Serial.println(" -> lighting the dish");
    } else {
      Serial.println(" invalid combo, no leds lit");
    }

  } else if (leftInput != "") {
    // only left side button pressed -> light up all leds for that ingredient
    for (Recipe r : recipes) {
      if (r.ingredient == leftInput) {
        digitalWrite(r.ledPin, HIGH);
      }
    }

  } else if (rightInput != "") {
    // only right side button pressed -> light up all leds for that method
    for (Recipe r : recipes) {
      if (r.method == rightInput) {
        digitalWrite(r.ledPin, HIGH);
      }
    }
  }

  delay(100);
}

void turnOffAllLEDs() {
  for (int pin : yellowLEDs) digitalWrite(pin, LOW);
  for (int pin : greenLEDs)  digitalWrite(pin, LOW);
  for (int pin : blueLEDs)   digitalWrite(pin, LOW);
  for (int pin : redLEDs)    digitalWrite(pin, LOW);
}
