#include "list.h"
#include <iostream>
using namespace linstl;
using namespace std;
int main()
{
    list<int> l;
    for(int i = 0;i<5;i++)
    {
        l.push_back(i);
    }
    list<int>::iterator iter=l.begin();
    for(;iter!=l.end();iter++)
    {
        cout<<*iter<<endl;
    }
    l.reserve();
    list<int>::iterator iter2=l.begin();
    for(;iter2!=l.end();iter2++)
    {
        cout<<*iter2<<endl;
    }
    return 0;


}