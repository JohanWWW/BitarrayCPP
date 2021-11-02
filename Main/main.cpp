#include <iostream>
#include "../BitArray/bitarray.h"
#include "../BitArray/bitarray.cpp"

int main()
{
    bitarray bits {0,0,0,1,1,0,0,0};

    bits[0] = 1;

    for (bool bit : bits)
        std::cout << bit;
    std::cout << std::endl;

    return 0;
}