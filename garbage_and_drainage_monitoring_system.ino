// Garbage and Drainage Monitoring System
// Developed in Embedded C/C++
// Microcontroller: Arduino Uno

// Sensors and Modules
#define TRIG_PIN_GARBAGE  2
#define ECHO_PIN_GARBAGE  3
#define TRIG_PIN_DRAINAGE 4
#define ECHO_PIN_DRAINAGE 5
#define BUZZER_PIN        6
#define LED_GARBAGE_FULL  7
#define LED_DRAINAGE_FULL 8

// Thresholds (in centimeters)
#define GARBAGE_FULL_THRESHOLD  10
#define DRAINAGE_BLOCK_THRESHOLD  15

// Variables
long duration;
int distance_garbage;
int distance_drainage;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  
  // Garbage Sensor
  pinMode(TRIG_PIN_GARBAGE, OUTPUT);
  pinMode(ECHO_PIN_GARBAGE, INPUT);
  
  // Drainage Sensor
  pinMode(TRIG_PIN_DRAINAGE, OUTPUT);
  pinMode(ECHO_PIN_DRAINAGE, INPUT);
  
  // Output devices
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_GARBAGE_FULL, OUTPUT);
  pinMode(LED_DRAINAGE_FULL, OUTPUT);

  // Initially OFF
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_GARBAGE_FULL, LOW);
  digitalWrite(LED_DRAINAGE_FULL, LOW);
}

void loop() {
  distance_garbage = measureDistance(TRIG_PIN_GARBAGE, ECHO_PIN_GARBAGE);
  distance_drainage = measureDistance(TRIG_PIN_DRAINAGE, ECHO_PIN_DRAINAGE);
  
  Serial.print("Garbage Bin Distance: ");
  Serial.print(distance_garbage);
  Serial.println(" cm");

  Serial.print("Drainage Level Distance: ");
  Serial.print(distance_drainage);
  Serial.println(" cm");

  // Garbage Bin Full
  if (distance_garbage < GARBAGE_FULL_THRESHOLD) {
    digitalWrite(LED_GARBAGE_FULL, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(LED_GARBAGE_FULL, LOW);
  }
  
  // Drainage Blockage Detected
  if (distance_drainage < DRAINAGE_BLOCK_THRESHOLD) {
    digitalWrite(LED_DRAINAGE_FULL, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(LED_DRAINAGE_FULL, LOW);
  }
  
  // If both normal, turn OFF buzzer
  if (distance_garbage >= GARBAGE_FULL_THRESHOLD && distance_drainage >= DRAINAGE_BLOCK_THRESHOLD) {
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(2000); // Delay for 2 seconds
}

// Function to Measure Distance
int measureDistance(int trigPin, int echoPin) {
  long duration;
  int distance;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  
  distance = duration * 0.034 / 2;
  
  return distance;
}
