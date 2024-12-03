/*
 * This function detects button presses and releases to change the menu options displayed on the LCD. 
 * When a button is pressed, it sets a flag to indicate an action, and on release, it clears the flag, updates the menu variable, and refreshes the LCD
 * with the new menu option. This function is central to navigating between different display modes or options in the project.
 */


/*
 * Button Press Detection: 
 * digitalRead(LeftButton) and digitalRead(RightButton) are used to read the state of the "Left" and "Right" buttons, respectively.
 * If the "Left" button is pressed (!digitalRead(LeftButton)), the e_LeftButton flag is set to 1.
 * If the "Right" button is pressed (!digitalRead(RightButton)), the e_RightButton flag is set to 1.
 */

/*
 * Button Release Handling: 
 * Once the "Left" button is released (digitalRead(LeftButton) && e_LeftButton), it confirms that a "Left" press occurred. It then:
 *  Clears the e_LeftButton flag,
 *  Clears the LCD to prepare for the new menu,
 *  Increments menu to advance to the next option.
 * Similarly, if the "Right" button is released (digitalRead(RightButton) && e_RightButton), it:
 *  Clears the e_RightButton flag,
 *  Clears the LCD,
 *  Decrements menu to go back to the previous option.
 */

/*
 * Menu Limits:
 * menu is constrained within a range of 1 to 3:
 *  If incrementing menu makes it greater than 3, it loops back to 1.
 *  If decrementing menu makes it less than 1, it loops back to 3.
 */

void ChangeMenu(){

   if(!digitalRead(LeftButton)){e_LeftButton = 0x01;}    // Check if the "Left" button is pressed. If so, set the e_LeftButton flag to 1
   if(!digitalRead(RightButton)){e_RightButton = 0x01;}    // Check if the "Right" button is pressed. If so, set the e_RightButton flag to 1
      
   if(digitalRead(LeftButton) && e_LeftButton){          // Check if "Left" button is released AND e_LeftButton flag is set
                                                   // If true..
      e_LeftButton = 0x00;                            // Clear the e_LeftButton flag (set it back to 0)
      
      lcd.clear();                                 // Clear the LCD display
      menu++;                                      // Increment the menu variable to move to the next menu option
      
      if(menu > 0x03){ menu = 0x01;}               // If menu exceeds 3, reset it to 1 (loops back to the first menu option)
   } 
   
   if(digitalRead(RightButton) && e_RightButton){           // Check if "Right" button is released AND e_RightButton flag is set
                                                    // If true...
      e_RightButton = 0x00;                             // Clear the e_RightButton flag (set it back to 0)
      
      lcd.clear();                                  // Clear the LCD display
      menu--;                                       // Decrement the menu variable to move to the previous menu option
      
      if(menu < 0x01){ menu = 0x03;}                // If menu goes below 1, reset it to 3 (loops back to the last menu option)
   }    
}
