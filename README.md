# 🧠 Minimal Microkernel OS

A minimal operating system kernel built entirely from scratch using Assembly and C. This project serves as a foundational step toward understanding how low-level systems interact with hardware, memory management, interrupts, and bootloaders.

Features
Multiboot-compliant boot via GRUB

VGA text mode terminal output

Basic input/output handling

Initial Global Descriptor Table (GDT) and Interrupt Descriptor Table (IDT) setup

Simple memory and interrupt management

Low-level stack and time handling

# Directory Structure

MicroKernel/
├── includes/             # Header files for kernel modules
├── isodir/               # ISO boot image structure
│   └── boot/
│       └── grub/         # GRUB configuration
├── srcs/                 # Source files for kernel (C and Assembly)
│   └── boot/             # Bootloader and initial Assembly code
├── Makefile              # Build system
├── linker.ld             # Linker script
├── .gitignore
└── gcc-13.1.0.tar.gz     # GCC source archive (optional)

# Getting Started

Prerequisites
You need the following tools installed:

make

gcc (preferably cross-compiler targeting i386)

nasm

qemu (or another emulator)

Build Instructions
To compile the kernel and create a bootable ISO:

bash
Copy
Edit
make
To run the kernel using QEMU:

bash
Copy
Edit
make run
To clean the build artifacts:

bash
Copy
Edit
make clean
File Descriptions
Makefile: Automates compilation, linking, ISO creation, and QEMU execution.

linker.ld: Custom linker script used to control memory layout of the final kernel binary.

grub.cfg: GRUB bootloader configuration for launching the kernel.

boot.s: The entry point written in Assembly which sets up the initial execution context.


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
