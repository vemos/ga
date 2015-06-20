#ifndef CHROMOSOME_CPP
#define CHROMOSOME_CPP

#include <vector>

using namespace std;


template<typename T>
class Chromosome
{
public:
    Chromosome() {}
    Chromosome(int size);

    const T* data() const;
    int length() const;

     T& operator [](int index);
     const T& operator [](int index) const;
private:
    vector<T> _data;
};

template<typename T>
Chromosome<T>::Chromosome(int size)
{
    _data.resize(size);
}

template<typename T>
const T* Chromosome<T>::data() const
{
    return _data.data();
}

template<typename T>
int Chromosome<T>::length() const
{
    return (int)_data.size();
}

template<typename T>
T& Chromosome<T>::operator [](int index)
{
    return _data[index];
}

template<typename T>
const T& Chromosome<T>::operator [](int index) const
{
    return _data[index];
}

#endif
