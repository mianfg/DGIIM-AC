/**
 * @file pmm-secuencial.c
 * @brief Cálculo del producto de dos matrices - secuencial, var. globales
 * @author Miguel Ángel Fernández Gutiérrez <mianfg@correo.ugr.es>
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Vectores globales
#define MAX 10000
double A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];


int main(int argc, char ** argv){
	struct timespec cgt1,cgt2; double t;	// para tiempos
	
	if ( argc < 2 ) {
		printf("[ERROR]-Debe insertar tamaño matriz\n");
		exit(-1);
	}
	
	unsigned int N = atoi(argv[1]);
	if ( N > MAX )
		N = MAX;	
	
	int i, j, k;
	double suma;	
	
	// Inicialización matrices B, C
	for ( i = 0; i < N; i++ )
		for ( j = 0; j < N; j++ ) {
			B[i][j]=j+1;
			C[i][j]=j+1;
		}
		
	// Tiempo
	clock_gettime(CLOCK_REALTIME,&cgt1);

	// Cálculo de A=B*C
	for ( j = 0; j < N ; j++ )
		for ( i = 0; i < N; i++ ) {
			A[i][j] = 0;
			for ( k = 0; k < N; k++ )
				A[i][j] = A[i][j]+B[i][k]*C[k][j];
		}
		
	// Tiempo
	clock_gettime(CLOCK_REALTIME,&cgt2);
	
	t = (double) (cgt2.tv_sec-cgt1.tv_sec)+
	    (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));
	
	// Impresión de tiempo de ejecución
	printf("Tiempo (seg): %11.9f\n", t);
	
	
	// Impresión de resultados
	printf("\n__________\nResultados:\n");
	
	printf("\nMatriz B: \n");
	if ( N < 10 )
		for ( i = 0; i < N; i++ ) {
			for ( j = 0; j < N; j++ )
				printf("%f ", B[i][j]);
			printf("\n");
		}
	else
		printf("B[0][0]=%f B[%d][%d]=%f\n", B[0][0], N-1, N-1, B[N-1][N-1]);
		
	printf("\nMatriz C: \n");
	if ( N < 10 )
		for ( i = 0; i < N; i++ ) {
			for ( j = 0; j < N; j++ )
				printf("%f ", C[i][j]);
			printf("\n");
		}
	else
		printf("C[0][0]=%f C[%d][%d]=%f\n", C[0][0], N-1, N-1, C[N-1][N-1]);
	
	printf("\nMatriz A=B*C: \n");
	if ( N < 10 )
		for ( i = 0; i < N; i++ ) {
			for ( j = 0; j < N; j++ )
				printf("%f ", A[i][j]);
			printf("\n");
		}
	else
		printf("A[0][0]=%f A[%d][%d]=%f\n", A[0][0], N-1, N-1, A[N-1][N-1]);
		
	printf("\n");
	
	return 0;
}
