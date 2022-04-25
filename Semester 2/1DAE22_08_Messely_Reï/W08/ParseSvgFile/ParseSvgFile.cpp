#include "pch.h"
#include <iostream>
#include <fstream>

std::string GetAttributeValue(const std::string& attrName, const std::string& element);

int main()
{
    std::ifstream inputFile{ "Resources/Level.svg" };
    if (inputFile.fail()) throw "Wrong filepath";

	inputFile.seekg(0, inputFile.end);
	int length = int(inputFile.tellg());
	inputFile.seekg(0, inputFile.beg);

	char* buffer = new char[length];

	inputFile.read(buffer, length);
	std::string strBuffer;
	for (int i{ 0 }; i < length; ++i) strBuffer += buffer[i];

	size_t place = strBuffer.find("<path");
	std::string parsingBuffer;
	for (size_t i{ place }; i < strBuffer.length(); ++i) parsingBuffer += strBuffer[i];

	std::string atr = GetAttributeValue(" d=", parsingBuffer);

	for (int i{ 0 }; i < atr.length(); ++i)
	{
		if (atr[i] == ' ') std::cout << '\n';
		else if ((atr[i] >= ',' && atr[i] <= '9'))
		{
			std::cout << atr[i];
		}
		else
		{
			std::cout << '\n';
			std::cout << atr[i];
		}
	}

	delete[] buffer;
	buffer = nullptr;
}

std::string GetAttributeValue(const std::string& attrName, const std::string& element)
{
	std::string attribute;

	std::string buffer;

	bool foundAttr{ false };
	int j{ 0 };
	for (int i{ 0 }; i < element.size(); ++i)
	{
		if (!attribute.empty()) return attribute;
		if (!foundAttr)
		{
			if (element[i] == attrName[j])
			{
				buffer += element[i];
				++j;
				if (buffer.back() == '\"')
				{
					buffer.clear();
					j = 0;
				}
				if (buffer == attrName)
				{
					if (attrName == "Label")
					{
						if (element[i - buffer.size()] == 't') continue;
					}
					foundAttr = true;
					buffer.clear();
				}
			}
			else
			{
				buffer.clear();
				j = 0;
			}
		}
		if (!foundAttr) continue;
		// Found the start ->" "
		if (element[i] == '\"' || !buffer.empty())
		{
			if (buffer.empty()) ++i;
			if (element[i] == '\"')
			{
				attribute = buffer;
			}
			else buffer += element[i];
		}
	}

	return attribute;
}