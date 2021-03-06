/*
Implementaci?n Pr?ctica 03: Codificaci?n voraz de Huffman
*/


//CABECERA
#include "FuncionesAuxiliares.h"

/*
Descripci?n: Funci?n que convertir? un n?mero entero a su equivalente binario
Recibe: int n (n?mero a convertir)
Devuelve: char (binario del n?mero)
Observaciones:
*/
char decBin(int n){
	char c=0;
	int i;
	for(i=128;i>0;i/=2){
		if(n>=i){
			c=c|i;
			n-=i;
		}
	}
	return c;
}

/*
Descripci?n: Funci?n que convertir? un n?mero binario a su equivalente decimal
Recibe: char c (variable que contiene el binario del n?mero)
Devuelve: unsigned int (binario en su representaci?n de entero)
Observaciones:
*/
unsigned int binDec(char c){
	int i;
	unsigned n=0;
	for(i=0;i<8;i++){
		if((c>>i)&1){
			n+=pow(2,i);
		}
	}
	return n;
}

/*
Descripci?n: Funci?n que imprimir? un valor binario en el documento
Recibe: char n (representaci?n binaria a imprimir)
Devuelve: 
Observaciones:
*/
void imprimeBinario(char n){
	int i;
	for(i=7;i>=0;i--){
		printf("%d",(n>>i)&1);
	}
}
