//Used Claud to help because I got stuck with working the buttons

#define ARRAY_SIZE 10
#define RED_LED 5
#define GREEN_LED 4
#define BLUE_LED 3  // Change to your blue LED pin
#define OPERATION_BUTTON 2
#define EXECUTE_BUTTON 7  // Change to your second button pin

int gArray1[ARRAY_SIZE] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50};
int gArray2[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int gResultArray[ARRAY_SIZE] = {0};

int gOperationCounter = 0;  // 1=add, 2=subtract, 3=multiply
bool gLastOpButtonState = HIGH;
bool gCurrentOpButtonState = HIGH;
bool gLastExButtonState = HIGH;
bool gCurrentExButtonState = HIGH;

void setup() {
  Serial.begin(9600);
  
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(OPERATION_BUTTON, INPUT_PULLUP);
  pinMode(EXECUTE_BUTTON, INPUT_PULLUP);
  
  // Start with all LEDs off
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
}

void loop() {
  // Read operation button
  gCurrentOpButtonState = digitalRead(OPERATION_BUTTON);
  
  // Check if operation button was pressed
  if(gLastOpButtonState == HIGH && gCurrentOpButtonState == LOW){
    delay(50);  // Debounce
    
    gOperationCounter++;
    
    // Cycle through operations (1, 2, 3, then back to 1)
    if(gOperationCounter > 3){
      gOperationCounter = 1;
    }
    
    // Turn on appropriate LED based on operation
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
    
    if(gOperationCounter == 1){
      digitalWrite(RED_LED, HIGH);
      Serial.println("Operation: Addition selected");
    }
    else if(gOperationCounter == 2){
      digitalWrite(GREEN_LED, HIGH);
      Serial.println("Operation: Subtraction selected");
    }
    else if(gOperationCounter == 3){
      digitalWrite(BLUE_LED, HIGH);
      Serial.println("Operation: Multiplication selected");
    }
  }
  
  gLastOpButtonState = gCurrentOpButtonState;
  
  // Read execute button
  gCurrentExButtonState = digitalRead(EXECUTE_BUTTON);
  
  // Check if execute button was pressed
  if(gLastExButtonState == HIGH && gCurrentExButtonState == LOW){
    delay(50);  // Debounce
    
    if(gOperationCounter > 0){
      // Turn off all LEDs
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(BLUE_LED, LOW);
      
      Serial.println("Executing operation...");
      
      // Perform operation on all array elements
      for(int i = 0; i < ARRAY_SIZE; i++){
        if(gOperationCounter == 1){
          gResultArray[i] = gArray1[i] + gArray2[i];
        }
        else if(gOperationCounter == 2){
          gResultArray[i] = gArray1[i] - gArray2[i];
        }
        else if(gOperationCounter == 3){
          gResultArray[i] = gArray1[i] * gArray2[i];
        }
      }
      
      // Turn on all LEDs when complete
      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(BLUE_LED, HIGH);
      
      Serial.println("Operation complete! Results:");
      for(int i = 0; i < ARRAY_SIZE; i++){
        Serial.print("Result[");
        Serial.print(i);
        Serial.print("] = ");
        Serial.println(gResultArray[i]);
      }
      
      // Reset operation counter
      gOperationCounter = 0;
    }
    else{
      Serial.println("No operation selected!");
    }
  }
  
  gLastExButtonState = gCurrentExButtonState;
}
