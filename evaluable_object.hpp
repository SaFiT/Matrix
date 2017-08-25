#ifndef EVALUABLE_OBJECT_H
#define EVALUABLE_OBJECT_H

#include "math_object.hpp"

template <class EO, class _Proxy = EO>
struct evaluable_object : math_object<EO, _Proxy>
{
protected:
    evaluable_object(size_t cols, size_t rows) : m_cols(cols), m_rows(rows) {}

    void f (evaluable_object<EO> &evaluable_object)
    {evaluable_object.self().print();}

public:
    size_t esize_cols() const { return m_cols; }
    size_t esize_rows() const { return m_rows; }

protected:
    const size_t m_cols;
    const size_t m_rows;

};



#endif // EVALUABLE_OBJECT_H
