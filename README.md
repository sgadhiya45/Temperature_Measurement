# Temperature_Measurement System

This project is a temperature measurement system that utilizes a PT100 sensor, Wheatstone bridge, and microcontroller for accurate temperature monitoring. The system is designed to measure temperatures within the range of -15°C to 110°C and provide outputs via a serial interface.

## Features
- **Temperature Sensor**: Uses a PT100 platinum resistance thermometer.
- **Measurement Circuit**: Includes a Wheatstone bridge and instrumentation amplifier for signal conditioning.
- **Microcontroller Integration**: Data acquisition and automatic calibration are performed using an ATmega32 microcontroller.
- **SPICE Simulation**: Circuit simulations are conducted using LT-SPICE to ensure accuracy and reliability.

## Project Structure
- `/docs`: Contains project documentation and references.
- `/src`: Source code for the microcontroller and any related scripts.
- `/simulation`: SPICE simulation files and results.

## Getting Started
1. **Circuit Design**: Review the circuit diagram and assemble the components on a breadboard or PCB.
2. **Microcontroller Programming**: Load the provided code onto the ATmega32 microcontroller.
3. **Calibration**: Follow the calibration procedure to ensure accurate temperature readings.
4. **Simulation**: Use the SPICE files to simulate the circuit and verify the design.

## Usage
After setting up the hardware and loading the microcontroller program, the system will provide real-time temperature data. The temperature can be monitored through a serial connection to a PC or other devices.

