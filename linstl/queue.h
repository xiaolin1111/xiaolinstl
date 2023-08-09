#ifndef QUEUE_H_
#define QUEUE_H_

#include "deque.h"

namespace linstl
{

template<class T,class Deq = deque<T>>
class queue
{
public:
    typedef typename Deq::value               value_type;
    typedef typename Deq::pointer             pointer;
    typedef typename Deq::reference           reference;
    typedef typename Deq::const_reference     const_reference;
    typedef typename Deq::size_type           size_type;
    typedef typename Deq::ptrdiff_t           distance_type;

    queue(){ que(); }

    const_reference front(){ return que.front(); }

    const_reference back() { return que.back(); }

    void push(const value_type& value){ que.push_back(value); }

    void pop(){ que.pop_front(); }

    sizse_type size(){ return que.size(); }

private:
    Deq que;
};















}


#endif