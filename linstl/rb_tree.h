#ifndef RB_TREE_H_
#define RB_TREE_H_ 

#include "iterator.h"

namespace linstl
{
typedef bool  node_color; 

const node_color red   = false;
const node_color black = true;


struct rb_tree_node_base
{
    typedef rb_tree_node_base*    base_ptr;

    node_color     color;            //节点颜色
    base_ptr       parent;           //父节点
    base_ptr       left;             //左子节点
    base_ptr       right;            //右子节点
};

template <class T>
struct rb_tree_node:rb_tree_node_base
{
    T value;        //节点值 
};

//————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
//红黑树迭代器

template<class T,class Ref,class Ptr>
struct rb_tree_iterator
{
    typedef T             value_type;
    typedef Ref           reference;
    typedef Ptr           pointer;
    typedef bid_iter_tag  iterator_category;
    typedef ptrdiff_t     difference_type;

    typedef rb_tree_iterator<T,Ref,Ptr>  self;

    rb_tree_iterator(){}
    rb_tree_iterator(rb_tree_node<T>* p):node(p){}
    rb_tree_iterator(const self& iter):node(iter.node){}

    reference operator*() { return node->value; }
    pointer operator->(){ return &(operator*()); }

    self& operator++();
    self  operator++(int)
    {
        self tmp = *this;
        ++*this;
        return tmp;
    }
    self& operator--();
    self  operator--(int)
    {
        self tmp = *this;
        --*this;
        return tmp;
    }
    rb_tree_node<T>* node;
};

//节点移动遵循二叉排序树规则
template<class T,class Ref,class Ptr>
rb_tree_iterator<T,Ref,Ptr>&
rb_tree_iterator<T,Ref,Ptr>::operator++()
{
    if(node->right != nullptr)               //如果有右子树，节点向右移动
    {
        node = node->right;
        while(node->left != nullptr)         //之后一直向左走,最左节点即是下一个节点
            node = node->left;
    }
    else                                     //没有右子树，说明当前节点走到底了，需要上升，顺着父节点
    {                                        //向上找下一个节点
        rb_tree_node<T>* p = node->parent;
        if(p->left == node)                  //如果node的父节点的左子节点为node,那么父节点是下一个节点
        {   
            node = p;
        }
        else                                 //node的父节点的右子节点为node,说明父节点的序号在node之前
        {                                    //需要继续上升，找到第一个不为父节点右子树的节点。相应的，      
            while(p->right == node)          //如果node不为父节点的右子节点，那么node一定是左子节点
            {                                //就回到了  if(p->left == node) 此时将node = parent。
                node = p;                           
                p = p->parent;               //注意！！我们模拟的情况是一定有下一个节点,如果迭代器没有下一个节点
            }                                //++iter 会变为nullptr,此时说明走到了end()。
            node = p;                               
        }                                               
    }
    return *this;
}

template<class T,class Ref,class Ptr>
rb_tree_iterator<T,Ref,Ptr>&
rb_tree_iterator<T,Ref,Ptr>::operator--()    //同上
{
    if(node->left != nullptr)
    {
        node = node->left;
        while(node->right != nullptr)         
            node = node->right;
    }
    else
    {
        rb_tree_node<T>* p = node->parent;
        if(p->right == node)
        {
            node = p;
        }
        else 
        {
            while(p->left == node)
            {
                node = p;
                p = p->parent;
            }
            node = p;
        }
    }
    return *this;
}











}

#endif