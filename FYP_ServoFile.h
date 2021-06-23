#include <Servo.h>

class ServoRotator
{
  
  private:
  
  const int servoPin = 3;
  
  const int angle1=10;
  const int angle2=angle1+40;

  Servo Motor;
  int a;                            //initial angle

  public:
    
  void Rotator()
  {
   for(a=angle1;a<=angle2;a++)
   {
     Motor.write(a);
     delay(1);
   }
   for(a=angle2;a>=angle1;a--)
   {
     Motor.write(a);
     delay(1);
   }
  }

  void Reset()
  {
    Motor.write(106);
  }

  void SetServoPin()
  {
    Motor.attach(servoPin);
  }

  void SetInitialAngle(int x)
  {
    a = x;
  }
  void Off()
  {
    Motor.detach();
  }
};
