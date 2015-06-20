#include <vector>
#include <iostream>
#include <stdexcept>
#include "chromosome.cpp"
#include <memory>

using namespace std;



template<typename T>
class Population
{
public:
    Population();

    void generate(int size);
    void print()
    {
        //cout << _pop[0].
        cout << _pop[0]->length();
    }

private:
    vector< shared_ptr<Chromosome<T>> > _pop;
};


template<typename T>
Population<T>::Population()
{
}

template<typename T>
void Population<T>::generate(int size)
{
    if (size < 1)
        throw new invalid_argument("Population size cann't be less then 1!");
    //_pop.push_back(make_shared<Chromosome<T>>(13));
}
