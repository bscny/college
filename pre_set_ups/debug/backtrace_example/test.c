#include <stdio.h>
#include <stdlib.h>
#ifdef BACKTRACE
#include "backtrace.h"
#endif

int main(int argc, char **argv)
{
    int a = 1;
    int b = 0;

#ifdef BACKTRACE
    set_signal_handler();
#endif

    return a / b;
}
