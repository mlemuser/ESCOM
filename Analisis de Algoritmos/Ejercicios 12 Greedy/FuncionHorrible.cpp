#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
bool comparacion(pair <long long int, long long int> par1, pair <long long int, long long int> par2)
{
  return par1.first > par2.first;
}

bool comparacionFinal(pair <long long int, long long int> par1, pair <long long int, long long int> par2)
{
  return par1.second < par2.second;
}
int main(void)
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  long long int N, M, K, tipoAux, auxA, auxB, auxI;
  cin >> N >> M >> K;
  for(int i = 0 ; i < N ; i++)
    cin >> tipoAux >> auxA >> auxB;
  vector <pair<long long int, long long int> > numeros;
  vector <pair<long long int, long long int> > resultado;
  for(int i = 0 ; i < M ; i++)
  {
    cin >> auxI;
    numeros.push_back(make_pair(auxI, i + 1));
  }
  int contador = 0;
  sort(numeros.begin(), numeros.end(), comparacion);
  for(auto a : numeros)
  {
    resultado.push_back(a);
    contador++;
    if(contador == K)
      break;
  }
  sort(resultado.begin(), resultado.end(), comparacionFinal);
  for(auto a : resultado)
    cout << a.second << " ";
  cout << "\n";
  return 0;
}
