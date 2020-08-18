#include "fact_k.h"

int fact_k(int val)
{   
    if(val > 1)
    {
        return fact_k(val-1)*val;
    }
    //static int ctr = 0;
    //return ++ctr;
    //return temp;
    return 1;

} 