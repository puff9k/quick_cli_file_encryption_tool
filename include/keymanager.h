#ifndef KEYMANAGER_H
#define KEYMANAGER_H

#include <stdint.h>

#define KEYSIZE 32

void resizekey(uint8_t *key, char *input);

void extractkeyfromfile(uint8_t *key, const char *filename);

void viewkey(const uint8_t *key, uint8_t hex_format);

#endif
