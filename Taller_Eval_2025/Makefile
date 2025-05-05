GCC = gcc
CFLAGS = -lm
FOPENMP = -fopenmp -O3
POSIX = -lpthread

modulo = funciones.c

PROGRAMAS = mmClasicaOpenMP mmClasicaFork mmClasicaPosix

ALL: $(PROGRAMAS)


mmClasicaPosix:
	$(GCC) $(modulo) $(CLFAGS) $@.c -o $@ $(POSIX)

mmClasicaFork:
	$(GCC) $(modulo) $(CLFAGS) $@.c -o $@

mmClasicaOpenMP:
	$(GCC) $(modulo) $(CLFAGS) $@.c -o $@ $(FOPENMP)

clean:
	$(RM) $(PROGRAMAS)
