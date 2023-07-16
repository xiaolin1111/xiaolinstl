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
//指针偏特化
template<class T>
void swap<T*>(T* lhs,T* rhs)
{
    T* tmp = lhs;
    lhs = rhs;
    rhs = tmp;
}



}