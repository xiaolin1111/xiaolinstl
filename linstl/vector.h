#ifndef VECTOR_H_
#define VECTOR_H_

//注：有些函数写在类内是为了让大家更直观的看到函数实现，并且节省空间，并非一定是内联函数
//    移动操作需告知编译器 noexcept
//    大部分函数的实现是最低程度的异常安全，有能力的小伙伴可以自行添加异常处理函数
//    vector 包含了c++ primer 的大部分函数功能的实现，如有漏写，大家可以自行添加哦
//    还有许多需要修改的地方，优化的地方，有能力的小伙伴可以自行添加

#include <initializer_list>
#include "allocator.h"
#include "allocator_alog.h"
#include "except.h"    
#include "alog.h"

namespace linstl{


template <class T>
class vector 
{
public:
    
    typedef  linstl::allocator<T>    data_allocator;
    
    typedef  T*                      iterator;     
    typedef  const T*                const_iterator;

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
    vector(size_type n,const value_type value){ fill_initialize(n,value); }

    vector(const_iterator begin,const_iterator end){ copy_initialize(begin,end); }

    vector(std::initializer_list<T> tlist){ copy_initialize(tlist.begin(),tlist.end()); }

    //析构函数，先执行函数体，所以无需担心先行释放类成员
    ~vector()
    {
        data_allocator::destroy(start,finish);
        data_allocator::deallocate(start,capecity());
    }

    //拷贝
    vector(const vector<T>& vec){ copy_initialize(vec.begin(),vec.end()); }

    //移动构造函数
    vector(vector<T>&& vec) noexcept
    :start(vec.start),finish(vec.finish),max_memory(vec.max_memory)
    {
        vec.start = vec.finish = vec.max_memory = nullptr;
    }

    //赋值运算符
    vector& operator=(const vector<T>& vec);

    vector& operator=(vector<T>&& vec) noexcept;



public:
    //迭代器操作
    iterator begin() { return start;  }

    iterator end()   { return finish; }

    const_iterator begin() const { return start;  }

    const_iterator end()   const { return finish; }  

    bool empty() const { return start == finish; } 

    size_type size() const { return static_cast<size_type>((finish-start)); }    

    size_type capecity() const { return static_cast<size_type>((max_memory-start)); }

    size_type max_size() const { return static_cast<size_type>(max_memory-start); }

    void swap(vector<T>& vec);        

    void push_back(const value_type& value);

    void push_back(value_type&& value);

    template <class ...Args>
    void emplace_back(Args&& ...args);

    void pop_back(){ if(start==finish) return; data_allocator::destroy(*--finish); }

    reference front(){ return *start; }

    reference back(){ return *(finish-1);}

    reference at(const size_type& n){ assert(n<max_memory-start); return *(start+n); }
    
    //第一个参数为迭代器
    iterator insert(iterator iter,const value_type& value) noexcept;                     

    iterator insert(iterator iter,value_type&& value) noexcept;
    
    iterator insert(iterator iter,size_type n,const value_type& value);

    template<class Inputiter>
    iterator insert(Inputiter first,Inputiter last,iterator p);

    iterator insert(iterator p,const std::initializer_list<T>& il);
    
    void erase(iterator iter) noexcept;

    void clear() { data_allocator::destroy(start,finish); finish = start; }

    void reserve() noexcept;           //max_memory*2

    void reserve(size_type n) noexcept;

    // void swap(vector<T>& rhs) noexcept;

//assign，shrink to fit函数没什么用，所以选择不写，有兴趣的同学可以自行实现哦

    
    //运算符重载
    bool operator==(const vector<T>& vec);

    bool operator!=(const vector<T>& vec) { return !(*this == vec); }

    bool operator<(const vector<T>& vec);

    bool operator<=(const vector<T>& vec) { return !(*this > vec); }

    bool operator>(const vector<T>& vec);

    bool operator>=(const vector<T>& vec) { return !(*this < vec); }

    T&   operator[](const size_type n);

    const T& operator[](const size_type n) const;

private:
    //辅助函数
    void     fill_initialize(size_type n,const T& value);

