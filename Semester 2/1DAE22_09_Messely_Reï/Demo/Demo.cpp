#include "pch.h"
#include <iostream>

template <typename T>
T Lerp(T min, T max, double alpha)
{
    return static_cast<T>((1 - alpha)* min + alpha * max);
}

int main()
{
    std::cout << "Hello World!\n";  
    for (double alpha = 0; alpha <= 1; alpha += 0.1)
    {
        double result = Lerp(3.1415, 6.2830, alpha);
        std::cout << result << '\n';
    }
}