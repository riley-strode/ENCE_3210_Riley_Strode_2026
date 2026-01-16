#define ARRAY_SIZE 20
#define RED_LED 5
#define GREEN_LED 4

char gCharArray[ARRAY_SIZE] = {'W', 'A', 'R', 'I', 'Z', 'C', '4', 'R', 'I', 'Z',
                                'F', 'Z', 'R', 'H', 'I', 'J', 'K', 'T', 'R', 'I'}; //testing array

char gSecretCodeArray[3] = {'R', 'I', 'Z'}; //pattern

int gRIZCount = 0; //start RIZ counter at zero

void setup() {
  Serial.begin(9600);
  
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  
  //Start LEDs off
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  
  // Search for RIZ in array
  for(int i = 0; i < ARRAY_SIZE; i++){
    if(gCharArray[i] == 'R'){//check for 'R'
      if(gCharArray[i+1] == 'I'){// check next element for 'I'
        if(gCharArray[i+2] == 'Z'){// check next element for 'Z'
          gRIZCount +=1;
          }
          }
          }
          }
  //turn on Red or Green LED
  if(gRIZCount > 0){
    digitalWrite(GREEN_LED, HIGH);
    }
  else{
    digitalWrite(RED_LED, HIGH);
    }


  //print results
  Serial.print("RIZ appears ");
  Serial.print(gRIZCount);
  Serial.println(" time(s).");
}

void loop() {
  
}
