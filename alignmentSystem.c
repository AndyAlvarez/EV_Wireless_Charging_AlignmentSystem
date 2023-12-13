// Imports 
#include <stdlib.h> 

// Pin Declarations 
const uint8_t LED_OUTPUT_PIN = 34; 
const int HALLEFFECT_INPUT_PIN = A8; 

// Values Depend on Magnet 
const uint16_t LOWER_BOUND_MAX_SENSOR_VALUE = 390; 
const uint16_t MAX_SENSOR_VALUE = 405; 
const uint16_t TURN_DURATION_90_DEG = 10250; // 10000; 
const uint16_t TURN_DURATION_180_DEG = TURN_DURATION_90_DEG * 2; // 20500; 

// Motors 
// Inputs are for wheel spin direction 
// Enable for speed 

// Motor A:  
int enA = 9;  
int in1 = 8; 
int in2 = 7;  
  
// Motor B 
int enB = 3; 
int in3 = 5; 
int in4 = 4; 
 
// Function Declarations 
void runForwardFor(); 
void runBackwardsFor(int milliseconds); 
void turnLeft(int turnDurationMS); 
void turnRight(int turnDurationMS); 
double calculateMisalignment(int actual, int maxVal); 
//double calculatePercentages(int actual, int maxVal); 

void runStop(); 
void runStopFor(); 
//void runSpiral(); 
//void singleAxisAlignment(); 
//double calibrateMidValue(int sampleSize); 

// Variable Declarations 
int hallEffectVal; // Current magnetic field value 
int lasthallEffectVal; // Previous magnetic field value 
double percentMisalignment; 
// Spiral Function Variable: Requires Tuning 
int tourtime = 1000; // circle tourtime. it is about intersection areas between each spiral. it should be less than circle time 
int increasetime = 10; // time for next tour, larger spiral needs more time 
int numberofspiral = 10; // number of circle 
int minspeed = 5; // initial speed for spiral.  
int maxspeed = 200;// max speed 
int ledVal; 

void setup() 
{
 // redundant 
 int lasthallEffectVal; 
 int hallEffectVal;  
 double percentMisalignment; 

 // Set all the motor control pins to outputs 

  pinMode(enA, OUTPUT); 
  pinMode(enB, OUTPUT); 
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 
  pinMode(in3, OUTPUT); 
  pinMode(in4, OUTPUT); 

   // put your setup code here, to run once: <-motors 
  pinMode(LED_BUILTIN, OUTPUT); 
 /* Lmotor.setSpeed(255); 
  Rmotor.setSpeed(255);*/ 

  //sensor 
  pinMode(LED_OUTPUT_PIN, OUTPUT); 
  pinMode(HALLEFFECT_INPUT_PIN, INPUT); 
  Serial.begin(9600); 
} 

 

void loop() 
{
  lasthallEffectVal = hallEffectVal; 
  hallEffectVal = analogRead(HALLEFFECT_INPUT_PIN); 

  // Remap the value for output. In my experiments, the minimum input 
  // value for when the north part of the magnet was directly in front of  
  // the Hall effect sensor was ~22 
  //int ledVal = map(hallEffectVal, 12.5, 1023, 0, 255); 
 
   //double averageMidvalue = calibrateMidValue(50); // 

  // To middle 

//  if (hallEffectVal >= LOWER_BOUND_MAX_SENSOR_VALUE ){ 

//    runStopFor(100000); 

//    //runStop(); 

//     

//     

//  } else { 

//    runForwardFor(); 

////    turnRight(TURN_DURATION_90_DEG); 

////    runStopFor(5000); 

////    turnLeft(TURN_DURATION_180_DEG); 

////    runStopFor(5000); 

//  } 

  percentMisalignment = calculateMisalignment(hallEffectVal, MAX_SENSOR_VALUE); 

  // Print the raw photocell value and the converted led value (e,g., for Serial  
  // Console and Serial Plotter) 
 //Serial.print(averageMidvalue); 
 //Serial.print(",");- 
 Serial.print(hallEffectVal); 
 Serial.print(", "); 
 Serial.print("Percent Misalignment: "); 
 Serial.print(percentMisalignment); 
 Serial.println("%"); 

// Serial.print("Percent Misalignment: "); 

// Serial.print(percentArr[0]); 

// Serial.print(", "); 

// Serial.print("Percent Alignment: "); 

// Serial.println(percentArr[1]); 

 //Serial.println(lasthallEffectVal); 

 

  // Write out the LED value.  
  analogWrite(LED_OUTPUT_PIN, ledVal); 
  Serial.println(ledVal); 

  delay(20); // read at 50Hz  
} 

 

double calibrateMidValue(int sampleSize) 

