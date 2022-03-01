//Librerias utilizadas
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//#include "tiempo.h"

struct argumentos {
	int *arr;
	int target; //
	int li; //Limite inferior
	int ls; //Limite superior
};

/*
	la funcion binarySearch realiza una busqueda binaria en el intervalo dado
	Recibe: (Struct) args que contienen los limites superior e inferior para acotar la busqueda, el numero a buscar y el arreglo donde buscar.
	Finalmente imprime si ha encontrado el numero 
*/
void *binarySearch(void *args){
	int status = 0;
	struct argumentos *bargs = (struct argumentos*) args;
	int li = bargs -> li; //Empezmos a buscar desde aqui
	int ls = bargs -> ls; //Terminamos la busqueda aca
	//Algoritmo binaria
	while (li <= ls) { 
        int index = li + (ls - li) / 2; 
        if (bargs->arr[index] == bargs->target){
            printf("Encontrado\n");
        }
        if (bargs->arr[index] < bargs->target)
            li = index + 1; 
        else
            ls = index - 1; 
    } 
    //Aqui retorna un -1, señal de que no lo encontro
	pthread_exit((void*)&status);
}

/*
	main
	Recibe: Tamaño de problema (argv[1]), Numero a buscar (argv[2]).
	DESCRIPCION: Realiza la identificacion de limites del algoritmo de busqueda exponencial, posteriormente crea hilos que se encargan de la busqueda binaria.
	DEVUELVE: El tiempo que tarda en ejecutarse el algoritmo.
	Nota: argv[1] DEBE SER MAYOR A 0.
*/
void main(int argc, char *argv[]){
	int *numeros = NULL, n = 0, i = 0, target = 0, li = 0, ls = 0, aux = 0;
	struct argumentos *margs[4];
	pthread_t id[4];
	int eid[4]; //Status del hilo
//	double utime0, stime0, wtime0,utime1, stime1, wtime1;

	n = atoi(argv[1]);
	target = atoi(argv[2]);

	numeros = malloc(sizeof(int)*n);
	
	for(i=0;i<4;i++){
		margs[i] = malloc(sizeof(struct argumentos));
	}

	if(numeros==NULL)
		exit(2);
	//Se leen los numeros desde la consola o un archivo
	for(i=0;i<n;i++){
		scanf("%i",&numeros[i]);
	}

	for(i=0;i<4;i++){
		margs[i]->target=target;
		margs[i]->arr=numeros;
	}

	//Comenzamos el algoritmo exponencial
//	uswtime(&utime0, &stime0, &wtime0);

	if(numeros[0]==target){
		//Aqui salimos del programa de una buena vez
//		uswtime(&utime1, &stime1, &wtime1); 
		printf("Encontrado en la posicion 0\n");
		printf("\n");
//		printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
		exit(0);
	}

	i=1; //Partimos de la posicion 1
	while((i < n) && (numeros[i] <= target)){
		i = i*2;
	}

	//La i ha alcanzado un valor mayor al buscado o es el mismo, establecemos limites
	li = i/2; //Comenzaremos a buscar desde aqui
	if(i<(n-1))
		ls = i; //Terminamos de buscar aqui
	else
		ls = (n-1); //Terminamos de buscar en la ultima posicion del arreglo
	margs[0]->li=li;
	//En este caso eviataremos la utilizacion del for
	ls = (ls-li)/4;
	margs[0]->ls=li+ls;
	pthread_create(&id[0],NULL,binarySearch,(void*)margs[0]);
	margs[1]->li=li+ls;
	margs[1]->ls=li+ls*2;
	pthread_create(&id[1],NULL,binarySearch,(void*)margs[1]);
	margs[2]->li=li+ls*2;
	margs[2]->ls=li+ls*3;
	pthread_create(&id[2],NULL,binarySearch,(void*)margs[2]);
	margs[3]->li=li+ls*3;
	margs[3]->ls=li+ls*4;
	pthread_create(&id[3],NULL,binarySearch,(void*)margs[3]);

	for(i=0;i<4;i++){
		pthread_join(id[i],(void*)&eid[i]);
	}

//	uswtime(&utime1, &stime1, &wtime1); 

	printf("\n");
//	printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);	

	return;
}
