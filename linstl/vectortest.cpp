#include "vector.h"
#include <iostream>
using namespace linstl;
using namespace std;
int main()
{
    vector<int> vec;
    for(int i = 0;i<8;i++)
    {
        vec.push_back(i);
        std::cout<<"元素："<<vec[i]<<" ";
        std::cout<<"长度："<<vec.size()<<" ";
        std::cout<<"容量："<<vec.capecity()<<" ";
        cout<<endl;
    }
    
    cout<<"首元素："<<vec.front()<<endl;
    cout<<"尾元素："<<vec.back() <<endl;
    cout<<"*(vec.begin())为："<<*vec.begin()<<endl;
    cout<<"*(vec.end()-1)为："  <<*(vec.end()-1)<<endl;

    vec.insert(vec.begin(),10);
    for(int i = 0;i<vec.size();i++)
    {
        cout<<"元素："<<vec[i]<<" ";
        cout<<"长度："<<vec.size()<<" ";
        cout<<"容量："<<vec.capecity()<<" ";
        cout<<endl;
    }
    vector<int> vec2={1,2,3,4,5};
    for(int i = 0;i<vec2.size();i++)
    {
        cout<<"元素："<<vec2[i]<<" ";
    }


    return 0;
}