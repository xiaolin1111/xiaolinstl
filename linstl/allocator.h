#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_

#include"construct.h"
namespace linstl{


template <class T>
class allocator
{
public:
    typedef  T              value_type;
    typedef  T*             pointer;
    typedef  const T*       const_pointer;
    typedef  T&             reference;   
    typedef  size_t         size_type;
    typedef  ptrdiff_t      difference_type;

    static T*               allocate();
    static T*               allocate(size_type n);
    
    static void             deallocate(T* p,size_type n);
    static void             deallocate(T* p);

    static void             construct(T* ptr);
    static void             construct(T* ptr,const T& value);
    static void             construct(T* ptr,T&& value);
    
    static void             destroy(T* ptr);
    static void             destroy(T* first,T* last);
};

template<class T>
T* allocator<T>::allocate(size_t n)
{
    return static_cast<T*>(::operator new(n*sizeof(T)));
}

template<class T>
T* allocator<T>::allocate()
{
    return static_cast<T*>(::operator new(sizeof(T)));
}
//查阅了很多资料，只能勉强得出结论：编译器会自行释放申请的一块空间，无关n的长度（仅供参考）
template<class T>
void allocator<T>::deallocate(T* ptr,size_t n)
{
    ::operator delete (ptr);
}

template<class T>
void allocator<T>::deallocate(T* ptr)
{
    ::operator delete (ptr);
}

template<class T>
void allocator<T>::construct(T* ptr)
{
    linstl::construct(ptr);
}

template<class T>
void allocator<T>::construct(T* ptr,const T& value)
{
    linstl::construct(ptr,value);
}

template<class T>
void allocator<T>::construct(T* ptr,T&& value)
{
    linstl::construct(ptr,std::forward<T>(value));
}

template<class T>
void allocator<T>::destroy(T* ptr)
{
    linstl::destroy(ptr);
}

template<class T>
void allocator<T>::destroy(T* first,T* last)
{
    linstl::destroy(first,last);
}



}



#endif