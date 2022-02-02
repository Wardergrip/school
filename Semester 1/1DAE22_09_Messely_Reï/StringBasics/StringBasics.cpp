//
// 1DAE22 Messely, Reï
//

#include "pch.h"
#include <iostream>
#include <cstring>
#include <string>

std::string g_Gutenburg{"One morning, when Gregor Samsa woke from troubled dreams, he found himself transformed in his bed into a horrible vermin. He lay on his armour - like back,and if he lifted his head a little he could see his brown belly, slightly domedand divided by arches into stiff sections.The bedding was hardly able to cover itand seemed ready to slide off any moment.His many legs, pitifully thin compared with the size of the rest of him, waved about helplessly as he looked.\n"};
const char* g_pGutenburg = g_Gutenburg.c_str();

int main()
{
    std::cout << "~ Explore string class ~\n";
    std::cout << g_Gutenburg << std::endl;
    std::cout << "Length: " << g_Gutenburg.length() << " chars\n";
    std::cout << "Size: " << g_Gutenburg.size() << " bytes\n";
    std::cout << "Capacity: " << g_Gutenburg.capacity() << " bytes\n";

    for (int i{ 0 }; i < g_Gutenburg.length(); i++)
    {
        std::cout << g_pGutenburg[i] << '_';
    }

    // [] allows you to go out of range
    std::cout << "\nFirst char: " << g_Gutenburg[0] << "\nLast char: " << g_Gutenburg[g_Gutenburg.length() - 2];
    // .at will throw an exception at you if you go out of range
    std::cout << "\nFirst char: " << g_Gutenburg.at(0) << "\nLast char: " << g_Gutenburg.at(g_Gutenburg.length() - 2);

    std::cout << "\nThe string to search for in the above text? ";
    std::string input{};
    std::cin >> input;
    std::cout << "Occurances of '" << input << "' at:\n";
    std::size_t found{ g_Gutenburg.find(input) };
    while (found < g_Gutenburg.length())
    { 
        std::cout << found << " ";
        found = g_Gutenburg.find(input, found + 1);
    }
    std::cout << "\nIn reverse order:\n";
    found = g_Gutenburg.rfind(input);
    while (found < g_Gutenburg.length())
    {
        std::cout << found << " ";
        found = g_Gutenburg.rfind(input, found - 1);
    }
    std::cout << "\nThe word to replace by * in the above text? ";
    std::cin >> input;
    found = g_Gutenburg.find(input);
    while (found < g_Gutenburg.length())
    {
        std::string rplcmnt{};
        for (int i{ 0 }; i < input.length(); i++)
        {
            rplcmnt += "*";
        }
        g_Gutenburg.replace(found, input.length(), rplcmnt);
        found = g_Gutenburg.find(input, found + 1);
    }
    std::cout << g_Gutenburg << std::endl;
    std::cout << "The string you want to erase from the text? ";
    std::cin >> input;
    found = g_Gutenburg.find(input);
    while (found < g_Gutenburg.length())
    {
        g_Gutenburg.erase(found, input.length());
        found = g_Gutenburg.find(input, found + 1);
    }
    std::cout << g_Gutenburg << std::endl;
    std::cout << "Length: " << g_Gutenburg.length() << " chars\n";
    std::cout << "Size: " << g_Gutenburg.size() << " bytes\n";
    std::cout << "Capacity: " << g_Gutenburg.capacity() << " bytes\n";

}
