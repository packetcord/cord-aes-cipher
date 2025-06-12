# cord-aes
Highly configurable AES-128/192/256 cipher implementation to work on any device from small microcontrollers to the latest hardware crypto-accelerated CPUs (Intel/AMD/ARMv8/RISC-V).

## 🔧 Build Instructions

To compile the project, run the following command in the root directory:

```bash
gcc -o main main.c aes_cipher.c aes_helpers.c
