#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>
#include "funciones.h" // Archivo con funciones auxiliares como iniMatrix, impMatrix, etc.

// Función para realizar la multiplicación de matrices
// mC: Matriz resultado
// D: Dimensión de las matrices
void multiMatrix(double *mA, double *mB, double *mC, int D, int filaI, int filaF) {
    double Suma, *pA, *pB;
    for (int i = filaI; i < filaF; i++) {
        for (int j = 0; j < D; j++) {
            Suma = 0;
            pA = mA + i * D; 
            pB = mB + j;     
            for (int k = 0; k < D; k++, pA++, pB += D) {
                Suma += *pA * *pB; // Producto escalar
            }
            mC[i * D + j] = Suma; // Asignar el resultado a la matriz C
        }
    }
}

// Función principal
int main(int argc, char *argv[]) {
    // Validación de argumentos
    if (argc < 3) {
        printf("\n \t\tUse: $./nom_ejecutable Tamaño(NXN) Numero_procesos  \n");
        exit(0);
    }

    // Lectura de argumentos
    int N = (int) atoi(argv[1]);    // Tamaño de la matriz
    int num_P = (int) atoi(argv[2]); // Número de procesos

    // Reserva de memoria para las matrices
    double *matA = (double *) calloc(N * N, sizeof(double));
    double *matB = (double *) calloc(N * N, sizeof(double));
    double *matC = (double *) calloc(N * N, sizeof(double));

    srand(time(0)); // Semilla para la generación de números aleatorios

    // Inicialización e impresión de las matrices
    iniMatrix(matA, matB, N);
    impMatrix(matA, N);
    impMatrix(matB, N);

    // División del trabajo entre los procesos
    int rows_per_process = N / num_P;

    // Inicia la medición del tiempo
    InicioMuestra();

    // Creación de procesos hijos
    for (int i = 0; i < num_P; i++) {
        pid_t pid = fork(); // Crear un nuevo proceso

        if (pid == 0) { // Código del proceso hijo
            int start_row = i * rows_per_process; // Fila inicial
            int end_row = (i == num_P - 1) ? N : start_row + rows_per_process; // Fila final

            // Multiplicación de matrices para las filas asignadas
            multiMatrix(matA, matB, matC, N, start_row, end_row);

            // Si el tamaño de la matriz es menor a 9, imprimir el resultado parcial
            if (N < 9) {
                //printf("\nChild PID %d calculated rows %d to %d:\n", getpid(), start_row, end_row - 1);
                for (int r = start_row; r < end_row; r++) {
                    for (int c = 0; c < N; c++) {
                        matC[N * r + c];
                        //printf(" %f ", matC[N * r + c]);
                    }
                    //printf("\n");
                }
            }
            exit(0); // Termina el proceso hijo
        } else if (pid < 0) { // Error al crear el proceso
            perror("fork failed");
            exit(1);
        }
    }

    // El proceso padre espera a que todos los hijos terminen
    for (int i = 0; i < num_P; i++) {
        wait(NULL);
    }

    // Finaliza la medición del tiempo
    FinMuestra();

    // Liberación de memoria
    free(matA);
    free(matB);
    free(matC);

    return 0;
}
