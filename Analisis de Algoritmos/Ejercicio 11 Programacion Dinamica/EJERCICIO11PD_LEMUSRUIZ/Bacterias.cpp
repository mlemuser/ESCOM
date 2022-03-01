#include <iostream>
#include <vector>
using namespace std;

int M, N, auxI;

/*
Recibe el arreglo de las cantidades del quimico en la tabla y el arreglo DP
con el que se hará la programación dinámica para sacar el camino menos costoso
por el que pueden pasar las bacterias
*/
int caminoMenor(vector <vector<int> > DP, vector <vector<int> > quimico)
{
    for(int i = 1 ; i < M ; i++)
        for(int j = 1 ; j < N ; j++)
            /*
            Se va checando el valor entre la casilla de arriba y la casilla de la
            derecha ya que las bacterias solo pueden moverse hacia el este y hacia el
            sur
            */
            DP[i][j] = quimico[i][j] + min(DP[i - 1][j], DP[i][j - 1]);
    return DP[M - 1][N - 1];

}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> M >> N;
    vector <vector <int> > compuestoQ(M, vector <int> (N, 0));
    vector <vector <int> > DP(M, vector <int> (N));
    int res;
    for(int i = 0 ; i < M ; i++)
    {
        for(int j = 0 ; j < N ; j++)
        {
            cin >> auxI;
            compuestoQ[i][j] = auxI;
        }
    }
    //Se empieza con la primer casilla que es donde empieza el recorrido
    DP[0][0] = compuestoQ[0][0];
    /*
    Se va haciendo un barrido acuulado sobre la primer columna para poder saber
    cuanto cuesta moverse hacia abajo
    */
    for(int i = 1 ; i < M ; i++)
        DP[i][0] = DP[i - 1][0] + compuestoQ[i][0];
    /*
    Se va haciendo un barrido acuulado sobre la primer columna para poder saber
    cuanto cuesta moverse hacia la derecha
    */
    for(int i = 1 ; i < N ; i++)
        DP[0][i] = DP[0][i - 1] + compuestoQ[0][i];
    res = caminoMenor(DP, compuestoQ);
    cout << res << "\n";
}
