#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int main(void)
{
    int cases;
    cin >> cases;
    while(cases--)
    {
        int M, izq, der, auxI, auxD;
        cin >> M;
        vector <pair<int, int> > izqDers;
        bool encontrado = false, neg = false;
        while(cin >> izq >> der && (izq != 0 || der != 0))
            izqDers.push_back(make_pair(izq,der));
        encontrado = false;
        vector <pair<int, int> > pedazos;
        sort(izqDers.begin(), izqDers.end());
        /*
        Se declara un pivote que servirá para saber cual es la posicion última que se
        quiere cubrir. (pivoteIzq)
        Se declara un índice que hace referencia a un segmento del arreglo que cumple
        con la condición y que posteriormente se va a agreagar al arreglo de resultados (agregarPos)
        Se declara un indice que corresponde a la posicion derecha del segmento (limDer)
        */
        int pivoteIzq = 0, agregarPos, limDer;
        bool agregarValores = true;
        int i = 0;
        /*
        Código que se ejecuta mientras haya un segmento que se pueda agregar
        al arreglo de las soluciones.
        */
        while(agregarValores)
        {
            limDer = pivoteIzq;
            agregarValores = false;
            //Se busca el último segmento que sea menor o igual que el pivote izquierda
            while(i < izqDers.size() && izqDers[i].first <= pivoteIzq)
            {
                /*
                Se pregunta si el valor derecho del segmento actual es mayor que
                el limite derecho actual lo cual significa que se va extendiendo la cobertura total,
                acecándose a cubrir de 0 a M
                */
                if(izqDers[i].second > limDer)
                {
                    agregarPos = i;
                    limDer = izqDers[i].second;
                    agregarValores = true;
                }
                i++;
            }
            /*
            Se actualiza el pivote izquierdo, que se convierte en el limite derecho
            esto para ir recorriendo los limites e ir buscando los segmentos que cumplan
            */
            pivoteIzq = limDer;
            if(agregarValores)
                pedazos.push_back(izqDers[agregarPos]);
            /*
            Si el limite derecho es mayor que la M significa que ya se encontraron los
            segementos que cubren de 0 a M
            */
            if(limDer >= M)
            {
                encontrado = true;
                agregarValores = false;
                break;
            }
        }
        if(!encontrado)
            cout << "0\n";
        else
        {
            //Se imprimen los valores en el arreglo de resultados
            cout << pedazos.size() << "\n";
            sort(pedazos.begin(), pedazos.end());
            for(auto a : pedazos)
                cout << a.first << " " << a.second << "\n";
        }
        if(cases > 0)
            cout << "\n";
    }
}
