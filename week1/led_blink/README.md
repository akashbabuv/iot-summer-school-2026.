# LED Blink using Arduino

## Project Title

LED Blink using Arduino with Adjustable Blink Speed


## Hardware Required

- Arduino Uno
- LED
- 220Ω Resistor
- Potentiometer (10kΩ)
- Breadboard
- Jumper Wires
- USB Cable


## Circuit Diagram Description

- Connect the LED anode (+) to Arduino Digital Pin 13 through a 220Ω resistor.
- Connect the LED cathode (-) to GND.
- Connect one side of the potentiometer to 5V.
- Connect the other side to GND.
- Connect the middle pin (wiper) of the potentiometer to Analog Pin A0.


## How to Upload Code

1. Connect the Arduino Uno to the computer using a USB cable.
2. Open the Arduino IDE.
3. Open the `led_blink.ino` file.
4. Select **Arduino Uno** from **Tools → Board**.
5. Select the correct COM port from **Tools → Port**.
6. Click the **Upload** button.
7. Open the Serial Monitor at **9600 baud** to view the blink count.

## Expected Output

- The LED blinks continuously.
- Turning the potentiometer changes the blink speed.
- The Serial Monitor displays the blink count after each blink.

## Troubleshooting Tips

1. Check that the Arduino board and COM port are correctly selected.
2. Ensure all wiring connections are secure.
3. Verify that the LED polarity is correct.
4. Make sure the potentiometer is connected to A0.
5. Confirm the Serial Monitor is set to 9600 baud.

## Author

Akash Babu
