#include "population.h"
#define drand() ((double)rand() / RAND_MAX)

// TODO: после того, как разброс значений целевой фукнции становиться меньше 5%,
// то перейти на поиск более узкого решения

Population::Population()
{
    gen = 0;
    created = false;
    fract = 0;
    popSize = 0;
    a = b = 0;
    p_calc = nullptr;
    comp.setCriterion(Criterion::MIN);
}

void Population::checkBounds(int &chromLen, int maxChromLen, double a, double b)
{
    int fa, fb;
    fa = std::isinf(a);
    fb = std::isinf(b);
    if (chromLen > maxChromLen || fa || fb)
        chromLen = maxChromLen;
    // если обе границы являются бесконечностями
    if (fa && fb)
    {
        a = -pow(2.0, chromLen) / 2;
        b = pow(2.0, chromLen) / 2;
    }
    else if (fa) // если только левая граница является бесконечностью
        a = b - pow(2.0, chromLen);
    else if (fb) // если только правая граница является бесконечностью
        b = a + pow(2.0, chromLen);
    this->prec = (b - a) / (pow(2.0, chromLen) - 1);
    this->a = a;
    this->b = b;
}

void Population::createPopulation(Criterion cr, fun calc, double a, double b, int popSize, int maxChromLen, int fract)
{
    // вычисление длины хромосомы в зависимости от диапазона значений
    int chromLen = (int)ceil(log2(pow(10.0, fract) * (b - a)));
    created = false;
    if (cr != Criterion::MIN && cr != Criterion::MAX)
        throw invalid_argument("Неверное значение критерия для вычисления функции!");
    if (fract >= maxChromLen || fract < 0)
        throw invalid_argument("Неверно указана точность вычислений!");
    if (maxChromLen < 2)
        throw invalid_argument("Максимальная длина хромосомы не может быть меньше двух!");
    if (popSize < 2)
        throw invalid_argument("Размер популяции не может быть меньше двух!");
    if (calc == nullptr)
        throw invalid_argument("Указатель на функцию оптимальности не может быть равен NULL!");
    checkBounds(chromLen, maxChromLen, a, b);
    // настроить оператор сравнения
    comp.setCriterion(cr);
    this->gen = 0;
    this->fract = fract;
    this->p_calc = calc;
    this->popSize = popSize;
    bank.resize(popSize);
    for (int i = 0; i < popSize; i++)
        bank[i] = make_shared<Chromosome>(chromLen);
    vector< shared_ptr<Chromosome> >::iterator iter = bank.begin();
    // расчитать для всех хромосом значение функции оптимальности
    while (iter != bank.end())
    {
        funOpt(**iter);
        ++iter;
    }
    created = true;
}

int Population::generation(float co, float m)
{
    if (co > 1 || co < 0)
        throw invalid_argument("Значение вероятности скрещивания должно находится в пределах [0;1]!");
    if (m > 1 || m < 0)
        throw invalid_argument("Значение вероятности мутации должно находится в пределах [0;1]!");
    if (!created)
        throw logic_error("Популяция не была создана!");
    crossingOver(co, m);
    selection();
    if (bank.size() == 0)
        throw underflow_error("Численность популяции равна нулю!");
    return ++gen;
}

Chromosome& Population::best()
{
    return *bank[bestIndex()];
}

int Population::bestIndex()
{
    int best = 0;
    for (int i = 0; i < bank.size(); ++i)
        if (!comp(bank[best], bank[i]))
            best = i;
    return best;
}

double Population::binToDec(Chromosome &c)
{
    int i;
    unsigned int val = 0;
    for (i = 0; i < c.size(); ++i)
        if (c[i])
            val += (unsigned int)pow(2.0, i);
    return a + prec * val;
}

double Population::average() const
{
    double res = 0;
    vector< shared_ptr<Chromosome> >::const_iterator iter = bank.begin();
    while (iter != bank.end())
    {
        res += iter->get()->getP();
        ++iter;
    }
    res /= bank.size();
    return res;
}

