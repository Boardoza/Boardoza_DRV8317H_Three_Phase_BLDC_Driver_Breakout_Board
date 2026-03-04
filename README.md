# Boardoza DRV8317H – Three-Phase BLDC Motor Driver Breakout Board

The **Boardoza DRV8317H Breakout Board** is a high-performance, integrated **three-phase BLDC motor driver** designed for compact and efficient motor control applications. Based on the **Texas Instruments DRV8317H**, this device integrates three half-bridges with low R<sub>DS(ON)</sub> MOSFETs, programmable current sensing, and advanced protection mechanisms into a single solution.

Supporting supply voltages up to **24V (absolute maximum)** and delivering up to **5A peak output current**, the DRV8317H is ideal for robotics, steward and gimbal systems, drones, industrial automation, pumps, and smart motorized systems. With flexible control options such as **6x PWM mode and 3x PWM mode**, this board allows both simple and advanced motor control implementations.

## [Click here to purchase!](https://www.ozdisan.com/ureticiler/boardoza)

| Front Side | Back Side |
|:---:|:---:|
| ![DRV8317H Front](./assets/DRV8317%20Front.png) | ![DRV8317H Back](./assets/DRV8317%20Back.png) |

---

## Key Features

- **Integrated Three-Phase Driver:** Drives BLDC and PMSM motors with a compact all-in-one solution.
- **Up to 5A Peak Output Current:** Suitable for medium-power motor applications.
- **Flexible Control Options:** Supports **6x PWM** and **3x PWM**.
- **High PWM Frequency Support:** Operates with PWM frequencies up to **200 kHz**.
- **Integrated Current Sensing:** No external shunt resistor required.
- **Programmable Slew Rate:** Helps reduce EMI and optimize switching performance.
- **Comprehensive Protection Features:** Includes UVLO, OVP, CPUV, OCP, OTW, and OTS protections.
- **Shoot-Through Protection:** Integrated hardware-level safety for reliable operation.

---

## Technical Specifications

**Model:** DRV8317H  
**Manufacturer:** Boardoza  
**Manufacturer IC:** Texas Instruments  
**Driver Type:** Integrated 3-Phase Gate Driver with MOSFETs  
**Functions:** Three-Phase PWM BLDC Motor Driver  
**Input Voltage (VM):** 4.5V – 20V (24V Absolute Maximum)  
**Peak Output Current:** 5A (per phase, peak)  
**Control Interfaces:** 6x PWM / 3x PWM    
**Maximum PWM Frequency:** 200 kHz  
**RDS(ON) (HS + LS):** 130 mΩ (typical at 25°C)  
**Current Sensing:** Integrated (Programmable Gain)  
**Protection Features:**  
- UVLO (Undervoltage Lockout)  
- OVP (Overvoltage Protection)  
- CPUV (Charge Pump Undervoltage)  
- OCP (Overcurrent Protection)  
- OTW (Overtemperature Warning)  
- OTS (Overtemperature Shutdown)  

**Operating Temperature:** -40°C to +125°C  
**Board Dimensions:** 60mm x 80mm  

 

---

## Board Pinout / User Guide

>Pin functions are multiplexed and may vary depending on selected control mode (6x PWM, 3x PWM).  
For detailed pin descriptions, alternate-function mappings, electrical characteristics, and application examples, please refer to the official Board User Guide:
[DRV8317H User Guide.pdf](./assets/DRV8317H%20User%20Guide.pdf)

---

## Board Dimensions

<img src="./assets/DRV8317 Dimensions.png" alt="DRV8317H Board Dimensions" width="450"/>

---

## Step Files

[Boardoza DRV8317H.step](./assets/DRV8317%20Step.step)

---

## Datasheet

[DRV8317H Datasheet.pdf](./assets/DRV8317%20Datasheet.pdf)

---

## Version History

- v1.0.0 - Initial Release

---

## Support

- If you have any questions or need support, please contact **support@boardoza.com**

---

## **License**

This repository contains both hardware and software components:

### **Hardware Design**

[![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

All hardware design files are licensed under [Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg

### **Software/Firmware**

[![BSD-3-Clause][bsd-shield]][bsd]

All software and firmware are licensed under [BSD 3-Clause License][bsd].

[bsd]: https://opensource.org/licenses/BSD-3-Clause
[bsd-shield]: https://img.shields.io/badge/License-BSD%203--Clause-blue.svg
