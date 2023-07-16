#ifndef _CONSTRUCT_H_
#define _CONSTRUCT_H_
//                        该头文件负责对象的构造与析构
#include <new>
#include "type_traits.h"
namespace linstl{

//construct:
//无参构造
template<class T>
inline
void construct(T* ptr)
{
    ::new (ptr) T();               //调用类型T的默认构造函数
}

//有参构造
template<class T1,class T2>
inline
void construct(T1* ptr,const T2& value)
{
    ::new (ptr) T1(value);         //在p指定的位置构造
}
//右值引用参数
template<class T1,class T2>
inline
void construct(T1* ptr,T2&& value)
{
    ::new (ptr) T1(std::move(value));
}

//destroy:
//接受单指针参数
template<class T>
inline
void destroy(T* ptr)
{
    ptr->~T();
}

//接受两个迭代器参数
template<class Iter>
inline
void destroy(Iter first,Iter last)
{
    //判断迭代器所指类型是否容易销毁
    typedef typename iterator_traits<first>::value_type value_type;
    typedef typename linstl::m_type_traits<value_type>::has_trivial_destructor  trivial_Des;
    _destroy(Iter first,Iter last,trivial_Des());
}

//类类型，需要逐个销毁
template<class Iter>
void _destroy(Iter first,Iter last,linstl::false_type)
{
    while(first != last)
    {
        destroy(&(*first));
        first++;
    }
}

//内置类型，什么也不做
template<class Iter>
void _destroy(Iter first,Iter last,linstl::true_type){}


}
#endif

