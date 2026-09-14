# Pick & Place Color-Sorting Robotic System

## 1. Background
Sorting materials by color is a fundamental automation process across modern packaging, logistics, and manufacturing operations. Industrial robotic manipulators streamline production lines by automatically identifying, handling, and categorizing individual items based on distinct visual parameters.

This project implements a **6-DOF Pick and Place Robotic Arm** capable of sorting primary color targets (Red, Green, Blue). The system utilizes a **TCS3200 color sensor** to identify the color profile of a target object, compares it against designated destination parameters, and coordinates a sequence of motor movements to pick up the object and drop it into its matching bin. The entire control pipeline, sensor interface, and kinematic sequence are managed by a **TM4C123GH6PM (Tiva C)** microcontroller.

---

## 2. Materials

| Component | Description / Role |
| :--- | :--- |
| **Microcontroller** | TM4C123GH6PM (Tiva C Series) - Main processing & PWM motion control |
| **Color Sensor** | TCS3200 Color Light Sensor Module - Target color detection |
| **Actuator System** | 6 Servo Motors (or DC Geared Motors) - Kinematic articulation & translation |
| **End Effector** | Robotic Mechanical Gripper - Object acquisition and release |
| **Display** | 16x2 Character LCD - Real-time system state and color telemetry |
| **Mechanical Frame** | 6-DOF Robotic Arm Structural Rig |

---

## 3. Key Technical Deliverables

* **Primary Color Classification:** Accurately classifies targets into **Red**, **Green**, or **Blue** spectral signatures using the TCS3200 sensor array.
* **Synchronized Motor Control:** Executes precise multi-axis motion profiling across all six motors for smooth base rotation, reach, and end-effector placement.
* **Target Validation:** Evaluates whether a detected object matches the assigned target box parameters before initiating the physical sequence, ignoring unmatched targets.
* **Gripper Actuation:** Handles physical object acquisition (pick) and release (place) using the end-effector.
* **Live Telemetry:** Displays current sensor detection states, system status, and sorting status on a 16x2 LCD.
    J --> K[Open Gripper -> Place Object in Box]
    K --> L[Return Robotic Arm to Home Position]
    L --> B
