#ifndef EVALUABLE_OBJECT_H
#define EVALUABLE_OBJECT_H

#include "math_object.hpp"

template <class EO, class _Proxy = EO>
struct evaluable_object : math_object<EO, _Proxy>
{
protected:
    evaluable_object(size_t esize) : m_esize(esize) {}

    void f (evaluable_object<EO> &evaluable_object)
    {evaluable_object.self().print();}

public:
    size_t esize() const { return m_esize; }

protected:
    const size_t m_esize;
};



#endif // EVALUABLE_OBJECT_H
