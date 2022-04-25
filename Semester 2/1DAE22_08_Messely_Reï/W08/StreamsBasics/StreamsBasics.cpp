#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>

void ReadSentence(std::istream& istream, std::string& sentence);

int main()
{
    std::ifstream quotesInput{ "Resources/SoftwareQuotesInput.txt" };
    if (quotesInput.fail()) throw "File failed";

    std::string fullInput;
    std::string input;

    quotesInput.seekg(0, quotesInput.end);
    int length = quotesInput.tellg();
    quotesInput.seekg(0, quotesInput.beg);

    char* buffer = new char[length];

    do
    {
        //std::getline(std::cin, input);
        quotesInput.getline(buffer, length);
        input = std::string(buffer);
        fullInput += input;
        if (fullInput.back() == '.') fullInput += '\n';
        else fullInput += ' ';
    } while (!quotesInput.eof());
    std::cout << fullInput;
    delete[] buffer;
    buffer = nullptr;

    std::ofstream outputFile{ "Resources/SoftwareQuotesOutput.txt" };
    outputFile.write(fullInput.c_str(),fullInput.length());

    std::string sentence;
    std::ifstream stream{ "Resources/SoftwareQuotesInput.txt"};

    //ReadSentence(stream, sentence);
    std::cout << sentence;
}

void ReadSentence(std::istream& istream, std::string& sentence)
{
    if (!istream) return;

    std::string fullInput;
    std::string input;

    istream.seekg(0, istream.end);
    int length = istream.tellg();
    istream.seekg(0, istream.beg);

    char* buffer = new char[length];

    do
    {
        //std::getline(std::cin, input);
        istream.getline(buffer, length);
        input = std::string(buffer);
        fullInput += input;
    } while (input.back() != '.');
    sentence = fullInput;
}