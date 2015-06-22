#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <vector>
#include <iostream>
#include <memory.h>

using namespace std;

class Chromosome
{
public:
    Chromosome();
    Chromosome(int length);
    Chromosome(int *body, int length);
    Chromosome(const Chromosome &c);
    ~Chromosome();

    void    mutate(float p);                    // операция мутации хромосомы
    int     size() const { return _size; }      // длина хромосомы
    const int* data() const { return _body; }   // данные хромосомы
    void    print() const;                      // вывод на экран хромосомы
    int&    operator[] (int i);                 // получение доступа к i-му гену хромосомы
    Chromosome& operator=(const Chromosome &c);
    double  getP() const { return _P; }         // получить значение функции оптимальности
    void    setP(double p) { _P = p; }          // установить значение функции оптимальности
private:
    double _P;      // значение функции оптимальности
    int _size;      // размер хромосомы
    int* _body; 	// гены хромосомы
};

#endif // CHROMOSOME_H
