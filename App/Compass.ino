/*
  * Function Purpose:
  * The Compass function displays the heading value of the compass along with the corresponding cardinal direction on the LCD screen.
  * Behavior Summary:
  *   The first line of the LCD shows the title < Magnetic Compass >.
  *   The second line dynamically updates to show:
  *   The numeric heading value (in degrees).
  *   The corresponding cardinal direction (e.g., North, Southeast).
  *   Pressing the Enter button toggles between states using the set1 variable.
  * Cardinal Direction Mapping:
  *   The heading value is categorized into cardinal directions:
  *     0° to 5° and 355° to 360°: North.
  *     5° to 85°: Northeast.
  *     85° to 95°: East, and so on.
  *   This mapping ensures that the displayed direction corresponds to the compass heading.
  * Placeholder Heading:
  *   The heading variable is hardcoded to 5 in this version of the code.
  *   To make this functional, you need to calculate the heading based on the compass sensor's readings (compass.m.x, compass.m.y).
  */

void Compass(){ 

  lcd.setCursor(0,0);
  // Display title Magnetic Compass the first LCD line.
  lcd.print("< Mag Compass >");
      
  // Check if the Enter button is pressed and set a flag.
  if(!digitalRead(EnterButton))e_EnterButton = 0x01; 
  
  // If the Enter button is released and the flag is set.
  if(digitalRead(EnterButton) && e_EnterButton){     
                                                
     e_EnterButton = 0x00; // Clear the flag.                       
     set1++; // Increment the `set1` counter.                                     
     
     if(set1 > 2) set1 = 0x01; // If `set1` exceeds 2, reset it to 1 to cycle between states.
    
    // When in state `set1 == 1`, display the compass heading.
     while (set1 == 0x01){

          // Read compass and accelerometer data.                    
          compass.read(); 
          accelerometer.read();

          // Placeholder heading value (to replace with actual calculation).
          int heading = computeHeading();
          // Display the numeric heading value with a degree symbol.
          lcd.setCursor(0,1);
          lcd.print(heading);
          lcd.write(B11011111); // Degree symbol.
          
          // Display the corresponding cardinal direction based on the heading.
          if(heading >= 0 && heading <= 5 ){
            lcd.print(" North          ");
          }
          if(heading > 5 && heading < 85){
            lcd.print(" Northeast       ");
          }
          if(heading >= 85 && heading <= 95){
            lcd.print(" East          ");
          }
          if(heading > 95 && heading < 175){
            lcd.print(" Southeast        ");
          }
          if(heading >= 175 && heading <= 185){
            lcd.print(" South            ");
          }
          if(heading > 185 && heading < 265){
            lcd.print(" Southwest       ");
          }
          if(heading >= 265 && heading <= 275){
            lcd.print(" West          ");
          }
          if(heading > 275 && heading < 355){
           lcd.print(" Northwest       ");
          }
          if(heading >= 355 && heading <= 360){
            lcd.print(" North          ");
          }

          // Check if the Enter button is pressed and set the flag.      
          if(!digitalRead(EnterButton))e_EnterButton = 0x01; 

          // If the Enter button is released and the flag is set, increment `set1`.
          if(digitalRead(EnterButton) && e_EnterButton){     
            e_EnterButton = 0x00; 
            set1++;                                 
          }

          delay(300); // Delay for button debounce. 
      }
    }
}


/*
source: https://github.com/pololu/lis3mdl-arduino/blob/master/examples/HeadingWithLSM6/HeadingWithLSM6.ino#L86
Returns the angular difference in the horizontal plane between the
"from" vector and north, in degrees.

Description of heading algorithm:
Shift and scale the magnetic reading based on calibration data to find
the North vector. Use the acceleration readings to determine the Up
vector (gravity is measured as an upward acceleration). The cross
product of North and Up vectors is East. The vectors East and North
form a basis for the horizontal plane. The From vector is projected
into the horizontal plane and the angle between the projected vector
and horizontal north is returned.
*/
template <typename T> float computeHeading(LIS3MDL::vector<T> from)
{
  LIS3MDL::vector<int32_t> temp_m = {compass.m.x, compass.m.y, compass.m.z};

  // copy acceleration readings from LSM6::vector into an LIS3MDL::vector
  LIS3MDL::vector<int16_t> a = {accelerometer.a.x, accelerometer.a.y, accelerometer.a.z};

  // subtract offset (average of min and max) from magnetometer readings
  temp_m.x -= ((int32_t)running_min.x + running_max.x) / 2;
  temp_m.y -= ((int32_t)running_min.y + running_max.y) / 2;
  temp_m.z -= ((int32_t)running_min.z + running_max.z) / 2;

  // compute E and N
  LIS3MDL::vector<float> E;
  LIS3MDL::vector<float> N;
  LIS3MDL::vector_cross(&temp_m, &a, &E);
  LIS3MDL::vector_normalize(&E);
  LIS3MDL::vector_cross(&a, &E, &N);
  LIS3MDL::vector_normalize(&N);

  // compute heading
  float heading = atan2(LIS3MDL::vector_dot(&E, &from), LIS3MDL::vector_dot(&N, &from)) * 180 / PI;
  if (heading < 0) heading += 360;
  return heading;
}

/*
Returns the angular difference in the horizontal plane between a
default vector (the +X axis) and north, in degrees.
*/
float computeHeading()
{
  return computeHeading((LIS3MDL::vector<int>){1, 0, 0});
}