#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
 
struct nodoarbol{                        //Realizamos la estructura del arbol
         struct nodoarbol *izqnodo;
         int info;
         struct nodoarbol *dernodo;
         };
typedef struct nodoarbol NODO;    //Definicion del tipo de Nodo
typedef NODO *ArbolBinarioBusqueda;               //Declaramos la variable que apunte al codigo

void insertanodonuevo(ArbolBinarioBusqueda *,int);    //Declaramos funciones
void inorden(ArbolBinarioBusqueda);
void preorden(ArbolBinarioBusqueda);
 
main(){
int i;                          //Conteo
char newnod,chain[20000],elementos;    //Nuevo valor para insertar en el arbol
//clrscr();
ArbolBinarioBusqueda raiz=NULL;                //Variable tipo arbol
printf("\n\n\tIntroduzca una cadena de caracteres:\n");
gets(chain);
elementos=strlen(chain);         //Encargado del Tamaño de cadena y tipo de nodo
for(i=1;i<=elementos;i++)  {
       newnod=chain[i-1];
     insertanodonuevo(&raiz,newnod);
}
printf("\n ");
preorden(raiz);                 //Funcion Preorden
printf("\n ");
inorden(raiz);                  //Funcion en orden
getch();
raiz=NULL;                  //Valor nulo a la raiz
return 0;
}
 

void insertanodonuevo(ArbolBinarioBusqueda *rarbol,int nuevo){
 if(*rarbol==NULL){                          //Nuevo nodo
 *rarbol=(NODO *)malloc(sizeof(NODO));
 if(*rarbol!=NULL){
             //Asignacion de valores en nuevo nodo
 (*rarbol)->info=nuevo;
 (*rarbol)->izqnodo =NULL;
 (*rarbol)->dernodo=NULL;
 }
 else{printf("\nMemoria No Disponible\n");}
 }
 else
         if(nuevo<(*rarbol)->info)  //checa si el elemento nuevo es mayor que el elemento padre
                 insertanodonuevo(&((*rarbol)->izqnodo),nuevo);  //coloca el elemento a la izquierda del padre o raiz
         else
                 if(nuevo>(*rarbol)->info)  //checa si el elemento nuevo es menor que el elemento padre
                          insertanodonuevo(&((*rarbol)->dernodo),nuevo);  //coloca el elemento a la derecha del padre o raiz
}

void preorden(ArbolBinarioBusqueda rarbol){
if(rarbol!=NULL){
printf(" %c ",rarbol->info);
preorden(rarbol->izqnodo);
preorden(rarbol->dernodo);
	}
}

void inorden(ArbolBinarioBusqueda rarbol){
if(rarbol!=NULL){
inorden(rarbol->izqnodo);
printf(" %c ",rarbol->info);
inorden(rarbol->dernodo);
	}
}
