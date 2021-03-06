/**
 * @brief Código para calcular producto de una matriz cuadrada por un vector
 * @author Miguel Ángel Fernández Gutiérrez <mianfg@correo.ugr.es>
 * @date 11 abril, 2019
 */

#include <stdlib.h>	// atoi(), malloc(), free()
#include <stdio.h>	// printf()
#include <time.h>	// clock_gettime()

//#define VECTOR_GLOBAL	// descomentar si se desea usar vectores globales
#define VECTOR_DYNAMIC	// descomentar si se desea usar vectores dinámicos

#ifdef VECTOR_GLOBAL
#define MAX 33554432

double v1[MAX], v2[MAX], M[MAX][MAX];
#endif

int main(int argc, char** argv) {
	struct timespec cgt1, cgt2; double ncgt;	// tiempos de ejecución

	if ( argc < 2 ) {
		printf("ERROR: falta el tamaño N de la matriz NxN y del vector\n");
		exit(EXIT_FAILURE);
	}

	unsigned int N = atoi(argv[1]);		// Tamaño del vector

	#ifdef VECTOR_DYNAMIC
	double *v1, *v2, **M;
	v1 = (double*) malloc(N*sizeof(double));
	v2 = (double*) malloc(N*sizeof(double));
	M = (double**) malloc(N*sizeof(double*));
	for ( int i = 0; i < N; i++ )
		M[i] = (double*) malloc(N*sizeof(double));

	if ( (v1==NULL) || (v2==NULL) || (M==NULL) ) {
		printf("ERROR: en la reserva de memoria dinámica para matriz y vectores\n");
		exit(EXIT_FAILURE);
	}
	#endif

	// Inicialización de vectores y matriz
	for ( int i = 0; i < N; i++ ) {
		v1[i] = i;
		v2[i] = 0;

		// haremos que la matriz M sea 2*Id (Id = "matriz identidad"), entonces podremos
		// comprobar el resultado simplemente viendo que debe ser v2 = 2*v1
		for ( int j = 0; j < N; j++ )
			if ( i == j )
				M[i][j] = 2;
			else
				M[i][j] = 0;
	}

	clock_gettime(CLOCK_REALTIME, &cgt1);
	// calculamos el producto v2 = M*v1
	for ( int i = 0; i < N; i++ )
		for ( int k = 0; k < N; k++ )
			v2[i] += M[i][k]*v1[i];
	clock_gettime(CLOCK_REALTIME, &cgt2);

	ncgt = (double) (cgt2.tv_sec-cgt1.tv_sec) +
	       (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));

	// imprimimos v2 por pantalla, y el tiempo de ejecución
	printf("Resultado: v2 = ");
	for ( int i = 0; i < N; i++ )
		printf("%f ", v2[i]);
	printf("\n\nTamaño: %d -> Tiempo de ejecución: %f\n\n", N, ncgt);

	#ifdef VECTOR_DYNAMIC
	free(v1);
	free(v2);
	for ( int i = 0; i < N; i++ )
		free(M[i]);
	free(M);
	#endif
}
