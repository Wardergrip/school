// +----------------------+
// | Messely, Reï, 1DAE22 |
// +----------------------+

#include "pch.h"
#include <iostream>

int Count(int* pArray, int size, int value);
int MinElement(int* pArray, int size);
int MaxElement(int* pArray, int size);
void Swap(int* pArray, int size, int idx1, int idx2);
void Shuffle(int* pArray, int size, int swaps);
void BubbleSort(int* pArray, int size);

void TestCount();
void TestMinMax();
void TestSwap();
void TestShuffle();
void TestBubbleSort();

const int arr1Size{ 10 };
const int arr2Size{ 5 };
int arr1[arr1Size]{ 10,2,-5,10,4,7,0,-9,-1,23 };
int arr2[arr2Size]{ 40,-8,6,3,-8 };

int main()
{
    TestCount();
}

int Count(int* pArray, int size, int value)
{
    int count{0};
    for (int i{ 0 }; i < size; i++)
    {
        if (pArray[i] == value) count++;
    }
    return count;
}
int MinElement(int* pArray, int size)
{
    int min{ pArray[0] };
    for (int i{ 0 }; i < size; i++)
    {
        if (pArray[i] < min) min = pArray[i];
    }
    return min;
}
int MaxElement(int* pArray, int size)
{
    int max{ pArray[0] };
    for (int i{ 0 }; i < size; i++)
    {
        if (pArray[i] > max) max = pArray[i];
    }
    return max;
}
void Swap(int* pArray, int size, int idx1, int idx2)
{
    int a{ pArray[idx1] };
    pArray[idx1] = pArray[idx2];
    pArray[idx2] = a;
}
void Shuffle(int* pArray, int size, int swaps)
{
    for (int i{ 0 }; i < swaps; i++)
    {
        int idx1{ rand() % size };
        int idx2{ rand() % size };
        int a{ pArray[idx1] };
        pArray[idx1] = pArray[idx2];
        pArray[idx2] = a;
    }
}

void TestCount()
{
    std::cout << "== Test of Count function ==\n";
    for (int i{ 0 }; i < arr1Size; i++)
    {
        std::cout << arr1[i] << " ";
    }
    std::cout << "\n" << "10 occurs " << Count(arr1, arr1Size, 10) << " time(s) in this array.\n\n";
    for (int i{ 0 }; i < arr2Size; i++)
    {
        std::cout << arr2[i] << " ";
    }
    std::cout << "\n" << "10 occurs " << Count(arr2, arr2Size, 10) << " time(s) in this array.\n";
}
void TestMinMax()
{
    std::cout << "== Test of MinElement and MaxElement functions ==\n";
    for (int i{ 0 }; i < arr1Size; i++)
    {
        std::cout << arr1[i] << " ";
    }
}
void TestSwap()
{

}
void TestShuffle()
{

}
void TestBubbleSort()
{

}