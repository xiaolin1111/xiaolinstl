#ifndef VECTOR_H_
#define VECTOR_H_

//注：有些函数写在类内是为了让大家更直观的看到函数实现，并且节省空间，并非一定是内联函数
//    大部分函数的实现是最低程度的异常安全，有能力的小伙伴可以自行添加异常处理函数
//    vector包含了c++ primer 的大部分函数功能的实现，如有漏写，大家可以自行添加哦
//    还有许多需要添加，修改，优化的地方，有能力的小伙伴可以自行添加

#include <initializer_list>
#include "allocator.h"
#include "allocator_algo.h"
#include "except.h"    
#include "algo.h"

namespace linstl{

//反向迭代器
template<class T>
class vector_reverse_iterator
{
public:
    typedef vector_reverse_iterator   self;
    
    typedef random_iter_tag           iterator_category;
    typedef T                         value_type;
    typedef ptrdiff_t                 difference_type;
    typedef T*                        pointer;
    typedef T&                        reference;
    typedef size_t                    size_type;

    vector_reverse_iterator(){};
    
    vector_reverse_iterator(T* r):p(r){};

    vector_reverse_iterator(self& r):p(r.p){};

    //运算符重载，--变++，++变--
    self& operator++(){ p--; return *this; }
    self& operator--(){ p++; return *this; }
    self  operator++(int) { self tmp = *this; --*this; return tmp; }
    self  operator--(int) { self tmp = *this; ++*this; return tmp; }

    reference operator*(){ self tmp(p); ++tmp; return *(tmp.p); }
    pointer  operator->(){ return &(operator*()); }

    self& operator+(size_type n){ p-=n; return *this; }
    self& operator-(size_type n){ p+=n; return *this; }
private:
    T*  p;
};

template <class T,class Alloc = allocator<T>>
class vector 
{
public:

    //T*作为正向迭代器
    typedef  T*                      iterator;     
    typedef  const T*                const_iterator;
    
    typedef  vector_reverse_iterator<T>          reverse_iterator;
    typedef  vector_reverse_iterator<const T>    const_reverse_iterator;

    typedef  T                       value_type;
    typedef  T*                      pointer;
    typedef  T&                      reference;
    typedef  const T&                const_reference;
    typedef  size_t                  size_type;
    typedef  ptrdiff_t               difference_type;   


    //构造函数
    vector():start(nullptr),finish(nullptr),max_memory(nullptr){}           
    
    explicit 
    vector(size_type n){ fill_initialize(n,value_type());}
    
    explicit 
    vector(size_type n,const value_type& value){ fill_initialize(n,value); }

    template<class Iter>
    vector(Iter begin,Iter end){ copy_initialize(begin,end); }

    vector(std::initializer_list<T> tlist){ copy_initialize(tlist.begin(),tlist.end()); }

    //析构函数
    ~vector()
    {
        Alloc::destroy(start,finish);
        Alloc::deallocate(start,capecity());
    }

    //拷贝
    vector(const vector<T,Alloc>& vec){ copy_initialize(vec.begin(),vec.end()); }

    //移动构造函数
    vector(vector<T,Alloc>&& vec) noexcept
    :start(vec.start),finish(vec.finish),max_memory(vec.max_memory)
    {
        vec.start = vec.finish = vec.max_memory = nullptr;
    }
    
    //赋值运算符
    vector& operator=(const vector<T,Alloc>& vec);

    vector& operator=(std::initializer_list<T> tlist){ vector tmp(tlist); swap(tmp); return *this; }

    vector& operator=(vector<T,Alloc>&& vec) noexcept;

public:
    //迭代器操作
    iterator begin() { return start;  }

    iterator end()   { return finish; }

    reverse_iterator rbegin() { reverse_iterator tmp(finish); return tmp; }

    reverse_iterator rend() { return start; }

    const_iterator begin() const { return start; }

    const_iterator end()   const { return finish; }

    const_reverse_iterator rcbegin() { return finish; }

    const_reverse_iterator rcend() { return start; }  

