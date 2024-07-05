# define xStepPin 2
# define xDirPin 5
# define yStepPin 3
# define yDirPin 6
# define zStepPin 4
# define zDirPin 7
# define enablePin 8

# define joystickX A0
# define joystickY A1

# define joystickZ A2

# define stepsPerRev 200

void setup() {
 	pinMode(xStepPin, OUTPUT);
  pinMode(xDirPin, OUTPUT);
  pinMode(yStepPin, OUTPUT);
  pinMode(yDirPin, OUTPUT);
  pinMode(zStepPin, OUTPUT);
  pinMode(zDirPin, OUTPUT);
  pinMode(joystickX, INPUT);
  pinMode(joystickY, INPUT);
  pinMode(joystickZ, INPUT);
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW);
}

void loop() {

  int xVal = analogRead(joystickX);
  int yVal = analogRead(joystickY);
  int zVal = analogRead(joystickZ);

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

  if(zVal > 700) {
    digitalWrite(zDirPin, HIGH); // Sens de rotation par défaut
    runOneZStep();
  }

  if(zVal < 300) {
    digitalWrite(zDirPin, LOW); // Sens de rotation inverse
    runOneZStep();
  }
}

void runOneXStep() {
 	runOneStep(xStepPin);
}

void runOneYStep() {
  runOneStepMicroStep4(yStepPin);
}

void runOneZStep() {
  runOneStepMicroStep4(zStepPin);
}

void runOneStep(int stepPin) {
  digitalWrite(stepPin, HIGH);
 	delayMicroseconds(350);
 	digitalWrite(stepPin, LOW);
 	delayMicroseconds(350);
}

void runOneStepMicroStep4(int stepPin) {
  digitalWrite(stepPin, HIGH);
 	delayMicroseconds(100);
 	digitalWrite(stepPin, LOW);
 	delayMicroseconds(100);
}

