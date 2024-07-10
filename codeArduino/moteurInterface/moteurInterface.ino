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

# define xFinDeCoursePin 9
# define yFinDeCoursePin 10
# define zFinDeCoursePin 11

# define xMaxPos 8000
# define yMaxPos 1000
# define zMaxPos 1000

# define stepsPerRev 200
# define noCalibration 1

int xJoystickVal = 0;
int yJoystickVal = 0;
int zJoystickVal = 0;

int xPosCalibrated = 0;
int yPosCalibrated = 0;
int zPosCalibrated = 0;

int xPos = 0;
int yPos = 0;
int zPos = 0;

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

  pinMode(xFinDeCoursePin, INPUT);
  pinMode(yFinDeCoursePin, INPUT);
  pinMode(zFinDeCoursePin, INPUT);

  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW);

  Serial.begin(9600);

  if(noCalibration) {
    Serial.println("Pas de calibration !");
  } else {
    calibrateXYZ();
  }
}

void loop() {

  xJoystickVal = analogRead(joystickX);
  yJoystickVal = analogRead(joystickY);
  zJoystickVal = analogRead(joystickZ);

  if(xJoystickVal > 800) {
    xStepDown();
  }

  if(xJoystickVal < 200) {
    xStepUp();
  }

  if(yJoystickVal > 800) {
    yStepUp();
  }

  if(yJoystickVal < 200) {
    yStepDown();
  }

  if(zJoystickVal > 700) {
    zStepUp();
  }

  if(zJoystickVal < 300) {
    zStepDown();
  }
}

void calibrateXYZ() {
  while(!xPosCalibrated) {
    xStepDown();
  }
  Serial.println("Axe X calibré !");
  while(!yPosCalibrated) {
    yStepDown();
  }
  Serial.println("Axe Y calibré !");
  while(!zPosCalibrated) {
    zStepDown();
  }
  Serial.println("Axe Z calibré !");
}

void xStepDown() {
  if(digitalRead(xFinDeCoursePin)) {
    xPos = 0;
    xPosCalibrated = 1;
  }
  if(!xPosCalibrated || xPos > 0) {
    digitalWrite(xDirPin, HIGH);
    runOneXStep();
    xPos --;
  }
}

void xStepUp() {
  if(xPos < xMaxPos) {
    digitalWrite(xDirPin, LOW);
    runOneXStep();
    xPos ++;
  }
}

void yStepDown() {
  if(digitalRead(yFinDeCoursePin)) {
    yPos = 0;
    yPosCalibrated = 1;
  }
  if(!yPosCalibrated || yPos > 0) {
    digitalWrite(yDirPin, LOW);
    runOneYStep();
    yPos --;
  }
}

void yStepUp() {
  if(yPos < yMaxPos) {
    digitalWrite(yDirPin, HIGH);
    runOneYStep();
    yPos ++;
  }
}

void zStepDown() {
  if(digitalRead(zFinDeCoursePin)) {
    zPos = 0;
    zPosCalibrated = 1;
  }
  if(!zPosCalibrated || zPos > 0) {
    digitalWrite(zDirPin, LOW);
    runOneZStep();
    zPos --;
  }
}

void zStepUp() {
  if(zPos < zMaxPos) {
    digitalWrite(zDirPin, HIGH);
    runOneZStep();
    zPos ++;
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

