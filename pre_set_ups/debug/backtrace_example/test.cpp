#include <stdio.h>
#include <stdlib.h>
#include "backtrace.h"

int main(int argc, char **argv)
{
    int a = 1;
    int b = 0;

    set_signal_handler();

    return a / b;
}
