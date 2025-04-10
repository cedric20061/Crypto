# Cryptography Project

## Overview

This project implements various cryptographic algorithms and utilities for encrypting and decrypting messages. It includes Caesar cipher, keyword-based encryption, Playfair cipher, and more. The project also provides tools for analyzing text and guessing encryption keys.

## Features

- **Caesar Cipher**: Encrypt and decrypt messages using a shift key.
- **Keyword-Based Cipher**: Encrypt and decrypt messages using a keyword.
- **Perfect Cipher**: Encrypt messages using a key extracted from a file.
- **Playfair Cipher**: Encrypt and decrypt messages using the Playfair cipher.
- **Key Guessing**: Guess the most probable keys for encrypted messages.
- **Text Analysis**: Analyze text for linguistic patterns and probabilities.

## File Descriptions

### `main.c`

The main entry point of the program. It provides a menu-driven interface for selecting encryption methods and performing encryption or decryption.

### `utils/crypto.c`

Contains the implementation of various cryptographic algorithms, including:

- Caesar cipher (`crypto_v1`, `decrypto_v1`)
- Keyword-based cipher (`crypto_v2`, `decrypto_v2`)
- Perfect cipher (`crypto_v3`, `decrypto_v3`)
- Playfair cipher (`crypto_v4`, `decrypto_v4`)
- Key guessing (`guessTheKey`)
- Utility functions for text manipulation and key extraction.

### `utils/tests.c`

Implements text analysis functions to evaluate the quality of decrypted text:

- Presence of vowels in words.
- Detection of consecutive consonants.
- Analysis of common and rare digrams.
- Frequency analysis based on the French language.
- Detection of common French words and grammatical structures.

### `README.md`

This file provides an overview of the project, its features, and usage instructions.

## Compilation Instructions

To compile the project, use the following command:

```bash
gcc -Iinclude utils/crypto.c utils/tests.c utils/global.c main.c -o output/crypto_v1
```

## Usage

1. Run the compiled program:
   ```bash
   ./output/crypto_v1
   ```
2. Follow the menu to select an encryption method and provide the necessary inputs (e.g., message, key).

## Dependencies

- Standard C libraries (`stdio.h`, `stdlib.h`, `string.h`, etc.)
- Custom headers (`crypto.h`, `global.h`, `test.h`)

## Project Structure

```
Crypto/
├── main.c
├── utils/
│   ├── crypto.c
│   ├── tests.c
│   ├── global.c
├── include/
│   ├── crypto.h
│   ├── global.h
│   ├── test.h
├── data/
│   ├── key.txt
├── output/
│   ├── crypto_v1
└── README.md
```

## Future Improvements

- Add support for additional cryptographic algorithms.
- Enhance the text analysis functions for better accuracy.
- Implement a graphical user interface (GUI) for easier usage.

## License

This project is open-source and available under the MIT License.
