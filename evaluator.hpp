#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <functional>
#include <QDebug>
template<typename From, typename To>
struct my_is_convertible : std::integral_constant<bool,
    std::is_integral<From>::value && std::is_floating_point<To>::value>{};

template<typename T>
struct my_is_convertible<T, T> : std::true_type{};

template<bool B, typename T>
struct my_enable_if;

template<typename T>
struct my_enable_if<true, T>{
    typedef T type;
};

template<typename T>
struct my_enable_if<false, T>{};

template<class EO1, class BO, class EO2>
struct evaluator_binary : evaluable_object <evaluator_binary<EO1, BO, EO2> >
{
    typedef evaluable_object <evaluator_binary<EO1, BO, EO2> > super;

    static_assert(
        my_is_convertible<typename EO2::value_type, typename EO1::value_type>::value ||
        my_is_convertible<typename EO1::value_type, typename EO2::value_type>::value,
        "EO2 should be convertible to EO1");

    typedef typename std::conditional<
        my_is_convertible<typename EO2::value_type, typename EO1::value_type>::value,
        typename EO1::value_type, typename EO2::value_type>::type value_type;

    typedef BO bin_op;

    evaluator_binary(const evaluable_object<EO1, typename EO1::proxy_type> &eobj1,
                    bin_op op,
                   const evaluable_object<EO2, typename EO2::proxy_type> &eobj2) :  super(eobj1.esize_cols(), eobj1.esize_rows()),
        eobj1_proxy(eobj1.get_proxy()), op(op), eobj2_proxy(eobj2.get_proxy())
    {
        assert(eobj1.esize_cols() == eobj2.esize_cols() && eobj1.esize_rows() == eobj2.esize_rows());
    }

    value_type operator()(size_t i, size_t j) const {
        return op(eobj1_proxy(i, j), eobj2_proxy(i, j));
    }

    void print(){cout<<"hello"<<endl;}

private:
    const typename EO1::proxy_type eobj1_proxy;
    const bin_op op;
    const typename EO2::proxy_type eobj2_proxy;
};

template<class EO1, class EO2>
typename std::enable_if<
    my_is_convertible<typename EO2::value_type, typename EO1::value_type>::value,
    evaluator_binary<EO1, std::plus<typename EO1::value_type>, EO2>
>::type
operator+(const evaluable_object<EO1, typename EO1::proxy_type> &eobj1,
          const evaluable_object<EO2, typename EO2::proxy_type> &eobj2)
{
    return evaluator_binary<EO1, std::plus<typename EO1::value_type>, EO2>
            (eobj1, std::plus<typename EO1::value_type>(), eobj2);
}

template<class EO1, class EO2>
evaluator_binary<EO1, std::minus<typename EO1::value_type>, EO2>
operator-(const evaluable_object<EO1, typename EO1::proxy_type> &eobj1,
          const evaluable_object<EO2, typename EO2::proxy_type> &eobj2)
{
    return evaluator_binary<EO1, std::minus<typename EO1::value_type>, EO2>
            (eobj1, std::minus<typename EO1::value_type>(), eobj2);
}

template<class EO, class BO>
struct evaluator_binary_scalar : evaluable_object <evaluator_binary_scalar<EO, BO> >
{
    typedef evaluable_object <evaluator_binary_scalar<EO, BO> > super;
    typedef typename EO::value_type value_type;
    typedef BO bin_op;

    evaluator_binary_scalar(const evaluable_object<EO, typename EO::proxy_type> &eobj,
                    bin_op op, value_type arg) : super(eobj.esize_cols(), eobj.esize_rows()),
    eobj_proxy(eobj.get_proxy()), op(op), arg(arg){}

    value_type operator()(size_t i, size_t j) const {
        return op(eobj_proxy(i, j), arg);
    }

    void print(){cout<<"hello"<<endl;}

private:
    const typename EO::proxy_type eobj_proxy;
    const bin_op op;
    const value_type arg;
};

template<class EO>
evaluator_binary_scalar<EO, std::multiplies<> >
operator*(const evaluable_object<EO, typename EO::proxy_type> &eobj,
          const typename EO::value_type arg)
{
    return evaluator_binary_scalar<EO, std::multiplies<> >
            (eobj, std::multiplies<>(), arg);
}

template<class EO>
evaluator_binary_scalar<EO, std::divides<> >
operator/(const evaluable_object<EO, typename EO::proxy_type> &eobj,
          const typename EO::value_type arg)
{
    return evaluator_binary_scalar<EO, std::divides<> >
            (eobj, std::divides<>(), arg);
}

template<class EO1, class EO2>
struct evaluator_mult : evaluable_object <evaluator_mult<EO1, EO2> >
{
    typedef evaluable_object <evaluator_mult<EO1, EO2> > super;

    static_assert(std::is_same<typename EO1::value_type, typename EO2::value_type>::value,
        "Value types should be the same");

    typedef typename EO1::value_type value_type;

    evaluator_mult(const evaluable_object<EO1, typename EO1::proxy_type> &eobj1,
                   const evaluable_object<EO2, typename EO2::proxy_type> &eobj2
                   ) : super(eobj1.esize_cols(),eobj1.esize_rows()),
    eobj1_proxy(eobj1.get_proxy()), eobj2_proxy(eobj2.get_proxy())
    {
        assert(eobj1.esize_cols() == eobj2.esize_rows());
    }

    value_type operator()(size_t i, size_t j) const
    {
        value_type result = 0;
        for(size_t k = 0; k < super::esize_rows(); ++k)
           { result += eobj1_proxy(i, k) * eobj2_proxy(k, j);
            QDebug(QtDebugMsg)<<"i = "<<i<<"j = "<<j<<"k = "<<k;}
        return result; // todo
    }

    void print(){cout<<"hello"<<endl;}

private:
    const typename EO1::proxy_type eobj1_proxy;
    const typename EO2::proxy_type eobj2_proxy;
};

template<class EO1, class EO2>
evaluator_mult<EO1, EO2>
operator*(const evaluable_object<EO1, typename EO1::proxy_type> &eobj1,
          const evaluable_object<EO2, typename EO2::proxy_type> &eobj2)
{
    return evaluator_mult<EO1, EO2>(eobj1, eobj2);
}

//*****************************************************************************************

#endif  //EVALUATOR_H
