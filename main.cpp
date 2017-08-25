#include <cassert>
#include <vector>
#include "matrix.hpp"
#include "evaluator.hpp"
#include <qdebug.h>

template<class EO>
void print(const evaluable_object<EO, typename EO::prox_type> &eobj)
{
    eobj.self().print();
}

int main(int argc, char *argv[])
{

    const size_t N = 4;
matrix<double> ma(3,3),mb(3,3), mc(3,3);
for(size_t j = 0; j < 3; ++j)
    for(size_t i = 0; i < 3; ++i)
    {
        ma(i, j) = (j + i+2);
    }
for(size_t j = 0; j < 3; ++j)
    for(size_t i = 0; i < 3; ++i)
    {
        mb(i, j) = (j + i) + 10;
    }


mc = ma * mb;


ma.print();
mb.print();
mc.print();
    return 0;
}

