#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <dirent.h>
#include "pgm_utils.h"

#define MAX_IMAGES 2000
#define PATH_LEN 256

char filenames[MAX_IMAGES][PATH_LEN];
int num_images = 0;

void listar_imagenes(const char *folder) {
    DIR *dir = opendir(folder);
    struct dirent *ent;
    if (!dir) {
        perror("No se puede abrir la carpeta");
        exit(1);
    }
    while ((ent = readdir(dir)) != NULL) {
        if (strstr(ent->d_name, ".pgm")) {
            sprintf(filenames[num_images++], "%s/%s", folder, ent->d_name);
        }
    }
    closedir(dir);
}

// === Ejemplo de filtros ===
void filtro_invertir(PGMImage *img) {
    for (int i = 0; i < img->width * img->height; i++)
        img->data[i] = 255 - img->data[i];
}

void filtro_blur(PGMImage *img) {
    int w = img->width, h = img->height;
    unsigned char *tmp = malloc(w * h);
    int kernel[3][3] = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    for (int y = 1; y < h - 1; y++) {
        for (int x = 1; x < w - 1; x++) {
            int sum = 0;
            for (int ky = -1; ky <= 1; ky++)
                for (int kx = -1; kx <= 1; kx++)
                    sum += img->data[(y + ky) * w + (x + kx)] * kernel[ky + 1][kx + 1];
            tmp[y * w + x] = sum / 9;
        }
    }
    memcpy(img->data, tmp, w * h);
    free(tmp);
}

// === Procesamiento secuencial ===
void procesar_secuencial(const char *carpeta) {
    listar_imagenes(carpeta);
    double t_ini = omp_get_wtime();

    for (int i = 0; i < num_images; i++) {
        PGMImage *img = readPGM(filenames[i]);
        if (!img) continue;

        filtro_invertir(img);
        filtro_blur(img);

        char out[PATH_LEN];
        sprintf(out, "out_seq_%d.pgm", i);
        writePGM(out, img);
        freePGM(img);
    }

    double t_fin = omp_get_wtime();
    printf("Tiempo total secuencial: %.4f segundos\n", t_fin - t_ini);
}

// === Procesamiento paralelo ===
void procesar_paralelo(const char *carpeta) {
    listar_imagenes(carpeta);
    double t_ini = omp_get_wtime();

    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < num_images; i++) {
        PGMImage *img = readPGM(filenames[i]);
        if (!img) continue;

        filtro_invertir(img);
        filtro_blur(img);

        char out[PATH_LEN];
        sprintf(out, "out_par_%d.pgm", i);
        writePGM(out, img);
        freePGM(img);
    }

    double t_fin = omp_get_wtime();
    printf("Tiempo total paralelo: %.4f segundos\n", t_fin - t_ini);
}

int main() {
    const char *carpeta = "C:/Users/jeyco/Documents/GitHub/FiltradoEspacio/images";

    printf("Procesando imágenes desde: %s\n", carpeta);

    procesar_secuencial(carpeta);
    procesar_paralelo(carpeta);

    return 0;
}
