#include <vector>
#include <iostream>
#include <stdexcept>
#include "chromosome.cpp"
#include <memory>

using std::cout;
using std::endl;
using std::shared_ptr;
using std::vector;

typedef void* (*create)(int size);


template<typename T, typename F>
class population
{
public:
    population();

    void generate(int size, int chr_size, create cr);
    void print()
    {
        cout << _pop.size() << endl;
        for (shared_ptr<chromosome<T, F>> val : _pop) {
            cout << *val << endl;
        }
    }

private:
    bool _is_gen;
    vector< shared_ptr<chromosome<T, F>> > _pop;
};


template<typename T, typename F>
population<T, F>::population()
{
    _is_gen = false;
}

template<typename T, typename F>
void population<T, F>::generate(int size, int chr_size, create cr)
{
    chromosome<T, F>* chm;
    if (size < 1)
        throw new std::invalid_argument("Population size cann't be less then 1!");
    _pop.clear();
    for (int i = 0; i < size; ++i)
    {
        chm = (chromosome<T, F>*)cr(chr_size);
        _pop.push_back(shared_ptr<chromosome<T, F>>(chm));
    }
    _is_gen = true;
}