    bool empty() const { return start == finish; } 

    size_type size() const { return static_cast<size_type>((finish-start)); }    

    size_type capecity() const { return static_cast<size_type>((max_memory-start)); }

    size_type max_size() const { return static_cast<size_type>(max_memory-start); }

    void swap(vector<T,Alloc>& rhs) noexcept;        

    void push_back(const value_type& value);

    void push_back(value_type&& value);

    template <class ...Args>
    void emplace_back(Args&& ...args);

    void pop_back(){ if(start==finish) return; Alloc::destroy(*--finish); }

    reference front(){ return *start; }

    reference back(){ return *(finish-1);}

    reference at(const size_type& n){ assert(n<max_memory-start); return *(start+n); }
    
    iterator insert(iterator iter,const value_type& value) noexcept;                     

    iterator insert(iterator iter,value_type&& value) noexcept;
    
    iterator insert(iterator iter,size_type n,const value_type& value);

    template<class Inputiter>
    iterator insert(Inputiter first,Inputiter last,iterator p);

    iterator insert(iterator p,const std::initializer_list<T>& il);
    
    void erase(iterator iter) noexcept;

    void clear() { Alloc::destroy(start,finish); finish = start; }

    void reserve() noexcept;           //max_memory*2

    void reserve(size_type n) noexcept;

    void sort(iterator beg,iterator end);

//assign，shrink to fit函数有兴趣的同学可以自行实现哦

    
    //运算符重载
    bool operator==(const vector<T,Alloc>& vec);

    bool operator!=(const vector<T,Alloc>& vec) { return !(*this == vec); }

    bool operator<(const vector<T,Alloc>& vec);

    bool operator<=(const vector<T,Alloc>& vec) { return !(*this > vec); }

    bool operator>(const vector<T,Alloc>& vec);

    bool operator>=(const vector<T,Alloc>& vec) { return !(*this < vec); }

    T&   operator[](const size_type n);

    const T& operator[](const size_type n) const;

private:
    //辅助函数
    void     fill_initialize(size_type n,const T& value);

