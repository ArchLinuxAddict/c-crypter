#include <stdio.h>
#include <stdlib.h>

void xor_encrypt(const char *input_filename, const char *output_filename, char key) {
    FILE *input_file = fopen(input_filename, "rb");
    if (!input_file) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    FILE *output_file = fopen(output_filename, "wb");
    if (!output_file) {
        perror("Failed to open output file");
        fclose(input_file);
        exit(EXIT_FAILURE);
    }

    fseek(input_file, 0, SEEK_END);
    long file_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(file_size);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(input_file);
        fclose(output_file);
        exit(EXIT_FAILURE);
    }

    fread(buffer, 1, file_size, input_file);
    for (long i = 0; i < file_size; i++) {
        buffer[i] ^= key;
    }

    fwrite(buffer, 1, file_size, output_file);
    fclose(input_file);
    fclose(output_file);
    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <input_file> <output_file> <key>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_filename = argv[1];
    const char *output_filename = argv[2];
    char key = argv[3][0];

    xor_encrypt(input_filename, output_filename, key);

    printf("File %s has been encrypted to %s using key '%c'\n", input_filename, output_filename, key);

    return EXIT_SUCCESS;
}
