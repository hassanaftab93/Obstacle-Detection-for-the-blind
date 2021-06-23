class Buzzer
{
  private:

  const int ledPin = 6;

  public:

  void LedOn()
  {
    digitalWrite(ledPin,HIGH);
  }

  void LedOff()
  {
    digitalWrite(ledPin,LOW);
  }

  void SetLedPin()
  {
    pinMode(ledPin,OUTPUT);
  }
};
