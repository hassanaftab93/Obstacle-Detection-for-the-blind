class ObstacleDetector
{
  private:
  
    const int trigPin = 4;
    const int echoPin = 5;
    
    unsigned long duration = 0;
    int distance = 0;
    
    const int leastDist = 8;
    const int readableDistance = 40;
    
    
  public:

    void SetTriggerPin()
    {
      pinMode(trigPin,OUTPUT);
    }

    void SetEchoPin()
    {
      pinMode(echoPin,INPUT);
    }
  
    int Sense(int safedistance)
    {
      digitalWrite(trigPin,LOW);
      delayMicroseconds(5);
    
      digitalWrite(trigPin,HIGH);
      delayMicroseconds(15);
      digitalWrite(trigPin,LOW);
    
      duration = pulseIn(echoPin,HIGH,30000);
      delay(1);
      while (duration != 0)
      {
        //Edit Start
      distance = (duration * 0.0342)/2;
      distance = distance / 2.54;
      
      if(distance <= readableDistance && distance != 5 && distance != 3)
      {
        if(distance <= safedistance)
        {
          Serial.print("\nDistance: ");
          Serial.print(distance);
          Serial.println(" inch");
          Serial.println(" WARNING, OBJECT IS WITHIN SAFE DISTANCE");
          return 1;
        }
        else
        return 0;
      }
      else
        return 0;
      } // While Loop Edit
    }
};
