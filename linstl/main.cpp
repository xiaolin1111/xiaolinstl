#include "vector.h"
#include <iostream>
using namespace linstl;
int main()
{
    vector<int> vec;
    
    for(int i = 0;i<5;i++)
    {
        vec.push_back(i);
    }
    for(int i = 0;i<5;i++)
    {

        std::cout<<vec[i]<<" "<<std::endl;
    }
    return 0;
}