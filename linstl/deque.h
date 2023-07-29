#ifndef _DEQUE_H_
#define _DEQUE_H_

#include "allocator.h"
#include <initializer_list>


#define Buffsize 512
namespace linstl
{

//申请一块未使用的内存，默认大小为512
template<class T,size_t Buf = Buffsize,class alloc = allocator<T>>
struct memory_block
{
    typedef size_t               size_type;
    typedef memory_block         self;

    //申请内存
    memory_block(){ memory_block_init(); }
    //释放内存
    void del_memory_block(T* h,T* t){ alloc::destroy(h,t); alloc::deallocate(h); }

    //内存初始化
    memory_block* memory_block_init();

    //内存块起始位置与结束位置
    T* s;      //start
    T* f;      //finish
    //上一块内存块与下一块内存块
    memory_block* pre;
    memory_block* next;
};

template<class T,size_t Buf,class alloc>
memory_block<T,Buf,alloc>*
memory_block<T,Buf,alloc>::
memory_block_init()
{
    //出现类类型大于512时，分配一个单位的空间
    if(Buf<sizeof(T))
    {
        s  = alloc::allocate(1);
        f  = s+sizeof(T);
    }
    else
    {
        size_type tmp = Buf/sizeof(T);
        s             = alloc::allcoate(tmp);
        f             = s+tmp;
    }
        pre           = nullptr;
        next          = nullptr;
    return this;
}

//队列迭代器
template<class T,class Ptr = T*,class Ref = T&>
class deque_iterator
{
    typedef deque_iterator<T,Ptr,Ref>   self;


    typedef T                           value_type;
    typedef T*                          pointer;
    typedef T&                          reference;
    typedef ptrdiff_t                   difference_type;
    typedef bid_iter_tag                iterator_category;         //迭代器类别为双向迭代器


public:
    deque_iterator()  = default;
    deque_iterator(self& iter):p(iter.p),memptr(iter.memptr){}
    deque_iterator(pointer p1,memory_block<T>* p2):p(p1),memptr(p2){}
    
    ~deque_iterator() = default;

    //运算符重载
    Ref operator*() const { return p; }
    Ptr operator->() const { return &(*p); }
    self& operator++()
    { 
        if(p == memptr->f&&(memptr->next == nullptr)) throw std::out_of_range("下标越界");
        if(p == memptr->f)
        { 
            memptr = memptr->next;
            p = memptr->s;
        }
        p++;
        return *p;
    }
    self& operator--()
    {
        if(p == memptr->s&&(memptr->pre == nullptr)) throw std::out_of_range("下标越界");
        if(p == memptr->s)
        {
            memptr = memptr->pre;
            p = memptr->f;
        }
        p--;
        return *p;
    }
    self operator++(int){ deque_iterator tmp = *this; ++*this; return tmp; }
    self operator--(int){ deque_iterator tmp = *this; --*this; return tmp; }

    bool operator==(const self& rhs){ return (this->p == rhs.p); }
    bool operator!=(const self& rhs){ return !(*this == rhs); }

private:
    Ptr  p;
    memory_block<T>*  memptr;       //内存块指针，方便迭代器跳转内存块
};


template<class T,class Alloc = memory_block<T>>
class deque
{
public:
    typedef deque_iterator<T,T*,T&>                 iterator;
    typedef deque_iterator<T,const T*,const T&>     const_iterator;

    typedef T                           value_type;
    typedef T*                          pointer;
    typedef T&                          reference;
    typedef size_t                      size_type;
    typedef ptrdiff_t                   distance_type;

    deque(){ deque_init(); }

    deque(const deque& que){}

    deque(size_type n){}

    explicit deque(size_type n,const T& value){}

    deque(std::initializer_list<T> tlist){}

    deque& operator=(const deque& que){}

    deque& operator=(std::initializer_list<T> tlist){}

//deque操作
public:
    iterator begin(){ iterator tmp(begin,head); return tmp; }

    const_iterator cbegin(){ const_iterator tmp(begin,head); return tmp; }

    iterator end(){ iterator tmp(end,tail); return tmp; }

    const_iterator cend(){ const_iterator tmp(end,tail); return tmp; }

    size_type size(){ return len; }

    bool empty(){ return (start == finish); } 

    void push_back(value_type& value);

    void push_front(value_type& value);

    void pop_back();

    void pop_front(); 

private:
    //辅助函数
    void deque_init();



private:
    //队列起始与结尾
    T* start;
    T* finish;
    size_type len;
    memory_block<T>* head;      //起始内存块
    memory_block<T>* tail;      //结尾内存块

};

template<class T,class Alloc>
void deque<T,Alloc>::deque_init()
{
    head  = Alloc::memory_block_init();
    tail  = head;
    start = head->start;
    finish= start;
}

template<class T,class Alloc>
void deque<T,Alloc>::push_back(value_type& value)
{
    //空间不足时
    if(tail->f == finish)
    {
        memory_block<T>* tmp = Alloc::memory_block();
        tmp->pre   = tail;
        tail->next = tmp;
        finish     = tmp->s;
        tail       = tmp;
        linstl::construct(finish++,value);
        len++;
    }
    else
    {
        linstl::construct(finish++,value);
        len++;
    }
}

template<class T,class Alloc>
void deque<T,Alloc>::push_front(value_type& value)
{
    if(head->s == start)
    {
        memory_block<T>* tmp = Alloc::memory_block();
        tmp->next = head;
        head->pre = tmp;
        start     = tmp->f;
        head      = tmp;
        Alloc::construct(++start,value);
        len++;
    }
    else
    {
        Alloc::construct(++start,value);
        len++;
    }
}

template<class T,class Alloc>
void deque<T,Alloc>::pop_back()
{
    if(start == finish) return;
    if(tail->s == (--finish))
    {
        memory_block<T>* tmp = tail;
        Alloc::del_memory_block(tail->s,tail->f);
        tail   = tmp;
        finish = tail->f;
        len--;
    }
    else
    {
        Alloc::destroy(finish);
        len--;
    }
}



















};


#endif