#include "xor.h"
#include "filename.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define KEYSIZE 32

void xorencrypt(char *filename, uint8_t *key) {
	FILE *f = fopen(filename, "rb");
	if (f == NULL) {
		perror("Error with source file\n");
		return;
	}

	char encrypted_file_name[256];
	strcpy(encrypted_file_name, encfilename(filename, 256)); 

	FILE *fo = fopen(encrypted_file_name, "wb");
	if (fo == NULL) {
		fclose(f);
		perror("Error with destination file\n");
		return;
	}


	int c;
	size_t keyidx = 0;
	while ((c = fgetc(f)) != EOF) {
		fputc(c ^ key[keyidx], fo);
		keyidx = (keyidx + 1) % KEYSIZE;
	}

	if (ferror(f) || ferror(fo)) {
		perror("Error while handling files\n");
	}
	if (fclose(f) != 0) {
		perror("Error while closing src file\n");
	}
	if (fclose(fo) != 0)  {
		perror("Error while closing dest file\n");
	}
}
