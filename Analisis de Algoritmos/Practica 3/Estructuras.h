/*
Implementaci�n Pr�ctica 03: Codificaci�n voraz de Huffman
Por: Git Gud (Equipo Arbol)
Versi�n: 1.0
Descripci�n: Programa que obtiene una codificaci�n prefijo �ptima con base al algoritmo de Huffman
Observaciones:
*/

/*
	Estructura que har� la funci�n de un �rbol binario
*/
typedef struct arbol{
	unsigned long n;
	char c;
	struct arbol *izq;
	struct arbol *der;
}arbol;


/*
	Estructura que simular� una lista de �rboles binarios
*/
typedef struct lista{
	struct arbol *a;
	struct lista *sig;
}lista;

/*
Descripci�n: Funci�n que unir� dos �rboles y mantendr� como valor la suma de ambas frecuencias
Recibe: arbol *a (apuntador a un �rbol binario), arbol *b (apuntador a un �rbol binario)
Devuelve: arbol* (apuntador al nuevo �rbol donde convergen los dos �rboles)
Observaciones:
*/
struct arbol* nuevoArbol(struct arbol *a,struct arbol *b);

/*
Descripci�n: Funci�n que recorrer� el �rbol de codificaci�n de manera recursiva guardando las codificaciones 
	en bits para cada caracter encontrado
Recibe: arbol *a (apuntador al nodo donde nos encontremos en el �rbol), char c[256][256] (arreglo de caracteres
	que guardar� las codificaciones de bits en el caracter respectivo, char *b (arreglo de caracteres que 
	contendr� la codificaci�n en bits temporalmente, int n (nivel del �rbol donde nos encontremos)
Devuelve: 
Observaciones:
*/
void recorreArbol(struct arbol *a,char c[256][256],char *b,int n);

/*
Descripci�n: Funci�n que insertar� un �rbol al final de la lista
Recibe: lista **l (apuntador al inicio de la lista), arbol *a (�rbol que desea a�adirse)
Devuelve: 
Observaciones:
*/
void insertaLista(struct lista **l,struct arbol *a);

/*
Descripci�n: Funci�n que unir� los dos primeros �rboles de la lista para posteriormente insertarlo 
	en la lista acorde a su frecuencia
Recibe: lista **l (apuntador al inicio de la lista)
Devuelve: 
Observaciones:
*/
void dosMenoresArboles(struct lista **l);

/*
Descripci�n: Funci�n que ordenar� el arreglo de �rboles en orden ascendente de acuerdo al n�mero de apariciones del byte
Recibe: arbol *A (arreglo de �rboles a ordenar),int izq (l�mite inferior),int der (l�mite superior)
Devuelve: 
Observaciones: La ordenaci�n se realiza por medio de Merge Sort
*/
void ordena(struct arbol *A,int izq,int der);
