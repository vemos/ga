#include "chromosome.h"
#define drand() ((double)rand() / RAND_MAX)


Chromosome::Chromosome()
{
    _size = 0;
    _P = 0;
    _body = nullptr;
}

Chromosome::Chromosome(int length)
{
    _size = length;
    _P = 0;
    _body = new int[_size];
    for (int i = 0; i < _size; i++)
        _body[i] = rand() % 2;
}

Chromosome::Chromosome(int *body, int length)
{
    _size = length;
    _P = 0;
    _body = new int[_size];
    memcpy(_body, body, _size * sizeof(int));
}

Chromosome::Chromosome(const Chromosome &c)
{
    _P = c._P;
    _size = c._size;
    _body = new int[_size];
    memcpy(_body, c._body, _size * sizeof(int));
}

Chromosome::~Chromosome()
{
    delete[]_body;
}

void Chromosome::mutate(float p)
{
    if (drand() <= p)
    {
        int n = rand() % _size;
        for (int i = 0; i < n; ++i)
        _body[i] = _body[i] == 1 ? 0 : 1;
    }
}

void Chromosome::print() const
{
    cout << _P << "\t";
    for (int i = 0; i < _size; ++i)
        cout << _body[i];
    cout << endl;
}

int& Chromosome::operator[] (int i)
{
    return _body[i];
}

Chromosome& Chromosome::operator = (const Chromosome &c)
{
    if (this == &c)
        return *this;
    _P = c._P;
    _size = c._size;
    delete[]_body;
    _body = new int[_size];
    memcpy(_body, c._body, _size * sizeof(int));
    return *this;
}
