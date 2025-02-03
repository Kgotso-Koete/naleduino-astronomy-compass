// Compass calibration function
char report[80];
/*
 * Performs a calibration routine by continuously reading sensor data to find min/max compass values, 
 * displaying the progress visually as a bar, and completing with a message when finished. 
 * The calculated min/max values help the compass provide accurate directional information.
 */
void Calibrate(){
    /*
    * Looping and Calibration Progress:
    * The while loop runs until contador (the counter variable) reaches 101, which indicates that calibration is complete. 
    * Within each loop:
    *   compass.read() gathers the current magnetic field values from the compass sensor.
    */
    while (calibrationCounter != 101){ // Loop until calibrationCounter reaches 101 (indicating calibration is complete)
          compass.read(); // Read the current compass data
          
          // Initialize min/max values for calibration
          LIS3MDL::vector<int16_t> running_min = {32767, 32767, 32767}, running_max = {-32768, -32768, -32768}; 

          /*
          * Running Min/Max Calculation:
          * running_min and running_max are initialized with extreme values to ensure they capture the minimum and maximum readings during calibration. 
          * min and max functions update running_min and running_max with the lowest and highest readings from 
          * compass.m.x, compass.m.y, and compass.m.z, tracking the range of the sensor's readings.
          */
      
          // Update running_min and running_max based on current compass readings
          running_min.x = min(running_min.x, compass.m.x); // Track minimum x value
          running_min.y = min(running_min.y, compass.m.y); // Track minimum y value
          running_min.z = min(running_min.z, compass.m.z); // Track minimum z value

          running_max.x = max(running_max.x, compass.m.x); // Track maximum x value
          running_max.y = max(running_max.y, compass.m.y); // Track maximum y value
          running_max.z = max(running_max.z, compass.m.z); // Track maximum z value

          snprintf(report, sizeof(report), "min: {%+6d, %+6d, %+6d}   max: {%+6d, %+6d, %+6d}",
          running_min.x, running_min.y, running_min.z,
          running_max.x, running_max.y, running_max.z);
          Serial.println(report);
    
          /*
          * Displaying Calibration Progress:
          * The progress percentage (percent) is displayed on the LCD, and the second row uses custom characters to show a progress bar.
          * nb_columns is calculated to determine the visual length of the progress bar based on percent.
          * The loop iterates through LCD columns, displaying either empty, partial, or full blocks according to nb_columns.
          */
          lcd.clear(); // Clear the LCD
          lcd.setCursor (0,0); // Set cursor to the first row, first column
          lcd.print("Calibrating "); // Display "Calibrating"
          lcd.print (percent);  // Display the current calibration progress percentage
          lcd.print (F("%")); // Display the "%" symbol
    
          lcd.setCursor (0,1); // Move cursor to the second row

          /*
          * The map() function in Arduino scales a value from one range to another. 
          * In this case, it takes the percent value (which ranges from 0 to 100) and maps it to a new range of 0 to LCD_NB_COLUMNS * 5.
          * Here, LCD_NB_COLUMNS is set to 16 (indicating the LCD has 16 columns), so LCD_NB_COLUMNS * 5 equals 80.
          * Each column on the LCD can show 5 different fill levels (from 0 to 5) due to custom characters (DIV_0_OF_5, DIV_1_OF_5, etc.).
          * By multiplying LCD_NB_COLUMNS by 5, map() converts percent into a scale that represents these fill levels for each column, so the progress bar displays smoothly.
          * nb_columns becomes the "progress units" for the LCD display. 
          * nb_columns represents how many of the total 80 units (16 columns with 5 levels each) should be displayed based on the current percent.
          * In each iteration of the loop, nb_columns decreases as blocks are filled on the progress bar.
          */
          byte nb_columns = map(percent,0,100,0,LCD_NB_COLUMNS * 5 ); // Map percent to LCD column units
          
          // Iterate over LCD columns to draw the progress bar
          for (byte i=0; i<LCD_NB_COLUMNS; ++i){
             // If no progress, show an empty block
            if (nb_columns == 0){  
              lcd.write((byte)0); 
            }
            // If enough progress for a full block
            else if(nb_columns >= 5){ 
            lcd.write(5); // Display a fully filled block
            nb_columns -= 5; // Reduce nb_columns by 5
            }
            // If remaining part of a partial block
            else{
            lcd.write(nb_columns); // Display partial block
            nb_columns = 0 ; // Reset nb_columns to 0
            } 
          }
          // If percent reaches 101, reset it
          if (++percent == 101){
            percent = 0;
            delay(1000); // Delay to show full calibration
          }

          delay(100); // Brief delay to slow the calibration process visually
          calibrationCounter++; // Increment calibrationCounter by 1
    
   }

   lcd.setCursor(0,0); // After calibration, move cursor to the first row
   lcd.print("Calibrated! "); // Display "Calibrated!" 
   delay(3000); // Show message for 3 seconds
}
