#include "pch.h"
#include <iostream>
#include <map>
#include <string>

void print(const std::map<int, std::string>& mapMonths);

int main()
{
    std::map<int, std::string> months;

    months.insert(std::pair<int, std::string>{1, "January"});

    months.insert(std::make_pair<int, std::string>(2, "February"));

    print(months);

    months[3] = "March";

    print(months);

}

void print(const std::map<int, std::string>& mapMonths)
{
    std::cout << "Size = " << mapMonths.size() << '\n';
    for (const std::pair<int, std::string>& pair : mapMonths)
    {
        std::cout << "Key = " << pair.first << " Value = " << pair.second << '\n';
    }

}