# Taller Evaluacion de Rendimiento

Este repositorio contiene un taller de evaluación de rendimiento de algoritmos de multiplicación de matrices en C, utilizando distintos modelos de paralelismo: POSIX Threads, OpenMP y procesos con `fork()`. Se va comparar el desempeño de cada enfoque en términos de tiempo de ejecución y eficiencia. Con el fin de poder analizar los algoritmos seriales y paralelos

## Contenido del repositorio

- `EnunciadoEval.pdf`: Documento con las instrucciones y objetivos del taller.
- `TallerEvRendimiento_SisOp`: Documento final sobre el taller con el analisis de resultados
- `funciones.c` y `funciones.h`: Funciones auxiliares para la generación y
- `mmClasicaPosix.c`: Implementación de multiplicación de matrices utilizando hilos POSIX.
- `mmClasicaOpenMP.c`: Implementación utilizando directivas OpenMP.
- `mmClasicaFork.c`: Implementación utilizando procesos con `fork()`.
- `lanza.pl`: Script en Perl para automatizar la ejecución de pruebas.
- `Makefile`: Archivo para compilar los programas.

## Requisitos

- Compilador de C (por ejemplo, `gcc`) con soporte para OpenMP.
- Perl (para ejecutar el script `lanza.pl`).
- Sistema operativo compatible con POSIX (Linux o macOS).

## Compilación

Para compilar los programas, utiliza el siguiente comando:

```bash
make
```

Este comando generará los ejecutables:

- `mmClasicaPosix`
- `mmClasicaOpenMP`
- `mmClasicaFork`

## Ejecución

Puedes ejecutar independiente cada programa de la siguiente manera:

```bash
./mmClasicaPosix TamañoMatriz Cantidad_Procesos
./mmClasicaOpenMP TamañoMatriz Cantidad_Procesos
./mmClasicaFork TamañoMatriz Cantidad_Procesos
```

Para automatizar las pruebas y recopilar resultados, puedes utilizar el script en Perl, debes modificarlo para que se utilice
para cada uno de los ejecutables:

```bash
./lanza.pl
```

Este script ejecutará las pruebas para cada implementación y almacenará los resultados correspondientes.

## Resultados

Los resultados estaran dentro de sus respectivas carpetas, cada archivo incluye datos sobre los tiempos de ejecución y otros parámetros relevantes para el análisis comparativo.
