#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>
#include "funciones.h" // Archivo con funciones auxiliares como iniMatrix, impMatrix, etc.


//Paraleliza la multiplicacion de matrices utilizando OpenMP.
//mA = Puntero a la matriz A.
//mB = Puntero a la matriz B.
//mC = Puntero a la matriz resultado C.
//D = Dimensión de las matrices (D x D).
void multiMatrix(size_t *mA, size_t *mB, size_t *mC, int D) {
    size_t Suma, *pA, *pB;

    // Paralelismo con OpenMP
    #pragma omp parallel
    {
        // Dividir el trabajo entre los hilos
        #pragma omp for 
        for (int i = 0; i < D; i++) { // Iterar sobre las filas de la matriz A
            for (int j = 0; j < D; j++) { // Iterar sobre las columnas de la matriz B
                pA = mA + i * D; // Apuntador a la fila de la matriz A
                pB = mB + j;     // Apuntador a la columna de la matriz B
                Suma = 0.0;

                // Producto escalar entre la fila de A y la columna de B
                for (int k = 0; k < D; k++, pA++, pB += D) {
                    Suma += *pA * *pB;
                }

                // Asignar el resultado a la matriz C
                mC[i * D + j] = Suma;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    // Validación de argumentos
    if (argc < 3) {
        printf("\n Use: $./clasicaOpenMP SIZE Hilos \n\n");
        exit(0);
    }

    // Lectura de argumentos
    int N = atoi(argv[1]); // Tamaño de la matriz (N x N)
    int TH = atoi(argv[2]); // Número de hilos a utilizar

    // Reserva de memoria para las matrices
    size_t *matrixA = (size_t *)calloc(N * N, sizeof(size_t));
    size_t *matrixB = (size_t *)calloc(N * N, sizeof(size_t));
    size_t *matrixC = (size_t *)calloc(N * N, sizeof(size_t));
    srand(time(NULL)); // Inicialización de la semilla para números aleatorios

    // Configuración del número de hilos para OpenMP
    omp_set_num_threads(TH);

    // Inicialización de las matrices A y B con valores aleatorios
    iniMatrix(matrixA, matrixB, N);

    // Impresión de las matrices A y B (solo si el tamaño es pequeño)
    impMatrix(matrixA, N);
    impMatrix(matrixB, N);

    // Inicio de la medición del tiempo
    InicioMuestra();

    // Multiplicación de matrices
    multiMatrix(matrixA, matrixB, matrixC, N);

    // Impresión de la matriz resultado C (solo si el tamaño es pequeño)
    impMatrix(matrixC, N);

    // Fin de la medición del tiempo
    FinMuestra();

    // Liberación de memoria
    free(matrixA);
    free(matrixB);
    free(matrixC);

    return 0;
}
