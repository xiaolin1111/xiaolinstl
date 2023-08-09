#ifndef HEAP_H_
#define HEAP_H_

#include "alog.h"
#include "iterator.h"

namespace linstl
{

//建堆,默认为大根堆——————————————————————————————————————————————————————————————————————//
template<class RandomIter>                                                              
void create_heap(RandomIter first,RandomIter last)                                      
{
    typedef typename RandomIter::value_type value_type;                                      
    _create_heap<value_type,RandomIter>(first,last);                                    
}                                                                                       
                                                                                    
//自定义排序                                                                 
template<class RandomIter,class func>                                                   
void create_heap(RandomIter first,RandomIter last,func)                                 
{                                                                                       
    typedef typename RandomIter::value_type value_type;                                 
    _create_heap<value_type,RandomIter,func>(first,last,func);                            
}

//从第一个非叶子节点开始调整                                                                
template<class T,class RandomIter,class Compare = linstl::greater<T>>                   
void _create_heap(RandomIter first,RandomIter last,Compare)                             
{
    size_t len = distance(first,last);                                                  
    size_t i = len/2;                                               2  1   3
    while(i>0)
    {
        if(2*i+1>len)                                                                   
        {
            if(Compare(*(first+i-1),*(first+2*i-1)))                                             
            {
                swap(*(first+i-1),*(first+2*i-1));                                                
            }
        }
        else                                                                            
        {
            if(Compare(*(first+2*i-1),*(first+2*i+1-1)))                                    
            {
                if(Compare(*(first+i-1),*(first+2*i-1)))                                    
                {
                    swap(*(first+i-1),*(first+2*i-1));                                      
                }
            }                                                                
            else                                                                        
            {
                if(Compare(*(first+i-1),*(first+2*i+1-1)))                                  
                {
                    swap(*(first+i-1),*(first+2*i+1-1));                                    
                }
            }
        }
        i--;                                                                            
    }                                                                                   
}                                                                                            
//—————————————————————————————————————————————————————————————————————————————————————//

//插入后调整————————————————————————————————————————————————————————————————————————————//
//在尾部插入元素,上升元素即可
template<class RandomIter>
void insert_adjust_heap(RandomIter first,RandomIter last)                                      
{
    typedef typename RandomIter::value_type value_type;                                      
    _insert_adjust_heap<value_type,RandomIter>(first,last);                                    
}

//自定义排序                                                                 
template<class RandomIter,class func>                                                   
void insert_adjust_heap(RandomIter first,RandomIter last,func)                                 
{                                                                                       
    typedef typename RandomIter::value_type value_type;                                 
    _insert_adjust_heap<value_type,RandomIter,func>(first,last,func);                            
}

template<class T,class RandomIter,class Compare = linstl::greater<T>>
void _insert_adjust_heap(RandomIter first,RandomIter last,Compare)
{
    size_t len = distance(first,last);
    while(len>0)
    {
        if(Compare(*(first+len/2-1),*(first+len-1)))
        {
            swap(*(first+len/2-1),*(first+len-1));
            len/=2;
        }
        else return;
    }
}

//删除头部后调整——————————————————————————————————————————————————————————————————————————//
//由于删除头部元素后会将尾部元素移到头部，所以只需将头部元素下坠即可
template<class RandomIter>
void del_adjust_heap(RandomIter first,RandomIter last)                                      
{
    typedef typename RandomIter::value_type value_type;                                      
    _del_adjust_heap<value_type,RandomIter>(first,last);                                    
}

//自定义排序                                                                 
template<class RandomIter,class func>                                                   
void del_adjust_heap(RandomIter first,RandomIter last,func)                                 
{                                                                                       
    typedef typename RandomIter::value_type value_type;                                 
    _del_adjust_heap<value_type,RandomIter,func>(first,last,func);                            
}

template<class T,class RandomIter,class Compare = linstl::greater<T>>
void _del_adjust_heap(RandomIter first,RandomIter last,Compare)
{
    size_t len = distance(first,last);
    size_t i = 1;
    while(i<len/2)
    {
        if(2*i+1>len)
        {
            if(!Compare(*(first+i-1),*(first+2*i-1)))                                             
            {
                swap(*(first+i-1),*(first+2*i-1));    
                i = 2*i;                                            
            }
            else return;
        }
        else
        {
            int tmp = Compare(*(first+2*i-1),*(first+2*i+1-1))? (2*i):(2*i+1);
            if(!Compare(*(first+i-1),*(first+tmp-1)))                                             
            {
                swap(*(first+i-1),*(first+2*i-1));    
                i = tmp;                                            
            }
            else return;
        }
    }
}

}

#endif