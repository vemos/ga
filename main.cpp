#include <iostream>
#include <time.h>
#include "chromosome.cpp"
#include "population.cpp"

using namespace std;


int main()
{
    srand(time(nullptr));
    population<char, double> p;

    p.generate(10, 10, [](int size) -> void* {
        chromosome<char, double> *chm = new chromosome<char, double>(size);
        for (int i = 0; i < size; ++i)
            (*chm)[i] = rand() % 4 + 'A';
        return chm;
    });
    p.print();

    return 0;
}

