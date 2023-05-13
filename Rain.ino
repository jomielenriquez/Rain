// Pin definitions
const int RELAY1_PIN = 3;
const int RELAY2_PIN = 4;

const int MOTOR_PIN = 3;

const int RAIN_PIN = A2;
const int RAIN_OUT = 2;

const int SOLAR_PIN = A1;
const int DELAY = 500;

const int MOTORDELAY = 5000;  // delay on motor to stop
// const int STOP_FORWARD = 8;
// const int STOP_REVERSE = 7;

// Threshold values
const int RAIN_THRESHOLD = 500; // Change this value to adjust rain sensitivity

// Global variables
float rainLevel = 0;
int rainOUT = 0;
int prevRainOUT = rainOUT;

bool isNewValue = false;
// bool isStopForward = false;
// bool isStopReverse = false;

// int buttonStateStopForward = 0;
// int buttonStateStopReverse = 0;

void setup() {
  // Set pin modes
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  // pinMode(STOP_FORWARD, INPUT);
  // pinMode(STOP_REVERSE, INPUT);
  
  //Serial 
  digitalWrite(RELAY1_PIN, HIGH);
  digitalWrite(RELAY2_PIN, HIGH);

  delay(1000);
  Serial.begin(9600);
}

void loop() {
  // buttonStateStopForward =  digitalRead(STOP_FORWARD);
  // buttonStateStopReverse =  digitalRead(STOP_REVERSE);
  // if(buttonStateStopForward == 0){
  //   Serial.print("F pressed ");
  //   isStopForward = true;
  // }

  // if(buttonStateStopReverse == 0){
  //   Serial.print("R pressed ");
  //   isStopReverse = true;
  // }
  // Read the rain sensor value
  rainLevel = analogRead(RAIN_PIN);
  // value becomes zero when reach the treshold
  prevRainOUT = rainOUT;
  rainOUT = digitalRead(RAIN_OUT);
  if(rainOUT != prevRainOUT){
    isNewValue = true;
  }
  else{
    isNewValue = false;
  }
  // Serial.print("FB Stop: ");
  // Serial.print(buttonStateStopForward);
  // Serial.print(" RB Stop: ");
  // Serial.print(buttonStateStopReverse);
  Serial.print(" Rain Level: ");
  Serial.print(rainLevel);
  Serial.print(" Rain output: ");
  Serial.print(rainOUT);

  if(isNewValue){
    ResetMotor();
  }
  // Check the value of rainOUT
  if(rainOUT==0){
    if(isNewValue){
      Forward();
    }
  }
  else{
    if(isNewValue){
      Reverse();
    }
  }
  Serial.println(";");
  delay(DELAY);
}

void ResetMotor(){
  digitalWrite(RELAY1_PIN, HIGH);
  digitalWrite(RELAY2_PIN, HIGH);
  delay(1000);
}

void Forward(){
  digitalWrite(RELAY1_PIN, HIGH);
  digitalWrite(RELAY2_PIN, LOW);
  delay(MOTORDELAY);
  ResetMotor();
}

void Reverse(){
  digitalWrite(RELAY1_PIN, LOW);
  digitalWrite(RELAY2_PIN, HIGH);
  delay(MOTORDELAY);
  ResetMotor();
}

void ForwardReverse(){
  digitalWrite(RELAY1_PIN, HIGH);
  digitalWrite(RELAY2_PIN, HIGH);
  delay(1000);
  digitalWrite(RELAY1_PIN, HIGH);
  digitalWrite(RELAY2_PIN, LOW);
  delay(5000);
  digitalWrite(RELAY1_PIN, LOW);
  digitalWrite(RELAY2_PIN, LOW);
  delay(1000);
  digitalWrite(RELAY1_PIN, LOW);
  digitalWrite(RELAY2_PIN, HIGH);
  delay(5000);
}