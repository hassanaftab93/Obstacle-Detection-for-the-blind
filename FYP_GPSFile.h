#include <TinyGPS.h>

TinyGPS gps;
SoftwareSerial gpsSerial(10,11); //Black Wire TX(gps) 10 -- White Wire RX(gps) 11

class GPS
{
  private:
  
  int baudrate;
  float longg;
  float latt;
  
  public:
  
    void getbaudRate(int baud)
    {
      baudrate = baud;
    }
    
    void InitializeGPS()
    {
      gpsSerial.begin(baudrate);
      delay(1000);
      if(gpsSerial.available())
      {
        Serial.print("\nGPS Initialized.\n");
      }
    }

    float setLatt()
    {
      return latt;
    }

    float setLongg()
    {
      return longg;
    }
    
    void GetLocation()
    {
      while(gpsSerial.available())
      {
        if(gps.encode(gpsSerial.read()))
        {
          Serial.println("\n(Values Decoded): ");
          gps.f_get_position(&latt,&longg);
          delay(500);
        }
      }
    }
  
    void displayInfo() 
    {
      Serial.print(F("Location taken: ")); 
      Serial.print(latt, 6);
      Serial.print(F(","));
      Serial.print(longg, 6);
    }

    void Off()
    {
      digitalWrite(10,LOW);
      digitalWrite(11,LOW);
    }
    void On()
    {
      digitalWrite(10,HIGH);
      digitalWrite(11,HIGH);
    }
};
