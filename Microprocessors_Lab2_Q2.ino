//Documentation: I used Claude for runLEDSequence function

#define LED_RED     4 //define buttons and LED pins
#define LED_GREEN   5
#define LED_BLUE    9 //not real, just a placeholder

#define BUTTON_PIN  3
#define STEP_DELAY  500   // 0.5 sec between steps

volatile bool gRunSequence = false; //start sequence off
volatile bool gButtonFlag = false;

int gState = 0; 

void setup() {
  pinMode(LED_RED, OUTPUT); //LEDs are outputs
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  pinMode(BUTTON_PIN, INPUT_PULLUP); //Button is input

  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), isr_buttonPress, FALLING); //set interrupt with falling edge for button
}

void loop() {

  if (gButtonFlag) {
    gButtonFlag = false;
    gRunSequence = !gRunSequence;   // toggle sequence ON/OFF
  }

  if (gRunSequence) { //when button is pressed an odd number of times, run sequence (state is 1)
    runLEDSequence();
    delay(STEP_DELAY);
  } else {
    turnOffLEDs(); //when not running, set LEDs to off
  }
}

void runLEDSequence() { //set each state of LEDs and sequence

  switch (gState) { //used Claude for this part as this wasn't the learning portion of activity
    case 0: // R
      digitalWrite(LED_RED, HIGH);
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_BLUE, LOW);
      break;

    case 1: // RG
      digitalWrite(LED_RED, HIGH);
      digitalWrite(LED_GREEN, HIGH);
      digitalWrite(LED_BLUE, LOW);
      break;

    case 2: // RGB
      digitalWrite(LED_RED, HIGH);
      digitalWrite(LED_GREEN, HIGH);
      digitalWrite(LED_BLUE, HIGH);
      break;

    case 3: // GB
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, HIGH);
      digitalWrite(LED_BLUE, HIGH);
      break;

    case 4: // B
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_BLUE, HIGH);
      break;

    case 5: // RB
      digitalWrite(LED_RED, HIGH);
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_BLUE, HIGH);
      break;
  }

  gState++;
  if (gState > 5) { //reset sequence to start
    gState = 0;
  }
}

void turnOffLEDs() { //set LEDs to off when not running
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);
}

void isr_buttonPress() { //set Flag (which stops/starts sequence)
  gButtonFlag = true;
}
