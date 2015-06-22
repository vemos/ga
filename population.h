#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "chromosome.cpp"
#include <memory>

#define drand() ((double)rand() / RAND_MAX)

using namespace std;

typedef void* (*create)(int size);
typedef double (*optimum)();


class population
{
public:
    population();

    void set_opt(optimum *opt) { _opt = opt; }
    void generate(int size, int chr_size, create cr);
    void crossover(float pk, float p);

private:
    bool _is_gen;
    vector<shared_ptr<chromosome>> _pop;
    optimum *_opt;
};

#endif // POPULATION_H
