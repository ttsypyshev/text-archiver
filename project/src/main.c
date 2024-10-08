/// Warning:
// large files (1MB+) can take a long time to open, this is not a problem with the algorithms,
// this is a problem with the language's built-in file reading method



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compress.h"
#include "decompress.h"

/**
 * Prints the usage instructions for the command-line tool.
 * Provides information on how to invoke the compression and decompression functionalities.
 */
void print_help() {
    printf("Usage:\n");
    printf("  -p, --pack <filename.txt> [archive_name.txt]   Compress the specified file.\n");
    printf("  -u, --unpack <archive_name.txt> [output_filename.txt]   Decompress the specified archive.\n");
    printf("  --help                                      Show this help message.\n");
}

/**
 * Main entry point of the application. Handles command-line arguments to invoke compression or decompression.
 *
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 * @return Exit status of the program (0 for success, 1 for failure).
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_help();
        return 1;
    }

    if (strcmp(argv[1], "--help") == 0) {
        print_help();
        return 0;
    }

    if ((strcmp(argv[1], "-p") == 0 || strcmp(argv[1], "--pack") == 0) && argc >= 3) {
        printf("Opening file...\n");
        const char *input_file = argv[2];
        const char *output_file = (argc >= 4) ? argv[3] : input_file;

        int size_enc = 0;
        int *enc1 = Compress1(input_file, &size_enc);

        int *enc2 = Analysis(&size_enc, enc1);
        free(enc1);

        Compress2(output_file, size_enc, enc2);
        free(enc2);

        printf("Compression completed successfully.\n");
    } else if ((strcmp(argv[1], "-u") == 0 || strcmp(argv[1], "--unpack") == 0) && argc >= 3) {
        printf("Opening file...\n");
        const char *input_file = argv[2];
        const char *output_file = (argc >= 4) ? argv[3] : input_file;

        int size_dec = 0;
        int *dec = Decompress1(input_file, &size_dec);

        int size_dec1 = 0;
        int **dec1 = Decompress2(dec, size_dec, &size_dec1);
        free(dec);

        Output(output_file, dec1, size_dec1);
        free(dec1);

        printf("Decompression completed successfully.\n");
    } else {
        print_help();
        return 1;
    }

    return 0;
}
