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

    p.createPopulation(Population::MAX, sqx, -5.5, 6.73, 100, 20, 5);
    for (int i = 0; i < 10; ++i)
        p.generation(0.7, 0.0001);
    cout << "average: " << p.average() << endl
        << "best: " << p.best().getP() << endl;

    return 0;
}

