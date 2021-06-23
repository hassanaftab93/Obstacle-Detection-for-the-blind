#include <SoftwareSerial.h>

SoftwareSerial simSerial(7,8); //txrx

class SIM
{
  private:
    String number;
    String type = "\"GSM\"";
    int baudrate;
  public:

    String getNumber(String Number)
    {
      number = Number;
      return number;
    }

    void getbaudRate(int baud)
    {
      baudrate = baud;
    }
    
    void InitializeGSM()
    {
      simSerial.begin(baudrate);
      
      Serial.println("\nHandshaking with GSM Module..");
      simSerial.println("AT"); //Handshake Test, Should return OK.
      delay(1000);
      updateSerial();

      Serial.println("\nPhone Functionality");
      simSerial.println("AT+CFUN?");
      delay(1000);
      updateSerial();

      Serial.println("\nSignal Quality Test. (0-31)");
      simSerial.println("AT+CSQ"); //Signal quality test, 31 Best Value
      delay(1000);
      updateSerial();

      Serial.println("\nSIM Plugged In Status..");
      simSerial.println("AT+CCID"); //Sim Plugged In?
      delay(1000);
      updateSerial();

      Serial.println("\nNetworks:-");
      simSerial.println("AT+COPS?"); //SIMs Network
      delay(1000);
      updateSerial();

      Serial.println("\nSIM Registration Status..");
      simSerial.println("AT+CREG?"); //Registered to Network?
      delay(1000);
      updateSerial();
    }

    void updateSerial()
    {
      delay(500);
       while (Serial.available()) 
       {
          simSerial.write(Serial.read());//Commands are forwarded to SimSerial Object
       }
       while(simSerial.available()) 
       {
          Serial.write(simSerial.read());//Replies are sent to Serial Monitor
       }
    }

    void sendSMS(String SMS)
    {
      Serial.println("\nConfiguring TEXT Mode..");
      simSerial.println("AT+CMGF=1\r"); // Configuring TEXT mode
      updateSerial();
      delay(2000);
      
      Serial.println("\nConfiguring SMS-Encoding to GSM Mode..");
      simSerial.println("AT+CSCS="+type);
      updateSerial();
      delay(2000);

      Serial.println("\nSending SMS..");
      simSerial.println("AT+CMGS="+number+"\r");
      simSerial.println((char)13);
      delay(2000);
      simSerial.println(SMS);
      delay(2000);
      simSerial.println((char)26);
      updateSerial();
      Serial.println("\nMessage Sent..");
    }
};
