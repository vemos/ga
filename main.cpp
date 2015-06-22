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
        static int a = 0;
        chromosome *chm = new chromosome(size);
        for (int i = 0; i < size; ++i)
            (*chm)[i] = rand() % 4 + 'A';
        return chm;
    });
    p.print();
    p.crossover(0.1, 0.5);
    p.print();

    return 0;
}

