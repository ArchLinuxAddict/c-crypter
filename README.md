# c-crypter
A crypter to encrypt and obfuscate a code and run in windows for now the program is only for windows

# Simple Crypter
This project provides a simple crypter that can encrypt an executable file and create a self-decrypting executable. This is intended for educational purposes only.

## Disclaimer

**This example is provided for educational purposes only. Misuse of this knowledge can result in severe legal consequences. Always ensure you have the right to modify and distribute any software you work with.**

## Overview

The crypter involves the following steps:
1. Encrypt the payload executable.
2. Create a stub executable that contains the decryption routine.
3. Append the encrypted payload to the stub.
4. Ensure the stub can extract, decrypt, and execute the payload.

## Components

1. **Encryptor**: Encrypts the payload executable using XOR encryption.
2. **Stub**: Contains the decryption routine that will be used to decrypt and run the payload.
3. **Appender**: Appends the encrypted payload to the stub.

## Files

- `encrypt.c`: Source code for the encryptor.
- `stub.c`: Source code for the stub.
- `append_payload.c`: Source code for the appender.

## Compilation

Use `gcc` to compile the provided source files.

### Encryptor

```sh
gcc -o encrypt encrypt.c
```

## Stub

```
gcc -o stub.exe stub.c -mwindows
```

## Appender

```
gcc -o append_payload append_payload.c
```

## Usage
Step 1: Encrypt the Payload
Use the encrypt program to encrypt the executable you want to protect.

```
./encrypt original_payload.exe encrypted_payload.exe key
```

- original_payload.exe: The original executable to encrypt.
- encrypted_payload.exe: The output encrypted executable.
- k: The encryption key (a single character).

Step 2: Append the Encrypted Payload to the Stub
Use the append_payload program to append the encrypted payload to the stub.

```
./append_payload stub.exe encrypted_payload.exe
```

- stub.exe: The stub executable to which the encrypted payload will be appended.
- encrypted_payload.exe: The encrypted payload to append.

Step 3: Run the Resulting Crypter
Run the resulting stub.exe. It will decrypt the payload and execute it.

```
stub.exe
```

## Notes
1. Security: This example uses simple XOR encryption, which is not secure for real-world applications. Use a more secure algorithm (like AES) for actual encryption needs.
2. Portability: The provided stub example is designed for Windows. Adjustments are needed for different platforms.
3. Complexity: This example omits handling PE headers properly, error handling, and various edge cases. Real-world crypters are much more sophisticated.


## License

This project is licensed under the MIT License. See the LICENSE file for details.

