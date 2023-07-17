#ifndef EXCEPT_H_
#define EXCEPT_H_
#include <stdexcept>
#include <assert.h>

namespace linstl
{
void check(bool b,const char* msg)
{
    if(!b)
        throw std::out_of_range(msg);
}





}
#endif