void Population::funOpt(Chromosome &c)
{
    double arg = binToDec(c), res;
    if (p_calc == nullptr)
        throw invalid_argument("Указатель на класс вычисления не может быть NULL!");
    // если a >= b, то вычислять функцию оптимальности не обращая внимание на
    // установленные ограничения значений аргумента, иначе проверять аргумент
    // на принадлежность заданному промежутку
    if (a < b && (arg < a || arg > b))
        res = NAN;
    else
        res = p_calc(arg);
    c.setP(res);
}

void Population::selection()
{
    int quarter = bank.size() / 4;
    vector< shared_ptr<Chromosome> >::iterator iter = bank.begin();
    sort(bank.begin(), bank.end(), comp);
    // удаляем все хромосомы с "патологиями"
    while (iter < bank.end() && std::isnan((*iter)->getP()))
        ++iter;
    bank.erase(bank.begin(), iter);
    // удаляем избыточные хромосомы
    while (bank.size() > popSize)
        bank.erase(bank.begin() + quarter + rand() % (bank.size() - quarter));
}

void Population::crossingOver(float co, float m)
{
    int i, j, indA, size, N = bank.size();
    int k1, k2;
    int *buf;
    float *prob, va, vb;
    double sum, cur, cur_sum, probA;
    shared_ptr<Chromosome> a, b;
    vector< shared_ptr<Chromosome> > chroms;
    // отобрать хромосомы участвующие в операции скрещивания
    // отбор методом ранжирования
    sort(bank.begin(), bank.end(), comp);
    va = drand() + 1.0;
    vb = 2 - va;
    sum = 0;
    prob = new float[N];
    size = bank.front()->size();
    buf = new int[size];
    for (i = 0; i < N; ++i)
    {
        prob[N - i - 1] = (va - (va - vb) * i / (N - 1)) / N;
        sum += prob[N - i - 1];
    }
    for (i = 0; i < N; ++i)
    {
        // генерация числа для ранжирования
        cur = drand() * sum;
        j = -1;	// индекс отобранной хромосомы
        cur_sum = 0;
        while (cur_sum <= cur && ++j < N)
            cur_sum += prob[j];
        if (j == N)
            --j;
        if (drand() <= co)
        {
            if (a.use_count() == 0) {
                a = bank[j];
                probA = prob[j];
                sum -= prob[j];
                prob[j] = 0;
                indA = j;
            }
            else
            {
                // скрестить хромосомы
                b = bank[j];
                k1 = rand() % (size - 2) + 1;
                do {
                    k2 = rand() % (size - 2) + 1;
                } while (k2 == k1);
                if (k1 > k2)
                    swap(k1, k2);
                // создать первого потомка
                memcpy(buf, a->data(), sizeof(int) * k1);
                memcpy(buf + k1, b->data() + k1, sizeof(int) * (k2 - k1));
                memcpy(buf + k2, a->data() + k2, sizeof(int) * (size - k2));
                chroms.push_back( make_shared<Chromosome>(buf, size) );
                // создать второго потомка
                memcpy(buf, b->data(), sizeof(int) * k1);
                memcpy(buf + k1, a->data() + k1, sizeof(int) * (k2 - k1));
                memcpy(buf + k2, b->data() + k2, sizeof(int) * (size - k2));
                chroms.push_back( make_shared<Chromosome>(buf, size) );
                a.reset();
                b.reset();
                prob[indA] = probA;
                sum += prob[indA];
            }
        }
    }
    delete[]prob;
    delete[]buf;
    mutation(chroms, m);
    bank.insert(bank.end(), chroms.begin(), chroms.end());
}

void Population::mutation(vector< shared_ptr<Chromosome> > &bank, float p)
{
    vector< shared_ptr<Chromosome> >::iterator iter = bank.begin();
    while (iter != bank.end())
    {
        (*iter)->mutate(p);
        // вычисление значения функции оптимальности для хромосомы
        funOpt(**iter);
        ++iter;
    }
}

Chromosome& Population::operator[](const int index) const
{
    return *bank[index];
}
