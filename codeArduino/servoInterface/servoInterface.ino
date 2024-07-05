#include <Servo.h> 

# define servoSerragePincePin 10
# define servoRotationPincePin 11
# define servoSerragePinceEquilibrePos 80
# define servoRotationPinceEquilibrePos 80
# define joystickSerragePince A0
# define joystickRotationPince A1

Servo servoSerragePince;
Servo servoRotationPince;

int servoSerragePincePos;
int servoRotationPincePos;

void setup()
{
  servoSerragePincePos = servoSerragePinceEquilibrePos;
  servoRotationPincePos = servoRotationPinceEquilibrePos;

  servoSerragePince.attach(servoSerragePincePin);
  servoSerragePince.write(servoSerragePincePos);

  servoRotationPince.attach(servoRotationPincePin);
  servoRotationPince.write(servoRotationPinceEquilibrePos);

  pinMode(joystickSerragePince, INPUT);
  pinMode(joystickRotationPince, INPUT);

}

void loop()
{
  int joystickSerragePinceVal = analogRead(joystickSerragePince);
  int joystickRotationPinceVal = analogRead(joystickRotationPince);

  if(joystickSerragePinceVal > 650) {
    servoSerragePincePos ++; // On incrémente la position du servomoteur
    servoSerragePince.write(servoSerragePincePos);
    delay(15);  // on attend 15 millisecondes
  }

  if(joystickSerragePinceVal < 350) {
    servoSerragePincePos --; // On décrémente la position du servomoteur
    servoSerragePince.write(servoSerragePincePos);
    delay(15);  // on attend 15 millisecondes
  }

  if(joystickRotationPinceVal > 650) {
    servoRotationPincePos ++; // On incrémente la position du servomoteur
    servoRotationPince.write(servoRotationPincePos);
    delay(15);  // on attend 15 millisecondes
  }

  if(joystickRotationPinceVal < 350) {
    servoRotationPincePos --; // On décrémente la position du servomoteur
    servoRotationPince.write(servoRotationPincePos);
    delay(15);  // on attend 15 millisecondes
  }
}
