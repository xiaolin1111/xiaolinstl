#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_

#include"construct.h"
namespace linstl{


template<class T>
T* _allocate(ptrdiff_t n,T*)
{
    return static_cast<T*>(::operator new(n*sizeof(T)));
}

template<class T>
T* _allocate(T*)
{
    return static_cast<T*>(::operator new(sizeof(T)));
}

template<class T>
void _deallocate(T* p)
{
    operator delete (p);
}


template <class T>
class allocator
{
public:
    typedef  T              value_type;
    typedef  T*             pointer;
    typedef  const T*       const_pointer;
    typedef  T&             reference;   
    typedef  const T&       const_reference;
    typedef  size_t         size_type;
    typedef  ptrdiff_t      difference_type;

    static T*               allocate(T*)
                            { return _allocate(pointer(0)); }

    static pointer          allocate(size_type n,const void* p = 0)
                            { return _allocate(n,pointer(0)); }
    
    static void             deallocate(T* p,size_type n){ return _deallocate(p); }
    static void             deallocate(T* p) { return _deallocate(p); }

    static void             construct(T* ptr);
    static void             construct(T* ptr,const T& value);
    // static void             construct(T* ptr,T&& value);
    
    static void             destroy(T* ptr);
    static void             destroy(T* first,T* last);

    

};

// template<class T>
// T* _allocate(ptrdiff_t n,T*)
// {
//     return static_cast<T*>(::operator new(n*sizeof(T)));
// }

// template<class T>
// T* _allocate(T*)
// {
//     return static_cast<T*>(::operator new(sizeof(T)));
// }
//查阅了很多资料，只能勉强得出结论：编译器会自行释放申请的一块空间，无关n的长度（仅供参考）


template<class T>
void allocator<T>::construct(pointer ptr)
{
    linstl::construct(ptr);
}

template<class T>
void allocator<T>::construct(pointer ptr,const_reference value)
{
    linstl::construct(ptr,value);
}

// template<class T>
// void allocator<T>::construct(T* ptr,T&& value)
// {
//     linstl::construct(ptr,std::forward<T>(value));
// }

template<class T>
void allocator<T>::destroy(pointer ptr)
{
    linstl::destroy(ptr);
}

template<class T>
void allocator<T>::destroy(pointer first,pointer last)
{
    linstl::destroy(first,last);
}



}



#endif