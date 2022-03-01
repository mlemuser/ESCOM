#include <iostream>
#include <vector>
using namespace std;

/*
Se recibe el arreglo resultante y el tamaño del arreglo y se regresa el mayor de estos.
*/
int maximoN(vector <int> DP, int tam)
{
    int maximo = -1e9;
    for(int i = 0 ; i < tam ; i++)
        maximo = max(DP[i], maximo);
    return maximo;
}

/*
Se recibe el arreglo de los números a los que se le quiere sacar la subsecuencia mayor
y el tamaño de este arreglo.
Regresa el tamaño de la subsecuencia mayor donde todos los valores van incrementando.
*/

int lis(vector <int> numeros, int tam)
{
    vector <int> DP(tam + 1);
    for(int i = 0 ; i <= tam ; i++)
    {
        /*
        Se cuenta la posición actual y se guarda en el arreglo que se usa para
        la DP.
        */
        DP[i] = 1;
        /*
        Se van checando todos los valores antes y se va asegurando que el valor
        actual sea mayor que estos y se mantiene el maximo de la DP en el valor actual
        y la DP en los indices menores más uno y el actual.
        */
        for(int j = 0 ; j < i ; j++)
            if(numeros[i] > numeros[j] && DP[i] < DP[j] + 1)
                DP[i] = DP[j] + 1;
    }
    return maximoN(DP, tam);
}

int main(void)
{
    ios::sync_with_stdio(false);
    int num, auxI;
    cin >> num;
    vector <int> numeros;
    for(int i = 0 ; i < num ; i++)
    {
        cin >> auxI;
        numeros.push_back(auxI);
    }
    cout << lis(numeros, num) << "\n";
}
