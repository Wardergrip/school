#include "pch.h"
#include <iostream>

#include "Float2.h"

int main()
{
    Float2 f1{ 10,20 }, f2{5,7},f3{0,0};
    f3 = f1 + f2;

    std::cout << "f1 = " << f1 << " f2 = " << f2 << '\n';
}