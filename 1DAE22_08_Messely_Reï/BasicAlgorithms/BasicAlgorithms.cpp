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
    std::cout << std::endl;
    TestMinMax();
    TestSwap();
    TestShuffle();
    TestBubbleSort();
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
void BubbleSort(int* pArray, int size)
{
    for (int j{ 0 }; j < size; j++)
    {
        int n{ size - j };
        for (int i{ 0 }; i < n; i++)
        {
            if (i + 1 == size);
            else if (pArray[i] > pArray[i + 1]) Swap(pArray, size, i+1, i);
        }
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
    std::cout << "\nLowest value in this array is: " << MinElement(arr1, arr1Size) << "\n";
    std::cout << "Highest value in this array is: " << MaxElement(arr1, arr1Size) << "\n";
    std::cout << std::endl;
    for (int i{ 0 }; i < arr2Size; i++)
    {
        std::cout << arr2[i] << " ";
    }
    std::cout << "\nLowest value in this array is: " << MinElement(arr2, arr2Size) << "\n";
    std::cout << "Highest value in this array is: " << MaxElement(arr2, arr2Size) << "\n";
}
void TestSwap()
{
    std::cout << "\n== Test of Swap function ==\n";
    std::cout << "Before swapping:\n";
    for (int i{ 0 }; i < arr1Size; i++)
    {
        std::cout << arr1[i] << " ";
    }
    Swap(arr1, arr1Size, 1, 4);
    std::cout << "\nAfter swapping the second and the fifth element:\n";
    for (int i{ 0 }; i < arr1Size; i++)
    {
        std::cout << arr1[i] << " ";
    }
    std::cout << "\nBefore swapping:\n";
    for (int i{ 0 }; i < arr2Size; i++)
    {
        std::cout << arr2[i] << " ";
    }
    Swap(arr2, arr2Size, 1, 0);
    std::cout << "\nAfter swapping the second and the first element:\n";
    for (int i{ 0 }; i < arr2Size; i++)
    {
        std::cout << arr2[i] << " ";
    }
    std::cout << std::endl;
}
void TestShuffle()
{
    std::cout << "\n== Test of Shuffle function ==\n";
    std::cout << "Before shuffling:\n";
    for (int i{ 0 }; i < arr1Size; i++)
    {
        std::cout << arr1[i] << " ";
    }
    Shuffle(arr1, arr1Size, 4);
    std::cout << "\nAfter shuffling 4 times:\n";
    for (int i{ 0 }; i < arr1Size; i++)
    {
        std::cout << arr1[i] << " ";
    }
    std::cout << "\nBefore shuffling:\n";
    for (int i{ 0 }; i < arr2Size; i++)
    {
        std::cout << arr2[i] << " ";
    }
    Shuffle(arr2, arr2Size, 40);
    std::cout << "\nAfter shuffling 40 times:\n";
    for (int i{ 0 }; i < arr2Size; i++)
    {
        std::cout << arr2[i] << " ";
    }
    std::cout << std::endl;

}
void TestBubbleSort()
{
    std::cout << "\n== Test of BubbleSort function ==\n";
    std::cout << "Before sorting:\n";
    for (int i{ 0 }; i < arr1Size; i++)
    {
        std::cout << arr1[i] << " ";
    }
    BubbleSort(arr1, arr1Size);
    std::cout << "\nAfter Sorting:\n";
    for (int i{ 0 }; i < arr1Size; i++)
    {
        std::cout << arr1[i] << " ";
    }
    std::cout << std::endl;
}