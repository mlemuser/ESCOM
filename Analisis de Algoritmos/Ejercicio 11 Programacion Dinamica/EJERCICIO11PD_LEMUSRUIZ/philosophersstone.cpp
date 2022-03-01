#include <iostream>
#include <vector>
using namespace std;

int columns, rows;

/*
Funci�n que recibe el arreglo donde est�n los resultados de la DP y de realizar
el proceso para sacar el valor m�ximo de piedras que se pueden recolectar
*/
 
int sacaMax(vector <int> valoresFin)
{
    int maximo = -1e9;
    for(auto a : valoresFin)
        maximo = max(maximo, a);
    return maximo;
}

int piedrasMaximas(vector <vector<int> > piedras, vector <vector<int> > DP)
{
    int maximo;
    for(int i = 1 ; i < rows ; i++)
    {
        for(int j = 1 ; j <= columns ; j++)
        {
            /*
            Se va checando cu�les son los mayores valores directamente arriba
            o a la diagonal derecha y la diagonal izquierda para poder escojer
            el m�imo n�mero de piedras, y posteriormente se suma con el valor
            del n�mero de piedras en la casilla actual.
            */
            maximo = -1e9;
            maximo = max(maximo, DP[i - 1][j - 1]);
            maximo = max(maximo, DP[i - 1][j]);
            maximo = max(maximo, DP[i - 1][j + 1]);
            DP[i][j] = maximo + piedras[i][j];
        }
    }

    return sacaMax(DP[rows - 1]);
}

int main(void)
{
    int cases, auxI;
    cin >> cases;
    while(cases--)
    {
        cin >> rows >> columns;
        vector <vector<int> > piedras(rows, vector<int> (columns + 2, 0));
        vector <vector<int> > DP(rows, vector<int> (columns + 2, 0));
        for(int i = 0 ; i < rows ; i++)
            for(int j = 1 ; j <= columns ; j++)
                cin >> piedras[i][j];
        /*
        Se guarda en el arreglo para la programaci�n din�mica la primer fila del
        arreglo de entrada ya que esta es la que empieza todo el proceso
        */
        for(int i = 1 ; i <= columns ; i++)
            DP[0][i] = piedras[0][i];
        cout << piedrasMaximas(piedras, DP) << "\n";
    }

}
