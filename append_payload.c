#include <stdio.h>
#include <stdlib.h>

void append_payload(const char *stub_filename, const char *payload_filename) {
    FILE *stub_file = fopen(stub_filename, "ab");
    FILE *payload_file = fopen(payload_filename, "rb");

    if (!stub_file || !payload_file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    fseek(payload_file, 0, SEEK_END);
    long payload_size = ftell(payload_file);
    fseek(payload_file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(payload_size);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(stub_file);
        fclose(payload_file);
        exit(EXIT_FAILURE);
    }

    fread(buffer, 1, payload_size, payload_file);
    fwrite(buffer, 1, payload_size, stub_file);
    fwrite(&payload_size, sizeof(payload_size), 1, stub_file);

    fclose(stub_file);
    fclose(payload_file);
    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <stub_file> <payload_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *stub_filename = argv[1];
    const char *payload_filename = argv[2];

    append_payload(stub_filename, payload_filename);

    printf("Payload %s has been appended to %s\n", payload_filename, stub_filename);

    return EXIT_SUCCESS;
}
