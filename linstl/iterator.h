#ifndef ITERATOR_H_
#define ITERATOR_H_
#include<cstddef>        //ptrdiff_t
namespace linstl{

//五类迭代器用来区分函数所使用的的迭代器类型,并针对不同容器函数的实现细节不同,无特定意义
// difference(first,last,random_iter_tag);
// difference(first,last,input_iter_tag);
//两种实现细节不同,vector容器可使用第一种，只需要O(1)
//类似于链表的数据结构只能使用第二种，需要O(n)
struct input_iter_tag{};
struct output_iter_tag{};
struct forward_iter_tag:public input_iter_tag{};
struct bid_iter_tag:public forward_iter_tag{};
struct random_iter_tag:public bid_iter_tag{};



//把指针包装成迭代器，可以看作一种超级指针
template<class Category,
         class T,
         class Distance = ptrdiff_t,
         class Pointer = T*,
         class Reference = T&>
class iterator
{
    typedef Category                iterator_category;
    typedef T                       value_type;
    typedef Distance                difference_type;
    typedef Pointer                 pointer;
    typedef Reference               reference;
};



//迭代器的属性
template<class Iter>
struct iterator_traits
{
    typedef typename Iter::iterator_category   iterator_category;
    typedef typename Iter::value_type          value_type;
    typedef typename Iter::difference_type     difference_type;
    typedef typename Iter::pointer             pointer;
    typedef typename Iter::reference           reference;
};


//原生指针转换为迭代器的偏特化版本
template<class T>
struct iterator_traits<T*>
{
    typedef T*                  pointer;
    typedef T                   value_type;
    typedef ptrdiff_t           difference_type;
    typedef random_iter_tag     iterator_category;
    typedef T&                  reference;
};
template<class T>
struct iterator_traits<const T*>
{
    typedef const T*            pointer;
    typedef T                   value_type;
    typedef ptrdiff_t           difference_type;
    typedef random_iter_tag     iterator_category;
    typedef const T&            reference;
};



//得到迭代器的类型
template<class Iter>
inline typename iterator_traits<Iter>::iterator_category
iterator_category(const Iter&)
{
    typedef typename iterator_traits<Iter>::iterator_category category;
    return category();       //类似与int();
}


template<class Iter>
inline typename iterator_traits<Iter>::difference_type*   
distance_type(const Iter&)
{
    typedef typename Iter::difference_type difference_type;
    return static_cast<difference_type*>(0);   //返回一个size_type* 
}

template<class Iter>
inline typename iterator_traits<Iter>::value_type*
value_type(const Iter&)
{
    typedef typename iterator_traits<Iter>::value_type value_type;
    return static_cast<value_type*>(0);        //返回一个T*
}
//**********************************************************************
//迭代器距离
template<class InputIter>
inline typename iterator_traits<InputIter>::difference_type
distance(InputIter first,InputIter last)
{
    typedef typename iterator_traits<InputIter>::iterator_category category;
    return distance_12(first,last,category()); 
}
//第一种,input_iter_tag
template<class InputIter>
inline typename iterator_traits<InputIter>::difference_type
distance_12(InputIter first,InputIter last,input_iter_tag)
{
    typename iterator_traits<InputIter>::difference_type n = 0;
    while(first!=last)
    {
        n++;
        first++;
    }
    return n;
}

//第二种
template<class RandomIter>
inline typename iterator_traits<RandomIter>::difference_type
distance_12(RandomIter first,RandomIter last,random_iter_tag)
{
    return last-first;
}

template<class Iter,class Distance>
void
inline advance(Iter& first,Distance n)
{
    typedef typename iterator_traits<Iter>::category category;
    return advance(first,n,category());
    
}

template<class InputIter,class Distance>
void 
inline advance_12(InputIter& first,Distance n,input_iter_tag)
{
    
    while(n>=0)
    {
        n--;
        first++;
    }
    return n;
}

template<class RandomIter,class Distance>
void
inline advance_12(RandomIter& first,Distance n,random_iter_tag)
{
    return first+=n;
}

}

#endif