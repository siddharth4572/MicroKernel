# 🧠 Minimal Microkernel OS

A lightweight educational microkernel operating system built from scratch. This project demonstrates core OS features such as process scheduling, inter-process communication (IPC), memory paging, and low-level hardware interrupt handling — all running in QEMU.

---

## 🚀 Features

- **Custom Bootloader**
  - Sets up protected mode
  - Loads kernel from disk and transfers control

- **Kernel Core**
  - Written in C with some assembly
  - Initializes memory, timers, and interrupt descriptors

- **Process Scheduler**
  - Round-Robin Scheduler
  - Supports multitasking

- **Memory Management**
  - Paging support (basic page table setup)
  - Kernel heap space

- **Inter-Process Communication (IPC)**
  - Message passing between processes

- **Hardware Interrupts**
  - Programmable interrupt controller (PIC) setup
  - Timer interrupt handling
  - Keyboard interrupt support

---

## 🗂️ Directory Structure

```
microkernel/
├── Makefile               # Build script
├── qemu.log               # Output log from QEMU
├── include/               # Header files
│   ├── io.h               # Port I/O operations
│   ├── scheduler.h        # Process scheduler interface
│   ├── idt.h              # Interrupt Descriptor Table
│   ├── isr.h              # Interrupt Service Routines
│   ├── ipc.h              # Message passing IPC
│   ├── memory.h           # Memory paging functions
│   ├── timer.h            # Timer configuration
│   └── kernel.h           # Kernel initialization
└── src/                   # (Assumed) Source implementation files
```

---

## 🛠️ How to Build & Run

### 🔧 Requirements

- `gcc`, `make`
- `nasm`
- `qemu-system-x86_64`
- Linux-based OS or WSL (for best compatibility)

### 🔨 Build

```bash
cd microkernel
make
```

This compiles the kernel and prepares the image for emulation.

### ▶️ Run in QEMU

```bash
make run
```

Or manually:

```bash
qemu-system-x86_64 -kernel build/kernel.bin
```

---

## 🧪 How It Works

1. **Bootloader** (in assembly) is the first code executed.
   - Switches to 32-bit protected mode.
   - Loads the kernel binary from disk and jumps to the kernel entry point.

2. **Kernel Initialization** (in `kernel.c` and `kernel.h`)
   - Sets up the stack, interrupt table (IDT), and memory paging.
   - Initializes basic hardware like the programmable interval timer (PIT) and keyboard.

3. **Interrupts and ISRs**
   - The system uses IRQs for timer and keyboard.
   - Custom handlers are defined in `isr.c` and `idt.c`.

4. **Scheduler**
   - Implements a Round-Robin algorithm.
   - Periodically switches between tasks using a timer interrupt.

5. **IPC (Inter-process Communication)**
   - Tasks can send/receive messages using message queues or shared memory.

6. **Paging**
   - Virtual memory is enabled by setting up page tables.
   - Helps separate kernel and task memory.

---

## 👥 Authors

- Dhananjay Pundir
- Aman Singh Rawat
- Govind Pratap Singh
- Siddharth Katyal

---

## 📦 Future Work

- Add user-space support
- Implement filesystem and syscall interface
- Improve memory protection and fault handling
- Add networking stack (optional)

---

## 📘 References

- [OSDev Wiki](https://wiki.osdev.org)
- Intel x86 Architecture Manuals
- “Operating Systems: Three Easy Pieces”

---

## 🧾 License

This project is released under the MIT License.
