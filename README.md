# CSC413 Assignment 2 – FoodCycle Blocks

This project supports our **FoodCycle Blocks** tangible educational system, designed to teach children how food is grown, processed, and cooked using interactive physical blocks, motors, LEDs, and RFID sensors.

## Code Overview

### 1. `rfid_control_step_motorr_.ino`
Controls the **Planting Machine** unit of the system.

- Uses an **RFID reader (RC522)** to detect ingredient blocks.
- Activates a **28BYJ-48 stepper motor** to rotate the seed block inside the chamber.
- Simulates plant growth stages by rotating the block to show **seed → sprout → mature crop**.

### 2. `12_led_lights_.ino`
Controls the **Cooking Machine** unit.

- Accepts combinations of ingredients (e.g., flour, potato, rice) and cooking methods (e.g., boil, steam, roast).
- Uses **12 output pins** to drive LEDs that represent the final food results.
- Lights up valid recipe options; confirms the selected combination (e.g., `flour + roast = bread`) by leaving only the correct LED on.

## Hardware Used

- Arduino UNO x2  
- RFID Reader (RC522)  
- 28BYJ-48 Stepper Motor + ULN2003 Driver  
- Breadboards, jumper wires  
- 12 × LEDs  
- Laser-cut wooden shell for structure  
- RFID-tagged wooden ingredient blocks  

## Build & Demo

This code is part of our CSC413 Assignment 2 submission at the University of Victoria. For full system design, interaction flow, CAD files, and write-up, please see the accompanying report and documentation.
