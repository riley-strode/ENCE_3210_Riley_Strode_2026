//I excluded blue from the pattern
//Claud helped me with syntax getting the button to work
//This program sometimes doesn't work and sometimes it does even though its the same code

#define RED_LED 5
#define GREEN_LED 4
#define BUTTON_PIN 2
#define delayTime 256

bool gSystemRunning = true;  // Track if sequence should run
bool gLastButtonState = HIGH; // Previous button state (HIGH = not pressed with pull-up)
bool gCurrentButtonState = HIGH;

void setup() {
  Serial.begin(9600);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Start with LEDs off
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
}

void loop() {
  gCurrentButtonState = digitalRead(BUTTON_PIN);// Read the button state
  
  // Check if button was just pressed (transition from HIGH to LOW)
  if(gLastButtonState == HIGH && gCurrentButtonState == LOW){
    delay(50);  // Debounce delay
    gSystemRunning = !gSystemRunning;  // Toggle the running state
    
    // Turn off all LEDs when stopping
    if(!gSystemRunning){
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, LOW);
    }
  }
  // Update last button state
  gLastButtonState = gCurrentButtonState;
  
  // Run LED sequence only if system is running
  if(gSystemRunning){
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    delay(delayTime);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    delay(delayTime);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    delay(delayTime);
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    delay(delayTime);
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    delay(delayTime);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    delay(delayTime);
  }
}
