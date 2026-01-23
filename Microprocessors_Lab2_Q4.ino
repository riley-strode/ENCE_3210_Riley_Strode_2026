#define ARRAY_SIZE 10 //define array size to be 10
#define Button_1 3 //button pin
#define Debounce_Time 200 //debounce time

volatile int gButtonState1 = 0; //set variable for button

int gArrayX[ARRAY_SIZE] = {3, 7, 2, 5, 12, 2, 18, 20, 4, 9}; //test array for x
int gArrayY[ARRAY_SIZE] = {}; //create empty array for y

void setup() {
  Serial.begin(9600);

   pinMode(Button_1, INPUT_PULLUP); //set button to be input

  attachInterrupt(digitalPinToInterrupt(Button_1), isr_button1, RISING); //set interrupt
}

void loop() {
 if (gButtonState1 == 1) //when button is pressed, start printing
 {
    gButtonState1 = 0; //reset button 1 state
    delay(Debounce_Time); //debounce
  
    Serial.println("Button Press Detected"); //print result
    Serial.print("Array Y = ");
    for (int i = 0; i < ARRAY_SIZE - 2; i++) //print elements of Y 1-9
    {
      Serial.print(gArrayY[i]);
      Serial.print(", ");
    }
    Serial.println(gArrayY[ARRAY_SIZE - 1]); //print element 10 and start new line

 }

}

void isr_button1(){ //interrupt code (doing calculations here)
    gButtonState1 = 1; //change button state

    gArrayY[0] = 2 * gArrayX[0]; //handle first term (n-1 doesnt exist)

    for (int i = 1; i < ARRAY_SIZE - 1; i++) //handle rest of terms
    {
      gArrayY[i] = (2 * gArrayX[i]) - gArrayX[i - 1];
    }
}
