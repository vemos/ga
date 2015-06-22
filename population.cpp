#include "population.h"

population::population()
{
    _is_gen = false;
    _opt = nullptr;
}

void population::generate(int size, int chr_size, create cr)
{
    chromosome* chm;
    if (size < 1)
        throw std::invalid_argument("Population size cann't be less then 1!");
    _pop.clear();
    for (int i = 0; i < size; ++i)
    {
        chm = (chromosome*)cr(chr_size);
        _pop.push_back(shared_ptr<chromosome>(chm));
    }
    _is_gen = true;
}

void population::crossover(float pk, float p)
{
    int i;
    size_t size = _pop.size();
    vector<shared_ptr<chromosome>> vec;
    for (i = 0; i < size; ++i)
        if (drand() < pk)
            vec.push_back(_pop[i]);

    sort(_pop.begin(), _pop.end());
}
