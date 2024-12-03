
/*
  * Function to draw the progress bar and display the percentage. 
  * Percentage Display on LCD:
  *   The first line of the LCD shows the numeric percentage value.
  *   The second line displays the progress bar.
  * Mapping to LCD Columns:
  *   The map() function converts the percentage (0–100%) into the number of segments to display on the LCD.
  *   Each LCD column can show 5 segments (custom characters). For example:
  *     25% corresponds to one column completely filled (5 segments).
  *     50% corresponds to two columns completely filled (10 segments).
  * Custom Characters:
  *   Characters 0 to 5 represent progress bar states, ranging from empty to fully filled.
  *   These characters are created in memory using the lcd.createChar() function (likely configured in another file, like ConfigProgressBar.ino).
  *   Dynamic Updates:
  *     The code includes logic to clear leftover characters when transitioning from higher to lower percentage values.
  *     For example, when going from 100% to 99%, extra digits from the previous value are erased by adding spaces.
  * Progress Bar Loop:
  *   The for loop iterates through each LCD column (LCD_NB_COLUMNS), determining how many segments to fill per column based on the nb_columns value.
 */

void ProgressBar(){ 
  
  lcd.clear(); // Clear the LCD display.

  // Display the percentage value on the first line.
  lcd.setCursor (0,0); 
  lcd.print (percent); 
  lcd.print (F("%")); // Add "%" after the percentage.
  
  // Add spaces to erase leftover digits when updating smaller numbers.
  // For example, when transitioning from 100% to 99%, the last "0" must be cleared.
  // Move the cursor to the second line of the LCD.
  lcd.setCursor (0,1); 
  
  // Map the percentage range (0–100%) to the total available progress bar width.
  // The bar consists of `LCD_NB_COLUMNS` characters, each with 5 segments.
  byte nb_columns = map(percent,0,100,0,LCD_NB_COLUMNS * 5 );
  
  // Draw each character in the progress bar.
  for (byte i=0; i<LCD_NB_COLUMNS; ++i){ 
  
    // If no more segments to display, fill with an empty character (0).
    if (nb_columns == 0){ // Case 
      lcd.write((byte)0); 
    }
    // If a full segment remains, display a completely filled character (5).
    else if(nb_columns >= 5){ 
      lcd.write(5); 
      nb_columns -= 5; // Reduce remaining segments by 5.
    }
    // If there are leftover segments (1–4), display the partially filled character.
    else { 
      lcd.write(nb_columns); 
      nb_columns = 0 ;  // Mark remaining segments as used.
    } 
    // Increment the percentage (for demo purposes).
    percent ++;
    // Delay for visibility between updates.
  }

 delay(500); // Delay for visibility between updates.
}
