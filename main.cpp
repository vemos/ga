#include <iostream>
#include "chromosome.cpp"
#include "population.cpp"

using namespace std;


int main()
{
    Population<int> p;
    Chromosome<int> ch2(10);

    p.generate(10);
    p.print();

    cout << "Hello World!" << endl;
    return 0;
}

