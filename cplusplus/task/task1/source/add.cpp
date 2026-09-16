#include "add.hpp"

int add(int x, int y)
{
    return x + y;
}

void add(int &x, int &y, int &ret)
{
    ret = x + y;
}