const int LED_PINS[] = {5, 4, 12, 14};

const int RELE_BUTTON_PIN = 13;
const int CHECK_BUTTON_PIN = 15;
const int BUZZER_PIN = 16;
const int RELE_PIN = 2;

const char INPUT_SEQUENCE[] = {'r', 'r', 'c', 'c', 'r', 'c', 'c', 'c', 'c', 'r', 'c', 'r', 'c'};
const int INPUT_ACTIONS[] =   { -1,  -1,  0 ,  -1,  -1,  1,  -1,  -1,   2 ,  -1,  -1,  -1,  3};
int lastPressedButtonIndex = -1;

bool currentReleButtonState;
bool currentCheckButtonState;
bool isDone;
bool isLockClosed;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  for(int i = 0; i < 4; i++){
    pinMode(LED_PINS[i], OUTPUT);
  }

  pinMode(RELE_BUTTON_PIN, INPUT_PULLUP);
  pinMode(CHECK_BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELE_PIN, OUTPUT);
  closeLock();

  currentReleButtonState = digitalRead(RELE_BUTTON_PIN);
  currentCheckButtonState = digitalRead(CHECK_BUTTON_PIN);

  Serial.begin(9600);
  Serial.write("Setup complete\n");
}

// the loop function runs over and over again forever
void loop() {
  if(isCheckButtonPressedUp()){
    makeSound();
    buttonPressed('c');
  }
  if(isReleButtonPressedUp()){
    makeSound();
    buttonPressed('r');
  }
}

bool isReleButtonPressedUp(){
  int newReleButtonState = digitalRead(RELE_BUTTON_PIN);
  //Serial.write("newReleButtonState "); Serial.print(newReleButtonState); Serial.write("\n");
  bool lastReleButtonState = currentReleButtonState;
  currentReleButtonState = newReleButtonState;
  return currentReleButtonState && !lastReleButtonState;
}

bool isCheckButtonPressedUp(){
  bool newCheckButtonState = digitalRead(CHECK_BUTTON_PIN);
  //Serial.write("newCheckButtonState "); Serial.print(newCheckButtonState); Serial.write("\n");
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

void makeShortSound(){
  digitalWrite(BUZZER_PIN ,HIGH);
  delay(50);
  digitalWrite(BUZZER_PIN, LOW);
}

void makeFinishSound(){
  makeSound();
  delay(100);
  makeSound();
  delay(100);
  makeSound();
}

void makeErrorSound(){
  makeShortSound();
  delay(50);
  makeShortSound();
}

void buttonPressed(char button){
  int currentButtonIndexToCheck = lastPressedButtonIndex + 1;
  if(isDone){
    openLock();
    delay(2000);
    closeLock();
    return;
  }
  if(INPUT_SEQUENCE[currentButtonIndexToCheck] == button){
    // Correct
    Serial.write("Correct "); Serial.print(button); Serial.write("\n");
    int inputAction = INPUT_ACTIONS[currentButtonIndexToCheck];
    if(inputAction > -1){
      doAction(inputAction);
    }
    lastPressedButtonIndex = currentButtonIndexToCheck;
  }
  else{
    // Incorrect
    Serial.write("Incorrect "); Serial.print(button); Serial.write("\n");
    delay(50);
    makeErrorSound();
    lastPressedButtonIndex = -1;
    for(int i = 0;i < 4; i++){
      ledOff(LED_PINS[i]);
    }
  }
}

void doAction(int inputAction){
  int ledIndex = inputAction;
  ledOn(LED_PINS[ledIndex]);
  if(inputAction == 3){
    isDone = true;
    delay(1000);
    makeFinishSound();
    delay(100);
    openLock();
    delay(2000);
    closeLock();
  }
}

void openLock(){
  digitalWrite(RELE_PIN, HIGH);
  isLockClosed = false;
}

void closeLock(){
  digitalWrite(RELE_PIN, LOW);
  isLockClosed = true;
}

void toggleLock(){
  if(isLockClosed){
    openLock();
  }
  else{
    closeLock();
  }
}
