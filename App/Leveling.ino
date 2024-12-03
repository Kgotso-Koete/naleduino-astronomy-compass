/*
  * This function provides a visual display of the X and Y axis values, which can help determine the device's tilt or leveling state
  * The function starts by displaying a title on the LCD
  * If the Enter button is pressed, it cycles between different states (set1 values)
  * In the first state (set1 == 1), it:
  *   Creates and uses custom arrow characters to visually represent directional tilt (up or down).
  *   Reads X and Y axis values from the magnetometer.
  *   Displays these values along with directional symbols.
  */

void Leveling(){
    
    lcd.setCursor(0,0);
    lcd.print("<  Leveling >"); // Displays "Leveling" on the first line of the LCD screen.
    
    if(!digitalRead(EnterButton))e_EnterButton = 0x01;// Check if the Enter button is pressed and set a flag.
    
    if(digitalRead(EnterButton) && e_EnterButton){     // If the Enter button is released and the flag is set.

      e_EnterButton = 0x00; // Clear the flag.
      set1++; // Increment the `set1` counter.
     
      if(set1 > 2) set1 = 0x01; // If `set1` exceeds 2, reset it to 1 to loop between states.
      
      /*
      * Custom Characters:
      *   The function defines two custom arrow characters:
      *     Upward arrow (upArrow): Indicates upward tilt.
      *     Downward arrow (downArrow): Indicates downward tilt.
      *     These characters are created and stored in the LCD's memory slots (lcd.createChar).
      */
      while (set1 == 0x01){                      
            // Create a custom arrow character pointing upward.
            byte upArrow[8] = {0b00100,0b01110,0b10101,0b00100,0b00100,0b00100,0b00100,0b00100};
            // Store the upward arrow in slot 1.
            lcd.createChar (1, upArrow); 
            // Create a custom arrow character pointing downward.
            byte downArrow[8] = {0b00100,0b00100,0b00100,0b00100,0b00100,0b10101,0b01110,0b00100}; 
            // Store the downward arrow in slot 2.
            lcd.createChar (2, downArrow);
    
            int regis_X; // Variable for X-axis data.
            int regis_Y; // Variable for Y-axis data.
        
            compass.read(); // Read compass data.
            
            // Normalize X and Y axis data for display.
            regis_X = (compass.m.x/1000);
            regis_Y = (compass.m.y/1000);
            
            // Display leveling data on the LCD.
            lcd.setCursor(0,1);
            lcd.write(B01111110); // Write a special character (block).
            lcd.print("+");
            lcd.write(B01111111); // Write another special character (block).
            lcd.print("-:");
            lcd.print(regis_X); // Display the X-axis value.

            lcd.print("  ");        
            lcd.write(2); // Display the downward arrow (custom character).
            lcd.print("+");
            lcd.write(1); // Display the upward arrow (custom character).
            lcd.print("-:");
            lcd.print(regis_Y);  // Display the Y-axis value.
    
            lcd.print("  ");
          
            // Check if Enter button is pressed and set the flag.
            if(!digitalRead(EnterButton))e_EnterButton = 0x01; 

            // If Enter button is released and flag is set, increment `set1`.
            if(digitalRead(EnterButton) && e_EnterButton){  
              e_EnterButton = 0x00;                         
              set1++;                                 
            }

            delay(300); // Wait 300 milliseconds to debounce buttons.
      }
   }
}
  
