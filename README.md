<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>RSA Encryption Algorithm on AT89s52</title>
</head>
<body>
    <h1>RSA Encryption Algorithm on AT89s52 Microcontroller</h1>

    <h2>Project Overview</h2>
    <p>The primary goal of this project is to implement the RSA public-key cryptographic algorithm on the 8051 Microcontroller Unit (MCU). RSA is widely used for secure data communication, leveraging its ability to encrypt and decrypt messages using public and private keys. This project demonstrates the feasibility of running RSA operations, including key generation, encryption, and decryption, on a constrained embedded system. <strong>Note: The current implementation has issues and does not work as intended.</strong></p>

    <h2>Features</h2>
    <ul>
        <li>
            <strong>Prime Number Validation:</strong>
            <ul>
                <li>Uses Fermat's Little Theorem for primality testing.</li>
                <li>Ensures valid prime numbers are selected for key generation.</li>
            </ul>
        </li>
        <li>
            <strong>Key Generation:</strong>
            <ul>
                <li>Computes public (e) and private (d) keys using the RSA algorithm.</li>
                <li>Implements modular arithmetic and the Extended Euclidean Algorithm for calculations.</li>
            </ul>
        </li>
        <li>
            <strong>Encryption and Decryption:</strong>
            <ul>
                <li>Encrypts plaintext (PT) or decrypts ciphertext (CT).</li>
                <li>Uses modular exponentiation for both processes.</li>
            </ul>
        </li>
        <li>
            <strong>UART Communication:</strong>
            <ul>
                <li>Facilitates communication with a PC terminal via UART.</li>
                <li>Allows user input for prime numbers, plaintext, and ciphertext.</li>
                <li>Displays key parameters and results in the terminal.</li>
            </ul>
        </li>
    </ul>

    <h2>Technical Details</h2>
    <ul>
        <li><strong>Hardware Platform:</strong> 8051 Microcontroller Unit (MCU)</li>
        <li><strong>Software Environment:</strong> Keil uVision</li>
        <li><strong>Programming Language:</strong> Embedded C</li>
        <li><strong>Key Algorithms:</strong>
            <ul>
                <li>Modular exponentiation for encryption and decryption.</li>
                <li>Extended Euclidean Algorithm for modular inverses.</li>
                <li>Primality testing for key generation.</li>
            </ul>
        </li>
        <li><strong>Data Communication:</strong> UART serial interface connected to Termite on a PC.</li>
    </ul>

    <h2>Code Functionality Breakdown</h2>
    <ul>
        <li><strong>Key Functions:</strong>
            <ul>
                <li><code>mod_exp:</code> Computes modular exponentiation to prevent overflow.</li>
                <li><code>mod_inv:</code> Calculates modular inverse using the Extended Euclidean Algorithm.</li>
                <li><code>primality_test:</code> Verifies primality using division and Fermat's tests.</li>
                <li><code>public_exp:</code> Determines a valid public exponent (<em>e</em>) coprime with phi.</li>
            </ul>
        </li>
        <li><strong>Serial Communication:</strong>
            <ul>
                <li><code>serial_init:</code> Initializes UART communication.</li>
                <li><code>Data_Uart:</code> Handles data transmission and reception via UART.</li>
                <li><code>serial0:</code> Implements interrupt-driven UART communication.</li>
                <li>Uses Termite as the terminal application on a PC for interaction.</li>
            </ul>
        </li>
        <li><strong>Main Flow:</strong>
            <ul>
                <li>Accepts two prime numbers (<em>p</em> and <em>q</em>) via UART.</li>
                <li>Calculates <em>n</em>, phi, <em>e</em>, and <em>d</em>.</li>
                <li>Encrypts plaintext to ciphertext or decrypts ciphertext to plaintext based on user input.</li>
                <li>Displays results in the Termite terminal.</li>
            </ul>
        </li>
    </ul>

    <h2>Challenges and Optimizations</h2>
    <ul>
        <li><strong>Arithmetic Overflow:</strong> Utilized modular reduction to fit computations within the 8051's constraints.</li>
        <li><strong>Limited MCU Resources:</strong> Optimized memory usage and implemented efficient data handling techniques.</li>
        <li><strong>Input Validation:</strong> Ensured robust handling of user input for key generation and operations.</li>
        <li><strong>Termite Integration:</strong> Established smooth UART communication between the MCU and the PC application.</li>
    </ul>

    <h2>GitHub Repository</h2>
    <p>You can find the project code and further documentation on my GitHub account: <a href="https://github.com/Mostafa-Salama-1">Mostafa-Salama-1</a>.</p>
</body>
</html>
