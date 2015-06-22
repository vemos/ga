#ifndef POPULATION_H
#define POPULATION_H

#include <stdexcept>
#include <vector>
#include <math.h>
#include <memory>
#include <algorithm>
#include "chromosome.h"

using namespace std;


typedef double (*fun)(double x);


class Comparator {
private:
    int cr;
public:
    Comparator() { cr = 0; }
    Comparator(int cr) : cr(cr) { }
    Comparator(const Comparator &comp) { this->cr = comp.cr; }
    void setCriterion(int cr) { this->cr = cr; }
    bool operator() (const shared_ptr<Chromosome> &a, const shared_ptr<Chromosome> &b) const
    {
        if (std::isnan(a->getP()) && !std::isnan(b->getP()))
            return true;
        else if (std::isnan(b->getP()))
            return false;
        return (a->getP() * cr) > (b->getP() * cr);
    }
    Comparator operator- ()
    {
        Comparator comp(-cr);
        return comp;
    }
};

class Population
{
public:
    enum Criterion { MIN = -1, MAX = 1 };

    Population();
    Population(Criterion cr, fun calc, double a, double b, int popSize, int fract)
        { createPopulation(cr, calc, a, b, popSize, fract); }
    Population(Criterion cr, fun calc, double a, double b, int popSize, int maxChromLen, int fract)
        { createPopulation(cr, calc, a, b, popSize, maxChromLen, fract); }
    ~Population() { ; }

    void	createPopulation(Criterion cr, fun p_calc, double a, double b, int popSize, int fract)
        { createPopulation(cr, p_calc, a, b, popSize, fract, 20); }
    void	createPopulation(Criterion cr, fun p_calc, double a, double b, int popSize, int maxChromLen, int fract);
    bool    isCreated() const { return created; }
    double	average() const;
    Chromosome& best();     // лучшая хромосома
    int     bestIndex();    // индекс лучшей хромосомы
    int 	size() const { return bank.size(); }
    double	binToDec(Chromosome &c);
    int 	generation(float co, float m);
    int		genNumber() const { return gen; }
    vector< shared_ptr<Chromosome> > population() const { return bank; }
    Chromosome& operator[](const int index) const;

private:
    bool created;
    int gen;		// номер поколения
    int fract;      // длина дробной части
    int popSize;	// ограничение на максимальное кол-во хромосом
    double a, b;	// пределы вычисления функции
    double prec;	// цена "деления" (одного шага)
    //Criterion cr;	// критерий отбора: MIN или MAX
    Comparator comp;// критерий отбора: MIN или MAX
    vector< shared_ptr<Chromosome> > bank;
    fun p_calc;// функция отбора

    void funOpt();
    void funOpt(Chromosome &c);
    void selection();
    void crossingOver(float co, float m);
    void mutation(vector<shared_ptr<Chromosome> > &bank, float p);
    void checkBounds(int &chromLen, int maxChromLen, double a, double b);
    void logPopulationInfo();
};

#endif // POPULATION_H
