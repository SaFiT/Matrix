#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
using namespace std;

#include "evaluable_object.hpp"

template<typename T>
struct matrix_proxy;

template<typename T>
struct matrix : evaluable_object <matrix<T>, matrix_proxy<T> >,
        vector<T>
{
    typedef T value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef evaluable_object <matrix, matrix_proxy<T> > super;
    typedef vector<value_type> base_vec;

    matrix(size_t N, size_t M) : super(N, M), base_vec(N * M),
                                 m_cols((*this).esize_cols()),
                                 m_rows((*this).esize_rows()){}

    size_t index (size_t i, size_t j) const
    {

        return j * m_cols + i;
    }

    reference operator()(size_t i, size_t j){
        return base_vec::operator[](index(i, j));
    }

    const_reference operator()(size_t i, size_t j) const {
        return base_vec::operator[](index(i, j));
    }

    template<class EO>
    void operator=(const evaluable_object<EO, typename EO::proxy_type> &eobj0)
    {
        const EO &eobj = eobj0.self();
        // assert();
        for(size_t i = 0; i < m_cols; ++i)
            for(size_t j = 0; j < m_rows; ++j)
                (*this)(i, j) = eobj(i, j);
    }


    void print(){
        for(size_t j = 0; j < m_cols; ++j)
       { cout<<endl;
            for(size_t i = 0; i < m_rows; ++i)
            {
            cout<<(*this)(j,i)<<" ";
            }}
        cout<<endl;

    }
//private:
//    const size_t m_esize;
private:
    const size_t m_cols;
    const size_t m_rows;

};

template<typename T>
struct matrix_proxy
{
    typedef T value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;

    matrix_proxy(const matrix<T> &m): m_data(&m.front()),
                                      m_cols(m.esize_cols()),
                                      m_rows(m.esize_rows()){}
    size_t esize() const { return m_cols; }
    size_t index (size_t i, size_t j) const
    {

        return j * m_cols + i;
    }

    reference operator()(size_t i, size_t j){
        return m_data[index(i, j)];
    }

    const_reference operator()(size_t i, size_t j) const {
        return m_data[index(i, j)];
    }

private:
    const_pointer m_data;
    const size_t m_cols;
    const size_t m_rows;

};

#endif // MATRIX_H
