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

# define xMaxPos 8000 // position maximale que le moteur X peut atteindre (sans foncer dans le mur)
# define xCenterCamera 4000 // position du moteur X pour que la pince se trouve au milieu de la camera
# define xOffsetCalibrationCamera 1000 // Le nombre de step que le moteur X doit faire pour calibrer la camera selon X (entre 2 photos)
# define xMicrostepping 1 // La valeur de microstepping utilisée sur l'axe X (jumper X sur l'arduino shield)

# define yMaxPos 1000 // position maximale que le moteur Y peut atteindre (sans foncer dans le mur)
# define yCenterCamera 500 // position du moteur Y pour que la pince se trouve au milieu de la camera
# define yOffsetCalibrationCamera 200 // Le nombre de step que le moteur Y doit faire pour calibrer la camera selon X (entre 2 photos)
# define yMicrostepping 4 // La valeur de microstepping utilisée sur l'axe Y (jumper Y sur l'arduino shield)

# define zMaxPos 1000 // // position maximale que le moteur Z peut atteindre (sans foncer dans le mur)
# define zCenterCamera 500 // position du moteur Z pour que la pince se trouve au milieu de la camera
# define zOffsetCalibrationCamera 200 // Le nombre de step que le moteur Z doit faire pour calibrer la camera selon X (entre 2 photos)
# define zMicrostepping 4 // La valeur de microstepping utilisée sur l'axe Z (jumper Z sur l'arduino shield)

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
    xStepDown(1);
  }

  if(xJoystickVal < 200) {
    xStepUp(1);
  }

  if(yJoystickVal > 800) {
    yStepUp(1);
  }

  if(yJoystickVal < 200) {
    yStepDown(1);
  }

  if(zJoystickVal > 700) {
    zStepUp(1);
  }

  if(zJoystickVal < 300) {
    zStepDown(1);
  }
}

// -------------------------------------------CALIBRATION FUNCTIONS-----------------------------------------------//

void calibrateXYZ() {
  while(!xPosCalibrated) {
    xStepDown(1);
  }
  Serial.println("Axe X calibré !");
  while(!yPosCalibrated) {
    yStepDown(1);
  }
  Serial.println("Axe Y calibré !");
  while(!zPosCalibrated) {
    zStepDown(1);
  }
  Serial.println("Axe Z calibré !");
}

// -------------------------------------------MOVE FUNCTIONS-----------------------------------------------//

void moveToPositionXYZ(int targetX, int targetY, int targetZ) {
  moveToPositionX(targetX);
  moveToPositionY(targetY);
  moveToPositionZ(targetZ);
}

void moveToPositionX(int targetX) {
  int remainingSteps = targetX - xPos;
  xStep(remainingSteps);
}

void moveToPositionY(int targetY) {
  int remainingSteps = targetY - yPos;
  yStep(remainingSteps);
}

void moveToPositionZ(int targetZ) {
  int remainingSteps = targetZ - zPos;
  zStep(remainingSteps);
}

// -------------------------------------------STEP FUNCTIONS-----------------------------------------------//
void xStep(int nbSteps) {
  if(nbSteps > 0) {
    xStepUp(nbSteps);
  } else if(nbSteps < 0) {
    xStepDown(-nbSteps);
  }
}

void xStepUp(int nbSteps) {
  xPos = stepUp(nbSteps, xPos, xMaxPos, xStepPin, xDirPin, xMicrostepping);
}

void xStepDown(int nbSteps) {
  xPos = stepDown(nbSteps, xPos, &xPosCalibrated, xFinDeCoursePin, xStepPin, xDirPin, xMicrostepping);
}

void yStep(int nbSteps) {
  if(nbSteps > 0) {
    yStepUp(nbSteps);
  } else if(nbSteps < 0) {
    yStepDown(-nbSteps);
  }
}

void yStepUp(int nbSteps) {
  yPos = stepUp(nbSteps, yPos, yMaxPos, yStepPin, yDirPin, yMicrostepping);
}

void yStepDown(int nbSteps) {
  yPos = stepDown(nbSteps, yPos, &yPosCalibrated, yFinDeCoursePin, yStepPin, yDirPin, yMicrostepping);
}

void zStep(int nbSteps) {
  if(nbSteps > 0) {
    zStepUp(nbSteps);
  } else if(nbSteps < 0) {
    zStepDown(-nbSteps);
  }
}

void zStepUp(int nbSteps) {
  zPos = stepUp(nbSteps, zPos, zMaxPos, zStepPin, zDirPin, zMicrostepping);
}

void zStepDown(int nbSteps) {
  zPos = stepDown(nbSteps, zPos, &zPosCalibrated, zFinDeCoursePin, zStepPin, zDirPin, zMicrostepping);
}

int stepUp(int nbSteps, int pos, int maxPos, int stepPin, int dirPin, int microstep) {
  for(int i = 0; i < nbSteps; i ++) {
    if(pos < maxPos) {
      digitalWrite(dirPin, LOW);
      runOneStep(stepPin, microstep);
      pos ++;
    }
  }
  return pos;
}

int stepDown(int nbSteps, int pos, int* posCalibrated, int finDeCoursePin, int stepPin, int dirPin, int microstep) {
  for(int i = 0; i < nbSteps; i ++) {
    if(digitalRead(finDeCoursePin)) {
      pos = 0;
      *posCalibrated = 1;
    }
    if(!*posCalibrated || pos > 0) {
      digitalWrite(dirPin, HIGH);
      runOneStep(stepPin, microstep);
      pos --;
    }
  }
  return pos;
}

void runOneStep(int stepPin, int microstep) {
  int delayMicros = 400 / microstep;
  for(int i = 0; i < microstep; i ++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delayMicros);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delayMicros);
  }
}

// -------------------------------------------GETTER FUNCTIONS-----------------------------------------------//

void getXCenterCamera() {
  return xCenterCamera;
}

void getXOffsetCalibrationCamera() {
  return xOffsetCalibrationCamera;
}

void getYCenterCamera() {
  return yCenterCamera;
}

void getYOffsetCalibrationCamera() {
  return yOffsetCalibrationCamera;
}

void getZCenterCamera() {
  return zCenterCamera;
}

void getZOffsetCalibrationCamera() {
  return zOffsetCalibrationCamera;
}
