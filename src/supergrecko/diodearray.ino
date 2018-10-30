/**
 * Declare arrays containing the different pins
 * for LED's and switches
 */
int led_pins[] = {3, 4, 5, 6, 7, 9};
int switch_pins[] = {11};

int buttonState = HIGH;
int reading;
int lastBounce = 0;
int lastState = HIGH;

int bounceDelay = 200;
/**
 * Declare the binary DIODE array
 */
int diodes[] = {1, 1, 1, 1};

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
  // put your setup code here, to run once:
  //pinMode(led_pins[0], OUTPUT);
  //pinMode(led_pins[1], OUTPUT);
  pinMode(led_pins[2], OUTPUT);
  pinMode(led_pins[3], OUTPUT);
  pinMode(led_pins[4], OUTPUT);
  pinMode(led_pins[5], OUTPUT);

  pinMode(switch_pins[0], INPUT_PULLUP);
  //pinMode(switch_pins[1], INPUT_PULLUP);
  //pinMode(switch_pins[2], INPUT_PULLUP);

  Serial.begin(9600);
}

/**
 * Display the current binary array
 */
int display_array(int states[] = {})
{
  digitalWrite(led_pins[2], states[0]);
  digitalWrite(led_pins[3], states[1]);
  digitalWrite(led_pins[4], states[2]);
  digitalWrite(led_pins[5], states[3]);
}

/**
 * Reset the binary counter
 * @return void
 */
void reset()
{
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

  reading = digitalRead(11);

  if(reading == LOW && lastState == HIGH && millis() - lastBounce > bounceDelay) {
    state = !state;

    lastBounce = millis();
  }

  lastState == reading;

  if(readState()) {
    display_array(diodes);
  }
  Serial.print(String(state, HEX) + "\n");
}
