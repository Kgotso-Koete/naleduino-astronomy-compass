// Function to display the horizontal tilt angle or Latitude
void Inclination(){


    lcd.setCursor(0,0);
    lcd.print("<  Inclination  >");
     
    /*
    * Checks if the "Enter" button is pressed (digitalRead returns LOW when pressed).
    * If true, it sets the flag e_EnterButton to 0x01.
    */
    if(!digitalRead(EnterButton))e_EnterButton = 0x01; // Enter button pressed? Set flag
    
    /*
    * Checks if the "Enter" button is released (digitalRead returns HIGH) and the flag e_EnterButton is set (0x01). 
    * This condition ensures the button is not held continuously.
    */
    if(digitalRead(EnterButton) && e_EnterButton){   // Enter button released and flag set?  

      // Clears the button flag (e_EnterButton) and increments the variable set1, which tracks the submenu state.
      e_EnterButton = 0x00; // Clear the flag
      set1++; // Increment set1
      
      // Resets set1 to 0x01 if it exceeds 2. This creates a cyclic menu structure.
      if(set1 > 2) set1 = 0x01; // Reset set1 to 1 if it exceeds 2
     
      /*
      * Inclination display loop 
      * Enters a loop when set1 equals 0x01. This loop handles the display and logic for the Inclination mode.
      */
      while (set1 == 0x01){
     
            int regis_Y; // Declare an integer regis_Y to store the processed inclination value
            compass.read(); // Read compass sensor data

            /*
            * This equation transforms the raw magnetometer data (compass.m.y) 
            * into a meaningful inclination angle that fits a desired range (e.g., -90° to +90°).
            * Processes the compass.m.y (magnetometer’s Y-axis value) to calculate the inclination angle
            * Divides compass.m.y by 100 to normalize the reading.
            * Multiplies by 90 / 175 to scale it to an inclination range.
            * Multiplies by -1 to invert the value.
            */
            regis_Y = (compass.m.y / 100) *90/175*-1; // Process Y-axis for inclination
   
            lcd.setCursor(0,1);
            lcd.print("<= "); // Left arrow
            lcd.print(regis_Y); // Display inclination value
            lcd.write(B11011111); // Degree symbol
            lcd.print(" Latitude       "); // Label as Latitude
        
            if(!digitalRead(EnterButton))e_EnterButton = 0x01; // Enter button pressed? Set flag
            if(digitalRead(EnterButton) && e_EnterButton){    // Enter button released and flag set?
              e_EnterButton = 0x00; // Clear flag
              set1++; // Exit loop                                 
            }

            delay(300); // Stabilize display and debounce button
      } 
   }
}
