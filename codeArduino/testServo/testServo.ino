#include <Servo.h> 

Servo monServo;

void setup()
{
    monServo.attach(10);
}

void loop()
{
    for (int position = 50; position <=120; position ++){
        monServo.write(position);  // le bras du servomoteur prend la position de la variable position
        delay(15);  // on attend 15 millisecondes
    }

    for (int position = 120; position >=50; position --){
        monServo.write(position);  // le bras du servomoteur prend la position de la variable position
        delay(15);  // le bras du servomoteur prend la position de la variable position
    }
}
