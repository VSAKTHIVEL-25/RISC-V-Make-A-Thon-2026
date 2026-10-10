# Smart Parking Assist & Slot Monitoring System 🚗

A bare-metal embedded systems project developed during a 3-day hackathon using the **ATmega2560 microcontroller and Embedded C**. The system monitors parking slot availability and assists drivers while reversing by measuring the distance to a parking boundary.

## 📌 Project Overview

Finding an available parking space and parking safely can be challenging. This project combines IR-based parking slot monitoring with ultrasonic distance measurement to provide visual and audible feedback to the driver.

The project focuses on **register-level programming, custom peripheral drivers, modular software design, and hardware integration** without relying on Arduino libraries.

## 🎯 Objectives

- Detect parking slot occupancy using IR sensors.
- Measure the distance to a parking boundary using an ultrasonic sensor.
- Display parking availability on an LCD.
- Indicate the number of available slots using a seven-segment display.
- Provide distance-based visual alerts using LEDs.
- Generate audible parking alerts using PWM and a buzzer.
- Develop reusable peripheral drivers using Embedded C.

## ⚙️ Hardware Components

- ATmega2560 microcontroller / Arduino Mega 2560 board
- Ultrasonic distance sensor (HC-SR04)
- Two IR sensors for parking slot detection
- 16×2 LCD
- Seven-segment display
- LEDs and current-limiting resistors
- Buzzer
- Regulated power supply
- Breadboard and connecting wires

## 🧠 Software and Technologies

- Embedded C
- Bare-metal register-level programming
- ATmega2560 GPIO registers
- Hardware timers
- PWM generation
- ADC driver
- Ultrasonic sensor driver
- IR sensor driver
- LCD driver
- Seven-segment display driver
- Modular driver APIs

## 🏗️ System Architecture

```text
          IR Sensor 1 ──┐
                        │
          IR Sensor 2 ──┤
                        ▼
                 ┌──────────────┐
Ultrasonic Sensor│  ATmega2560  │
   (TRIG/ECHO) ─►│              │
                 │ Embedded C   │
                 │ Driver APIs  │
                 └──────┬───────┘
                        │
          ┌─────────────┼─────────────┐
          ▼             ▼             ▼
       16×2 LCD    Seven-Segment    LEDs
                        │
                        ▼
                  PWM Buzzer
```

## 🔧 Main Features

### 1. Parking Slot Monitoring

The IR sensors detect whether each parking slot is occupied or available.

| Slot 1 | Slot 2 | Free slots | Seven-segment output |
|---|---|---:|---:|
| Occupied | Occupied | 0 | 0 |
| Free | Occupied | 1 | 1 |
| Occupied | Free | 1 | 1 |
| Free | Free | 2 | 2 |

The LCD displays the overall parking availability.

### 2. Ultrasonic Distance Measurement

The ultrasonic sensor measures the distance between the vehicle and the parking boundary. The microcontroller generates a trigger pulse, measures the ECHO pulse duration using Timer1, and calculates the approximate distance.

### 3. Distance-Based LED Indication

The implemented distance thresholds are:

| Distance | Indication |
|---|---|
| Above 30 cm | Safe indication — LED A2 |
| 15–30 cm | Caution indication — LED A3 |
| 10–15 cm | Warning indication — LED A4 |
| Below 5 cm | Stop indication — LED A5 |

The LED behavior for the 5–10 cm range can be refined in a future version.

### 4. PWM Buzzer Alert

The buzzer provides audible feedback according to the measured distance. PWM is generated using a hardware timer, allowing the alert output to be controlled by the application.

### 5. LCD Display

The 16×2 LCD displays parking slot availability and the measured distance.

Example:

```text
Slots: 1 FREE
Distance: 24 cm
```

## 🧩 Driver Architecture

The project uses a modular driver-based structure to separate hardware control from application logic.

| Driver | Responsibility |
|---|---|
| GPIO | Configure pins and read/write digital signals |
| Switch | Read digital switch inputs |
| LED | Control indicator LEDs |
| Seven-segment | Display numerical values |
| Timer | Provide timing operations |
| PWM | Generate PWM output |
| ADC | Read analog input values |
| IR sensor | Detect parking slot occupancy |
| Ultrasonic | Measure distance |
| LCD | Display parking status and distance |

The intended software flow is:

```text
Application Layer
       ↓
Peripheral Driver APIs
       ↓
ATmega2560 Hardware Registers
       ↓
Connected Sensors and Outputs
```

## 📁 Suggested Repository Structure

```text
smart-parking-assist/
├── README.md
├── main.c
├── GPIO.h
├── GPIO.c
├── IR.h
├── IR.c
├── LED.h
├── LED.c
├── Sevensegment.h
├── Sevensegment.c
├── LCD.h
├── LCD.c
├── ultrasonic.h
├── ultrasonic.c
├── PWM.h
├── PWM.c
├── Buzzer.h
├── Buzzer.c
├── ADC.h
├── ADC.c
├── switch.h
└── switch.c
```

*Adjust the file list to match the files actually included in your repository.*

## 🚀 Working Principle

1. Initialize the peripheral drivers and configure the required GPIO pins.
2. Read both IR sensors to determine parking slot availability.
3. Count the free slots and display the result on the seven-segment display.
4. Trigger the ultrasonic sensor and measure the ECHO pulse duration.
5. Calculate the approximate distance to the parking boundary.
6. Update the LCD and distance-indicator LEDs.
7. Generate the appropriate buzzer alert using PWM.
8. Repeat the monitoring cycle continuously.

## 🧪 Testing and Demonstration

The project can be demonstrated through the following scenarios:

- Both parking slots occupied.
- One parking slot available.
- Both parking slots available.
- Vehicle approaching the parking boundary.
- Changes in distance-based LED indication.
- Changes in buzzer behavior as the measured distance changes.
- Simultaneous display of parking availability and distance.

Record actual hardware and simulation test results before marking each scenario as successfully tested.

## 📚 Learning Outcomes

Through this hackathon project, I gained practical experience in:

- Bare-metal programming on the ATmega2560.
- Understanding microcontroller registers and bitwise operations.
- Developing reusable peripheral drivers.
- Working with timers, PWM, ADC, and GPIO.
- Interfacing sensors and display modules.
- Debugging hardware and software integration issues.
- Organizing embedded C projects using modular APIs.

## 🔮 Future Improvements

- Implement non-blocking, timer-driven application logic.
- Improve ultrasonic measurement using timer input capture.
- Add a keypad for configuration and manual control.
- Introduce an automatic parking barrier.
- Improve sensor error detection and boundary handling.
- Expand the system to monitor more parking slots.

## 🏁 Hackathon Experience

This project was developed as part of a three-day bare-metal embedded systems hackathon. The experience helped me understand how individual peripheral drivers can be integrated into a complete embedded application. It also strengthened my debugging skills and my understanding of register-level programming and hardware interfacing.

## 📄 License

Choose a license before distributing or reusing this project. For example, the MIT License can be used if you want to permit reuse with attribution.

---

**Developed using Embedded C and the ATmega2560.**
