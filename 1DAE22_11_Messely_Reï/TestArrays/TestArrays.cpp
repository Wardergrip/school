#include "pch.h"
#include <iostream>
#include "Time.h"

const int g_AmountOfTimers{ 4 };
Time* g_pTimers[g_AmountOfTimers]{};

void InitTimers();
void ModifyTimers();
void DeleteTimers();

int main()
{
    InitTimers();
    ModifyTimers();
    DeleteTimers();
}

void InitTimers()
{
    for (int i{ 0 }; i < g_AmountOfTimers; ++i)
    {
        g_pTimers[i] = new Time{unsigned int(rand())};
    }
}
void ModifyTimers()
{
    for (int i{ 0 }; i < g_AmountOfTimers; ++i)
    {
        g_pTimers[i]->AddSeconds(abs(rand()));
    }
}
void DeleteTimers()
{
    for (int i{ 0 }; i < g_AmountOfTimers; ++i)
    {
        delete g_pTimers[i];
        g_pTimers[i] = nullptr;
    }
}