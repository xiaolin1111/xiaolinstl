#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

#include "vector.h"
#include "heap.h"

namespace linstl{

//vector 作为底层容器
template<class T,class Que = vector<T>,class Compare = less<typename vector<T>::value_type>>
class priority_queue
{
public:
    typedef typename  Que::value_type         value_type;
    typedef typename  Que::size_type          size_type;
    typedef typename  Que::reference          reference;
    typedef typename  Que::const_reference    const_reference;

public:
    priority_queue():que(){}

    template<class InputIter>
    priority_queue(InputIter first,InputIter last):que(first,last)
    {
        create_heap(que.first(),que.last(),compare);
    }

    bool empty() const { return que.empty; }
    
    size_type size() const { return que.size(); }

    void push(const value_type& value) { que.push(value); insert_adjust_heap(que.first(),que.last(),compare); }

    void pop(){ swap(que.front(),swap(que.back())); que.pop_back(); del_adjust_heap(que.first(),que.last(),compare); }

    const_reference top() const { return que.front(); }

private:
    Que     que;            //容器
    Compare compare         //比较方式

};

}
#endif