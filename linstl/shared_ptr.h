#ifndef _SHARED_PTR_H_
#define _SHARED_PTR_H_


namespace linstl
{
template<class T>
struct ptr_count
{
    




    unsigned int count;
    T* object;

};
}
#endif