#include "keymanager.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdint.h>

/*key should be 32 bytes (character) long, else it will be repeated / truncated*/
/*if key is null, it will be randomly generated*/

/*extract key from file converts the chars in the file to ascii values*/
/*!!!key from file may vary from a system to another*/

void resizekey(uint8_t *key, char *input) {
	if (key == NULL || input == NULL) {
		fprintf(stderr, "null pointer");
		return;
	}

	size_t inputlen = strlen(input);

	if (inputlen == 0) {
		srand((unsigned int)time(NULL));
		for (size_t i = 0; i < KEYSIZE; i++) {
			key[i] = (uint8_t)(rand() % 256);
		}
		FILE *f = fopen("key.txt", "wb");
		if (f == NULL) {
			perror("Error while creating key.txt\n");
			return;
		}

		size_t written = fwrite(key, 1, KEYSIZE, f);
		if (written != KEYSIZE) {
			perror("Error while writing in key.txt");
		}
		if (ferror(f)) {
			perror("Error while manipulating key.txt\n");
		}
		if (fclose(f) != 0) {
			perror("Error while closing key.txt\n");
		}
	} else {

		for (size_t i = 0; i < KEYSIZE; i++) {
			key[i] = (uint8_t)input[i % inputlen];
		}
	}
}

void extractkeyfromfile(uint8_t *key, const char *filename) {
	if (key == NULL) {
		fprintf(stderr, "Error : null pointer\n");
		return;
	}
	FILE *f = fopen(filename, "rb");
	if (f == NULL) {
		perror("Error with the file containing the key");
		return;
	}
	int c;
	size_t i = 0;
	while ((c = fgetc(f)) != EOF && i <= KEYSIZE) {
		key[i] = (uint8_t)c;
		i++;
	}
	if (ferror(f)) {
		perror("Error while handling the file containing the key");
		fclose(f);
	}
	if (fclose(f) != 0) {
		perror("Error while closing the file containing the key");
	}
	if (strlen((char *)key) < KEYSIZE) {
		resizekey(key, (char *)key);
	}
}

void viewkey(const uint8_t *key, uint8_t hex_format) {
	printf("Key %d bytes : ", KEYSIZE);

	if (hex_format) {
		for (size_t i = 0; i < KEYSIZE; i++) {
			printf("%02X", key[i]);
		}
	} else {
		for (unsigned short int i = 0; i < KEYSIZE; i++) {
			if (i % 8 == 0) printf("\n[%02d] ", i);
			printf("%02X ", key[i]);
		}
	}
	printf("\n");
}
