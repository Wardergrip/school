#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> g_ValidOperations{ "+","-","*","/","**" };

void InvalidParametersMsg();
void InvalidOperation();
bool IsNumber(const std::string& string);

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        InvalidParametersMsg();
        return 0;
    }
    std::string operation{argv[1]};
    bool isValid{false};
    int operationIdx{ 0 };
    for (int i{0};i<g_ValidOperations.size();++i)
    {
        if (operation == g_ValidOperations[i])
        {
            isValid = true;
            operationIdx = i;
            break;
        }
    }
    if (!isValid)
    {
        InvalidOperation();
        return 0;
    }

    std::string strNumberOne{ argv[2] }, strNumberTwo{ argv[3] };
    if (IsNumber(strNumberOne) && IsNumber(strNumberTwo)) 
    {
        int numberOne{std::stoi(strNumberOne)},numberTwo{std::stoi(strNumberTwo)};
        std::cout << "The result is ";
        if (g_ValidOperations[operationIdx] == "+")
        {
            std::cout << (numberOne + numberTwo);
        }
        else if (g_ValidOperations[operationIdx] == "-")
        {
            std::cout << (numberOne - numberTwo);
        }
        else if (g_ValidOperations[operationIdx] == "*")
        {
            std::cout << (numberOne * numberTwo);
        }
        else if (g_ValidOperations[operationIdx] == "/")
        {
            if (numberTwo == 0)
            {
                std::cout << "inf";
            }
            else 
            {
                std::cout << (numberOne / numberTwo);
                if ((numberOne % numberTwo) != 0)
                { 
                    std::cout << " with rest " << (numberOne % numberTwo);
                }
            }
        }
        else if (g_ValidOperations[operationIdx] == "**")
        {
            std::cout << std::pow(numberOne, numberTwo);
        }
        std::cout << ".\n";
    }
    else 
    {
        InvalidParametersMsg();
        return 0;
    }

    return 0;
}

void InvalidParametersMsg()
{
    std::cout << "The parameters are invalid. The required parameters are: operation firstNumber secondNumber\n";
}

void InvalidOperation()
{
    std::cout << "The operation you entered is not valid. Please make sure the input is the symbol of the operation.\n";
    std::cout << "Valid operations are: ";

    for (auto str : g_ValidOperations)
    {
        std::cout << str << " ";
    }

    std::cout << '\n';
}

bool IsNumber(const std::string& string)
{
    for (auto str : string)
    {
        if (std::isdigit(str) == 0)
        {
            return false;
        }
    }
    return true;
}