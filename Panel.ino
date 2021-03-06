const int LED1_PIN = 12;
const int LED2_PIN = 5;
const int LED3_PIN = 14;
const int LED4_PIN = 4;

//const int RELE_BUTTON_PIN = 13;
//const int CHECK_BUTTON_PIN = 8;

//bool currentReleButtonState;
//bool currentCheckButtonState;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED1_PIN, OUTPUT);
   pinMode(LED2_PIN, OUTPUT);
   pinMode(LED3_PIN, OUTPUT);
   pinMode(LED4_PIN, OUTPUT);

   //pinMode(RELE_BUTTON_PIN, INPUT);
   //pinMode(CHECK_BUTTON_PIN, INPUT);

   //currentReleButtonState = digitalRead(RELE_BUTTON_PIN);
   //currentCheckButtonState = digitalRead(CHECK_BUTTON_PIN);

   blinkAll();
}

// the loop function runs over and over again forever
void loop() {
  /*if(isReleButtonPressedUp()){
    Serial.println("Rele pressed");
  }*/
  blinkAll();
}

/*bool isReleButtonPressedUp(){
  bool newReleButtonState = digitalRead(RELE_BUTTON_PIN);
  bool lastReleButtonState = currentReleButtonState;
  currentReleButtonState = newReleButtonState;
  return currentReleButtonState && !lastReleButtonState;
}*/

/*bool isCheckButtonPressedUp(){
  bool newCheckButtonState = digitalRead(RELE_BUTTON_PIN);
  bool lastCheckButtonState = currentCheckButtonState;
  currentCheckButtonState = newCheckButtonState;
  return !currentCheckButtonState && lastCheckButtonState;
}*/
void blinkAll(){
  led1On();
  led2On();
  led3On();
  led4On();

  delay(500);

  led1Off();
  led2Off();
  led3Off();
  led4Off();

  delay(500);
}

void led1On(){
  digitalWrite(LED1_PIN, HIGH);
  //Serial.println("LED 1 on");
}

void led2On(){
  digitalWrite(LED2_PIN, HIGH);
}

void led3On(){
  digitalWrite(LED3_PIN, HIGH);
}

void led4On(){
  digitalWrite(LED4_PIN, HIGH);
}

void led1Off(){
  digitalWrite(LED1_PIN, LOW);
  //Serial.println("LED 1 off");
}

void led2Off(){
  digitalWrite(LED2_PIN, LOW);
}

void led3Off(){
  digitalWrite(LED3_PIN, LOW);
}

void led4Off(){
  digitalWrite(LED4_PIN, LOW);
}
