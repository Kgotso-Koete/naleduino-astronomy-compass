# Naleduino Astronomy Compass

This is my implementation of the Compass for Astronomers project originally created by [Armando LeonardoS](https://www.instructables.com/member/Armando+LeonardoS/) is a DIY digital navigation tool for stargazing, allowing you to detect where the telescope' OTA is pointing to (Azimuth and Altitude position).

- Naledi means "star" in Sesotho.

## Important Note

I struggled to get calibrate the compass and learned that IMU's are not accurate Digital Setting Circles (DSCs). I abandoned the project to focus on using encoders. If you are still interested in calibrating the compass, you can check out [this blog post](https://sailboatinstruments.blogspot.com/2011/08/improved-magnetometer-calibration.html).

---

## Demo

[Link to video demo](https://youtube.com/shorts/odLFw2xVd5E?feature=share)

---

## Images

|        Naleduino Top         |        Naleduino Circuit         |
| :--------------------------: | :------------------------------: |
| ![](/images/compass_top.jpg) | ![](/images/compass_circuit.jpg) |

|        Naleduino Side         |         Schematic          |
| :---------------------------: | :------------------------: |
| ![](/images/compass_side.jpg) | ![](/images/schematic.jpg) |

---

## Project Overview

This project is a DIY compass amateur astronomers, designed to make finding planets in the night sky easier. It displays the telescopes Altitude and Azimuth position on the LCD.

### Key Features

1. **Leveling**: Guage to help level the telescope.
2. **Incliniation**: Altitude coordinates of the OTA.
3. **Magnetic Compass**: Azimuth position of the OTA.

---

## What This Code Base Covers

This Arduino code runs on the Arduino Nano to handle:

1. **Calibration**: Performs a calibration routine by continuously reading sensor data to find min/max compass values.
2. **Menu Display**: Determines which menu option to display based on the menu variable set.
3. **Compass**: The Compass function displays the heading value of the compass along with the corresponding cardinal direction on the LCD screen.
4. **Inclination**: Display the horizontal tilt angle or Latitude.
5. **Leveling**: provides a visual display of the X and Y axis values, which can help determine the device's tilt or leveling state.

---

## Bill of Materials

Here are the hardware components and tools required to build this project, following the exact parts as recommended in the original [Compass for Astronomers](https://www.instructables.com/Compass-for-Astronomers/):

### Hardware Components

1. **Telescope**: Zhumell Z114 - 114 mm (4.5 inch) Tabletop Dobsonian
2. **Microcontroller**: Arduino Nano
3. **LCD Display**: 16x2 I2C LCD Display, preferably with a PCF8574 I2C expander (Model: YwRobot 1602)
4. **Inertial Measurement Unit (IMU)**:
   - Pololu AltIMU-10 v6 Gyro, Accelerometer, Compass, and Altimeter (LSM6DSO, LIS3MDL, and LPS22DF Carrier)
   - [IMU link](https://www.pololu.com/product/2863)
   - The original tutorial used an LSM303D. I could not get this delivered to me in Johannesburg, so I went for a AltIMU-10 even if it was more expensive. It would be better to use the cheaper LSM303D is possible.
5. **Buttons**: Generic push button
6. **Breadboard and Jumper Wires**: To connect components
7. **Power Supply**: Reliable 9V battery power supply, hooked to an off-switch

### Tools

1. **Screwdrivers**: For assembly and adjustment
2. **Soldering Kit**: For any necessary soldering (depending on motor connections)
3. **Multimeter**: For testing connections and voltage if needed

---

## Technology Stack

Please note that the libraries below are based on the AltIMU-10 instead of the LSM303D. Please refere to the original tutorial for the LSM303D.

- **Programming Language**: C++
- **Libraries**:
  - **LiquidCrystal_I2C.h==1.1.2**: LCD display library with I2C communication by Frank de Brabander
  - **Wire==0.7.0**: I2C communication library
  - **LIS3MDL==2.0.0**: Library for LIS3MDL compass and accelerometer module by Pololu
  - **LSM6==2.0.1**: Library for accelerometer and gyro by Pololu

---

## Tutorial Used

The project was inspired by [Compass for Astronomers](https://www.instructables.com/Compass-for-Astronomers/) on Instructables. This tutorial is a comprehensive guide on building a compass for telescopes, especially useful for amateur astronomers.

---

## How to Build

### 1. Hardware Setup

- Connect the 16x2 I2C LCD display to the Arduino Nano.
- Attach the jumpers to the buttons and the Arduino Nano.

---

### Acknowledgements

Special thanks to [Armando LeonardoS](https://www.instructables.com/member/Armando+LeonardoS/) for creating a really cool astronomy project [Compass for Astronomers](https://www.instructables.com/Compass-for-Astronomers/). I got to explore both astronomy and my messing around with the Arduino Nano with this experiment.

---

## Experiment outcomes

It was a good experiment and I am grateful that Armano put this together. I would not recommend this project though because an IMU based compass can be easily affected by interference from metals on the telescope. They are also tricky to calibrate but are not accurate once calibrated. Vladimir Atehortúa has [documented](https://github.com/vlaate/vladsc) his journey building a similar device and ended up winvesting more in an encoder based DSC. I actually built Vladimir Atehortúa's encoder based [Dobsonian DSC](https://github.com/vlaate/DobsonianDSC) and it's a much better investment. The cheapest low-no friction navitation system is the Raspberry Pi based [Cedar Solver](https://github.com/smroid/cedar-server?tab=readme-ov-file) by Steven Rosenthal.

---

### License

The codebase is MIT licensed unless otherwise specified.

---

To be modified further, by Kgotso Koete
<br/>
Johannesburg, South Africa
