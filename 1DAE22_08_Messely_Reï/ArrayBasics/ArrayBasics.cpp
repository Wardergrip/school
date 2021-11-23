#include "pch.h"
#include <iostream>
#include "structs.h"

const int size{ 5 };
int arr1[size]{5,4,3,2,1};
int arr2[]{ 10,20,30,40,50 };
int arr3[size]{ 15,25 };

const int gridSize{ 20 };
Point2f grids[gridSize]{};

void PrintElements(int* pNumbers, int size);
void PrintElements(int* pNumbers, int startIdx, int endIdx);
int GetIndex(int rowIdx, int colIdx, int nrCols);

int main()
{
    std::cout << "Hello World!\n";
    std::cout << "First element: " << arr1[0] << '\n';
    std::cout << "Last element: " << arr1[4] << '\n';
    for (int i{ 0 }; i < size; i++)
    {
        std::cout << arr1[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "nr of bytes in array: " << sizeof(arr1) << std::endl;
    std::cout << "nr of bytes of element in array: " << sizeof(arr1[0]) << std::endl;
    std::cout << "Amount of elements in array: " << sizeof(arr1) / sizeof(arr1[0]) << std::endl;
    std::cout << '\n';
    PrintElements(arr1, size);
    std::cout << '\n';
    PrintElements(arr2, size);
    std::cout << '\n';
    PrintElements(arr3, 1, 3);
    std::cout << '\n';
    
    for (int i{ 0 }; i < gridSize; i++)
    {
        
    }
}

void PrintElements(int* pNumbers, int size) 
{
    for (int i{ 0 }; i < size; i++)
    {
        std::cout << pNumbers[i] << " ";
    }
}
void PrintElements(int* pNumbers, int startIdx, int endIdx)
{
    for (int i{ startIdx }; i < endIdx; i++)
    {
        std::cout << pNumbers[i] << " ";
    }
}

int GetIndex(int rowIdx, int colIdx, int nrCols)
{
    return (rowIdx * nrCols + colIdx);
}