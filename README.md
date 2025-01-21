# RSA Encryption Algorithm on AT89s52 Microcontroller

## Project Overview
The primary goal of this project is to implement the RSA public-key cryptographic algorithm on the 8051 Microcontroller Unit (MCU). RSA is widely used for secure data communication, leveraging its ability to encrypt and decrypt messages using public and private keys. This project demonstrates the feasibility of running RSA operations, including key generation, encryption, and decryption, on a constrained embedded system. **Note: The current implementation has issues and does not work as intended.**

## Features

- **Prime Number Validation:**
  - Uses Fermat's Little Theorem for primality testing.
  - Ensures valid prime numbers are selected for key generation.

- **Key Generation:**
  - Computes public (e) and private (d) keys using the RSA algorithm.
  - Implements modular arithmetic and the Extended Euclidean Algorithm for calculations.

- **Encryption and Decryption:**
  - Encrypts plaintext (PT) or decrypts ciphertext (CT).
  - Uses modular exponentiation for both processes.

- **UART Communication:**
  - Facilitates communication with a PC terminal via UART.
  - Allows user input for prime numbers, plaintext, and ciphertext.
  - Displays key parameters and results in the terminal.

## Technical Details

- **Hardware Platform:** 8051 Microcontroller Unit (MCU)
- **Software Environment:** Keil uVision
- **Programming Language:** Embedded C
- **Key Algorithms:**
  - Modular exponentiation for encryption and decryption.
  - Extended Euclidean Algorithm for modular inverses.
  - Primality testing for key generation.
- **Data Communication:** UART serial interface connected to Termite on a PC.

## Code Functionality Breakdown

- **Key Functions:**
  - `mod_exp`: Computes modular exponentiation to prevent overflow.
  - `mod_inv`: Calculates modular inverse using the Extended Euclidean Algorithm.
  - `primality_test`: Verifies primality using division and Fermat's tests.
  - `public_exp`: Determines a valid public exponent (e) coprime with phi.

- **Serial Communication:**
  - `serial_init`: Initializes UART communication.
  - `Data_Uart`: Handles data transmission and reception via UART.
  - `serial0`: Implements interrupt-driven UART communication.
  - Uses Termite as the terminal application on a PC for interaction.

- **Main Flow:**
  - Accepts two prime numbers (p and q) via UART.
  - Calculates n, phi, e, and d.
  - Encrypts plaintext to ciphertext or decrypts ciphertext to plaintext based on user input.
  - Displays results in the Termite terminal.

## Challenges and Optimizations

- **Arithmetic Overflow:** Utilized modular reduction to fit computations within the 8051's constraints.
- **Limited MCU Resources:** Optimized memory usage and implemented efficient data handling techniques.
- **Input Validation:** Ensured robust handling of user input for key generation and operations.
- **Termite Integration:** Established smooth UART communication between the MCU and the PC application.

## GitHub Repository
You can find the project code and further documentation on my GitHub account: [Mostafa-Salama-1](https://github.com/Mostafa-Salama-1).
