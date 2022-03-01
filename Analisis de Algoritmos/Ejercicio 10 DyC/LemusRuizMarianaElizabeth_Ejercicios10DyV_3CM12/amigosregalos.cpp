#include <iostream>
#include <cmath>
using namespace std;
long long int C1, C2, P1, P2;

int func(long long int ResBin)
{
    long long int prim, seg, resta, suma, LCM = P1 * P2, numLCM, R1, R2;
    numLCM = floor(ResBin / LCM);
    //ResBin -= numLCM;
    prim = (ResBin / P1) - numLCM;
    seg = (ResBin / P2) - numLCM;
    resta = (ResBin - (prim + seg) - numLCM);
    //suma = ((C2 - prim) + (C1 - seg));
    R1 = max(C2 - prim, (long long int)0);
    R2 = max(C1 - seg, (long long int)0);
    suma = R1 + R2;
    if(resta > suma)
        return 1;
    else if(resta < suma)
        return -1;
    else
        return 0;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin >> C1 >> C2 >> P1 >> P2;
    long long int ini, fin, mid, res;
    ini = 1;
    fin = 3 * (C1 +  C2);
    while(ini <= fin)
    {
        mid = (ini + fin) >> 1;
        res = func(mid);
        if(res == 0)
        {
            if(mid % (P1 * P2) == 0)
                mid--;
            cout << mid << "\n";
            return 0;
        }
        else if(res == 1)
            fin = mid - 1;
        else
            ini = mid + 1;
    }
    return 0;
}
