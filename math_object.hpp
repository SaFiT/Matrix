#ifndef MATH_OBJECT_HPP
#define MATH_OBJECT_HPP

template<class O, class _Proxy = O>
struct math_object
{
    typedef O final_type;
    typedef _Proxy proxy_type;

    final_type& self(){ return static_cast<final_type&>(*this); }
    const final_type& self() const { return static_cast<const final_type&>(*this); }

    proxy_type get_proxy() const { return self(); }
};

#endif // MATH_OBJECT_HPP
