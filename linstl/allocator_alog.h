#include "iterator.h"
#include "type_traits.h"
#include "construct.h"
namespace linstl{

//填充迭代器之间的元素
template<class Iter,class T>
void uninitialized_fill(Iter first,Iter last,const T& value)
{
    typedef typename m_type_traits<T>::has_trivial_assignment_operator  assignment;
    uninitialized_fill_U(first,last,value,assignment());
}
template<class Iter,class T>
void uninitialized_fill_U(Iter first,Iter last,const T& value,true_type)
{
    std::fill(first,last,value);
}
template<class Iter,class T>
void uninitialized_fill_U(Iter first,Iter last,const T& value,false_type)
{
    Iter tmp = first;
    try
    {
        while(tmp != last)
        {
            linstl::construct(&*tmp, value);
            tmp++;
        }
    }
    catch(...)
    {
        while(tmp!=first)
        {
            linstl::destroy(&*tmp);
            tmp--;
        }
    }
}

//填充n个元素
template<class Iter,class T>
void uninitialized_fill_n(Iter first,size_t n,const T& value)
{
    typedef typename m_type_traits<T>::has_trivial_assignment_operator  assignment;
    uninitialized_fill_n_U(first,size_t n,const T& value,assignment()); 
}

template<class Iter,class T>
void uninitialized_fill_n_U(Iter first ,size_t n ,const T& value,true_type)
{
    std::fill_n(first,n,value);
}
template<class Iter,class T>
void uninitialized_fill_n_U(Iter first,size_t n,const T& value,false_type)
{
    Iter tmp = first;
    try
    {
        while(n-- > 0)
        {
            linstl::construct(first++,value);
        }
    }
    catch(...)
    {
        while(tmp!=first)
        {
            linstl::destroy(&*tmp);
            tmp--;
        }
    }
    
}

//拷贝迭代器之间的元素
template<class InputIter,class Iter>
void uninitialized_copy(InputIter first,InputIter last,Iter result)
{
    typedef typename iterator_traits<first>::value_type  value_type;
    typedef typename m_type_traits<value_type>::has_trivial_copy_constructor has_trivial_copy_constructor;
    uninitialized_copy_U(first,last,result,has_trivial_copy_constructor()); 
}

template<class InputIter,class Iter>
void uninitialized_copy_U(InputIter first,InputIter last,Iter result,true_type)
{
    ptrdiff_t n = last-first;
    std::copy(first,last,result);
}

template<class InputIter,class Iter>
void uninitialized_copy_U(InputIter first,InputIter last,Iter result,false_type)
{
    InputIter tmp = first;
    try
    {
        while(tmp!=last)
        {
            linstl::construct(&*(result++),*tmp++);
        }
    }
    catch(...)
    {
        while(tmp!=first)
        {
            linstl::destroy(&*(--result),*--tmp);
        }
    }
    
}

//拷贝n个元素
template<class Iter,class T>
void uninitialized_copy_n(Iter first,size_t n,const T& value)
{
    typedef typename iterator_traits<T>::value_type  value_type;
    typedef typename m_type_traits<value_type>::has_trivial_copy_constructor has_trivial_copy_constructor;
    uninitialized_copy_n_U(first,n,value,has_trivial_copy_constructor()); 
}

template<class Iter,class T>
void uninitialized_copy_n_U(Iter first,size_t n,const T& value,true_type)
{
    copy(first,n,value);
}

template<class Iter,class T>
void uninitialized_copy_n_U(Iter first,size_t n,const T& value,false_type)
{
    Iter tmp = first;
    try
    {
        while(n-- > 0)
        {
            linstl::construct(first++,value);
        }
    }
    catch(...)
    {
        while(tmp!=first)
        {
            linstl::destroy(&*tmp);
            tmp--;
        }
    }
}











}