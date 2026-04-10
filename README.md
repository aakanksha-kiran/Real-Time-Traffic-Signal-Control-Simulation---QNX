# Real-Time-Traffic-Signal-Control-Simulation---QNX
Smart QNX-based traffic simulator using threads, synchronization, scheduling, and FSM logic to manage signals dynamically with reliability, safety, and emergency prioritization.
--------------------------------------------------------------------------------------------------------------------------------------------------
🚦 Real-Time Traffic Signal Control Simulator using QNX RTOS

📌 Overview
This project presents a real-time traffic signal control simulator developed using QNX RTOS concepts. It demonstrates how embedded systems can efficiently manage traffic flow through concurrency, synchronization, and deterministic scheduling.

---

🎯 Objective
The main objective of this project is to design and simulate a smart traffic signal system that adapts to real-time conditions such as traffic density and emergency situations while maintaining system reliability.

---

⚙️ Features
Multithreading using POSIX threads
Mutex-based synchronization
Priority-based scheduling
Finite State Machine (FSM) for signal control
Emergency vehicle override system
Traffic density-based signal adjustment
Watchdog mechanism for system monitoring

🧠 Concepts Used
QNX RTOS fundamentals
Thread management and scheduling
Inter-thread communication
Synchronization (Mutex)
Real-time system design
Fault detection and recovery

🏗️ System Architecture
The system consists of multiple modules:
Timer Thread → Controls signal timing
Signal Controller → FSM-based logic
Traffic Input → Simulated density/emergency
Output Display → Signal states
Watchdog → Monitors system health

🔄 Working
The system initializes all threads and starts simulation.
Traffic inputs are processed dynamically, and signals are controlled using FSM logic.
Synchronization ensures safe data access, while scheduling guarantees timely execution.
Emergency conditions override normal flow for priority handling.

📂 Project Structure
code/        → Source code
ppt/         → Presentation
flowchart/   → Workflow diagram
output/      → Execution results

▶️ How to Run
gcc traffic_signal.c -o traffic -lpthread
./traffic

📸 Output
(Upload your screenshot in output folder)

📽️ Presentation
Refer to the PPT in the ppt/ folder.

🚀 Future Scope
AI-based traffic prediction
IoT-based smart traffic systems
Integration with real sensors
Smart city deployment

📌 Conclusion
This project successfully demonstrates the application of QNX RTOS concepts in building a reliable and efficient real-time traffic control system.

👩‍💻 Team
Aakanksha K
Preetisree V
