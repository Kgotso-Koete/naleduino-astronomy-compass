/*
 * Function to display the menu
 * Determines which menu option to display based on the menu variable set in ChangeMenu(). 
 * This function is key for displaying the selected feature (compass, leveling, or inclination) 
 * and likely updates the LCD to reflect these readings.
 */

void DisplayMenu(){
  
  switch(menu){ // Control based on the value of menu
       case 0x01: // Case 1
             Compass();// Call the compass function (displays compass reading)
             break; // break
       case 0x02: // Caso 2
             Leveling(); // Call the leveling function (displays leveling information)
             break; // break
       case 0x03: // Caso 3
             Inclination(); // Call the inclination function (displays inclination data)
             break; // break
  }
}
