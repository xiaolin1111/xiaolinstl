#ifndef LIST_H_
#define LIST_H_
#include <initializer_list>
#include "allocator.h"
//注：
//  list包含了c++ primer 的大部分函数功能的实现，如有漏写，大家可以自行添加哦
//  还有许多需要添加，修改，优化的地方，有能力的小伙伴可以自行添加
//
namespace linstl
{

//链表节点struct
template<class T>
struct list_node
{
    list_node():pre(nullptr),next(nullptr),data(){}
    list_node(const T& value):pre(nullptr),next(nullptr),data(value){}
    list_node(list_node<T>* p,list_node<T>* q,T val):pre(p),next(q),data(val){}

    list_node<T>* pre;
    list_node<T>* next;
    T data;
};
//链表迭代器
template<class T,class Ptr = T*,class Ref = T&>
struct list_iterator
{ 
    typedef list_node<T>                        list_type;
    typedef list_iterator<T,Ptr,Ref>            self;
    typedef list_iterator<T,T*,T&>              iterator;
    typedef bid_iter_tag                        iterator_category; 

    typedef T                                   value_type;
    typedef T*                                  pointer;
    typedef T&                                  reference;
    typedef size_t                              size_type;
    typedef ptrdiff_t                           difference_type;



    //构造函数
    list_iterator() = default;
    list_iterator(list_type* p):node(p){}
    list_iterator(const iterator& p):node(p.node){}
    //运算符重载
    Ref       operator* ()    { return (node->data); }
    Ptr       operator->()    { return &(operator*()); }

    self&     operator++()    { node = (*node).next; return *this; }
    self&     operator--()    { node = (*node).pre; return *this;  }
    self      operator++(int) { self tmp = *this; ++*this; return tmp; }
    self      operator--(int) { self tmp = *this; --*this; return tmp; }

    bool      operator==(const self& rhs) { return node == rhs.node; }
    bool      operator!=(const self& rhs) { return !(node == rhs.node); }

    list_node<T>* node;

};
//反向迭代器
template<class T,class Ptr = T*,class Ref = T&>
struct list_reverse_iterator
{
    typedef list_node<T>                        list_type;
    typedef list_reverse_iterator<T,Ptr,Ref>    self;
    typedef list_reverse_iterator<T,T*,T&>      reverse_iterator;
    typedef bid_iter_tag                        iterator_category; 

    typedef T                                   value_type;
    typedef T*                                  pointer;
    typedef T&                                  reference;
    typedef size_t                              size_type;
    typedef ptrdiff_t                           difference_type;


    //构造函数
    list_reverse_iterator() = default;
    list_reverse_iterator(list_type* p):node(p){}
    list_reverse_iterator(const list_reverse_iterator& p):node(p.node){}
    //运算符重载
    Ref       operator* ()    { return (node->data); }
    Ptr       operator->()    { return &(operator*()); }

    //++变--，--变++
    self&     operator++()    { node = (*node).pre; return *this; }
    self&     operator--()    { node = (*node).next; return *this;  }
    self      operator++(int) { list_reverse_iterator tmp = *this; --*this; return tmp; }
    self      operator--(int) { list_reverse_iterator tmp = *this; ++*this; return tmp; }

    bool      operator==(const self& rhs) { return node == rhs.node; }
    bool      operator!=(const self& rhs) { return !(node == rhs.node); }

    list_node<T>* node;
};

template<class T,class Alloc = allocator<list_node<T>>>
class list
{
public:
    typedef list_node<T>                                 list_node;
    typedef list_iterator<T,T*,T&>                       iterator;
    typedef list_iterator<T,const T*,const T&>           const_iterator;
    typedef list_reverse_iterator<T,T*,T&>               reverse_iterator;
    typedef list_reverse_iterator<T,const T*,const T&>   const_reverse_iterator;

    typedef T                                            value_type;
    typedef T*                                           pointer;
    typedef T&                                           reference;
    typedef ptrdiff_t                                    difference_type;
    typedef size_t                                       size_type;

    //构造函数
    list(){ list_init(); }

    explicit list(size_type n,const value_type& value){ fill_init(n,value); }
    
    list(const std::initializer_list<T>& tlist)
    {
        list_init();
        auto p = tlist.begin();
        while(p != tlist.end())
        {
            emplace_back(*p++);
        }
    }
    //拷贝构造
    list(const list<T>& l) { copy_init(l.cbegin(),l.cend()); }

    list(list<T>&& l) { head = l.head; l.head = nullptr; }

    //赋值
    list<T>& operator=(const list<T>& l) {  return *this; } 

    list<T>& operator=(list<T>&& l){ head = l.head; l.head = nullptr; return *this; }

public:
    //链表操作
    iterator begin(){ iterator tmp(head->next); return tmp; }

    const_iterator cbegin(){ const_iterator tmp(head->next); return tmp; }
    
    iterator end()  { iterator tmp(head); return tmp; }

    const_iterator cend(){ const_iterator tmp(head); return tmp; }

    bool empty() { return head->next == head; }

    size_type size() { return distance(begin(),end()); }

    reference front() { return *begin(); }

    reference back()  { return *(--(--begin())); }

    iterator insert(iterator pos,const value_type& value);

    iterator erase (iterator pos);

    void push_back (const T& value){ insert(end(),value); }

    void push_front(const T& value){ insert(begin(),value); }
    
    template<class ...Args>
    void emplace_back(Args&& ...args);