    iterator copy_initialize(const_iterator first,const_iterator last);



private:
    iterator  start;        //元素起始位置
    iterator  finish;       //元素结束位置
    iterator  max_memory;   //内存结束位置
};

template<class T>
void vector<T>::fill_initialize(size_type n,const T& value)  
{
    iterator tmp = data_allocator::allocate(n);
    linstl::uninitialized_fill_n(start,n,value);
    start      = tmp;
    finish     = start + n;
    max_memory = finish;
}

template<class T>
typename vector<T>::iterator
vector<T>::copy_initialize(const_iterator first,const_iterator last)
{
    ptrdiff_t n  = last - first;
    iterator tmp = data_allocator::allocate(n);
    linstl::uninitialized_copy(first,last,tmp);
    start      = tmp;
    finish     = start + n;
    max_memory = finish;
}

template<class T>
vector<T>& 
vector<T>::operator=(const vector<T>& vec)
{
    vector<T> tmp(vec);
    swap(tmp);
    return *this;
}

template<class T>
vector<T>& 
vector<T>::operator=(vector<T>&& vec) noexcept
{
    data_allocator::deallocate(start,size());
    start      = vec.start;
    finish     = vec.finish;
    max_memory = vec.max_memory;
    vec.start  = nullptr;
    vec.finish = nullptr;
    vec.max_memory = nullptr;
}

template<class T>
void vector<T>::swap(vector<T>& rhs)
{
    using linstl::swap;
    swap(this->start,rhs.start);
    swap(this->finish,rhs.finish);
    swap(this->max_memory,rhs.max_memory);
}

template<class T>
void swap(vector<T>& lhs,vector<T>& rhs) noexcept
{
    lhs.swap(rhs);
}


template<class T>
void vector<T>::push_back(const value_type& value)
{
    if(finish!=max_memory)
    {
        data_allocator::construct(finish++,value);
    }
    else
    {
        reserve();
        data_allocator::construct(finish++,value);
    }
}

template<class T>
void vector<T>::push_back(value_type&& value)
{
    if(finish!=max_memory)
    {
        data_allocator::construct(finish++,std::move(value));
    }
    else
    {
        reserve();
        data_allocator::construct(finish++,std::move(value));
    }
}

template<class T>
template <class ...Args>
void vector<T>::emplace_back(Args&& ...args)
{
    if(finish == max_memory)
    {
        reserve();
        data_allocator::construct(finish++,std::forward<Args>(args)...);
    }
    else
    {
        data_allocator::construct(finish++,std::forward<Args>(args)...);

    }
}

template<class T>
typename vector<T>::iterator
vector<T>::insert(iterator iter,const value_type& value) noexcept
{
    if(finish == max_memory) 
        reserve();
    
    iterator tmp = finish++;
    tmp--;
    do
    {
        data_allocator::construct(tmp+1,std::move(*tmp));
    }while(tmp--!=iter);
    data_allocator::construct(++tmp,value);
    return tmp;
}

template<class T>
typename vector<T>::iterator
vector<T>::insert(iterator iter,value_type&& value) noexcept
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
        data_allocator::construct(tmp+1,std::move(*tmp));
    }while(tmp--!=iter);
    data_allocator::construct(++tmp,std::move(value));
    return tmp;
}

template<class T>
typename vector<T>::iterator
vector<T>::insert(iterator iter,size_type n,const value_type& value)
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
        data_allocator::construct(tmp+n,std::move(*tmp));
    }while(tmp--!=iter);
    tmp = iter;
    for(int i = 0;i<n;i++) 
        data_allocator::construct(*tmp++,value);    
    finish = start + n + len;
    return iter;
}

template<class T>
template<class Inputiter>
typename vector<T>::iterator
vector<T>::insert(Inputiter first,Inputiter last,iterator iter)
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
        data_allocator::construct(tmp+n,std::move(*tmp));
    }while(tmp--!=iter);
    tmp = iter;
    for(int i = 0;i<n;i++,first++)
    {
        data_allocator::construct(*tmp++,*first);
    } 
    finish = start + n + len;
    return iter;
}

template<class T>
typename vector<T>::iterator
vector<T>::insert(iterator iter,const std::initializer_list<T>& il)
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
        data_allocator::construct(tmp+n,std::move(*tmp));
    }while(tmp--!=iter);
    tmp = iter;
    for(int i = 0;i<n;i++,first++)
    {
        data_allocator::construct(*tmp++,*first);
    } 
    finish = start + n + len;
    return iter;
}

template<class T>
void vector<T>::erase(iterator iter) noexcept
{
    iterator tmp = iter;
    tmp++;
    do
    {
        data_allocator::construct(tmp-1,std::move(*tmp));
    }while(tmp++!=finish);
    finish--;
}

template<class T>
void vector<T>::reserve() noexcept
{
    auto i      = size();
    size_type n = i!=0? 2*size():1; 
    T* ptr1   = data_allocator::allocate(n,pointer(0));
    auto ptr2   = ptr1; 
    auto ptr3   = start;
    while(ptr3!=finish)
    {
        data_allocator::construct(ptr2++,std::move(*ptr3++));
    }
    data_allocator::deallocate(start);
    start      = ptr1;
    finish     = start+i;
    max_memory = start+n;
}

template<class T>
void vector<T>::reserve(size_type n) noexcept
{
    if(n>finish-start)
    {
        auto ptr1 = data_allocator::allocate(n);
        auto ptr2 = ptr1; 
        auto ptr3 = begin();
        while(ptr2!=finish)
        {
            data_allocator::construct(ptr2++,std::move(*ptr3++));
        }
        data_allocator::deallocate(start,max_memory-start);
        finish     = ptr1+finish-start;
        start      = ptr1;
        max_memory = start+n;
    }
    else
    {
        auto ptr1 = data_allocator::allocate(n);
        auto ptr2 = ptr1; 
        auto ptr3 = begin();
        for(int i = 0;i < n;i++)
        {
            data_allocator::construct(ptr2++,std::move(*ptr3++));
        }
        data_allocator::deallocate(start,max_memory-start);
        finish     = ptr1+n;
        start      = ptr1;
        max_memory = finish;
    }
}


template<class T>
bool vector<T>::operator==(const vector<T>& vec)
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

template<class T>
bool vector<T>::operator<(const vector<T>& vec)
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

template<class T>
bool vector<T>::operator>(const vector<T>& vec)
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


template<class T>
typename vector<T>::reference               
vector<T>::operator[](const size_type n)
{
    check(n<size(),"index out of range");
    return *(start+n);
}

template<class T>
typename vector<T>::const_reference          
vector<T>::operator[](const size_type n) const
{
    check(n<size(),"index out of range");
    return *(start+n);
}

}

#endif 