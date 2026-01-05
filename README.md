# I²C-Based Temperature, Fan Control, and RPM Monitoring System

## 📌 Overview
This project implements a **real-time embedded fan control and monitoring system** using the **PIC18F4620 microcontroller**. The system integrates temperature sensing, real-time clock functionality, RPM measurement, PWM-based fan control, and IR remote input, with real-time visualization on an **ST7735 TFT display**.

The firmware is written in **Embedded C**, emphasizing **interrupt-driven execution**, **deterministic timing**, and **low-level peripheral integration**.

---

## ⚙️ Hardware Components
- **Microcontroller:** PIC18F4620  
- **RTC:** DS3231 (I²C)
- **Temperature Sensor:** DS1621 (I²C)
- **Display:** ST7735 TFT LCD
- **Fan Control:** PWM-driven DC fan
- **User Input:** IR Remote (NEC protocol)
- **Indicators:** RGB LEDs (RPM and duty-cycle visualization)

---

## 🧠 System Features
- Real-time clock and calendar display
- Temperature measurement (°C and °F)
- PWM-based fan speed control
- RPM measurement and visualization
- IR remote-based user interaction
- RGB LED status indicators
- UART-based serial debugging output

---

## 🔄 Program Flow

### Initialization
- Configure internal oscillator (8 MHz)
- Initialize UART for serial debugging
- Configure GPIO direction registers
- Initialize I²C bus (100 kHz)
- Initialize DS3231 RTC and DS1621 temperature sensor
- Initialize TFT display
- Configure timers, PWM, and interrupts
- Set default fan speed and duty cycle

### Main Loop
- Read time from **DS3231** once per second
- Read temperature from **DS1621**
- Convert temperature to Fahrenheit
- Measure fan RPM
- Update TFT display with time, temperature, RPM, and duty cycle
- Update RGB LEDs based on RPM and PWM duty cycle
- Process IR remote commands
- Update PWM output as needed

---

## 🎮 IR Remote Controls
| Button | Function |
|------|---------|
| Play / Pause | Toggle fan ON / OFF |
| “–” | Decrease fan speed |
| “+” | Increase fan speed |
| EQ | Reset RTC time |
| Other buttons | Ignored |

NEC protocol decoding is handled via external interrupts and validated against a known button code table.

---

## 🖥️ Serial Debug Output
The system outputs real-time diagnostic information over UART, including:
- Time and date
- Temperature (°C / °F)
- Fan RPM
- PWM duty cycle
- IR button codes

Example output:
12:45:10 04/21/21 Temp = 26 C = 78 F RPM = 1350 dc = 60
NEC_Code = 0xA8


---

## 🧩 Software Architecture
- **Low-level drivers:** I²C, UART, PWM
- **Sensor drivers:** DS3231 RTC, DS1621 temperature sensor
- **Interrupt handling:** IR decoding, timing control
- **Control logic:** Fan speed and RPM feedback
- **Display driver:** ST7735 TFT rendering
- **Utilities:** RGB LED indicators, buzzer feedback

---

## 📂 Key Source Files
- `main.c` – System initialization and control loop
- `I2C.c / I2C_Support.c` – I²C communication
- `Interrupt.c` – NEC IR decoding and interrupt handling
- `Fan_Support.c` – Fan PWM control and RPM measurement
- `ST7735_TFT.c` – TFT display driver

---

## 📚 Learning Outcomes
This project demonstrates:
- Real-time embedded firmware development
- Interrupt-driven system design
- PWM motor control and feedback
- Multi-peripheral integration (**I²C, UART, PWM**)
- IR remote protocol decoding
- Embedded debugging and validation techniques
- Sensor-based control loops

---

## 🚀 Future Enhancements
- Closed-loop temperature-based fan control
- Non-volatile storage of configuration parameters
- Low-power sleep modes
- Menu-based UI navigation
- Fault detection for stalled or disconnected fan

---

## 📄 License
Educational use only  
Developed for **ECE3301L – Embedded Systems Lab**

---

## 👥 Authors
Developed as part of an embedded systems curriculum.  
Maintained for instructional and portfolio use.
