//For the lights, I only did it with the Red and Green LEDs

#define ARRAY_SIZE 20
#define RED_LED 5
#define GREEN_LED 4

char gCharArray[ARRAY_SIZE] = {'R', 'A', '4', 'B', 'R', 'C', '4', 'R', 'D', 'E',
                                'F', '4', 'R', 'H', 'I', 'J', 'K', 'L', 'M', 'N'}; //test array without 'G'

int gRedCount = 0;
int gGreenCount = 0;
int gBlueCount = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  
  //Start LEDs off
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  
  // Search for R, G, and B in the array
  for(int i = 0; i < ARRAY_SIZE; i++){
    if(gCharArray[i] == 'R') {
      gRedCount +=1;//add to red count
    }
    else if(gCharArray[i] == 'G'){
      gGreenCount +=1;//add to green count
    }
    else if(gCharArray[i] == 'B'){
      gBlueCount +=1;//add to blue count
    }
  }
  
  // Turn on LEDs if color are detected
  if(gRedCount > 0){
    digitalWrite(RED_LED, HIGH);
    Serial.println("Red LED ON");
  }
  
  if(gGreenCount > 0){
    digitalWrite(GREEN_LED, HIGH);
    Serial.println("Green LED ON");
  }
  
  // Print the number of each colors found
  Serial.print("Number of R's found: ");
  Serial.println(gRedCount);
  Serial.print("Number of G's found: ");
  Serial.println(gGreenCount);
  Serial.print("Number of B's found: ");
  Serial.println(gBlueCount);
}

void loop() {
}
