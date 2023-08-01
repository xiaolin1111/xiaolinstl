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
    cout <<"以下关于vector的构造函数测试:"<<endl;
    vector<int>     vec1;
    vector<string>  vec2(n);
    vector<string>  vec3(n,"lin");
    vector<string>  vec4(vec3.begin(),vec3.end());
    vector<int>     vec5({1,2,3,4,5});
    vector<int>     vec6(vec5);
    vector<int>     vec7 = vec6;
    vector<int>     vec8 = std::move(vec7);
    vector<string>  vec9 = {"c","+","+","xiao","lin"};

    f(vec1,"vec1的元素为:");
    f(vec2,"vec2的元素为:");
    f(vec3,"vec3的元素为:");
    f(vec4,"vec4的元素为:");
    f(vec5,"vec5的元素为:");
    f(vec6,"vec6的元素为:");
    f(vec7,"vec7的元素为:");
    f(vec8,"vec8的元素为:");
    f(vec9,"vec9的元素为:");

    cout<<endl<<endl;
    cout<<"以下关于vector操作的测试:"<<endl;
    cout<<"*(vec9.begin()):"<<*(vec9.begin())<<endl;
    cout<<"*(vec9.rbegin()):"<<*(vec9.rbegin())<<endl;

    return 0;

}