{ 
  int idleValueSample[sampleSize]; 
  int magneticFieldValueSum = 0; 
  double averageMagneticFieldValues; 

  for (int i = 0; i < sampleSize; i++){ 

    idleValueSample[i] = hallEffectVal; 
    magneticFieldValueSum += hallEffectVal; 

  } 
  averageMagneticFieldValues = magneticFieldValueSum / sampleSize; 

  return averageMagneticFieldValues; 
} 

 

void singleAxisAlignment()  
{ 
   if (hallEffectVal >= LOWER_BOUND_MAX_SENSOR_VALUE ){ 
    //runStopFor(5000); 
    runStop(); 

  } else { 

    runForwardFor(); 
//    turnRight(TURN_DURATION_90_DEG); 

//    runStopFor(5000); 

//    turnLeft(TURN_DURATION_180_DEG); 

//    runStopFor(5000); 
  } 

 Serial.print(hallEffectVal); 
 Serial.print(", "); 
 Serial.print("Percent Misalignment: "); 
 Serial.print(percentMisalignment); 
 Serial.println("%"); 

// Serial.print(","); 

// Serial.print(hallEffectVal); 

// Serial.print(","); 

// Serial.println(lasthallEffectVal); 
} 

void runForwardFor() 
{ 
  // Set Motor A direction to spin Forward 
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW); 

  // Set Motor A speed (0~255) 
  analogWrite(enA, 255); 

  // Set Motor B direction to spin Forward 
  digitalWrite(in3, LOW); 
  digitalWrite(in4, HIGH); 

  // Set Motor A speed (0~255) 
  analogWrite(enB, 255); 
} 

 

void runBackwardsFor(int milliseconds) 
{ 
  // Set Motor A direction to spin Forward 
  digitalWrite(in1, LOW); 
  digitalWrite(in2, HIGH); 

  // Set Motor A speed (0~255) 
  analogWrite(enA, 255); 

  // Set Motor B direction to spin Forward 
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW); 

  // Set Motor A speed (0~255) 
  analogWrite(enB, 255); 

  delay(milliseconds); 
} 

 

void runStopFor(int milliseconds) 
{ 
  analogWrite(enA, 0); 
  analogWrite(enB, 0); 
  delay(milliseconds); 
} 

 

void runStop() 
{ 
  analogWrite(enA, 0); 
  analogWrite(enB, 0); 
} 

 

double calculateMisalignment(int actual, int maxVal) 
{ 
    // Works ========================================= 

    //double percentMisalignment = (abs(actual - maxVal) / maxVal) * 100; 

    //  double absVal = abs(actual - maxVal); 

    //  double divi = absVal / maxVal; 

    //  double percent = divi * 100; 

    // 

    //  return percent; 

    //  //return percentMisalignment; 

    // Works ========================================= 

    // map(value, fromLow, fromHigh, toLow, toHigh) 

  double mappedVal = map(actual, 200, 405, 0, 405); 
  double percentMisalignment = (abs(mappedVal - maxVal) / maxVal) * 100; 
  double absVal = abs(mappedVal - maxVal); 
  double divi = absVal / maxVal; 
  double percent = divi * 100; 

  return percent; 
} 

 
void turnLeft(int turnDurationMS)// change 
{ // Motor A: Left; Motor B: Right 

  // Set Motor A (LEFT Motor) direction to spin Backward 
  digitalWrite(in1, LOW); 
  digitalWrite(in2, HIGH); 

  

  // Set Motor A speed (0~255) 
  analogWrite(enA, 255); 

  // Set Motor B (RIGHT Motor) direction to spin Forward 
  digitalWrite(in3, LOW); 
  digitalWrite(in4, HIGH); 

  // Set Motor B speed (0~255) 
  analogWrite(enB, 255); 

  delay(turnDurationMS); // how long it spins, optimize value 

  analogWrite(enA, 0); 

  analogWrite(enB, 0); 

} 

 

void turnRight(int turnDurationMS)// change 
{ // Motor A: Left; Motor B: Right 

  // Set Motor A (LEFT Motor) direction to spin Forward 
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW); 

  // Set Motor A speed (0~255) 
  analogWrite(enA, 255); 

  // Set Motor B (RIGHT Motor) direction to spin Backward 
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW); 

  // Set Motor B speed (0~255) 
  analogWrite(enB, 255); 

  delay(turnDurationMS); // how long it spins, optimize value 


  analogWrite(enA, 0); 

  analogWrite(enB, 0); 

} 

 

double calculatePercentages(int actual, int maxVal) 
{ 

//  // Need the actual value 

//    // 390 

//  double percentages[2]; // [misalignmet, alignment], // array may need to be a global var 

//   

//  // Find the Percent 

//    // |390-400| / 400 

//    // 10 / 400 = 0.025 * 100 = 2.5% 

//    // 100 - 2.5 

//  double percentMisalignment = (abs(actual - maxVal) / maxVal) * 100; 

//  percentages[0] = percentMisalignment; 

//     

//  double percentAlignment = 100 - percentMisalignment; 

//  percentages[1] = percentAlignment; 

//   

//  return percentages; 

} 