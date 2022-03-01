#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int maxValor(vector <pair<int, int> > objetos, int capacidad)
{
    vector <vector<int> > DP(objetos.size() + 1, vector <int> (capacidad + 1,-1));
    for(int i = 0 ; i <= objetos.size() ; i++)
    {
        for(int j = 0 ; j <= capacidad ; j++)
        {
            /*
            Se va llevando a cabo la DP en donde se tiene como base en donde no se tiene
            ningún objeto en la knaspack.
            */
            if(j == 0 || i == 0)
                DP[i][j] = 0;
            /*
            Si el peso del objeto actual es menor que la capacidad actual de la knaspack
            se debe de actualizar y evaluar la tabla en la posicion actual
            */
            else if(objetos[i - 1].first <= j)
            /*
            Se saca el máximo entre el valor del objeto anterior mas DP para el peso actual y el valor
            de la DP en el objeto anterior.
            En pocas palabras, entre tomar el objeto actual y no tomarlo.
            */
                DP[i][j] = max(objetos[i - 1].second + DP[i - 1][j - objetos[i - 1].first],
                    DP[i - 1][j]);
            /*
            Si el valor actual es mayor que la capacidad del knapsack, entonces no se toma
            */
            else
                DP[i][j] = DP[i - 1][j];
        }
    }
    return DP[objetos.size()][capacidad];
}

int main(void)
{
    int capacidad, objetos, auxValor, auxPeso;
    cin >> capacidad >> objetos;
    /*
    Se guardan el peso y el valor de los objetos que se pueden
    seleccionar para llenar el Knapsack.
    Se guarda en un arreglo de pares en donde el primer valor del par va a ser el peso
    y el segundo cuánto vale este objeto.
    */
    vector <pair<int, int> > cosas;
    for(int i = 0 ; i < objetos ; i++)
    {
        cin >> auxPeso >> auxValor;
        cosas.push_back(make_pair(auxPeso, auxValor));
    }
    /*
    Se ordena el arreglo con respecto al peso, esto para saber poder llenar la tabla de la
    programación dinámica
    */
    sort(cosas.begin(), cosas.end());
    cout << maxValor(cosas, capacidad) << "\n";
}
