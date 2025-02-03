  
/*
 * This file acts as the main sketch, 
 * setting up the LCD, buttons, and compass in setup(), 
 * and then updating the menu display in loop().
 */

/*
 * Global Variables and Constants: 
 * These include variables to handle LCD dimensions, button inputs, and compass calibration
 */

// Libraries
#include <LiquidCrystal_I2C.h> // LCD display library with I2C communication by Frank de Brabander
#include <Wire.h> // I2C communication library
#include <LIS3MDL.h> // Library for LIS3MDL compass and accelerometer module by Pololu
#include <LSM6.h> // Library for accelerometer and gyro by Pololu

// 3-axis gyroscope and 3-axis accelerometer
LSM6 accelerometer; 
// Compass/accelerometer. Defines pins A4 (SDA) and A5 (SCL)
LIS3MDL compass;
// Set the compass calibration range
LIS3MDL::vector<int16_t> running_min = {-6732, -3167, -5022}, running_max = {-287, +2147, +2649};

// Constants: LCD/Menus
LiquidCrystal_I2C lcd(0x27, 20, 3); // LCD object with I2C address 0x27, 20 columns, 3 rows
#define menu_max 3 // Max number of menus

// Buttons
#define EnterButton 11 // "Enter" button connected to pin 11
#define LeftButton 12 // "Left" button connected to pin 12
#define RightButton 10 // "Right" button connected to pin 10

 /*
  * Function prototypes are declarations that inform the compiler about functions that will be defined elsewhere in the code  
  * By declaring these prototypes, the main file (like Bussola3.ino) can call functions defined 
  * in other files or later in the same file without raising errors during compilation
  *  The prototypes include each function’s name, return type, and parameters but not the function's implementation
  */

// Function prototypes
void ChangeMenu(); // Changes the menu
void DisplayMenu(); // Displays the menu
void Compass(); // Main compass function
void ConfigProgressBar(); // Sets up the progress bar
void Calibrate(); // Calibration function for compass
void ProgressBar(); // Function for showing progress bar
void Leveling(); // Leveling function
void Inclination(); // Inclination function

// Global variables
float acc_x,  // X-axis acceleration
      acc_y, // Y-axis acceleration
      ax_offset = 0, // X-axis offset for calibration
      ay_offset = 0; // Y-axis offset for calibration

const int LCD_NB_ROWS = 2; // Number of rows on the LCD
const int LCD_NB_COLUMNS = 16; // Number of columns on the LCD

/*
 * Progress Bar Custom Characters: 
 * The byte arrays define different levels of the LCD's custom progress bar, 
 * allowing the display of partial fills.
 */
// Custom characters for progress bar, representing different fill levels (0/5 to 5/5)
byte DIV_0_OF_5[8] = {B00000,B00000,B00000,B00000,B00000,B00000,B00000,B00000}; // 0/5
byte DIV_1_OF_5[8] = {B10000,B10000,B10000,B10000,B10000,B10000,B10000,B10000}; // 1/5
byte DIV_2_OF_5[8] = {B11000,B11000,B11000,B11000,B11000,B11000,B11000,B11000}; // 2/5
byte DIV_3_OF_5[8] = {B11100,B11100,B11100,B11100,B11100,B11100,B11100,B11100}; // 3/5
byte DIV_4_OF_5[8] = {B11110,B11110,B11110,B11110,B11110,B11110,B11110,B11110}; // 4/5
byte DIV_5_OF_5[8] = {B11111,B11111,B11111,B11111,B11111,B11111,B11111,B11111}; // 5/5

static byte percent = 0; // Progress bar percentage value

int calibrationCounter = 0; // Counter for calibration

// Variables to hold the current menu and settings
char menu = 0x01, // Menu starts at menu1 on startup
     set1 = 0x00, // Activation variable 1
     set2 = 0x00; // Activation variable 2

// Button state variables
boolean e_EnterButton = 0x00, // State of "Enter" button
        e_LeftButton = 0x00, // State of "Left" button
        e_RightButton = 0x00; // State of "Right" button

////////////////////////////////////
void setup(){
  /*
  * Button and LCD Initialization: 
  * lcd.init() and lcd.backlight() prepare the LCD for use
  * Buttons are configured with INPUT_PULLUP mode, so they’re set as inputs with pull-up resistors for stable readings.
  */
  // LCD output setup
  lcd.init(); // Initialize the LCD
  lcd.backlight(); // Turn on the LCD backlight

  // Progress bar setup
  ConfigProgressBar();
   
  // Button configuration
  pinMode(EnterButton, INPUT_PULLUP); // Set "Enter" button as input with pull-up resistor
  pinMode(LeftButton, INPUT_PULLUP); // Set "Left" button as input with pull-up resistor
  pinMode(RightButton, INPUT_PULLUP); // Set "Right" button as input with pull-up resistor

// Reset button states
  e_EnterButton = 0x00; 
  e_LeftButton = 0x00;
  e_RightButton = 0x00;

  /*
    * Compass Calibration and Setup:  
    * The compass is initialized and calibrated with values that define its operational range.
    * The Calibrate() function performs automatic calibration steps.
    */

  // Compass initialization
  Serial.begin(9600);
  Wire.begin(); // Begin I2C communication

  compass.init(); // Initialize the LIS3MDL compass
  compass.enableDefault(); // Set default settings for the compass

  accelerometer.init(); // Initialize the LSM6 accelerometer
  accelerometer.enableDefault(); // Set default settings for the accelerometer

  // Auto calibration of the compass
  //Calibrate();
  percent = 0; // Reset progress percentage
  lcd.clear(); // Clear the LCD screen
}

//////////////////////

 /*
  * Loop Functions:  
  * ChangeMenu() and DisplayMenu() handle user interface interactions and display..
  * Each button press triggers a change in menu or related settings, which will change display output accordingly.
  */
void loop(){
     ChangeMenu(); // Change the menu based on button input
     DisplayMenu(); // Display the selected menu on the LCD
}
