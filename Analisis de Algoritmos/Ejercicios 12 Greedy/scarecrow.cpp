#include <iostream>
#include <string>
using namespace std;

int main(void)
{
    int cases, casosCont = 0;
    cin >> cases;
    while(cases--)
    {
        int tamanoC, puntosConsec = 0, hashConsec = 0, puntosTotal = 0, espantaPaj = 0, i;
        char posicion;
        string crop;
        cin >> tamanoC;
        cin >> crop;
        i = 0;
        while(i < crop.length())
        {
            if(crop[i] == '.')
            {
                espantaPaj++;
                i += 3;
            }
            else if(crop[i] == '#')
                i++;
        }
        cout << "Case " << ++casosCont << ": " << espantaPaj << "\n";
    }
}
