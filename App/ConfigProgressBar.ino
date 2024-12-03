// Stores custom characters in the LCD's memory for the progress bar.

/*
  * ConfigProgressBar sets up a custom progress bar by storing partial segments of the bar in the LCD's memory, 
  * ready to be used dynamically on the display. This allows the project to show smooth visual feedback for progress-related information.
  */

/*
  * Custom Character Storage:
  * The lcd.createChar() function is used to define custom characters on the LCD, which allows creating a progress bar.
  * Each DIV_X_OF_5 variable represents a different "step" or "division" of the progress bar, with progressively more filled blocks.
  */

/*
  * LCD Memory Locations:
  * The LCD display can store up to 8 custom characters (from locations 0 to 7).
  * Here, six custom characters (0 to 5) are stored to create a smooth visual for the progress bar.
  */

void ConfigProgressBar() {
  lcd.createChar ( 0 , DIV_0_OF_5); // Store the custom character DIV_0_OF_5 in LCD memory locat
  lcd.createChar ( 1 , DIV_1_OF_5); // Store DIV_1_OF_5 in LCD memory location 1
  lcd.createChar ( 2 , DIV_2_OF_5); // Store DIV_2_OF_5 in LCD memory location 2
  lcd.createChar ( 3 , DIV_3_OF_5); // Store DIV_3_OF_5 in LCD memory location 3
  lcd.createChar ( 4 , DIV_4_OF_5); // Store DIV_4_OF_5 in LCD memory location 4
  lcd.createChar ( 5 , DIV_5_OF_5); // Store DIV_5_OF_5 in LCD memory location 5
}
