#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;
vector <pair<double, double> > numeros;
 int fin)
{
	if(fin - ini == 1)
		return sqrt(pow(fabs(numeros[fin].first - numeros[ini].first), 2) +
			pow(fabs(numeros[fin].second - numeros[ini].second), 2));
	if(fin - ini == 2)
	{
		double izq, der, enmedio, menor;
		izq = sqrt(pow(fabs(numeros[ini + 1].first - numeros[ini].first), 2) +
			pow(fabs(numeros[ini + 1].second - numeros[ini].second), 2));
		der = sqrt(pow(fabs(numeros[fin].first - numeros[ini + 1].first), 2) +
			pow(fabs(numeros[fin].second - numeros[ini + 1].second), 2));
		enmedio = sqrt(pow(fabs(numeros[fin].first - numeros[ini].first), 2) +
			pow(fabs(numeros[fin].second - numeros[ini].second), 2));
		menor = min(izq, der);
		menor = min(enmedio, menor);
		return menor;
	}
	int mid = (fin + ini) / 2;
	double der, izq, midio, mini;
	der = cumulo(mid, fin);
	izq = cumulo(ini, mid);
	midio = cumulo(mid - 1, mid + 1);
	mini = min(izq, der);
	mini = min(mini, midio);
	return mini;
}
void merge(int ini, int mid, int fin, int XorY)
{
	int i, j, k;
	int tam1 = mid - ini + 1;
	int tam2 = fin - mid;

	vector <pair<double, double> > izq(tam1);
	vector <pair<double, double> > der(tam2);
	for(i = 0 ; i < tam1 ; i++)
	{
		izq[i].first = numeros[ini + i].first;
		izq[i].second = numeros[ini + i].second;
	}
	for(j = 0 ; j < tam2 ; j++)
	{

		der[j].first  = numeros[mid + 1 + j].first;
		der[j].second  = numeros[mid + 1 + j].second;
	}
	i = 0;
	j = 0;
	k = ini;
	if(XorY)
	{
		while(i < tam1 && j < tam2)
		{
			if(izq[i].second < der[j].second)
			{
				numeros[k].first = izq[i].first;
				numeros[k].second = izq[i].second;
				i++;
			}
			else
			{
				numeros[k].first = der[j].first;
				numeros[k].second = der[j].second;
				j++;
			}
			k++;
		}
	}
	else
	{
		while(i < tam1 && j < tam2)
		{
			if(izq[i].first < der[j].first)
			{
				numeros[k].first = izq[i].first;
				numeros[k].second = izq[i].second;
				i++;
			}
			else
			{
				numeros[k].first = der[j].first;
				numeros[k].second = der[j].second;
				j++;
			}
			k++;
		}
	}
	while(i < tam1)
	{
		numeros[k].first = izq[i].first;
		numeros[k].second = izq[i].second;
		i++;
		k++;
	}
	while(j < tam2)
	{
		numeros[k].first = der[j].first;
		numeros[k].second = der[j].second;
		k++;
		j++;
	}

}
void mergeSort(int ini, int fin, int XorY)
{
	if(ini < fin)
	{
		int mid = (fin + ini) / 2;
		mergeSort(ini, mid, XorY);
		mergeSort(mid + 1, fin, XorY);
		merge(ini, mid, fin, XorY);
	}
}
int main(void)
{
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(3);
	double cordX, cordY;
	int nums;
	cin >> nums;
	numeros.clear();
	for(int i = 0 ; i < nums ; i++)
	{
		cin >> cordX >> cordY;
		numeros.push_back(make_pair(cordX, cordY));
	}
	if(nums == 2)
	{
		double res = sqrt(pow(fabs(numeros[1].first - numeros[0].first), 2) +
			pow(fabs(numeros[1].second - numeros[0].second), 2));
		cout << res << "\n";
	}
	else
	{
		mergeSort(0, numeros.size() - 1, 0);
		double ejeX = cumulo(0, numeros.size() - 1);
		mergeSort(0, numeros.size() - 1, 1);
		double ejeY = cumulo(0, numeros.size() - 1);
		cout << min(ejeX, ejeY) << "\n";
	}
	return 0;
}
