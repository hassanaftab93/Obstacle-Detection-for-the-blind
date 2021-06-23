#include "FYP_ServoFile.h"
#include "FYP_DistanceDetectFile.h"
#include "FYP_BuzzerFile.h"
#include "FYP_GSMFile.h"
#include "FYP_GPSFile.h"

int safedistance = 25;             //In inches
float longitude;
float latitude;

String hassan = "\"+923135189591\"";
//String babar  = "\"+923349577831\"";
//String homenumber = "\"+923009878698\"";
/*
  Pins Used so Far in the Arduino
  
  3   -   Servo Motor
  4   -   Trig(UltraSonic)
  5   -   Echo(UltraSonic)
  6   -   Led(Buzzer)
  7   -   Transmitter(SIM VT)
  8   -   Reciever(SIM VR)
  9   -   Button LED
  10  -   TX (GPS)
  11  -   RX (GPS)
  
  Pending:
  1.    Set TXRX Pins to 7 and 8                                                                    DONE    - Pins Set
  1.1.  Figure out a way to put SoftwareSerial in GPS File in private variables. (Possibly Solved?) DONE    - SoftwareSerial Set in Files.
  2.    Check GSM Status                                                                            DONE    - GSM Tested
  2.1.  Send Messages                                                                               DONE    - Messages Sent
  3.    Set up the GPS Module                                                                       DONE    - Location saved
  3.1.  Send GPS Coordinates as Google URL as text.                                                 DONE    - Sent Successfully

*/

ServoRotator ServoObject;                //FYP_ServoFile.h
ObstacleDetector SensorObject;           //FYP_DistanceDetectFile.h
Buzzer BuzzerObject;                     //FYP_BuzzerFile.h
SIM SimObject;                           //FYP_GsmFile.h
GPS GpsObject;                           //FYP_GpsFile.h

const int buttonPin = 9;

int distanceDetect = 0;
int state = 0;
int baudrate = 19200;                     //Only 19200 works for SIM, so i used this for Serial Monitor too.
int gpsbaudrate = 9600;                   //Only 9600 works for GPS Module.

String locationMessage = "";

void setup() {

  SensorObject.SetTriggerPin();
  SensorObject.SetEchoPin();
  BuzzerObject.SetLedPin();

  ServoObject.SetInitialAngle(0);
  BuzzerObject.LedOff();
  
  Serial.begin(baudrate);
  Serial.println("Serial Monitor: Active\n");
  delay(500);
  
  String Registered = SimObject.getNumber(hassan);
  
  Serial.println("\nNumber:"+Registered+" has been registered.\n");
  delay(500);
  
  SimObject.getbaudRate(baudrate);
  Serial.println("\nBaudrate:"+ (String)baudrate +" set for SIM.\n");
  delay(500);
  
  SimObject.InitializeGSM();
  Serial.println("\nGSM SIM Module Initialized.\n");
  delay(500);
  
  GpsObject.getbaudRate(gpsbaudrate);
  Serial.println("\nBaudrate:"+ (String)gpsbaudrate +" set for GPS.\n");
  delay(500);
  
  GpsObject.InitializeGPS();
  Serial.println("\nGPS Module has been Initialized.\n");
  
  showDeviceStatus();
  Serial.println("\n-------Device is Ready.-------\n");
}

void loop()
{
  delay(200);
  MainRun();

  //--Module Testing--//
  
  //StartToDetect();            //UltraSonic Sensor
  //saveLocation();             //Location Retrieval on Main File.       
  //GpsObject.GetLocation();    //GPS Module
}

//----------------------------------------Functions-------------------------------------------//

void showDeviceStatus() //Led Blink + Beep Twice to signal that device is ready.
{
  BuzzerObject.LedOn();
  delay(200);
  BuzzerObject.LedOff();
  delay(200);
  BuzzerObject.LedOn();
  delay(200);
  BuzzerObject.LedOff();
}

void MainRun()
{
  if (digitalRead(buttonPin) == HIGH && state == 0) 
  {
    GpsObject.Off();
    constructSMS();
    delay(200);
    Serial.println(locationMessage);
    delay(1);
    SimObject.sendSMS(locationMessage);
    state = 1;
  } 
  else
  {
    state = 0;
    StartToDetect();
    GpsObject.On();
    saveLocation();
  }
}

void StartToDetect()
{
  distanceDetect = SensorObject.Sense(safedistance);

  if(distanceDetect == 1)
  {
    ServoObject.SetServoPin();
    BuzzerObject.LedOn();
    ServoObject.Rotator();
    ServoObject.Reset();
  }
  else if(distanceDetect == 0)
  {
    BuzzerObject.LedOff();
    ServoObject.Off();
  }
}

void saveLocation()
{
  GpsObject.GetLocation();
  longitude = GpsObject.setLongg();
  latitude = GpsObject.setLatt();
  Serial.println("\nLocation saved..\n");
  displayValuesSaved();
}

void displayValuesSaved()
{
  if(latitude == 0.0 && longitude == 0.0)
  {
    Serial.print("\nGPS can't get a fix, Please move outdoors.");
  }
  else
  {
    Serial.print(F("\nLatest Values: ")); 
    Serial.print(latitude, 6);
    Serial.print(F(","));
    Serial.print(longitude, 6);
    delay(20);
    constructSMS();
  }
  
}

void constructSMS()
{
  locationMessage = "";
  String latReady = String(latitude,6);
  String longReady = String(longitude,6);
  delay(20);
  locationMessage = "http://maps.google.com/?q="+latReady+","+longReady+""; //Working
  //int x = sprintf(locationMessage,"http://maps.google.com/?q=%f,%f",latitude,longitude);
  Serial.println();
  Serial.println(locationMessage);
  Serial.println("\nSMS Ready!\n");
}
