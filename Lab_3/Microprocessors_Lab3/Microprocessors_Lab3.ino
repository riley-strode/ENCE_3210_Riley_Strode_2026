#define BUTTON 2
#define LED_GREEN 4
#define LED_RED 5

int gGreenCounter = 0; //initialize counters at 0
int gRedCounter = 0;

volatile unsigned char gISRFlag1 = 0; //setup flag for timer 1 (green)
volatile unsigned char gISRFlag2 = 0; //set up flag for timer 2 (red)
volatile int gtimer2Counter = 0; //start red timer counter at zero



void setup() {
  Serial.begin(9600);
  
  pinMode(LED_GREEN, OUTPUT); //LEDs are outputs 
  pinMode(LED_RED, OUTPUT);


  pinMode(BUTTON, INPUT); //button is input – when pressed, reads as HIGH

  // Reset Timer 1 (green) registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  OCR1A = 15624; // green timer 1 Hz -> 16MHz/1024(prescaler) - 1 = 15624
  TCCR1B |= (1 << WGM12); //green timer CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10); // Prescaler 1024
  TIMSK1 |= (1 << OCIE1A); // Enable Timer1 compare interrupt


  //reset timer 2 (red) registers
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2  = 0;

  OCR2A = 155;           // 100 Hz base (to work with 8 bit) (need to divide by 10 later)
  TCCR2A |= (1 << WGM21); // CTC mode
  TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); // Prescaler 1024
  TIMSK2 |= (1 << OCIE2A); // Enable Timer2 compare interrupt

}

void loop() {
  if(gISRFlag1){
    gISRFlag1 = 0; //reset green flag

    gGreenCounter++; //increment green counter

    if (gGreenCounter % 2 == 0) { // every even second (changes every 1 Hz, not full cycle every 1 Hz)
      digitalWrite(LED_GREEN, LOW);
    }

    if (gGreenCounter % 2 == 1) { // every odd second (changes every 1 Hz)
      digitalWrite(LED_GREEN, HIGH);
    }
    
    if (gGreenCounter % 3 == 0) { //every 3 seconds print message
      Serial.println("I'm with the Mockingjay.");
  }

  }
  
  if(gISRFlag2){
    gISRFlag2 = 0; //reset red flag
    if(digitalRead(BUTTON) == 1){
      digitalWrite(LED_RED, HIGH); //turn on red LED when button is pressed
    }
    else{
      digitalWrite(LED_RED, LOW); //turn off red LED when not pressed
    }
  }
}

ISR(TIMER1_COMPA_vect) {
  gISRFlag1 = 1; //change timer 1 flag (green)
}

ISR(TIMER2_COMPA_vect) {
  gtimer2Counter++; //increment timer 2 counter
  if (gtimer2Counter >= 10) {   // 100 Hz / 10 = 10 Hz
    gtimer2Counter = 0;
    gISRFlag2 = 1; //change timer 2 flag (red)
  }
}
