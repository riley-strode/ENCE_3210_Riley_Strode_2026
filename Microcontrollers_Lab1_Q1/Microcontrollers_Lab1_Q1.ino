#define ARRAY_SIZE 512 //have array with 0-511

unsigned long result[ARRAY_SIZE]; // use unsigned variable because only need positive

unsigned long twice_square(unsigned int value) {
  return 2UL * value * value; // value squared times two
  //ChatGPT helped me with the "2UL" part for 32-bit functionality
  
}

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < ARRAY_SIZE; i++) {
    result[i] = twice_square(i); // save results to array "results"
    Serial.println(result[i]);   // print result of each iteration of function
  }
}

void loop() {
}
