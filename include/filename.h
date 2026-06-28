#ifndef FILENAME_H
#define FILENAME_H

#include <stddef.h>

const char *getfileext(const char *filename);
void getfileprefix(const char *filename, char *out, size_t out_size);
char *encfilename(char *filename, size_t strsize);

#endif
