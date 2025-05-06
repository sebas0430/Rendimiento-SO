#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "funciones.h"

#define DATA_SIZE (1024*1024*64*3) // Tamaño del bloque de memoria estática

pthread_mutex_t MM_mutex; // Mutex para sincronización (no usado activamente)
static double MEM_CHUNK[DATA_SIZE]; // Bloque de memoria estática para matrices
double *mA, *mB, *mC; // Punteros a las matrices A, B y C

// Estructura para pasar parámetros a los hilos
struct parametros {
    int nH;  // Número total de hilos
    int idH; // Identificador del hilo
    int N;   // Tamaño de la matriz (N x N)
};

// Función ejecutada por cada hilo para multiplicar matrices
void *multiMatrix(void *variables) {
    struct parametros *data = (struct parametros *)variables;
    
    int idH = data->idH; // ID del hilo
    int nH  = data->nH;  // Número total de hilos
    int N   = data->N;   // Tamaño de la matriz
    int ini = (data->N / data->nH) * data->idH;
    int fin = (data->idH == data->nH - 1) ? data->N : ini + (data->N / data->nH);
    // Multiplicación de matrices
    for (int i = ini; i < fin; i++) {
        for (int j = 0; j < N; j++) {
            double *pA, *pB, sumaTemp = 0.0;
            pA = mA + (i * N); // Puntero a la fila de mA
            pB = mB + j;       // Puntero a la columna de mB
            for (int k = 0; k < N; k++, pA++, pB += N) {
                sumaTemp += (*pA * *pB); // Producto escalar
            }
            mC[i * N + j] = sumaTemp; // Almacena el resultado en mC
        }
    }

    pthread_mutex_lock(&MM_mutex);   // Bloqueo del mutex (innecesario aquí)
    pthread_mutex_unlock(&MM_mutex); // Desbloqueo del mutex
    pthread_exit(NULL); // Finaliza el hilo
}

int main(int argc, char *argv[]) {
    // Verifica que se pasen los argumentos necesarios
    if (argc < 3) {
        printf("Ingreso de argumentos \n $./ejecutable tamMatriz numHilos\n");
        exit(0);	
    }

    int SZ = atoi(argv[1]); // Tamaño de la matriz
    int n_threads = atoi(argv[2]); // Número de hilos

    pthread_t p[n_threads]; // Arreglo de identificadores de hilos
    pthread_attr_t atrMM;   // Atributos de los hilos

    // Asignación de memoria para las matrices dentro de MEM_CHUNK
    mA = MEM_CHUNK;
    mB = mA + SZ * SZ;
    mC = mB + SZ * SZ;

    // Inicialización e impresión de matrices (comentado en iniMatrix)
    // iniMatrix(SZ);
    impMatrix(mA, SZ);
    impMatrix(mB, SZ);

    InicioMuestra(); // Inicia la medición de tiempo

    // Inicialización del mutex y atributos de los hilos
    pthread_mutex_init(&MM_mutex, NULL);
    pthread_attr_init(&atrMM);
    pthread_attr_setdetachstate(&atrMM, PTHREAD_CREATE_JOINABLE);

    // Creación de hilos
    for (int j = 0; j < n_threads; j++) {
        struct parametros *datos = (struct parametros *) malloc(sizeof(struct parametros)); 
        datos->idH = j;          // ID del hilo
        datos->nH  = n_threads;  // Número total de hilos
        datos->N   = SZ;         // Tamaño de la matriz
        pthread_create(&p[j], &atrMM, multiMatrix, (void *)datos);
    }

    // Espera a que todos los hilos terminen
    for (int j = 0; j < n_threads; j++)
        pthread_join(p[j], NULL);

    FinMuestra(); // Finaliza la medición de tiempo
    
    impMatrix(mC, SZ); // Imprime la matriz resultante

    // Limpieza de recursos
    pthread_attr_destroy(&atrMM);
    pthread_mutex_destroy(&MM_mutex);
    pthread_exit(NULL); // Finaliza el programa
}