    template<class Iter>
    void     copy_initialize(Iter first,Iter last);

private:
    T*  start;        //元素起始位置
    T*  finish;       //元素结束位置
    T*  max_memory;   //内存结束位置
};

template<class T,class Alloc>
void vector<T,Alloc>::fill_initialize(size_type n,const T& value)  
{
    iterator tmp = Alloc::allocate(n);
    start      = tmp;
    linstl::uninitialized_fill_n(start,n,value);
    finish     = start + n;
    max_memory = finish;
}

template<class T,class Alloc>
template<class Iter>
void vector<T,Alloc>::copy_initialize(Iter first,Iter last)
{
    size_t  n  = last - first;
    iterator tmp = Alloc::allocate(n);
    start      = tmp;
    linstl::uninitialized_copy(first,last,tmp);
    finish     = start + n;
    max_memory = finish;
}

template<class T,class Alloc>
vector<T,Alloc>& 
vector<T,Alloc>::operator=(const vector<T,Alloc>& vec)
{
    vector<T,Alloc> tmp(vec);
    swap(tmp);
    return *this;
}

template<class T,class Alloc>
vector<T,Alloc>& 
vector<T,Alloc>::operator=(vector<T,Alloc>&& vec) noexcept
{
    Alloc::deallocate(start,size());
    start      = vec.start;
    finish     = vec.finish;
    max_memory = vec.max_memory;
    vec.start  = nullptr;
    vec.finish = nullptr;
    vec.max_memory = nullptr;
}

template<class T,class Alloc>
void vector<T,Alloc>::swap(vector<T,Alloc>& rhs) noexcept
{
    linstl::swap(start,rhs.start);
    linstl::swap(finish,rhs.finish);
    linstl::swap(max_memory,rhs.max_memory);
}

template<class T,class Alloc>
void swap(vector<T,Alloc>& lhs,vector<T,Alloc>& rhs) noexcept
{
    lhs.swap(rhs);
}


template<class T,class Alloc>
void vector<T,Alloc>::push_back(const value_type& value)
{
    if(finish!=max_memory)
    {
        Alloc::construct(finish++,value);
    }
    else
    {
        reserve();
        Alloc::construct(finish++,value);
    }
}

template<class T,class Alloc>
void vector<T,Alloc>::push_back(value_type&& value)
{
    if(finish!=max_memory)
    {
        Alloc::construct(finish++,std::move(value));
    }
    else
    {
        reserve();
        Alloc::construct(finish++,std::move(value));
    }
}

template<class T,class Alloc>
template <class ...Args>
void vector<T,Alloc>::emplace_back(Args&& ...args)
{
    if(finish == max_memory)
    {
        reserve();
        Alloc::construct(finish++,std::forward<Args>(args)...);
    }
    else
    {
        Alloc::construct(finish++,std::forward<Args>(args)...);
    }
}

template<class T,class Alloc>
typename vector<T,Alloc>::iterator
vector<T,Alloc>::insert(iterator iter,const value_type& value) noexcept
{
    if(finish == max_memory) 
        reserve();
    
    iterator tmp = finish++;
    tmp--;
    do
    {
        Alloc::construct(tmp+1,std::move(*tmp));
    }while(tmp--!=iter);
    Alloc::construct(++tmp,value);
    return tmp;
}

template<class T,class Alloc>
typename vector<T,Alloc>::iterator
vector<T,Alloc>::insert(iterator iter,value_type&& value) noexcept
{ 
    if(finish == max_memory)
    { 
        size_type n = iter - start;
        reserve();
        iter = start + n;
    }
    
    iterator tmp = finish++;
    tmp--;
    do
    {
        Alloc::construct(tmp+1,std::move(*tmp));
    }while(tmp--!=iter);
    Alloc::construct(++tmp,std::move(value));
    return tmp;
}

template<class T,class Alloc>
typename vector<T,Alloc>::iterator
vector<T,Alloc>::insert(iterator iter,size_type n,const value_type& value)
{
    size_type index= iter - start;
    size_type len  = size();
    if(finish+n>max_memory)
    {
        size_type size = max(max_memory-start+n,2*(max_memory-start));
        reserve(size);
        iter = start + index;
    }
    iterator tmp = start + len;
    tmp--;
    do
    {
        Alloc::construct(tmp+n,std::move(*tmp));
    }while(tmp--!=iter);
    tmp = iter;
    for(int i = 0;i<n;i++) 
        Alloc::construct(*tmp++,value);    
    finish = start + n + len;
    return iter;
}

template<class T,class Alloc>
template<class Inputiter>
typename vector<T,Alloc>::iterator
vector<T,Alloc>::insert(Inputiter first,Inputiter last,iterator iter)
{
    auto n = last-first;
    size_type index= iter - start;
    size_type len  = size();
    if(finish+n>max_memory)
    {
        size_type size = max(max_memory-start+n,2*(max_memory-start));
        reserve(size);
        iter = start + index;
    }
    iterator tmp = start + len;
    tmp--;
    do
    {
        Alloc::construct(tmp+n,std::move(*tmp));
    }while(tmp--!=iter);
    tmp = iter;
    for(int i = 0;i<n;i++,first++)
    {
        Alloc::construct(*tmp++,*first);
    } 
    finish = start + n + len;
    return iter;
}

template<class T,class Alloc>
typename vector<T,Alloc>::iterator
vector<T,Alloc>::insert(iterator iter,const std::initializer_list<T>& il)
{
    iterator first = il.begin(),last = il.end();
    auto n = last - first;
    size_type index= iter - start;
    size_type len  = size();
    if(finish+n>max_memory)
    {
        size_type size = max(max_memory-start+n,2*(max_memory-start));
        reserve(size);
        iter = start + index;
    }
    iterator tmp = start + len;
    tmp--;
    do
    {
        Alloc::construct(tmp+n,std::move(*tmp));
    }while(tmp--!=iter);
    tmp = iter;
    for(int i = 0;i<n;i++,first++)
    {
        Alloc::construct(*tmp++,*first);
    } 
    finish = start + n + len;
    return iter;
}

template<class T,class Alloc>
void vector<T,Alloc>::erase(iterator iter) noexcept
{
    iterator tmp = iter;
    tmp++;
    do
    {
        Alloc::construct(tmp-1,std::move(*tmp));
    }while(tmp++!=finish);
    finish--;
}

template<class T,class Alloc>
void vector<T,Alloc>::reserve() noexcept
{
    auto i      = size();
    size_type n = i!=0? 2*size():1; 
    T* ptr1     = Alloc::allocate(n,pointer(0));
    auto ptr2   = ptr1; 
    auto ptr3   = start;
    while(ptr3!=finish)
    {
        Alloc::construct(ptr2++,std::move(*ptr3++));
    }
    Alloc::deallocate(start);
    start      = ptr1;
    finish     = start+i;
    max_memory = start+n;
}

template<class T,class Alloc>
void vector<T,Alloc>::reserve(size_type n) noexcept
{
    if(n>finish-start)
    {
        auto ptr1 = Alloc::allocate(n);
        auto ptr2 = ptr1; 
        auto ptr3 = begin();
        while(ptr2!=finish)
        {
            Alloc::construct(ptr2++,std::move(*ptr3++));
        }
        Alloc::deallocate(start,max_memory-start);
        finish     = ptr1+finish-start;
        start      = ptr1;
        max_memory = start+n;
    }
    else
    {
        auto ptr1 = Alloc::allocate(n);
        auto ptr2 = ptr1; 
        auto ptr3 = begin();
        for(int i = 0;i < n;i++)
        {
            Alloc::construct(ptr2++,std::move(*ptr3++));
        }
        Alloc::deallocate(start,max_memory-start);
        finish     = ptr1+n;
        start      = ptr1;
        max_memory = finish;
    }
}

template<class T,class Alloc>
void vector<T,Alloc>::sort(iterator beg,iterator end)
{
    if(beg == end) return;
    iterator h = beg;
    iterator t = end;
    t--;
    T base = *h;
    while(h != t)
    {
        while(*t >= base && h != t) t--;
        while(*h <= base && h != t) h++;
        if(h != t)
        {
            linstl::swap(*h,*t);
        }
    }
    *beg = *h;
    *h   = base;
    sort(beg,h);
    sort(++t,end);
}

template<class T,class Alloc>
bool vector<T,Alloc>::operator==(const vector<T,Alloc>& vec)
{
    if(this->size()!=vec.size()) return false;
    
    iterator tmp1 = this->begin();
    iterator tmp2 = vec.begin();
    while(tmp2!=vec.end())
    {
        if(*tmp1++!=*tmp2++) return false;

    }
    return true;
}

template<class T,class Alloc>
bool vector<T,Alloc>::operator<(const vector<T,Alloc>& vec)
{
    iterator tmp1 = this->begin();
    iterator tmp2 = vec.begin();
    while(tmp1!=this->end()&&tmp2!=vec.end())
    {
        if(*tmp1++!=*tmp2++)
        {
            return *tmp1<*tmp2;
        }
    }
    return this->size()<vec.size();
}

template<class T,class Alloc>
bool vector<T,Alloc>::operator>(const vector<T,Alloc>& vec)
{
    iterator tmp1 = this->begin();
    iterator tmp2 = vec.begin();
    while(tmp1!=this->end()&&tmp2!=vec.end())
    {
        if(*tmp1++!=*tmp2++)
        {
            return *tmp1>*tmp2;
        }
    }
    return this->size()>vec.size();
}


template<class T,class Alloc>
typename vector<T,Alloc>::reference               
vector<T,Alloc>::operator[](const size_type n)
{
    check(n<size(),"index out of range");
    return *(start+n);
}

template<class T,class Alloc>
typename vector<T,Alloc>::const_reference          
vector<T,Alloc>::operator[](const size_type n) const
{
    check(n<size(),"index out of range");
    return *(start+n);
}

}

#endif 