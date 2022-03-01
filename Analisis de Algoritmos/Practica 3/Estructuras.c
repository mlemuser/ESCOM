/*
Implementaci�n Pr�ctica 03: Codificaci�n voraz de Huffman
*/



//CABECERA
#include "Estructuras.h"



//DEFINICI�N DE FUNCIONES

/*
Descripci�n: Funci�n que unir� dos �rboles y mantendr� como valor la suma de ambas frecuencias
Recibe: arbol *a (apuntador a un �rbol binario), arbol *b (apuntador a un �rbol binario)
Devuelve: arbol* (apuntador al nuevo �rbol donde convergen los dos �rboles)
Observaciones:
*/
arbol* nuevoArbol(arbol *a, arbol *b){
	 arbol *nvo; 
	nvo=( arbol *)malloc(sizeof( arbol));
	nvo->n=a->n+b->n;
	nvo->der=a;
	nvo->izq=b;
	return nvo;
}

/*
Descripci�n: Funci�n que recorrer� el �rbol de codificaci�n de manera recursiva guardando las codificaciones 
	en bits para cada caracter encontrado
Recibe: arbol *a (apuntador al nodo donde nos encontremos en el �rbol), char c[256][256] (arreglo de caracteres
	que guardar� las codificaciones de bits en el caracter respectivo, char *b (arreglo de caracteres que 
	contendr� la codificaci�n en bits temporalmente, int n (nivel del �rbol donde nos encontremos)
Devuelve: 
Observaciones:
*/
void recorreArbol(arbol *a, char c[256][256], char *b, int n){
	if(!(a->izq)){ // Si el hijo izquierdo es un valor NULL
		int i;
		int k=binDec(a->c); // Tomamos el caracter del nodo hoja
		for(i=0;i<n;i++){
			c[k][i]=b[i]; // Copiaremos el recorrido binario para el caracter respectivo
		}
		c[k][i]=-1; // Colocamos -1 para indicar el fin de la codificaci�n
		return;
	}
	b[n]=0; // Colocamos 0 para el recorrido por la izquierda
	recorreArbol(a->izq,c,b,n+1); // Llamamos recursivamente a la funci�n bajando un nivel por la izquierda
	b[n]=1; // Sustituimos el valor por 1 para hacer el recorrido por la derecha desde este punto
	recorreArbol(a->der,c,b,n+1); // Llamamos recursivamente a la funci�n bajando un nivel por la derecha
	return;
}

/*
Descripci�n: Funci�n que insertar� un �rbol al final de la lista
Recibe: lista **l (apuntador al inicio de la lista), arbol *a (�rbol que desea a�adirse)
Devuelve: 
Observaciones:
*/
void insertaLista(lista **l, arbol *a){
	 lista **aux = l;
	while(*aux != NULL){
		aux = &((*aux)->sig);
	}
	*aux = ( lista *)malloc(sizeof( lista));
	(*aux)->a = a;
	(*aux)->sig = NULL;
	return;
}

/*
Descripci�n: Funci�n que unir� los dos primeros �rboles de la lista para posteriormente insertarlo 
	en la lista acorde a su frecuencia
Recibe: lista **l (apuntador al inicio de la lista)
Devuelve: 
Observaciones:
*/
void dosMenoresArboles( lista **l){
	lista *aux,*nvo; // Dos apuntadores a elementos de la lista
	arbol *a;
	nvo=aux=*l;	// Colocamos ambos en el inicio de la lista
	*l=(*l)->sig->sig; // Avanzamos la lista dos posiciones
	nvo->a=nuevoArbol(nvo->a,nvo->sig->a); // Unimos los primeros elementos de la lista
	free(aux->sig); // Liberamos el espacio requerido por malloc
	if(!(*l) || nvo->a->n <= (*l)->a->n){ // Si la lista apunta a un NULL o la frecuencia a donde apunta es mayor a la actual
		nvo->sig=*l; // El nuevo elemento de la lista apuntar� ya sea al NULL o al elemento con mayor frecuencia
		*l=nvo; // La lista apuntar� al nuevo elemento convergido
	}
	else{ // En caso de ser una posici�n v�lida con frecuencia menor a la del nuevo elemento
		aux=*l; // El auxiliar guardar� el primer elemento actual de la lista

		// Mientras la posici�n sea v�lida y la frecuencia del siguiente elemento sea menor al elemento que desea a�adirse
		while(aux->sig && nvo->a->n > aux->sig->a->n){  
			aux=aux->sig; 
		}

		// En cuanto encontramos su posici�n, insertamos el elemento
		nvo->sig=aux->sig;
		aux->sig=nvo;
	}
}

/*
Descripci�n: Funci�n que ordenar� el arreglo de �rboles en orden ascendente de acuerdo al n�mero de apariciones del byte
Recibe: arbol *A (arreglo de �rboles a ordenar),int izq (l�mite inferior),int der (l�mite superior)
Devuelve: 
Observaciones: La ordenaci�n se realiza por medio de Merge Sort
*/
void ordena(arbol *A,int izq,int der){
	if(izq==der){
		return;	
	}
	int k=0;
	arbol z[1+der-izq];
	int m=(izq+der)/2;
	int m1=m+1;
	int m2=izq;
	ordena(A,izq,m);
	ordena(A,m1,der);
	while(izq<=m&&m1<=der){
		if(A[izq].n<=A[m1].n){
			z[k]=A[izq];
			izq++;
		}
		else{
			z[k]=A[m1];
			m1++;
		}
		k++;
	}
	while(izq<=m){
		z[k]=A[izq];
		k++;
		izq++;
	}
	while(m1<=der){
		z[k]=A[m1];
		k++;
		m1++;
	}
	for(k=0;k<=(der-m2);k++){
		A[k+m2]=z[k];
	}
}
