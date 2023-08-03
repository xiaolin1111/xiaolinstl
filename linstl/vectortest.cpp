#include "vector.h"
#include <iostream>
using namespace linstl;
using namespace std;
using std::cin;
using std::cout;
using std::endl;
using std::string;

template<class T>
void f(vector<T>& vec,const char* msg)
{
    cout<<msg;
    for(int i = 0;i<vec.size();++i)
    {
        cout<<vec[i]<<" ";
    }
    cout<<",";
    cout<<endl;
}


int main()
{
    int n = 10;
    cout <<"**********以下关于vector的构造函数测试**********"<<endl<<endl;
    vector<int>     vec1;
    vector<string>  vec2(n);
    vector<string>  vec3(n,"lin");
    vector<string>  vec4(vec3.begin(),vec3.end());
    vector<int>     vec5({1,2,3,4,5});
    vector<int>     vec6(vec5);
    vector<int>     vec7 = vec6;
    vector<int>     vec8 = std::move(vec7);
    vector<string>  vec9 = {"c","+","+","xiao","lin"};

    f(vec1,"vec1的元素为: ");
    f(vec2,"vec2的元素为: ");
    f(vec3,"vec3的元素为: ");
    f(vec4,"vec4的元素为: ");
    f(vec5,"vec5的元素为: ");
    f(vec6,"vec6的元素为: ");
    f(vec7,"vec7的元素为: ");
    f(vec8,"vec8的元素为: ");
    f(vec9,"vec9的元素为: ");

    cout<<"**********以下关于vector操作的测试****************"<<endl<<endl;
    cout<<endl<<endl;
    cout<<"*(vec9.begin()): "<<*(vec9.begin())<<endl;
    cout<<"*(vec9.rbegin()): "<<*(vec9.rbegin())<<endl;
    //empty()
    cout<<endl;
    cout<<"vec1.empty(): "<<vec1.empty()<<endl;
    cout<<"vec9.empty(): "<<vec9.empty()<<endl;
    //size()
    cout<<endl;
    cout<<"vec1.size(): "<<vec1.size()<<endl;
    cout<<"vec2.size(): "<<vec2.size()<<endl;
    cout<<"vec3.size(): "<<vec3.size()<<endl;
    cout<<"vec4.size(): "<<vec4.size()<<endl;
    cout<<"vec5.size(): "<<vec5.size()<<endl;
    cout<<"vec6.size(): "<<vec6.size()<<endl;
    cout<<"vec7.size(): "<<vec7.size()<<endl;
    cout<<"vec8.size(): "<<vec8.size()<<endl;
    cout<<"vec9.size(): "<<vec9.size()<<endl;
    
    //capecity，push_back()
    cout<<endl;
    cout<<"vec1的当前容量为: "<<vec1.capecity()<<endl;
    for(int i = 0;i < 65;i++)
    {
        vec1.push_back(i);
        if(i%8 == 0)
        {
            cout<<"插入"<<i+1<<"个元素后vec1的容量为: "<<vec1.capecity()<<endl;
        }
    }
    
    cout<<endl;
    //swap
    f(vec3,"未交换前vec3的元素为: ");
    f(vec9,"未交换前vec9的元素为: ");
    vec3.swap(vec9);
    f(vec3,"交换后vec3的元素为: ");
    f(vec9,"交换后vec9的元素为: ");
    cout<<endl;
    //swap对vector的重载
    swap(vec3,vec9);
    f(vec3,"再次交换后vec3的元素为: ");
    f(vec9,"再次交换后vec9的元素为: ");
    
    cout<<endl;
    //emplace_back
    vec9.emplace_back("hello");
    vec9.emplace_back("world");
    vec9.emplace_back("!");
    vec9.emplace_back("!");
    vec9.emplace_back("!");
    f(vec9,"emplace_back()后vec9的元素为: ");
    
    
    
    
    return 0;

}