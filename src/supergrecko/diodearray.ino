/**
 * Declare arrays containing the different pins
 * for LED's and switches
 */
int led_pins[] = {3, 4, 5, 6, 7, 8};
int switch_pins[] = {};

/**
 * Declare the binary DIODE array
 */
int diodes[] = {0, 0, 0, 0};

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
  for(int i = 0; 0 < 6; i++) {
    pinMode(led_pins[i], OUTPUT);
  }

  for(int i = 0; i < 3; i++) {
    pinMode(switch_pins[i], INPUT);
  }
}

/**
 * Read button pin's value
 * 
 * @param  int pi
 * @return int
 */
int read_button(int pin)
{
  return digitalRead(pin);
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

void loop() {
  // put your main code here, to run repeatedly:

}
