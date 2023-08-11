#ifndef STACK_H_
#define STACK_H_

#include "deque.h"
namespace linstl
{
//deque 作为底层容器
template<class T,class Deq = deque<T>>
class stack
{ 
public:
    typedef typename Deq::value               value_type;
    typedef typename Deq::pointer             pointer;
    typedef typename Deq::reference           reference;
    typedef typename Deq::const_reference     const_reference;
    typedef typename Deq::size_type           size_type;
    typedef typename Deq::ptrdiff_t           distance_type;

    stack(){ stk();}

    reference top() { return c.back(); }
    
    const_reference top() { return c.back(); }
    
    void push(value_type& value){ stk.push_back(value); }

    void pop(){ stk.pop_back(); }

    bool empty() const { return stk.empty(); }

    size_type size() const { return stk.size(); }
private:
    Deq stk;
};


}


#endif