    void pop_back(){ iterator tmp(end()); erase(--tmp); }

    void pop_front() { erase(begin()); }

    void clear();

    void remove(const value_type& value);

    void sort(iterator first,iterator last);

    void merge(list<T>& l);

    void reserve();
    //释放所有节点
    ~list(){ clear(); destroy_node(head); }

    //创建节点
    list_node* get_node() { return Alloc::allocate(1); }

    void put_node(list_node* p) { Alloc::deallocate(p); }

    list_node* creat_node(const value_type& value){ list_node* tmp = get_node(); linstl::construct(&tmp->data,value); return tmp; }

    void destroy_node(list_node* p){ Alloc::destroy(p); put_node(p); }
public:
    //运算符重载略



private:
    //辅助函数
    //构造一个空的节点作为head；
    void list_init();

    void fill_init(size_type n,const T& value);

    void copy_init(const_iterator begin,const_iterator end);

    void transfer(iterator pos,iterator first,iterator last);

private:
    //链表头节点指针,哨兵节点,也是尾指针指向的节点
    list_node* head;  
};

template<class T,class Alloc>
typename list<T,Alloc>::iterator 
list<T,Alloc>::insert(iterator pos,const value_type& value)
{
    iterator tmp(creat_node(value));
    tmp.node->next = pos.node;
    tmp.node->pre  = pos.node->pre;
    pos.node->pre  = tmp.node;
    tmp.node->pre->next = tmp.node;
    return iterator(tmp);
}

template<class T,class Alloc>
typename list<T,Alloc>::iterator 
list<T,Alloc>::erase(iterator pos)
{
    iterator tmp((pos.node)->next);
    (pos.node)->next->pre = (pos.node)->pre;
    (pos.node)->pre->next = (pos.node)->next;
    destroy_node(pos.node);
    return tmp;
}

template<class T,class Alloc>
template<class ...Args>
void list<T,Alloc>::emplace_back(Args&& ...args)
{
    list_node* tmp = get_node();
    linstl::construct(&tmp->data,std::forward<Args>(args)...);

    iterator pos = end();
    ((pos.node)->pre)->next = tmp;
    tmp->pre = (pos.node)->pre;
    (pos.node)->pre = tmp;
    tmp->next = pos.node;
}

template<class T,class Alloc>
void list<T,Alloc>::clear()
{
    iterator tmp = begin();
    while(tmp!=end())
    {
        tmp = erase(tmp);
    }
}

template<class T,class Alloc>
void list<T,Alloc>::remove(const value_type& value)
{
    iterator tmp = begin();
    while(tmp!=end())
    {
        if(*tmp == value)
            tmp = erase(tmp);
    }
}

//sort采用快排的递归版本（属于偷懒行为），小伙伴们可以尝试写非递归版本哦
template<class T,class Alloc>
void list<T,Alloc>::sort(iterator first,iterator last)
{
    if(first == last) return ;
    //第一个节点作为中间节点，小于mid移到左边
    iterator h      = first;        //记录下一次排序的首节点
    iterator e      = last;
    iterator mid    = first++;           
    while(first != last)
    {
        if(*first<*mid)
        { 
            iterator tmp = first++;
            transfer(h,tmp,first);    //头插法
            h--;                      //h向后移动          
        }
        else
        {
            first++;              
        }
    }
    sort(h,mid);
    sort(++mid,e);
}

//需要先排序！！！
template<class T,class Alloc>
void list<T,Alloc>::merge(list<T>& l)
{
    iterator first1 = begin();
    iterator last1  = end();
    iterator first2 = l.begin();
    iterator last2 = l.end();

    while(first1 != last1&&first2 != last2)
    {
        if(*first2<*first1)
        {
            iterator next = first2;
            transfer(first1,first2,++next);
            first2 = next;
        }
        else
            first1++;
    }
    if(first2 != last2) transfer(last1,first2,last2);
}

template<class T,class Alloc>
typename list<T,Alloc>::iterator
merge(list<T,Alloc>& lhs,list<T,Alloc>& rhs)
{
    lhs.merge(rhs);
    return lhs.begin();
}

template<class T,class Alloc>
void list<T,Alloc>::reserve()
{
    if(head->next == head||head->next->next == head)
        return;
    iterator first = begin();

    while(first != end())
    {
        iterator tmp = first;
        ++first;
        transfer(begin(),tmp,first);
    }
}

template<class T,class Alloc>
void list<T,Alloc>::list_init()
{
    head = get_node(); 
    head->next = head; 
    head->pre  = head;
}

template<class T,class Alloc>
void list<T,Alloc>::fill_init(size_type n,const T& value)
{
    list_init();
    for(int i = 0;i < n;i++)
    {
        emplace_back(value);
    }
}

template<class T,class Alloc>
void list<T,Alloc>::copy_init(const_iterator begin,const_iterator end)
{
    list_init();
    while(begin != end)
    {
        emplace_back(*begin++);
    }
}

template<class T,class Alloc>
void list<T,Alloc>::transfer(iterator pos,iterator first,iterator last)
{
    if(pos != last)
    {   
        ((last.node)->pre)->next  = pos.node;
        ((first.node)->pre)->next = last.node;
        ((pos.node)->pre)->next   = first.node;
        iterator tmp((pos.node)->pre);
        (pos.node)->pre           = (last.node)->pre;
        (last.node)->pre          = (first.node)->pre;
        (first.node)->pre         = tmp.node;
    }
}

}

#endif