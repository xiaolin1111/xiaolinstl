#ifndef _TYPE_TRAUTS_H_
#define _TYPE_TRAITS_H_

namespace linstl
{

struct false_type {};
struct true_type  {};

//非内置类型
template<class T>
struct m_type_traits
{
    typedef false_type    has_trivial_default_constructor;
    typedef false_type    has_trivial_copy_constructor;
    typedef false_type    has_trivial_assignment_operator;
    typedef false_type    has_trivial_destructor;
    typedef false_type    is_POD_type;
};



//内置类型
template<>
struct m_type_traits<int>
{
    typedef true_type    has_trivial_default_constructor;
    typedef true_type    has_trivial_copy_constructor;
    typedef true_type    has_trivial_assignment_operator;
    typedef true_type    has_trivial_destructor;
    typedef true_type    is_POD_type;
};

template<>
struct m_type_traits<unsigned int>
{
    typedef true_type    has_trivial_default_constructor;
    typedef true_type    has_trivial_copy_constructor;
    typedef true_type    has_trivial_assignment_operator;
    typedef true_type    has_trivial_destructor;
    typedef true_type    is_POD_type;
};

template<>
struct m_type_traits<char>
{
    typedef true_type    has_trivial_default_constructor;
    typedef true_type    has_trivial_copy_constructor;
    typedef true_type    has_trivial_assignment_operator;
    typedef true_type    has_trivial_destructor;
    typedef true_type    is_POD_type;
};

template<>
struct m_type_traits<unsigned char>
{
    typedef true_type    has_trivial_default_constructor;
    typedef true_type    has_trivial_copy_constructor;
    typedef true_type    has_trivial_assignment_operator;
    typedef true_type    has_trivial_destructor;
    typedef true_type    is_POD_type;
};


template<>
struct m_type_traits<signed int>
{
    typedef true_type    has_trivial_default_constructor;
    typedef true_type    has_trivial_copy_constructor;
    typedef true_type    has_trivial_assignment_operator;
    typedef true_type    has_trivial_destructor;
    typedef true_type    is_POD_type;
};

template<>
struct m_type_traits<short>
{
    typedef true_type    has_trivial_default_constructor;
    typedef true_type    has_trivial_copy_constructor;
    typedef true_type    has_trivial_assignment_operator;
    typedef true_type    has_trivial_destructor;
    typedef true_type    is_POD_type;
};

template<>
struct m_type_traits<unsigned short>
{
    typedef true_type    has_trivial_default_constructor;
    typedef true_type    has_trivial_copy_constructor;
    typedef true_type    has_trivial_assignment_operator;
    typedef true_type    has_trivial_destructor;
    typedef true_type    is_POD_type;
};

template<>
struct m_type_traits<long>
{
    typedef true_type    has_trivial_default_constructor;
    typedef true_type    has_trivial_copy_constructor;
    typedef true_type    has_trivial_assignment_operator;
    typedef true_type    has_trivial_destructor;
    typedef true_type    is_POD_type;
};

template<>
struct m_type_traits<unsigned long>
{
    typedef true_type    has_trivial_default_constructor;
    typedef true_type    has_trivial_copy_constructor;
    typedef true_type    has_trivial_assignment_operator;
    typedef true_type    has_trivial_destructor;
    typedef true_type    is_POD_type;
};

template<>
struct m_type_traits<long long>
{
    typedef true_type    has_trivial_default_constructor;
    typedef true_type    has_trivial_copy_constructor;
    typedef true_type    has_trivial_assignment_operator;
    typedef true_type    has_trivial_destructor;
    typedef true_type    is_POD_type;
};

template<>
struct m_type_traits<float>
{
    typedef true_type    has_trivial_default_constructor;
    typedef true_type    has_trivial_copy_constructor;
    typedef true_type    has_trivial_assignment_operator;
    typedef true_type    has_trivial_destructor;
    typedef true_type    is_POD_type;
};

template<>
struct m_type_traits<double>
{
    typedef true_type    has_trivial_default_constructor;
    typedef true_type    has_trivial_copy_constructor;
    typedef true_type    has_trivial_assignment_operator;
    typedef true_type    has_trivial_destructor;
    typedef true_type    is_POD_type;
};
//原生指针
template<class T>
struct m_type_traits<T*>
{
    typedef true_type    has_trivial_default_constructor;
    typedef true_type    has_trivial_copy_constructor;
    typedef true_type    has_trivial_assignment_operator;
    typedef true_type    has_trivial_destructor;
    typedef true_type    is_POD_type;
};



}
#endif
