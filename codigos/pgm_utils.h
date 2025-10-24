#ifndef PGM_UTILS_H
#define PGM_UTILS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int width;
    int height;
    unsigned char *data;
} PGMImage;

PGMImage* readPGM(const char *filename);
void writePGM(const char *filename, const PGMImage *img);
void freePGM(PGMImage *img);

#endif

