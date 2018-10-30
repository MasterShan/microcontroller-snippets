/**
 * Declare arrays containing the different pins
 * for LED's and switches
 */
int led_pins[] = {2, 3, 4, 5, 6, 7};
int switch_pins[] = {8, 9, 11};

int buttonState1 = HIGH, buttonState2 = HIGH, buttonState3 = HIGH;
int reading1, reading2, reading3;
int lastBounce1 = 0, lastBounce2 = 0, lastBounce3 = 0;
int lastState1 = HIGH, lastState2 = HIGH, lastState3 = HIGH;

int bounceDelay = 200;
/**
 * Declare the binary DIODE array
 */
int diodes[] = {1, 1, 1, 1};
int empty[] = {0, 0, 0, 0};

/**
 * Current system state
 * @var bool state
 */
bool state = false;

/**
 * Current binary counter
 * @var int counter
 */
int counter = 0;

/**
 * Iterate over each of the arrays and start the pinMode.
 */
void setup() {
  for(int i = 0; i < 6; i++) {
    pinMode(led_pins[i], OUTPUT);
  }

  for(int i = 0; i < 3; i++) {
    pinMode(switch_pins[i], INPUT_PULLUP);
  }

  Serial.begin(9600);
}

/**
 * Display the current binary array
 */
int display_array(int states[] = {})
{
  digitalWrite(led_pins[0], states[0]);
  digitalWrite(led_pins[1], states[1]);
  digitalWrite(led_pins[2], states[2]);
  digitalWrite(led_pins[3], states[3]);
}

/**
 * Reset the binary counter
 * @return void
 */
void reset()
{
  digitalWrite(led_pins[4], HIGH);
  counter = 0;
}

/**
 * Read system state
 * @return bool
 */
bool readState()
{
  
  return state;
}

void loop() {
  // put your main code here, to run repeatedly:

  reading1 = digitalRead(switch_pins[0]);
  reading2 = digitalRead(switch_pins[1]);
  reading3 = digitalRead(switch_pins[2]);
  
  if(reading1 == LOW && lastState1 == HIGH && millis() - lastBounce1 > bounceDelay) {
    state = !state;

    lastBounce1 = millis();
  }

  if((reading2 == LOW && lastState2 == HIGH && millis() - lastBounce2 > bounceDelay) && (reading3 == LOW && lastState3 == HIGH && millis() - lastBounce3 > bounceDelay)) {
    reset();
    
    lastBounce2 = millis();
    lastBounce3 = millis();
  }else if(reading2 == LOW && lastState2 == HIGH && millis() - lastBounce2 > bounceDelay) {
    if(counter < 15 && state) {
      counter ++;
    }
    digitalWrite(led_pins[4], LOW);

    lastBounce2 = millis();
  }else if(reading3 == LOW && lastState3 == HIGH && millis() - lastBounce3 > bounceDelay) {
    if(counter > 0 && state) {
      counter--;
    }
    digitalWrite(led_pins[4], LOW);

    lastBounce3 = millis();
  }
  
  lastState1 == reading1;
  lastState2 == reading2;
  lastState3 == reading3;

  if(counter > 15) {
    counter = 15;
  }
  if(counter < 0) {
    counter = 0;
  }

  if(state) {
    for(int i = 2; i < 6; i++) {
      digitalWrite(i, bitRead(counter, i - 2));
    }
    digitalWrite(led_pins[5], HIGH);
    Serial.print(String(counter, HEX) + "\n");
  }else{
    display_array(empty);
    digitalWrite(led_pins[5], LOW);
    counter = 0;
  }
}
