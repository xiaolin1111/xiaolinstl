#ifndef TYPE_TRAITS_H_
#define TYPE_TRAITS_H_

#include <functional>
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

//标准类型转换——————————————————————————————————————————————————————————————————————//   

//移除引用
template<class T>             //当模板参数为X时
struct remove_reference
{   
    typedef T       type;
};

template<class T>             //当模板参数为X&时，对X&偏特化,   remove_reference<X&>::type = X;
struct remove_reference<T&>    
{
    typedef T       type;
};

template<class T>
struct remove_reference<T&&>   //同上
{
    typedef T       type;
};


//增加const
//判断T是函数还是类型，若是函数不改变，若T是类型则加const——————————————————————————————//
template<class T,bool b>                            
struct add_const_12{};                                      

template<class T>                                   
struct add_const_12<T,false>                        
{                                                   
    typedef const T    type;                          
};                                                       
                                                        
template<class T>                                   
struct add_const_12<T,true>                         
{                                                   
    typedef T          type;                        
};                                                 
//

template<class T>           //当参数模板为T时，add_const<T>::type = const T
struct add_const
{
    typedef typename add_const_12<T,std::is_function<T>::value>::type     type;
};

//对T&偏特化
template<class T>
struct add_const<T&>
{
    typedef T&        type;
};
//对const T偏特化
template<class T>
struct add_const<const T>
{
    typedef const T   type;
};

//移除指针————————————————————————————————————————————————————————————————————————————//
template<class T>
struct remove_pointer
{
    typedef T         type;
};

template<class T>
struct remove_pointer<T*>
{
    typedef T         type;
};

//增添指针————————————————————————————————————————————————————————————————————————————//
template<class T>
struct add_pointer
{
    typedef T*        type;
};

template<class T>
struct add_pointer<T&>
{
    typedef T*         type;
};

template<class T>
struct add_pointer<T&&>
{
    typedef T*         type;
};


}
#endif
