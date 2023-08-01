#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_

#include"construct.h"
namespace linstl{

template<class T>
T* _allocate(size_t n,T*)
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

    static T*               allocate(size_type n,const void* p = 0)
                            { return _allocate(n,pointer(0)); }
    
    static void             deallocate(T* p,size_type n){ return _deallocate(p); }
    static void             deallocate(T* p) { return _deallocate(p); }

    static void             construct(T* p);
    static void             construct(T* p,const T& value);
    static void             construct(T* p,T&& value);
    
    template <class ...Args>
    static void             construct(T* p, Args&& ...args);
    
    static void             destroy(T* p);
    static void             destroy(T* first,T* last);

    

};

template<class T>
void allocator<T>::construct(T* p)
{
    linstl::construct(p);
}

template<class T>
void allocator<T>::construct(T* p,const T& value)
{
    linstl::construct(p,value);
}

template<class T>
void allocator<T>::construct(T* p,T&& value)
{
    linstl::construct(p,std::move(value));
}

template<class T>
template<class ...Args>
void allocator<T>::construct(T* p, Args&& ...args)
{
    linstl::construct(p,std::forward<Args>(args)...);
}



template<class T>
void allocator<T>::destroy(T* p)
{
    linstl::destroy(p);
}

template<class T>
void allocator<T>::destroy(T* first,T* last)
{
    linstl::destroy(first,last);
}



}



#endif