# ArtificalOS

Welcome to **ArtificalOS**, a custom operating system that is designed from scratch, one line of code at a time. **ArtificalOS** is built with passion and an obsession with low-level programming. This project represents the ultimate adventure in learning operating systems development, using C and assembly language.

## 🚀 Features

- **Custom Kernel**: A minimal and fast kernel, designed to provide a foundation for your own custom applications.
- **Console Interface**: Fully functional command-line interface (CLI) with commands such as `info`, `help`, and `clear`.
- **Cross-Platform Bootable**: Boots on real hardware and virtual machines.
- **Low-Level Programming**: Written in C and assembly, giving you full control over the hardware.

## 🛠️ Getting Started

### Prerequisites

To build **ArtificalOS**, you'll need the following tools:

- **GCC**: A C compiler for compiling the kernel.
- **LD**: The linker for assembling the kernel image.
- **QEMU** or **Bochs**: For running the OS in a virtual machine (VM).
- **Make**: To automate the build process.
- **NASM**: For assembling the assembly files.
- **Fedora** or similar Linux distribution: This project has been developed and tested primarily on Fedora Linux, but should work on any Linux-based OS.

### Building ArtificalOS

1. Clone the repository:
   ```bash
   git clone https://github.com/BrightCat14/ArtificalOS.git
   cd ArtificalOS
   ```

2. Build the kernel:
   ```bash
   ./build.sh
   ```

3. Boot the OS using QEMU (or any other virtual machine software):
   ```bash
   qemu-system-x86_64 -cdrom ./artificalos.iso -boot d -m 16
   ```

### Directory Structure

- `src/` – Source code for the kernel.
- `boot/` – Bootloader code (Grub or custom).
- `bin/` – Binary output (kernel image, bootable disk image).
- `docs/` – Documentation and resources.

## 📜 Available Commands

- `info` – Display kernel information (version, developer, etc.).
- `help` – Show available commands and help messages.
- `clear` – Clear the screen.

### Example:

```bash
Enter command: info
Kernel version: 0.0.1
Developed by: AkaruiNeko
This is a tiny kernel shell.
```

## 🧑‍💻 Contributing

Contributions are welcome! If you'd like to improve **ArtificalOS**, feel free to fork the repository, make changes, and submit a pull request.

### How to contribute:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature/new-feature`).
3. Make your changes.
4. Commit your changes (`git commit -am 'Add new feature'`).
5. Push to the branch (`git push origin feature/new-feature`).
6. Create a new pull request.

## 📝 License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.

## 🛠️ TODOs and Future Features

- Add multi-tasking and scheduling.
- Implement a basic file system.
- Expand command-line interface (CLI) with more advanced commands.
- Add graphics support and create a simple GUI.
- Support networking and inter-process communication (IPC).
