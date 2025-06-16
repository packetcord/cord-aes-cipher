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
...

### 🧱 Hardware acceleration via the AES instructions (refers to x86-64, ARMv8 and RISC-V)
...

### 🧱 Column-Major Order
...

## 🔧 Build Instructions

To compile the project, run the following command in the root directory:

```bash
gcc -o main main.c aes_cipher.c aes_helpers.c
