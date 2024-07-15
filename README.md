# Operating Systems Assignment: Multi-threaded Co-Editing and Display System

## Overview
This repository contains the implementation of a multi-threaded application simulating a co-editing and display system. The system involves producers generating messages of different categories (sports, news, weather), which are then processed by co-editors and displayed by a screen manager.

## Features
- **Producers**: Multiple threads simulate producers generating messages categorized as sports, news, or weather.
- **Buffers**: Utilizes both bounded and unbounded buffers:
  - **Bounded Buffer**: Used by producers to store their messages with a fixed capacity.
  - **Unbounded Buffer**: Shared among co-editors and screen manager to handle messages of various categories.
- **Co-Editors**: Threads responsible for processing messages from the buffers and preparing them for display.
- **Screen Manager**: Displays processed messages on the screen.

## Components
1. **Producer Threads**:
   - Generate messages categorized as sports, news, or weather.
   - Use bounded buffers to store their messages.
   
2. **Dispatcher**:
   - Distributes messages from producers to appropriate co-editors based on message category.
   
3. **Co-Editors**:
   - Process messages received from the dispatcher.
   - Modify messages (simulated editing process) before forwarding them to the screen manager.
   
4. **Screen Manager**:
   - Collects processed messages from co-editors.
   - Displays messages on the screen.

## Implementation Details
- **Thread Management**: Uses C++11 `std::thread` for managing concurrency among producers, co-editors, and the screen manager.
- **Synchronization**: Implements mutex locks (`std::mutex`) and condition variables (`std::condition_variable`) to ensure thread safety and synchronized access to shared resources (e.g., buffers).
- **Error Handling**: Implements error checking for file operations (e.g., reading configuration files) and thread synchronization to avoid race conditions and deadlocks.
- **Documentation**: Provides inline comments and README documentation to explain the purpose and behavior of each component and class.

## Requirements
- **C++11 Compiler**: The project is written in C++11 and requires a compatible compiler.
- **Makefile**: Included for easy compilation and building of the project.
- **Configuration File**: `config.txt` specifies the number of products to produce and the queue sizes for each producer.

## Usage
1. **Clone the Repository**:
   ```bash
   git clone https://github.com/ShakedPeretz/Operating-Systems-Assignment-Multi-threaded-Co-Editing-and-Display-System.git
   cd Operating-Systems-Assignment-Multi-threaded-Co-Editing-and-Display-System
2. Build the Project:
   ```bash
   make
3. Run the Program:
   ```bash
   ./ex3.out config.txt

