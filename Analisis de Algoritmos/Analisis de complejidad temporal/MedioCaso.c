#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define VECES 10000
int Producto2Mayores(int *A, int n)
{
    int mayor1, mayor2, i, contador = 0;
    contador++; //Condicion
    if (A[0] > A[1])
    {
        mayor1 = A[0];
        contador++; //Asignacion
        mayor2 = A[1];
        contador++; //Asignaciom
    }
    else
    {
        mayor1 = A[1];
        contador++; //Asignacion
        mayor2 = A[0];
        contador++; //Asignacion
    }
    i = 2;
    while (i < n)
    {
        contador++; //Condicion
        if (A[i] > mayor1)
        {
            mayor2 = mayor1;
            contador++; //Asignacion
            mayor1 = A[i];
            contador++; //Asignacion
        }
        else
        {
            contador++; //Condicion
            if (A[i] > mayor2)
            {
                mayor2 = A[i];
                contador++; //Asignacion
            }
        }
        i++;
    }
    return contador;
    //return mayor1*mayor2
}

int main(int narg, char **varg)
{
    int n,i,k;
    int *A;
    int promedio = 0;
    int auxiliar;

    if (narg != 2)
    {
        printf("\nIntroduce una n");
        exit(1);
    }
    n = atoi(varg[1]);
    A = malloc(sizeof(int) * n);

    srand(time(NULL));
    for ( k = 0; k < VECES; k++)
    {
        for (i = 0; i < n; i++)
        {
            *(A + i) = rand() % ((1000 * n));
            //printf("Vuelta %d. Numero %d\n",k,A[i]);
        }
        auxiliar = Producto2Mayores(A, n);
        promedio = promedio + (float)auxiliar;
        //printf("Iteracion %d, el contador vale %d\n",k,auxiliar);
    }
    //printf("El promedio es %lf\n", promedio);
    promedio = promedio / VECES;
    printf("El promedio es %d", promedio);

    return 0;
}
