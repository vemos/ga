#ifndef CHROMOSOME_CPP
#define CHROMOSOME_CPP

#include <vector>
#include <iostream>

using namespace std;

typedef unsigned char byte;


class chromosome
{
public:
    chromosome() { _opt = 0; }
    chromosome(int size) { _opt = 0; _body.resize(size); }

    double  opt() const { return _opt; }
    const byte* data() const { return _body.data(); }
    int     size() const { return _body.size(); }

     byte& operator [](int index) { return _body[index]; }
     const byte& operator [](int index) const { return _body[index]; }
     virtual bool operator < (chromosome &chm) const = 0;
private:
     double _opt;            // value of the function of optimality
     vector<byte> _body;
};


#endif
