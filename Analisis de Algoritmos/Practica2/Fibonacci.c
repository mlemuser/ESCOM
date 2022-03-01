/*
  T�tulo: B�squeda de Fibonacci con hilos
  Descripci�n: B�squeda de un valor "x" por medio de b�squeda Fibonacci en un arreglo.
  Valores de entrada: Arreglo de enteros, tama�o y valor "x" a buscar.
  Valores de retorno:
  - Si se encuentra retorna la posici�n. 
  - En caso contrario se retorna -1.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// Struct
#include "datos.h"

// Funci�n para encontrar el m�nimo de dos elementos
int min_fibo(int x, int y)
{
	return (x <= y) ? x : y;
}

void *fibonacciAuxiliar(void *args)
{
	// printf("Entro hilo1\n");
	datos *fibonacci = (datos *)args;

	int left = fibonacci->left;
	int right = fibonacci->right;

	int n = (right - left) + 1;

	/* Inicializa los n�meros de fibonacci */
	int fibMMm2 = 0;							// (m-2) numero Fibonacci
	int fibMMm1 = 1;							// (m-1) numero Fibonacci
	int fibM = fibMMm2 + fibMMm1; // m numero Fibonacci

	/* fibM va a almacenar el menor n�mero de Fibonacci 
    mayor o igual a n */
	while (fibM < n)
	{
		fibMMm2 = fibMMm1;
		fibMMm1 = fibM;
		fibM = fibMMm2 + fibMMm1;
	}
	//Se marca el rango de eliminaci�n
	int offset = -1;
	/* mientras haya elementos para ser inspeccionados. 
    se compara arr[fibMm2] con x. Cuando fibM se convierte en 1, 
    fibMm2 se convierte en 0 */
	while (fibM > 1 && *fibonacci->found == -1)
	{
		//  Comprueba si fibMm2 es una ubicaci�n v�lida
		int i = min_fibo(offset + fibMMm2, n - 1);

		/* Si x es mayor que el valor en el �ndice fibMm2, 
        se corta el subarreglo a i */
		if (fibonacci->arreglo[i + left] < fibonacci->elemento)
		{
			fibM = fibMMm1;
			fibMMm1 = fibMMm2;
			fibMMm2 = fibM - fibMMm1;
			offset = i;
		}

		/* Si x es mayor que el valor en el �ndice fibMm2, 
        se corta el subarreglo despu�s de i+1 */
		else if (fibonacci->arreglo[i + left] > fibonacci->elemento)
		{
			fibM = fibMMm2;
			fibMMm1 = fibMMm1 - fibMMm2;
			fibMMm2 = fibM - fibMMm1;
		}

		/* Si se encuentra se regresa el �ndice */
		else
		{
			*fibonacci->found = 0;
			pthread_exit(NULL);
		}
	}

	/* compara el ultimo elemento con x*/
	if (fibMMm1 && fibonacci->arreglo[offset + 1 + left] == fibonacci->elemento)
	{
		*fibonacci->found = 0;
		pthread_exit(NULL);
	}

	/*Si el elemento se encuentra*/
	pthread_exit(NULL);
}

// Llamar a la funci�n para el main
int fibonacciSearchHilos(int arr[], int n, int x, int parts)
{
	pthread_t ids[parts]; // N�mero de hilos
	int found = -1;				// Encontr� el hilo o no (0 -> false)
	// Variable auxiliar para c�lculo de los rangos de los hilos
	int tamT = n / parts;
	// Variable auxiliar para divisibles no exactos
	int mod = n % parts;

	for (int i = 0; i < parts; i++)
	{
		// Creaci�n de memoria para
		datos *d = malloc(sizeof(datos));
		d->arreglo = arr;
		d->elemento = x;
		// Variable inicio del rango
		d->left = i * tamT;
		// Variable fin del rango
		d->right = (d->left + tamT) - 1;
		// Condicional para ajustar el rango
		if (i == parts - 1)
		{
			// Asignaci�n del valor de rango
			d->right += mod;
		}
		// Comunicaci�n entre hilos
		d->found = &found;

		// Lanza los hilos
		pthread_create(&ids[i], NULL, fibonacciAuxiliar, (void *)d);
	}

	for (int i = 0; i < parts; i++)
	{
		// Fin/terminar hilos
		pthread_join(ids[i], NULL);
	}

	return found;
}
