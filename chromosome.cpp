#include "chromosome.h"

template<typename T>
ostream& operator << (ostream& out, chromosome &chm)
{
    for (int i = 0; i < chm.size(); ++i)
        out << chm[i];
    return out;
}
