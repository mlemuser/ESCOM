#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
 
struct nodoarbol{                        //ESTRUCTURA DEL ARBOL
         struct nodoarbol *izqnodo;
         int info;
         struct nodoarbol *dernodo;
         };
typedef struct nodoarbol NODO;    //DEFINICION DE TIPO NODO
typedef NODO *ARBOL;               //DECLARACION DE VARIABLE PUNTERO A NODO
 
void insertanodonuevo(ARBOL *,int);    //DECLARACION DE FUNCIONES
void inorden(ARBOL);
void preorden(ARBOL);
void postorden(ARBOL);
void treefree(ARBOL);
 
 //Funcion Principal
main(){
int i;                          //CONTADOR
char newnod,chain[200],elementos;    //DECLARACION DE CADENA,BANDERA Y VARIABLE QUE CONTIENE EL NUEVO VALOR A INSERTAR EN EL ARBOL
//clrscr();
ARBOL raiz=NULL;                //DECLARACION DE VARIABLE DE TIPO ARBOL
printf("\n\n\tIntroduzca una cadena de caracteres (max. 200 elementos):\n");
gets(chain);
elementos=strlen(chain);         //CHECA EL TAMA¥O DE LA CADENA Y ESTABLECE EL NUMERO DE NODOS DEL ARBOL
for(i=1;i<=elementos;i++)  {
       newnod=chain[i-1];
     insertanodonuevo(&raiz,newnod);
 
}
printf("\n preorden ¯¯\t");
	preorden(raiz);                 //LLAMADO A FUNCION DE RECORRIDO EN PREORDEN
printf("\n inorden  ¯¯\t");
	inorden(raiz);                  //LLAMADO A FUNCION DE RECORRIDO EN INORDEN
printf("\n postorden ¯¯\t");
	postorden(raiz);                //LLAMADO A FUNCION DE RECORRIDO EN POSTORDEN
getch();
	treefree(raiz);            //LIBERACION DE MEMORIA DEL ARBOL.
raiz=NULL;                  //ASIGNACION DE UN VALOR NULO A LA RAIZ.
return 0;
}
 
//Creamos un nuevo nodo 
void insertanodonuevo(ARBOL *rarbol,int nuevo){
 if(*rarbol==NULL){                          //CREACION DE UN NUEVO NODO
 *rarbol=(NODO *)malloc(sizeof(NODO));
 if(*rarbol!=NULL){
             //ASIGNACION DE VALORES NUEVOS EN EL NODO NUEVO
 (*rarbol)->info=nuevo;
 (*rarbol)->izqnodo =NULL;
 (*rarbol)->dernodo=NULL;
 }
 else{printf("\n­­­­ Memoria No Disponible !!!!\n");}
 }
 else
         if(nuevo<(*rarbol)->info)  //checa si el elemento nuevo es mayor que el elemento padre
                 insertanodonuevo(&((*rarbol)->izqnodo),nuevo);  //coloca el elemento a la izquierda del padre o raiz
         else
                 if(nuevo>(*rarbol)->info)  //checa si el elemento nuevo es menor que el elemento padre
                          insertanodonuevo(&((*rarbol)->dernodo),nuevo);  //coloca el elemento a la derecha del padre o raiz
}
//FUNCION ITERATIVA LA CUAL RECORRE EL ARBOL IMPRIMIENDO SIEMPRE EL VALOR
//QUE CONTIENE LA RAIZ,DESPUES LA RAMA IZQUIERDA,LUEGO LA RAMA DERECHA,SIEMPRE
//Y CUANDO LA RAIZ SEA DIFERENTE DE UN VALOR NULO, SI ES NULO SALTA A LA SIGUIENTE INSTRUCCION.
void preorden(ARBOL rarbol){
	if(rarbol!=NULL){
		printf(" %c ",rarbol->info);
		preorden(rarbol->izqnodo);
		preorden(rarbol->dernodo);
 
	}
}
//FUNCION ITERATIVA LA CUAL RECORRE EL ARBOL BUSCANDO EL NODO MAS IZQUIERDO
//QUE CONTIENE EL ARBOL O SEA HASTA QUE LA RAMA DEL ULTIMO NODO SEA NULO,LUEGO LA IMPRIME,DESPUES
//DESPUES LA RAIZ DEL SUB-ARBOL,Y LUEGO EL NODO DE LA DERECHA.
 
void inorden(ARBOL rarbol){
	if(rarbol!=NULL){
		inorden(rarbol->izqnodo);
		printf(" %c ",rarbol->info);
		inorden(rarbol->dernodo);
 	}
}
//FUNCION ITERATIVA LA CUAL RECORRE EL ARBOL BUSCANDO EL NODO QUE ESTA MAS A LA IZQUIERDA
//LUEGO EL NODO DE LA DERECHA Y LUEGO LA RAIZ DE ESE SUB-ARBOL
void postorden(ARBOL rarbol){
	if(rarbol!=NULL){
		postorden(rarbol->izqnodo);
		postorden(rarbol->dernodo);
		printf(" %c ",rarbol->info);
	}
}
/*FUNCION ITERATIVA IDENTICA AL RECORRIDO EN POSTORDEN LA UNICA DIFERENCIA
ES QUE EN VEZ DE IMPRIMIR EN PANTALLA EL VALOR DE UN NODO ESTE ES ELIMINADO DEL ARBOL LIBERANDO LA MEMORIA CON LA FUNCION free(), ELEGI ESTA
FORMA YA QUE SE ELIMINA PRIMERO LOS NODOS HIJO DE EL SUB-ARBOL Y LUEGO LA RAIZ
YA QUE SI SE ELIMINA LA RAIZ PRIMERO, LOS DATOS DE LOS HIJOS SE DESCONECTAN
DEL ARBOL PERO LA MEMORIA QUE OCUPABAN SIGUE SIENDO UTILIZADA Y DE ESTA FORMA
SE ELIMINA EL ARBOL DE ABAJO HACIA ARRIBA (O SEA DE LOS HIJOS A LA RAIZ).*/
 
void treefree(ARBOL rarbol){
	if(rarbol!=NULL){
		treefree(rarbol->izqnodo);
		treefree(rarbol->dernodo);
		free(rarbol);
	}
}
