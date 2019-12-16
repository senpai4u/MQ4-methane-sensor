/*
 Arduino MQ4 gas sensor - Geekstips.com
 This example is to calculate the gas concentration using the R0
 calculated in the example above
 Also a OLED SSD1306 screen is used to display data, if you do not
 have such a display, just delete the code used for displaying
*/
#include <SPI.h>                                            //Library for SPI interface 
#include <Wire.h>                                           //Library for I2C interface 

int gas_sensor = A0;                             //Sensor pin
float m = -0.318;                                //Slope

float b = 1.133;                                 //Y-Intercept
float R0;                                        //Sensor Resistance in fresh air from previous code

void setup() {
  Serial.begin(9600);                            //Baud rate
  pinMode(gas_sensor, INPUT);                    //Set gas sensor as input

  Serial.println("What is the R0 value? ");      //Asks for user input of R0 value
  while(Serial.available()==0){ }                //Waits till user puts in value
  R0 = Serial.parseInt();                        //Takes in the value

}

void loop() {
  float sensor_volt;                             //Define variable for sensor voltage
  float RS_gas;                                  //Define variable for sensor resistance
  float ratio;                                   //Define variable for ratio
  float sensorValue = analogRead(gas_sensor);    //Read analog values of sensor
  sensor_volt = sensorValue * (5.0 / 1023.0);    //Convert analog values to voltage
  RS_gas = ((5.0 * 10.0) / sensor_volt) - 10.0;  //Get value of RS in a gas
  ratio = RS_gas / R0;                           // Get ratio RS_gas/RS_air

  double ppm_log = (log10(ratio) - b) / m;       //Get ppm value in linear scale according to the the ratio value
  double ppm = pow(10, ppm_log);                 //Convert ppm value to log scale
  double percentage = ppm / 10000;               //Convert to percentage

  Serial.print(ppm);
  Serial.println(" ppm");
  delay(500);
  }
