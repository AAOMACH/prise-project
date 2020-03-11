/*
 * 

 */

#include <SoftwareSerial.h>
 
#define VIN A0 // define the Arduino pin A0 as voltage input (V in)
const float VCC   = 5.0;// supply voltage is from 4.5 to 5.5V. Normally 5V.
const int model = 1;   // enter the model number (see below)

int offset =20;// set the correction offset value
SoftwareSerial sw(2, 3); // RX, TX

float cutOffLimit = 1.01;// set the current which below that value, doesn't matter. Or set 0.5

/*
          "ACS712ELCTR-05B-T",// for model use 0
          "ACS712ELCTR-20A-T",// for model use 1
          "ACS712ELCTR-30A-T"// for model use 2  
sensitivity array is holding the sensitivy of the  ACS712
current sensors. Do not change. All values are from page 5  of data sheet          
*/
float sensitivity[] ={
          0.185,// for ACS712ELCTR-05B-T
          0.100,// for ACS712ELCTR-20A-T
          0.066// for ACS712ELCTR-30A-T
     
         }; 


const float QOV =   0.5 * VCC;// set quiescent Output voltage of 0.5V
float voltage1;// internal variable for voltage

void setup() {
   
    Serial.begin(9600);// initialize serial monitor
    sw.begin(9600);
   
}

void loop() {

  //Serial.println("Am ok");

  // Voltage Sensor
  int volt = analogRead(A1);// read the input

  //ACS712 Current Sensor 
  float voltage_raw =   (5.0 / 1023.0)* analogRead(VIN);// Read the voltage from sensor
  voltage1 =  voltage_raw - QOV + 0.012 ;// 0.000 is a value to make voltage zero when there is no current
  float current = voltage1 / sensitivity[model];
  double voltage = map(volt,0,1023, 0, 2500) + offset;// map 0-1023 to 0-2500 and add correction offset
  voltage /=100;// divide by 100 to get the decimal values

 
  if(abs(current) > cutOffLimit ){
    //Serial.println("c%luv%lu",(current,voltage));
    Serial.println(current);
    Serial.println(voltage);
    sw.print("c");
    sw.print(current);
    sw.print(",");
    sw.print("v");
    sw.print(voltage);
    sw.print(",");
    
    //sw.print("c%f v%lf",(current,voltage));
    //Serial.println(current);
    //Serial.println("%lu",current);
  }else{
    //Serial.write("%lf",voltage);
    Serial.println("No Current and voltage");
    sw.print("c0v0");
  }
  delay(500);
} 
