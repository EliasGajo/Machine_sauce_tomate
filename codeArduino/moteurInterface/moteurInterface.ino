# define xStepPin 2
# define xDirPin 5
# define yStepPin 3
# define yDirPin 6
# define enablePin 8

# define joystickX A0
# define joystickY A1

# define stepsPerRev 200

void setup() {
 	pinMode(xStepPin, OUTPUT);
  pinMode(xDirPin, OUTPUT);
  pinMode(yStepPin, OUTPUT);
  pinMode(yDirPin, OUTPUT);
  pinMode(joystickX, INPUT);
  pinMode(joystickY, INPUT);
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW);
}

void loop() {

  int xVal = analogRead(joystickX);
  int yVal = analogRead(joystickY);

  if(xVal > 800) {
    digitalWrite(xDirPin, HIGH); // Sens de rotation par défaut
    runOneXStep();
  }

  if(xVal < 200) {
    digitalWrite(xDirPin, LOW); // Sens de rotation inverse
    runOneXStep();
  }

  if(yVal > 800) {
    digitalWrite(yDirPin, HIGH); // Sens de rotation par défaut
    runOneYStep();
  }

  if(yVal < 200) {
    digitalWrite(yDirPin, LOW); // Sens de rotation inverse
    runOneYStep();
  }
}

void runOneXStep() {
 	runOneStep(xStepPin);
}

void runOneYStep() {
  runOneStep(yStepPin);
}

void runOneStep(int stepPin) {
  digitalWrite(stepPin, HIGH);
 	delayMicroseconds(700);
 	digitalWrite(stepPin, LOW);
 	delayMicroseconds(700);
}

