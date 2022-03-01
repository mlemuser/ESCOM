/*Alumno: Lemus Ruiz Mariana Elizabeth
Practica 0: Operadores Binarios*/
#include <stdio.h>
#include <stdlib.h>

int main (){
	unsigned char caracter, i;	
	printf("\n Ingrese el caracter \n");
	scanf("%c", &caracter);
/*	printf("Caracter es %c y en decimal es %d \n",caracter,caracter);*/
	
	unsigned char cont = 128;
	for(cont; cont>0 ; cont>>=1){
		if (cont & caracter){
			i++;
		}
	}
	
	printf("Su caracter cuenta con %i Bits \n", i);
	
	system("pause");
	return 0;
}
