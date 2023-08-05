#include "list.h"
#include <iostream>
using namespace linstl;
using namespace std;
using std::cin;
using std::cout;
using std::endl;
using std::string;

template<class T>
void f(list<T>& lst,const char* msg)
{
    cout<<msg;
    for(auto iter = lst.begin();iter!=lst.end();++iter)
    {
        cout<<*iter<<" ";
    }
    cout<<",";
    cout<<endl;
}


int main()
{

    cout <<"**********以下关于list的构造函数测试**********"<<endl<<endl;
    
    list<int> lst1;
    list<string> lst2(5,"lin");
    list<int> lst3{1,2,3,4,5,6,7,8,9};

    list<int> lst4(lst3);
    list<int> lst5(std::move(lst4));
    list<int> lst6 = lst3;
    list<string> lst7 = std::move(lst2);

    f(lst1,"lst1的元素为: ");
    f(lst2,"lst2的元素为: ");
    f(lst3,"lst3的元素为: ");
    f(lst4,"lst4的元素为: ");
    f(lst5,"lst5的元素为: ");
    f(lst6,"lst6的元素为: ");
    f(lst7,"lst7的元素为: ");


    cout<<endl;
    cout<<"*(lst3.begin()): "<<*(lst3.begin())<<endl;
    cout<<"*(lst7.begin()): "<<*(lst7.begin())<<endl;
    cout<<"*(lst3.cbegin()): "<<*(lst3.cbegin())<<endl;
    cout<<"*(lst7.cbegin()): "<<*(lst7.cbegin())<<endl;
    cout<<"*(lst3.rbegin()): "<<*(lst3.rbegin())<<endl;
    cout<<"*(lst7.rbegin()): "<<*(lst7.rbegin())<<endl;

    cout <<"**********以下关于list的操作**********"<<endl<<endl;

    cout<<"lst1.empty(): "<<lst1.empty()<<" ";
    cout<<"lst3,empty(): "<<lst3.empty()<<endl;

    cout<<"lst1.size(): "<<lst1.size()<<endl;
    cout<<"lst3.size(): "<<lst3.size()<<endl;
    cout<<"lst7.size(): "<<lst7.size()<<endl;

    cout<<"lst3.front(): "<<lst3.front()<<endl;
    cout<<"lst3.back(): "<<lst3.back()<<endl;
    cout<<"lst7.front(): "<<lst7.back()<<endl;
    cout<<"lst7.back(): "<<lst7.back()<<endl;


    f(lst3,"插入前lst3的元素为: ");
    for(int i = 0;i<5;++i)
    {
        lst3.insert(lst3.begin(),10);
    }
    f(lst3,"插入后lst3的元素为: ");
    cout<<endl;
    f(lst7,"插入前lst7的元素为: ");
    lst7.insert(lst7.begin(),"c");
    lst7.insert(lst7.begin(),"+");
    lst7.insert(lst7.begin(),"+");
    f(lst7,"插入后lst7的元素为: ");

    lst3.sort(lst3.begin(),lst3.end());
    f(lst3,"排序后lst3的元素为: ");

    lst3.remove(1);
    lst3.remove(3);
    f(lst3,"删除1和3后lst3的元素为: ");

    lst3.merge(lst5);
    f(lst3,"合并lst3和lst5后lst3的元素为: ");
    f(lst5,"lst5的元素为: ");

    return 0;
}