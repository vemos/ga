#ifndef CHROMOSOME_CPP
#define CHROMOSOME_CPP

#include <vector>
#include <iostream>

using std::cout;
using std::endl;
using std::ostream;
using std::vector;


template<typename T, typename F>
class chromosome
{
public:
    chromosome() {}
    chromosome(int size) { _body.resize(size); }

    F       getOpt() const { return _opt; }
    void    setOpt(F opt) { _opt = opt; }
    const T* data() const { return _body.data(); }
    int     size() const { return _body.size(); }

     T&         operator [](int index) { return _body[index]; }
     const T&   operator [](int index) const { return _body[index]; }
private:
     F _opt;            // value of the function of optimality
     vector<T> _body;
};


template<typename T, typename F>
ostream& operator << (ostream& out, chromosome<T, F> &chm)
{
    for (int i = 0; i < chm.size(); ++i)
        out << chm[i];
    return out;
}


#endif
