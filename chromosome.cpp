#include "chromosome.h"


ostream& operator << (ostream& out, const chromosome &chm)
{
    for (int i = 0; i < chm.size(); ++i)
        out << chm[i];
    return out;
}

