#define ARRAY_SIZE 50 //50 elements in array

int gMyArray[ARRAY_SIZE] = {0};

int gMax = 0;
int g2Max = 0;

void setup() {
  Serial.begin(9600);
  
  for(int i=0; i<=ARRAY_SIZE-1; i++){ //fill array
  gMyArray[i] = i;
  }
  
  for(int i=0; i<=ARRAY_SIZE-1; i++){
    if (gMyArray[i] > g2Max){
      if (gMyArray[i] > gMax){
        g2Max = gMax;
        gMax = gMyArray[i];}
      else{
        g2Max = gMyArray[i];}
        

    }
    }
  // Write the second maximum to memory location just after array ends using pointer
  // Claude helped with this part
  int* ptrAfterArray = &gMyArray[ARRAY_SIZE];
  *ptrAfterArray = g2Max;

    
    //print results
    Serial.print("Maximum = ");
    Serial.println(gMax);
    Serial.print("Second Largest = ");
    Serial.println(g2Max);
    Serial.print("Value written to memory after array for Second Largest value = ");
    Serial.println(*ptrAfterArray);

}

void loop() {

}
