#include "cffix.h"

int CFFIX_API
inc(int x)
{
    return x+1;
}

size_t CFFIX_API
str_len(const char *ss)
{
    size_t  n  =  0;

    while (*ss++) n++;
    return n;
}
