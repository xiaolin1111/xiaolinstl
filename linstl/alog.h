#ifndef  ALOG_H_
#define  ALOG_H_
namespace linstl
{

template<class T>
T max(T& a,T& b)
{
    return a>b? a:b;
}

template<class T>
T min(T& a,T& b)
{
    return a<b? a:b;
}

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
    auto tmp(lhs);
    lhs = rhs;
    rhs = tmp;
}

template<class T>
struct less
{
    bool operator()(const T& x,const T& y)
    {
        return x<y;
    }
};

template<class T>
struct greater
{
    bool operator()(const T& x,const T& y)
    {
        return x>y;
    }
};


}
#endif