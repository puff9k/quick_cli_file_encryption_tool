#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "keymanager.h"
#include "xor.h"

#define MAX_CMD 256

void clear_stdout() {
	printf("\033[2J\033[H");
    fflush(stdout);
}

void print_banner() {
	clear_stdout();
	printf(
        "███████╗██╗██╗     ███████╗    ████████╗ ██████╗  ██████╗ ██╗\n"
        "██╔════╝██║██║     ██╔════╝    ╚══██╔══╝██╔═══██╗██╔═══██╗██║\n"
        "█████╗  ██║██║     █████╗         ██║   ██║   ██║██║   ██║██║\n"
        "██╔══╝  ██║██║     ██╔══╝         ██║   ██║   ██║██║   ██║██║\n"
        "██║     ██║███████╗███████╗       ██║   ╚██████╔╝╚██████╔╝███████╗\n"
        "╚═╝     ╚═╝╚══════╝╚══════╝       ╚═╝    ╚═════╝  ╚═════╝ ╚══════╝\n\n"
    );

	printf("type 'help' for a list of commands\n");
}

void help() {
	printf("\n\n		Prototype cli tool to do various things with files\n");
	printf("		To exit, enter 'exit'\n");
	printf("		For now you can only encrypt/decrypt a file with the xor algorithm\n");
	printf("		To do so, type 'encrypt'\n");
	printf("		You can choose the cypher key from a file, a string, or you can generate it\n\n");
}

void command(char *input) {
	if (strcmp(input, "help") == 0) {
		help();
		return;
	} else if (strcmp(input, "encrypt") == 0) {
		char file_to_encrypt[256] = {0};
		printf("\n\nEnter the path to the file you want to encrypt: ");		
		
		if (fgets(file_to_encrypt, sizeof(file_to_encrypt), stdin) == NULL) {
			perror("Error reading input\n");
			return;
		}

		file_to_encrypt[strcspn(file_to_encrypt, "\n")] = 0;

		uint8_t key[KEYSIZE];
		char keymode[256] = {0};

        printf("\n\nKeymodes:\n");
        printf("1. Press Enter to generate random key\n");
        printf("2. Type 'file' to use key from file\n");
        printf("3. Type any string to use as key (will be resized)\n");
        printf("Enter keymode: ");

        if (fgets(keymode, sizeof(keymode), stdin) == NULL) {
            perror("Error reading input\n");
            return;
        }

        keymode[strcspn(keymode, "\n")] = 0;

        if (strlen(keymode) == 0) {
            resizekey(key, "");
        }
        else if (strcmp(keymode, "file") == 0) {
			char file_key[256] = {0};
            printf("\n\nEnter path to key file: ");
            if (fgets(file_key, sizeof(file_key), stdin) == NULL) {
                perror("Error reading input\n");
                return;
            }
            file_key[strcspn(file_key, "\n")] = 0;
            extractkeyfromfile(key, file_key);
        }
        else {
            resizekey(key, keymode);
        }

        viewkey(key, 1);

		char encryptmode[256] = {0};

		printf("\n\nEnter cypher method\n");
		printf("Available methods :\n xor\n aes256 coming soon\n");
		printf("Enter mode: ");

		if (fgets(encryptmode, sizeof(encryptmode), stdin) == NULL) {
			perror("Error reading input");
			return;
		}

		encryptmode[strcspn(encryptmode, "\n")] = 0;

		if (strcmp(encryptmode, "xor") == 0) {
			xorencrypt(file_to_encrypt, key);
		} else {
			printf("No other method available yet\n");
			return;
		}

    	printf("\nOperation completed.\n");
    	printf("Generated key is saved in key.txt (if random key was generated)\n");
    	printf("Encrypted file: <originalname>.<originalextension>.<originalextension>\n");
		printf("Encrypted file is located in the same repository as the original file\n"); 
	}
}


void shell() {
    char input[MAX_CMD];

    print_banner();

    while (1) {
        printf("file_tool> ");
        fflush(stdout);

        if (!fgets(input, sizeof(input), stdin)) {
            break;
        }

        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "exit") == 0) {
            break;
        }

        command(input);
    }
}
