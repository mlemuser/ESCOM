#include<algorithm>
#include<iostream>
#include<climits>

typedef long long int largo;
using namespace std;

largo maximoSuma(largo numeros[], largo izquierda, largo centro, largo derecha);
largo DivideVenceras(largo numeros[], largo izquierda, largo derecha);

int main(void){
    largo elemArreglo=0;
    largo resultado=0;
    
    cin>>elemArreglo;
    largo numeros[elemArreglo];

    for(largo i=0; i<elemArreglo; i++)
        cin>>numeros[i];

    resultado=DivideVenceras(numeros ,0, elemArreglo);

    cout<<resultado<<endl;

    return 0;
}

largo DivideVenceras(largo numeros[], largo izquierda, largo derecha){
    if(izquierda==derecha)
        return numeros[izquierda];
    
    largo izqF, derF, mitad, medio;

    mitad=(izquierda+derecha)/2;
    izqF=DivideVenceras(numeros, izqF, mitad);
    derF=DivideVenceras(numeros, mitad+1, derF);
    medio=maximoSuma(numeros, izquierda, mitad, derecha);

    if(izqF>derF){
        if(izqF>medio)
            return izqF;
        else
            return medio;
    }else{
        if(medio>derF)
            return medio;
        else
            return derF;
    }
}

largo maximoSuma(largo numeros[], largo izquierda, largo centro, largo derecha){
    largo izqF=LLONG_MIN, derF=LLONG_MIN, suma;
    largo i;

    for(i=centro, suma=0; i>=izqF; i--){
        suma=suma+numeros[i];
        if(suma>izqF)
            izqF=suma;
    }

    for(i=centro+1, suma=0; i<=derecha; i++){
        suma=suma+numeros[i];
        if(suma>derF)
            derF=suma;
    }
    return derF+izqF;
}
