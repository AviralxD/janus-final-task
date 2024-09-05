#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include "ms4525do.h"

const float density = 1;

// Following code is an analogRead based implementation and does not use i2c communication
// I wrote it as a last resort if I'm unable to finish the task

// const short pressureInput = A0;   // select the analog input pin for the pressure transducer
// const int p_Zero = 0;             // value of sensor at 1 psi pressure 
//                                   //should be changed to correspond to the 
//                                   // experimental reading of the sensor at 1 psi pressure
// const int p_Max = 1023            // value of sensor at 150 psi pressure
//                                   // should be changed to correspond to the 
//                                   // experimental reading of the sensor at 150 psi pressure

// float pReading = 0;  // variable to store the output of the transducer

float pressure = 0;  // variable to store the calculated pressure
float velocity = 0;  // variable to store the calculated velocity

LiquidCrystal_I2C lcd(0x3f, 20, 4); //sets the LCD I2C communication address; format(address, columns, rows)
Ms4525do pSensor;

void setup() {

  Serial.begin(9600);  // initializes serial monitor at 9600 biits / sec
  lcd.begin();         // initialize the LCD screen
  Wire.begin           // initialises i2c communication
  Wire.setClock(400000); // sets i2c communication frequency to 400khz (as demonstrated in the libraries' example)
  pSensor.Config(&Wire, 0x28, 1.0f, -1.0f); // configures the sensor to use bus 0, with an i2c address of 0x28, and error range of +/- 1.0 psi
}

void loop() {

  // pressure = analogRead(pressureInput)
  // pressure = map(pressure, p_Zero, p_Max, 1, 150)

  pressure = pSensor.pres_pa(); // Reads the value from sensor

  velocity = sqrt( 2 * pressure / density )

  lcd.setCursor(0,0);     // sets cursor to column 0, row 0
  lcd.print("Velocity:"); // prints label
  lcd.print(velocity, 1); // prints pressure value to lcd screen, 1 digit on float
  lcd.print("m/s");       // prints label after value
  lcd.print("   ");       // to clear the display after large values or negatives
  delay(250);             // delay in milliseconds between read values
}