#ifndef  ALOG_H_
#define  ALOG_H_
namespace linstl
{

//find
template<class InputIter,class T>
InputIter 
find(InputIter first,InputIter last,const T& value)
{
    while(first != last && *first != value)
        first++;
    return first;
}

//swap
template<class T>
inline
void swap(T& lhs,T& rhs)
{
    T tmp(lhs);
    lhs = rhs;
    rhs = tmp;
}

template<class T>
inline
void swap(T* p1,T* p2)
{
    int *p = p1;
    p1 = p2;
    p2 = p;
}



}
#endif