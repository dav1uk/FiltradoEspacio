#include "pgm_utils.h"
#include <string.h>


PGMImage* readPGM(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("Error abriendo imagen");
        return NULL;
    }

    char magic[3];
    int width, height, maxval;
    fscanf(fp, "%2s", magic);
    if (strcmp(magic, "P5") != 0) {
        fclose(fp);
        fprintf(stderr, "Formato PGM no soportado: %s\n", filename);
        return NULL;
    }

    fscanf(fp, "%d %d %d", &width, &height, &maxval);
    fgetc(fp); // Salta salto de línea

    PGMImage *img = malloc(sizeof(PGMImage));
    img->width = width;
    img->height = height;
    img->data = malloc(width * height);

    fread(img->data, 1, width * height, fp);
    fclose(fp);
    return img;
}

void writePGM(const char *filename, const PGMImage *img) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("Error guardando imagen");
        return;
    }
    fprintf(fp, "P5\n%d %d\n255\n", img->width, img->height);
    fwrite(img->data, 1, img->width * img->height, fp);
    fclose(fp);
}

void freePGM(PGMImage *img) {
    if (img) {
        free(img->data);
        free(img);
    }
}
