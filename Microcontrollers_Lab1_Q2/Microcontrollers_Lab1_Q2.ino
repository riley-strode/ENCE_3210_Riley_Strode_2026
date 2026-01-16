#define DEG_TO_RAD 0.01745329252  // pi/180

float cosValues[361];  // Array to store cos(0°) through cos(360°). 361 total values

void setup() {
  Serial.begin(9600);

  for (int deg = 0; deg <= 360; deg++) { // go from 0 degrees to 360 degrees
    float radians = deg * DEG_TO_RAD; // convert degree values to radian
    cosValues[deg] = cos(radians); // store cosine values (calculated using radians) into the array cosValues

    // Print each value to sereial monitor
    Serial.print("cos(");
    Serial.print(deg);
    Serial.print("°) = ");
    Serial.println(cosValues[deg], 6); //print to 6 decimal places
  }
}

void loop() {
}
