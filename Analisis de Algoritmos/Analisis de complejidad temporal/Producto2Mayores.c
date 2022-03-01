#include<stdlib.h>
#include<stdio.h>
#include N_VECES 10000

int main(void){
	int n, *A, valor,mayor1,mayor2, cont=0,i,k;
	float promedio=0;
	
	
	scanf("%d",&n);
	A=malloc(sizeof(int)*n);
	
	for(i=0;i<n;i++)
		scanf("%d",&A[i]);
	
	for(k=0;k<N_VECES;K++){
		i=0;cont=0;
		valor=rand()%(n+2);
		if (valor>n-1) valor=0;
		valor=A[valor];
		
		if(A[1] > A[2]){
			mayor1=A[1];
			mayor2=A[2];
		}

		else{
			mayor1=A[1];
			mayor2=A[2];
		}	
		i=3;
		
		while(i<=n)
			if(A[i]>mayor1){
				mayor2=mayor1;
				mayor1=A[i];
			}
				
			else if(A[i>mayor2])
				mayor2=A[i];
			i=i+1;
	//	return=mayor1*mayor2;
		cont++;
		printf("\n%d",i);
		printf("\t%d",valor);
		printf("\t%d",cont);
		
		promedio=promedio+(float)cont;
		
	}
	
	promedio=promedio/N_VECES;
	printf("\nPromedio=%f",promedio);
	
	return 0;
	
}

