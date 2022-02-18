// Container - 1DAE22 Messely Reï

#include "pch.h"
#include <iostream>
#include "Container.h"

// READ ME PLEASE
// 
// After starting with the Smiley excercise, I realised I didn't solve
// the exercise as requested. I pretty much did all requested things
// in my own way.

int main()
{
    //std::cout << "Hello World!\n";
    Container* pCont{ new Container };
    
    for (int i{ 0 }; i < 10; ++i)
    {
        pCont->Pushback(10+i);
    }
    pCont->Info();
    pCont->Pushback(69);
    pCont->Info();
    std::cin.get();
    delete pCont;
    pCont = nullptr;
}

Container::Container(int capacity)
    :m_Size{0}
    ,m_Capacity{capacity}
    ,m_pElement{ new int[m_Capacity] }
{
}

Container::~Container()
{
    delete[] m_pElement;
    m_pElement = nullptr;
}

int Container::Size() const
{
    return m_Size;
}

int Container::Capacity() const
{
    return m_Capacity;
}

int Container::Get(int index) const
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
    if (m_Size == m_Capacity) Reserve(m_Capacity + 10);
    m_pElement[m_Size] = element;
    ++m_Size;
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
    m_Capacity = newCapacity;
}
void Container::Info(const std::string& preface) const
{
    std::cout << preface;
    if (preface != "") std::cout << " ";
    std::cout << "INFO: \n m_Capacity: " << m_Capacity << " m_Size: " << m_Size << '\n';
    std::cout << "All stored numbers: \n";
    for (int i{ 0 }; i < m_Size; ++i)
    {
        std::cout << m_pElement[i] << ' ';
    }
    std::cout << '\n';
    std::cout << "Capacity view: \n";
    for (int i{ 0 }; i < m_Capacity; ++i)
    {
        std::cout << m_pElement[i] << ' ';
    }
    std::cout << "\n\n";
}
