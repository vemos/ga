#include <iostream>
#include <time.h>
#include "chromosome.h"
#include "population.h"

using namespace std;

int main()
{
    srand(time(nullptr));
    population p;

    p.generate(10, 10, [](int size) -> void* {
        chromosome *chm = new chromosome(size);
        for (int i = 0; i < size; ++i)
            (*chm)[i] = rand() % 4 + 'A';
        return chm;
    });
    p.set_opt([](chromosome &c) -> double { return 0; });

    for (int i = 0; i < p.size(); ++i)
        cout << p[i] << endl;

    p.crossover(0.1, 0.5);

    return 0;
}

