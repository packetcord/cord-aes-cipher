# 🔐 CORD-AES

Highly configurable AES-128/192/256 cipher implementation to work on any device from small microcontrollers to the latest hardware crypto-accelerated CPUs (Intel/AMD/ARMv8/RISC-V).

> ⚠️ **Note**: This library focuses on the **core AES cipher**, providing a standalone, mode-agnostic engine suitable for integration into higher-level encryption schemes.
Cipher modes such as CBC, CTR, and GCM are about to be implemented separately.

## 🧠 What is AES?

**AES (Advanced Encryption Standard)** is a **block cipher** standardized by NIST in 2001. It encrypts fixed-size blocks of **128 bits (16 bytes)** using keys of varying lengths:
- 🔑 **128-bit key**
- 🔑 **192-bit key**
- 🔑 **256-bit key**

AES performs a series of transformations on the input data through multiple rounds:
- 128-bit key → **10 rounds**
- 192-bit key → **12 rounds**
- 256-bit key → **14 rounds**

Each round consists of the following operations:
1. **Substitute Bytes**
2. **Shift Rows**
3. **Mix Columns**
4. **Add Round Key**

## 🧩 Cipher Modes (CBC, CTR, GCM, etc.)
AES on its own only encrypts individual blocks. **Cipher modes** define how to apply AES to longer messages or to add features like randomness or authentication:

- **CBC (Cipher Block Chaining)** – Adds dependency between blocks.
- **CTR (Counter Mode)** – Converts AES into a stream cipher.
- **GCM (Galois/Counter Mode)** – Adds authentication (AEAD).

> 🧱 This library **does not** implement these modes directly, but is planned to be supported (either within this repo or via separate ones).

## 🔑 Key Expansion

The "Key Size" refers to the original size of the key (the number after the AES abbreviation: AES-**128**, AES-**192** and AES-**256**). It is represented as a matrix of 4 rows and N columns, depending on the key length. 

| **Key Size** | **N rows** | **N columns** |
|----------|--------|----------|
| 128-bit  | 4      | 4        |
| 192-bit  | 4      | 6        |
| 256-bit  | 4      | 8        |

| **AES Version** | **Key Size** | **Number of Rounds (Nr)** | **N rows**  | **N columns**                    | **Expanded Key Size (in bytes)** |
| --------------- | ------------ | ------------------------- |-------------| -------------------------------- | -------------------------------- |
| AES-128         | 128 bits     | 10                        | 4           | 4 × (10 + 1) = **44**            | 44 × 4 = **176 bytes**           |
| AES-192         | 192 bits     | 12                        | 4           | 4 × (12 + 1) = **52**            | 52 × 4 = **208 bytes**           |
| AES-256         | 256 bits     | 14                        | 4           | 4 × (14 + 1) = **60**            | 60 × 4 = **240 bytes**           |

AES operates on a **4×4 byte matrix** called the **state**, which evolves with each round. Each N-th round takes a square matrix of 4x4 (16 bytes) from the expanded key rectangular matrix. The longer key (more AES "bits" configuration) results in a longer expanded key and more rounds respectively (more portions of 4x4 squares to be applied as part of the *Add Round Key* operation).

## ⚙️ Fine Tuning
As mentioned above, the library is designed to be cool enough by providing the flexibility to be fine tuned for small footprint or performance (including utilisation the AES hardware instructions on any popular architecture).

### 🧱 AES key length
...

### 🧱 Mix Columns (refers to the purely software AES, non-hardware accelerated)
...

### 🧱 CPU vs RAM vs Flash utilisation (quite relevant for microcontrollers)
The AES key is a tricky point when it comes to memory optimisation, especially on microcontrollers with less then 1KB of memory (like the PIC16 series, for example).
As described above, the expanded key is either 176, 208 or even 240 bytes long and even though the "initial" original key could be stored in the flash memory, the expansion happens
at runtime which means that it will end up in the main memory (RAM).

The CORD-AES library comes with the following helper function (inside *aes_helpers.c* and *aes_helpers.h* files):

```c
void print_expanded_key(uint8_t expanded_key[Nb][AES_WORDS]);
```
The example output for the original key 
```c
uint8_t key[4 * Nk] = { 0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C };
```

looks as follows:

```c
//
// print_expanded_key(aes_expanded_key)
//
uint8_t aes_expanded_key[Nb][AES_WORDS] = {{ 0x2B, 0x7E, 0x15, 0x16, 0xA0, 0xFA, 0xFE, 0x17, 0xF2, 0xC2, 0x95, 0xF2, 0x3D, 0x80, 0x47, 0x7D, 0xEF, 0x44, 0xA5, 0x41, 0xD4, 0xD1, 0xC6, 0xF8, 0x6D, 0x88, 0xA3, 0x7A, 0x4E, 0x54, 0xF7, 0x0E, 0xEA, 0xD2, 0x73, 0x21, 0xAC, 0x77, 0x66, 0xF3, 0xD0, 0x14, 0xF9, 0xA8 },
{ 0x28, 0xAE, 0xD2, 0xA6, 0x88, 0x54, 0x2C, 0xB1, 0x7A, 0x96, 0xB9, 0x43, 0x47, 0x16, 0xFE, 0x3E, 0xA8, 0x52, 0x5B, 0x7F, 0x7C, 0x83, 0x9D, 0x87, 0x11, 0x0B, 0x3E, 0xFD, 0x5F, 0x5F, 0xC9, 0xF3, 0xB5, 0x8D, 0xBA, 0xD2, 0x19, 0xFA, 0xDC, 0x21, 0xC9, 0xEE, 0x25, 0x89 },
{ 0xAB, 0xF7, 0x15, 0x88, 0x23, 0xA3, 0x39, 0x39, 0x59, 0x35, 0x80, 0x7A, 0x1E, 0x23, 0x7E, 0x44, 0xB6, 0x71, 0x25, 0x3B, 0xCA, 0xF2, 0xB8, 0xBC, 0xDB, 0xF9, 0x86, 0x41, 0x84, 0xA6, 0x4F, 0xB2, 0x31, 0x2B, 0xF5, 0x60, 0x28, 0xD1, 0x29, 0x41, 0xE1, 0x3F, 0x0C, 0xC8 },
{ 0x09, 0xCF, 0x4F, 0x3C, 0x2A, 0x6C, 0x76, 0x05, 0x73, 0x59, 0xF6, 0x7F, 0x6D, 0x7A, 0x88, 0x3B, 0xDB, 0x0B, 0xAD, 0x00, 0x11, 0xF9, 0x15, 0xBC, 0xCA, 0x00, 0x93, 0xFD, 0x4E, 0xA6, 0xDC, 0x4F, 0x7F, 0x8D, 0x29, 0x2F, 0x57, 0x5C, 0x00, 0x6E, 0xB6, 0x63, 0x0C, 0xA6 }};
```

So, one can first start coding on their PC, expand the key, export it and copy-paste the array (probably by also making it *const*) inside the embedded project. This way the scheduled key may be tuned to end up in the flash memory of the MCU instead of occupying the limited RAM.

### 🧱 Hardware acceleration via the AES instructions (refers to x86-64, ARMv8 and RISC-V)
...

### 🧱 Column-Major Order
...

## 🔧 Build Instructions

To compile the project, run the following command in the root directory:

```bash
gcc -o main main.c aes_cipher.c aes_helpers.c
```