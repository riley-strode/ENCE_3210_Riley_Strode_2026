//Documentation: I got stuck with this one so I used Claude to help fix code


#define BUTTON_1 2   // Interrupt pin for operation selection
#define BUTTON_2 3    // interrupt pin for execution
#define LED_RED 5        // Addition
#define LED_GREEN 4     // Subtraction
#define LED_BLUE 11    // multiplication [placeholder for blue LED (none will actually turn on in real life)]

#define DEBOUNCE_DELAY 200 //debounce is 0.2 sec
#define RESET_TIMEOUT 1000 //reset time to 1 sec

#define ARRAY_SIZE 10



int array1[ARRAY_SIZE] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50}; //set the three arrays
int array2[ARRAY_SIZE] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int result[ARRAY_SIZE] = {};


volatile int operationCounter = 0; //set counter to zero
volatile bool executeFlag = false; //set flag to off
volatile unsigned long lastSelectPress = 0; //set buttons to unpressed state
volatile unsigned long lastExecutePress = 0;



void selectISR() { // ISR for selection button
  unsigned long currentTime = millis();
  
  // Debounce check with comparison
  if (currentTime - lastSelectPress > DEBOUNCE_DELAY) {
    operationCounter++;
    
    // Limit to 3 operations max
    if (operationCounter > 3) {
      operationCounter = 1;
    }
    
    lastSelectPress = currentTime;
    updateLEDs();
  }
}


void executeISR() { // ISR for execute button
  unsigned long currentTime = millis();
  
  // Debounce check
  if (currentTime - lastExecutePress > DEBOUNCE_DELAY) {
    if (operationCounter > 0) {
      executeFlag = true;
    }
    lastExecutePress = currentTime;
  }
}

void setup() {

  Serial.begin(9600);

  pinMode(BUTTON_1, INPUT_PULLUP); //buttons are inputs
  pinMode(BUTTON_2, INPUT_PULLUP);
  
  pinMode(LED_RED, OUTPUT); //LEDs are outputs 
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT); //blue placeholder
  
  
  digitalWrite(LED_RED, LOW); // Turn off all LEDs to start out 
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);
  
  attachInterrupt(digitalPinToInterrupt(BUTTON_1), selectISR, FALLING); //set selection interrupt to falling edge
  attachInterrupt(digitalPinToInterrupt(BUTTON_2), executeISR, FALLING); //set execution interrupt to falling edge (button 2)


}

void loop() {
  // Check if counter needs to be reset (timeout)
  if (operationCounter > 0 && 
      (millis() - lastSelectPress > RESET_TIMEOUT)) {
    // Keep the selected operation, don't reset
    // Operation stays selected until execute is pressed
  }
  
  // Execute operation if flag is set
  if (executeFlag) {
    executeFlag = false;
    performOperation();
  }
}

void updateLEDs() {
  // Turn off all LEDs to start out
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);
  
  // Turn on LED based on operation counter
  switch (operationCounter) {
    case 1:  // Addition
      digitalWrite(LED_RED, HIGH);
      Serial.println("Operation selected: ADDITION");
      break;
    case 2:  // Subtraction
      digitalWrite(LED_GREEN, HIGH);
      Serial.println("Operation selected: SUBTRACTION");
      break;
    case 3:  // Multiplication
      digitalWrite(LED_BLUE, HIGH);
      Serial.println("Operation selected: MULTIPLICATION");
      break;
  }
}

void performOperation() { //execute
  
  // Turn off all LEDs when starting execution
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);
  
  // Iterate the operation on all array elements
  for (int i = 0; i < ARRAY_SIZE; i++) {
    switch (operationCounter) {
      case 1:  // Addition
        result[i] = array1[i] + array2[i];
        break;
      case 2:  // Subtraction
        result[i] = array1[i] - array2[i]; 
        break;
      case 3:  // Multiplication
        result[i] = array1[i] * array2[i];
        break;
    }
  }
  

  printResults(); // Print results
  
  // Turn on all LEDs when operation is complete
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BLUE, HIGH);
  
  
  operationCounter = 0;   // reset operation counter
}

void printArrays() { //print the arrays functions
  Serial.println("Array 1:");
  for (int i = 0; i < ARRAY_SIZE; i++) { //first array
    Serial.print(array1[i]);
    Serial.print(" ");
  }
  Serial.println();
  
  Serial.println("Array 2:");
  for (int i = 0; i < ARRAY_SIZE; i++) { //second array
    Serial.print(array2[i]);
    Serial.print(" ");
  }
  Serial.println("\n");
}

void printResults() { //print function
  String opName;
  switch (operationCounter) {
    case 1: opName = "Addition"; break;
    case 2: opName = "Subtraction"; break;
    case 3: opName = "Multiplication"; break;
  }
  
  Serial.print("Operation: ");
  Serial.println(opName);
  Serial.println("Results:");
  
  for (int i = 0; i < ARRAY_SIZE; i++) {
    Serial.print("array1[");
    Serial.print(i);
    Serial.print("] ");
    
    switch (operationCounter) {
      case 1: Serial.print("+"); break;
      case 2: Serial.print("-"); break;
      case 3: Serial.print("*"); break;
    }
    
    Serial.print(" array2[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(result[i]);
  }
  Serial.println(); //new line  for next time
}