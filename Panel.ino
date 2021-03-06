const int LED_PINS[] = {12, 5, 14, 4};

const int RELE_BUTTON_PIN = 13;
const int CHECK_BUTTON_PIN = 15;
const int BUZZER_PIN = 16;

bool currentReleButtonState;
bool currentCheckButtonState;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  for(int i = 0; i < 4; i++){
    pinMode(LED_PINS[i], OUTPUT);
  }

  pinMode(RELE_BUTTON_PIN, INPUT_PULLUP);
  pinMode(CHECK_BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);

  currentReleButtonState = digitalRead(RELE_BUTTON_PIN);
  currentCheckButtonState = digitalRead(CHECK_BUTTON_PIN);

  Serial.begin(9600);
  Serial.write("Setup complete\n");
}

// the loop function runs over and over again forever
void loop() {
  if(isCheckButtonPressedUp()){
    toggleLed(LED_PINS[0]);
    makeSound();
  }
  if(isReleButtonPressedUp()){
    toggleLed(LED_PINS[1]);
    makeSound();
  }
}

bool isReleButtonPressedUp(){
  int newReleButtonState = digitalRead(RELE_BUTTON_PIN);
  Serial.write("newReleButtonState "); Serial.print(newReleButtonState); Serial.write("\n");
  bool lastReleButtonState = currentReleButtonState;
  currentReleButtonState = newReleButtonState;
  return currentReleButtonState && !lastReleButtonState;
}

bool isCheckButtonPressedUp(){
  bool newCheckButtonState = digitalRead(CHECK_BUTTON_PIN);
  Serial.write("newCheckButtonState "); Serial.print(newCheckButtonState); Serial.write("\n");
  bool lastCheckButtonState = currentCheckButtonState;
  currentCheckButtonState = newCheckButtonState;
  return !currentCheckButtonState && lastCheckButtonState;
}
void blinkAll(){
  ledOn(LED_PINS[2]);
  ledOn(LED_PINS[3]);

  delay(500);
  
  ledOff(LED_PINS[2]);
  ledOff(LED_PINS[3]);

  delay(500);
}

void ledOn(int pin){
  digitalWrite(pin, HIGH);
}

void ledOff(int pin){
  digitalWrite(pin, LOW);
}

void toggleLed(int pin){
  int state = digitalRead(pin);
  if(state){
    ledOff(pin);
  }
  else{
    ledOn(pin);
  }
}

void makeSound(){
  digitalWrite(BUZZER_PIN ,HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN, LOW);
}
