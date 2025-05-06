#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Variables globales para medición de tiempo
struct timeval inicio, fin;

// Inicia la medición de tiempo
void InicioMuestra() {
    gettimeofday(&inicio, NULL);
}

// Finaliza y muestra el tiempo de ejecución
void FinMuestra() {
    gettimeofday(&fin, NULL);
    fin.tv_usec -= inicio.tv_usec;
    fin.tv_sec  -= inicio.tv_sec;
    double tiempo = (double)(fin.tv_sec * 1000000 + fin.tv_usec);
    printf("%9.0f \n", tiempo);
}

// Inicializa matrices con valores aleatorios
void iniMatrix(double *mA, double *mB, int D) {
    for (int i = 0; i < D * D; i++) {
        mA[i] = rand() % 10;
        mB[i] = rand() % 10;
    }
}

// Imprime matrices si son pequeñas (D < 9)
void impMatrix(double *matrix, int D) {
    if (D < 9) {
        printf("\n");
        for (int i = 0; i < D * D; i++) {
            if (i % D == 0) printf("\n");
            printf("%.0f ", matrix[i]);
        }
        printf("\n-----------------\n");
    }
}