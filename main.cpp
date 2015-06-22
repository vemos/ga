#include <iostream>
#include <time.h>
#include "chromosome.h"
#include "population.h"

using namespace std;

double sqx(double x)
{
    return x;
}

int main()
{
    srand(time(nullptr));
    Population p;

    p.createPopulation(Population::MAX, sqx, 0, 256, 10, 30, 2);
    for (int i = 0; i < 1000; ++i)
        p.generation(0.64, 0.00001);
    cout << "average: " << p.average() << endl
        << "best: " << p.best().getP() << endl;

    return 0;
}

