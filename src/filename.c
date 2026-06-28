#include "filename.h" 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdint.h>

const char *getfileext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    return (dot && dot != filename) ? dot : "";
}

void getfileprefix(const char *filename, char *out, size_t out_size) {
    const char *dot = strrchr(filename, '.');
    size_t len = dot ? (size_t)(dot - filename) : strlen(filename);

    if (len >= out_size)
        len = out_size - 1;

    strncpy(out, filename, len);
    out[len] = '\0';
}

char *encfilename(char *filename, size_t size) {
    char prefix[256];
    const char *ext = getfileext(filename);

    getfileprefix(filename, prefix, sizeof(prefix));

    if (strlen(prefix) + 2 * strlen(ext) + 1 > size) {
        fprintf(stderr, "file name too long\n");
        return NULL;
    }

    snprintf(filename, size, "%s%s%s", prefix, ext, ext);
    return filename;
}

