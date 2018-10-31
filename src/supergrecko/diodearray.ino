/**
 * Arduino Controller
 * 
 * This is the program for an Arduino controller.
 * 
 * The controller has six LED's where one of them is
 * a RGB LED. The LED's each have a different value.
 * 
 *  - RGB LED is the system status switch.
 *    It displays ON/OFF state and possible errors/
 *    warnings.
 *    
 *  - LED 2 is the RESET LED. If a reset is triggered
 *    the LED 2 will turn on. If any button is hit
 *    after a reset, the light will turn back off.
 *    
 *  - LED 3/4/5/6 are all parts of an array. The
 *    array displays a binary number. The number
 *    can be any positive number in the range
 *    0 -> 15. 
 * 
 * The controller also has three switches. Two of
 * these buttons are momentary switches and the
 * last switch is used for turning the device
 * ON/OFF.
 * 
 *  - SWITCH 1 is our ON/OFF switch. It's the one
 *    that decides system state. If the system
 *    state is false, the other switches won't
 *    work.
 *    
 *  - MOMENTARY SWITCH 1 is our PLUS switch. When
 *    triggering this switch the binary value
 *    displayed by our LED array will go up
 *    by one. This number caps at 15.
 *    
 *  - MOMENTARY SWITCH 2 is our MINUS switch. When
 *    triggering this switch, the binary value
 *    displayed by our LED array will go down
 *    by one. This number caps at 0.
 */

/**
 * Declare arrays containing the different pins
 * for LED's and switches
 */
int led_pins[] = {2, 3, 4, 5, 6, 7};
int switch_pins[] = {8, 9, 11};

/**
 * Declare variables for debouncing the buttons
 * 
 * The buttons are named 1/2/3.
 *  - Button 1 is our ON/OFF switch
 *  - Button 2 is our PLUS momentary switch
 *  - Button 3 is our MINUS momentary switch
 * 
 * @var int buttonState?
 * @var int reading?
 * @var int lastBounce?
 * @var int lastState?
 */
int buttonState1 = HIGH, buttonState2 = HIGH, buttonState3 = HIGH;
int reading1, reading2, reading3;
int lastBounce1 = 0, lastBounce2 = 0, lastBounce3 = 0;
int lastState1 = HIGH, lastState2 = HIGH, lastState3 = HIGH;

/**
 * Declare delay for debounce
 * @var int bounceDelay
 */
int bounceDelay = 200;
/**
 * Declare the empty binary DIODE array
 * 
 * @var int[] empty
 */
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
 * Iterate over each of the arrays and pin the different modes.
 * 
 * We make a for loop which starts the pinMode function for each of the
 * led_pins[] array using the iterator variable i
 * 
 * We do the same for our button pins in the switch_pins[] array
 */
void setup() {
  for(int i = 0; i < 6; i++) {
    pinMode(led_pins[i], OUTPUT);
  }

  for(int i = 0; i < 3; i++) {
    pinMode(switch_pins[i], INPUT_PULLUP);
  }
  /**
   * We start the Serial reader at port 9600
   * 
   * This makes debugging easier
   */
  Serial.begin(9600);
}

/**
 * Display the current binary array
 * Prints the given array values to
 * our onboard array of LED's.
 * 
 * @param int[] states
 * 
 * @return void
 */
int display_array(int states[] = {})
{
  digitalWrite(led_pins[0], states[0]);
  digitalWrite(led_pins[1], states[1]);
  digitalWrite(led_pins[2], states[2]);
  digitalWrite(led_pins[3], states[3]);
}

/**
 * Reset our binary variable counter
 * aswell as turning the RESET LED on.
 * 
 * @return void
 */
void reset()
{
  digitalWrite(led_pins[4], HIGH);
  counter = 0;
}

void loop() {
  /**
   * We start the loop by getting each of the button states
   * 
   * We access the different pins using our array.
   */
  reading1 = digitalRead(switch_pins[0]);
  reading2 = digitalRead(switch_pins[1]);
  reading3 = digitalRead(switch_pins[2]);

  /**
   * We use an if statement to check if the button1 which is our ON/OFF
   * switch is triggered. If it is it'll toggle system status
   * 
   * In the statement we check if the current reading is LOW (We used the
   * in-built PULLUP-Resistors in the Arduino so the values are the opposite
   * of what they're named. (LOW means it's enabled, HIGH means they're disabled)
   * 
   * If current reading = enabled AND last reading = disabed AND current time - lastBounce > bounceDelay
   * 
   *  If it is we change state
   * 
   * Also resets the ON/OFF switch debounce timer
   */
  if(reading1 == LOW && lastState1 == HIGH && millis() - lastBounce1 > bounceDelay) {
    state = !state;

    lastBounce1 = millis();
  }
  /**
   * We use the same statement above to check if button 2 and 3 (The PLUS/MINUS momentary switches are triggered. If they are we reset.
   * If they are we call our reset function and set the last bounce timers to current time.
   */
  if((reading2 == LOW && lastState2 == HIGH && millis() - lastBounce2 > bounceDelay) && (reading3 == LOW && lastState3 == HIGH && millis() - lastBounce3 > bounceDelay)) {
    reset();
    
    lastBounce2 = millis();
    lastBounce3 = millis();
    /**
     * Use the same statement to check if the PLUS button is hit and if the device
     * is active. If it is we add one to the value
     * We also turn off the RESET LED if it is on.
     */
  }else if(reading2 == LOW && lastState2 == HIGH && millis() - lastBounce2 > bounceDelay) {
    if(counter < 15 && state) {
      counter ++;
    }
    digitalWrite(led_pins[4], LOW);

    lastBounce2 = millis();
    /**
     * Use the same statement to check if the MINUS button is hit and if the device
     * is active. If it is we remove one to the value
     * We also turn off the RESET LED if it is on.
     */
  }else if(reading3 == LOW && lastState3 == HIGH && millis() - lastBounce3 > bounceDelay) {
    if(counter > 0 && state) {
      counter--;
    }
    digitalWrite(led_pins[4], LOW);

    lastBounce3 = millis();
  }
  /**
   * After our statements we set the last states of the buttons
   * to the current reading.
   */
  lastState1 == reading1;
  lastState2 == reading2;
  lastState3 == reading3;

  /**
   * We make sure the counter never goes above 15 or below 0
   */
  if(counter > 15) {
    counter = 15;
  }
  if(counter < 0) {
    counter = 0;
  }
  /**
   * If the device is on we turn on our RGB and the LED array.
   */
  if(state) {
    for(int i = 2; i < 6; i++) {
      digitalWrite(i, bitRead(counter, i - 2));
    }
    digitalWrite(led_pins[5], HIGH);
    /**
     * We print the current counter in HEX format to the Serial reader
     */
    Serial.print(String(counter, HEX) + "\n");
  }else{
    /**
     * If it's off we display our empty array and turn off our RGB
     */
    display_array(empty);
    digitalWrite(led_pins[5], LOW);
    counter = 0;
  }
}
