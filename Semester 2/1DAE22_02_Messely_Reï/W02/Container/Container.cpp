// Container - 1DAE22 Messely Reï

#include "pch.h"
#include <iostream>
#include "Container.h"

int main()
{
    std::cout << "Hello World!\n";
}

Container::Container(int capacity)
    :m_Size{0}
    ,m_Capacity{capacity}
    ,m_pElement{nullptr}
{
}

Container::~Container()
{
    delete[] m_pElement;
    m_pElement = nullptr;
}

int Container::Size()
{
    return m_Size;
}

int Container::Capacity()
{
    return m_Capacity;
}

int Container::Get(int index)
{
    if ((index > -1) && (index < m_Size)) return m_pElement[index];
    return 0;
}

void Container::Set(int index, int newvalue)
{
    if ((index > -1) && (index < m_Size))
    {
        m_pElement[index] = newvalue;
    }
}

void Container::Pushback(int element)
{
    if (m_Size == m_Capacity) Reserve(m_Capacity * 2);
    m_pElement[m_Size + 1] = element;
}

void Container::Reserve(int newCapacity)
{
    int* temp{ new int[newCapacity] };

    for (int i{ 0 }; i < m_Size; ++i)
    {
        temp[i] = m_pElement[i];
    }
    delete[] m_pElement;
    m_pElement = temp;

    temp = nullptr;
}
