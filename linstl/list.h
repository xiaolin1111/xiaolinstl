#ifndef LIST_H_
#define LIST_H_
#include "allocator.h"


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

template<class T>
struct list_iterator
{ 
    typedef list_node<T>            list_type;
    typedef list_iterator<T>        iterator;
    typedef list_iterator<T>        self;
    typedef bid_iter_tag            iterator_category; 

    typedef T                       value_type;
    typedef T*                      pointer;
    typedef T&                      reference;
    typedef size_t                  size_type;
    typedef ptrdiff_t               difference_type;



    //构造函数
    list_iterator() = default;
    list_iterator(list_type* p):node(p){}
    list_iterator(const iterator& p):node(p.node){}
    //运算符重载
    reference operator* ()    { return (node->data); }
    pointer   operator->()    { return &(operator*()); }

    self     operator++()    { node = (*node).next; return *this; }
    self     operator--()    { node = (*node).pre; return *this;  }
    self     operator++(int) { iterator tmp = *this; ++*this; return tmp; }
    self     operator--(int) { iterator tmp = *this; --*this; return tmp; }

    bool      operator==(const self& rhs) { return node == rhs.node; }
    bool      operator!=(const self& rhs) { return !(node == rhs.node); }

    list_node<T>* node;

};
template<class T>
class list
{
public:
    //空间配置
    
    typedef list_node<T>            list_node;
    typedef list_iterator<T>        iterator;

    typedef T                       value_type;
    typedef T*                      pointer;
    typedef T&                      reference;
    typedef size_t                  size_type;

    //构造函数
    list(){ head = get_node(); head->next = head; head->pre = head; }
    

    
    //链表操作
    iterator begin(){ iterator tmp(head->next); return tmp; }
    
    iterator end()  { iterator tmp(head); return tmp; }

    bool empty() { return head->next == head; }

    size_type size() const{ return distance(begin(),end());}    

    reference front() { return *begin(); }

    reference back()  { return *(--(--begin())); }

    iterator insert(iterator pos,const value_type& value);

    iterator erase (iterator pos);

    void push_back (const T& value){ insert(end(),value); }

    void push_front(const T& value){ insert(begin(),value); }

    void pop_back(){ iterator tmp(end()); erase(--tmp); }

    void pop_front() { erase(begin()); }

    void clear();

    void remove(const value_type& value);

    void sort(iterator first,iterator last);

    void merge(list<T>& l);

    void reserve();




    list_node* get_node() { return alloc.allocate(1); }

    void put_node(list_node* p) { alloc.deallocate(p); }

    list_node* creat_node(const value_type& value){ list_node* tmp = get_node(); linstl::construct(&tmp->data,value); return tmp; }

    void destroy_node(list_node* p){ alloc.destroy(p); put_node(p); }
private:
    //辅助函数
    void transfer(iterator pos,iterator first,iterator last);

private:
    //链表头节点指针,哨兵节点,也是尾指针指向的节点
    list_node* head;     
    allocator<list_node> alloc;  
};

template<class T>
typename list<T>::iterator 
list<T>::insert(iterator pos,const value_type& value)
{
    iterator tmp(creat_node(value));
    tmp.node->next = pos.node;
    tmp.node->pre       = pos.node->pre;
    pos.node->pre  = tmp.node;
    tmp.node->pre->next = tmp.node;
    return iterator(tmp);
}

template<class T>
typename list<T>::iterator 
list<T>::erase(iterator pos)
{
    iterator tmp(pos->next);
    pos->next->pre = pos->pre;
    pos->pre->next = pos->next;
    destroy_node(pos);
    return tmp;
}

template<class T>
void list<T>::clear()
{
    iterator tmp = begin();
    while(tmp!=end())
    {
        tmp = erase(tmp);
    }
}

template<class T>
void list<T>::remove(const value_type& value)
{
    iterator tmp = begin();
    while(tmp!=end())
    {
        if(*tmp == value)
            tmp = erase(tmp);
    }
}

//sort采用快排的递归版本（属于偷懒行为），小伙伴们可以尝试写非递归版本哦
template<class T>
void list<T>::sort(iterator first,iterator last)
{
    //第一个节点作为中间节点，小于mid移到左边，大于移到右边
    iterator mid = first++;
    iterator first1 = mid;       //记录下一次排序的首节点
    iterator last1  = mid;       
    last1++;                     //记录下一次排序的尾节点，前开后闭，last1前进一格       
    while(first != last)
    {
        if(*first<*mid)
        { 
            iterator tmp = first++;
            transfer(mid,tmp,first);
            first1--;          
        }
        else
        {
            iterator tmp1 = first++;
            iterator tmp2 = (mid->node).next;
            transfer(tmp2,tmp1,first);         //last1不需要++
        }
    }
    sort(first1,mid);
    sort(mid,last1);
}

//需要先排序！！！
template<class T>
void list<T>::merge(list<T>& l)
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

template<class T>
typename list<T>::iterator
merge(list<T>& lhs,list<T>& rhs)
{
    lhs.merge(rhs);
    return lhs.begin();
}

template<class T>
void list<T>::reserve()
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

template<class T>
void list<T>::transfer(iterator pos,iterator first,iterator last)
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