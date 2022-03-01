#include<stdio.h>
#include<stdlib.h>

typedef long long int largo;

largo inversiones(largo* numeros, largo* numerosTemporal, largo izquierda, largo derecha);
largo merge(largo* numeros, largo* numerosTemporal, largo izquierda, largo centro, largo derecha);


int main(void){
    largo* numeros;
    numeros=NULL;
    largo* numerosTemporal;
    numerosTemporal=NULL;   
    largo resultado=0; 
    largo veces=0;
    largo totalNumeros=0;

    printf("Ingresa el numero de casos prueba\n");
    scanf("%lld", &veces);

    for(largo i=0; i<veces; i++){
        printf("Ingresa la cantidad de numeros a leer\n");
        scanf("%lld", &totalNumeros);
        numeros=(largo *) malloc(sizeof(largo)*totalNumeros);
        numerosTemporal=(largo *) malloc(sizeof(largo)*totalNumeros);

        printf("Ingresa los datos al arreglo\n");
        for(largo i=0; i<totalNumeros; i++)
            scanf("%lld", &numeros[i]);
    
        resultado=inversiones(numeros, numerosTemporal, 0, totalNumeros);
        printf("El numero total de inversiones es: %lld\n", resultado);
    }
    free(numeros);
    free(numerosTemporal);
    return 0;
}

largo inversiones(largo* numeros, largo* numerosTemporal, largo izquierda, largo derecha){
    largo centro, numeroInversiones=0;
    if(derecha>izquierda){
        centro=(derecha+izquierda)/2;
        numeroInversiones=inversiones(numeros, numerosTemporal, izquierda, centro);
        numeroInversiones+=inversiones(numeros, numerosTemporal, centro+1, derecha);
        numeroInversiones+=merge(numeros, numerosTemporal, izquierda, centro+1, derecha);
    }
    return numeroInversiones;
}

largo merge(largo* numeros, largo* numerosTemporal, largo izquierda, largo centro, largo derecha){
    largo i,j,k;
    largo numeroInversiones=0;

    i=izquierda;
    j=centro;
    k=izquierda;

    while((i<=centro-1) && (j<=derecha)){
        if(numeros[i]<=numeros[j]){
            numerosTemporal[k++]=numeros[i++];
        }else {
            numerosTemporal[k++]=numeros[j++];
            numeroInversiones+=(centro-i);
        }
    }

    while(i<=centro-1)
        numerosTemporal[k++]=numeros[i++];

    while(j<=derecha)
        numerosTemporal[k++]=numeros[j++];

    for(i=izquierda; i<=derecha; i++)
        numeros[i]=numerosTemporal[i];
    
    return numeroInversiones;
}
