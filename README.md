# 🚦Real-Time-Traffic-Signal-Control-Simulation---QNX
Smart QNX-based traffic simulator using threads, synchronization, scheduling, and FSM logic to manage signals dynamically with reliability, safety, and emergency prioritization.

--------------------------------------------------------------------------------------------------------------------------------------------------

## 📌 Projectr Overview
This project presents a real-time traffic signal control simulator based on QNX RTOS concepts. It models an intelligent traffic management system capable of handling dynamic traffic conditions using concurrency, synchronization, and deterministic scheduling.

---

## 🎯 Key Objectives
The objective of this project is to design a reliable and efficient traffic signal system that:
- Adapts to traffic density
- Handles emergency vehicle priority
- Ensures safe and synchronized signal transitions
- Demonstrates real-time system behavior

---

## ⚙️ Key Features
- Multithreading using POSIX threads  
- Mutex-based synchronization for safe data access  
- Priority-based scheduling for real-time execution  
- Finite State Machine (FSM) for signal control  
- Emergency override mechanism  
- Traffic density-based signal management  
- Watchdog system for fault detection  

---

## 🧠 Technologies & Concepts Used
- QNX RTOS fundamentals  
- Thread scheduling and management  
- Synchronization using mutex  
- Inter-thread communication  
- Real-time system design principles  
- Fault tolerance using watchdog  

---

## 🏗️ System Architecture
The system consists of the following modules:
- Timer Thread → Controls signal timing  
- Signal Controller → Implements FSM logic  
- Traffic Input → Simulates density/emergency conditions  
- Output Display → Shows signal states  
- Watchdog → Monitors system responsiveness  

---

## 🔄 Working
- The system initializes and starts multiple threads  
- Traffic conditions are simulated dynamically  
- The controller processes inputs using FSM logic  
- Signals transition between Red, Yellow, and Green states  
- Mutex ensures safe synchronization between threads  
- Scheduler ensures timely execution of tasks  
- Emergency and density conditions override normal behavior  
- Watchdog monitors system activity and detects failures  

---

## 📂 Project Structure
code/        → Source code  
ppt/         → Presentation  
flowchart/   → Workflow diagram  
output/      → Execution results  

---

## ▶️ How to Run
gcc traffic_signal.c -o traffic -lpthread  
./traffic  

---

## 📸 Output

### Normal Operation
![Normal](output/output1.png)

### Density-Based Control
![Density](output/density.png)

### Emergency Override
![Emergency](output/emergency.png)

### Watchdog Monitoring
![Watchdog](output/watchdog.png)

More output screenshots are available in the `output/` folder.

---

## 📽️ Presentation
Detailed explanation and additional outputs are available in:
ppt/Q-eHack-2026-Presentation.pdf

---

## 🔄 Flowchart
![Workflow](flowchart/workflow.png)

---

## 🚀 Future Scope
- AI-based traffic prediction  
- IoT-based smart traffic integration  
- Real-time sensor implementation  
- Smart city deployment  

---

## 📌 Conclusion
This project successfully demonstrates the application of QNX RTOS concepts such as multithreading, synchronization, and scheduling in building a reliable real-time traffic control system.

---

## 👩‍💻 Team
- Aakanksha K  
- Preetisree V
