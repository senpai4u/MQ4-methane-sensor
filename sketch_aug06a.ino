const int gasPin = A0;  //GAS sensor output pin to Arduino analog A0

void setup()
{
  Serial.begin(9600);   //Initialize serial port at 9600 bps
}

void loop()
{
  Serial.println(analogRead(gasPin));
  delay(1000);          //Prints value every 1 sec
}   
