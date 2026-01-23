#define Button_1 3 //set pins for buttons 1 and 2, LEDs
#define Button_2 2
#define LED_GREEN 4
#define LED_RED 5
#define Debounce_Time 200 //set debounce time to 0.2 sec

int gButtonCounter1 = 0; //set variables to count button presses
int gButtonCounter2 = 0;
volatile int gButtonState1 = 0; //set variables (volatitle) for each button's state
volatile int gButtonState2 = 0;


void setup() {
  Serial.begin(9600);

  pinMode(LED_GREEN, OUTPUT); //LEDs are outputs
  pinMode(LED_RED, OUTPUT);
  
  pinMode(Button_1, INPUT_PULLUP); //buttons are inputs
  pinMode(Button_2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Button_1), isr_button1, RISING); //buttons are interrupts
  attachInterrupt(digitalPinToInterrupt(Button_2), isr_button2, RISING);

}

void loop() {
  if(gButtonState1 == 1)
  {
    gButtonState1 = 0; //reset button 1 state
    delay(Debounce_Time);
    if(digitalRead(Button_1) == 1){ //check if button 1 is pressed after delay
      gButtonCounter1 += 1; //add to counter 1
      Serial.print("Right Button Count = "); //print updated presscount
      Serial.println(gButtonCounter1);
    }
  }

  if(gButtonState2 == 1)
  {
    gButtonState2 = 0; //reset button 2 state
    delay(Debounce_Time);
    if(digitalRead(Button_2) == 1){ //check if button 2 is pressed after delay
      gButtonCounter2 += 1; //add to counter 2
      Serial.print("Left Button Count = "); //print updated count
      Serial.println(gButtonCounter2);
    }
  }
  
  if(gButtonCounter1 > gButtonCounter2) //if button 1 has been pressed more, red is on
  {
    digitalWrite(LED_RED, HIGH); 
    digitalWrite(LED_GREEN, LOW);
    }
  if(gButtonCounter1 < gButtonCounter2) //if button 2 has been pressed more, green is on
  {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);
    }

  if(gButtonCounter1 == gButtonCounter2) //equal presses, then both LEDs are on (represents blue LED)
    {
      digitalWrite(LED_RED, HIGH);
      digitalWrite(LED_GREEN, HIGH);
      }
}

void isr_button1(){ //button 1 interrupt changes button state to high
    gButtonState1 = 1;
}

void isr_button2(){ //button 2 interrupt changes button state to high
    gButtonState2 = 1;
}
