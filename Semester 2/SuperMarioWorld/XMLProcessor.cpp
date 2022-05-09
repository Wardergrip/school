#include "pch.h"
#include "XMLProcessor.h"
#include <fstream>

std::string XMLProcessor::m_FilePath{ "" };

int XMLProcessor::GetAttributeValue(const std::string& attrName, const std::string& element)
{
	std::string attribute;
	std::string buffer;

	bool foundAttr{ false };
	int j{ 0 };
	for (int i{ 0 }; i < element.size(); ++i)
	{
		if (!attribute.empty())
		{
			return std::stoi(attribute);
		}
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

	return std::stoi(attribute);
}

bool XMLProcessor::SavePersonalBest(const std::string& XML)
{
	using PB = PBelement;
	std::vector<int> values{};
	ReadValues(values);
	int currentScore{ GetAttributeValue("score", XML) };
	if (currentScore > values[int(PB::score)])
	{
		SaveToFile(XML);
		return true;
	}
	else if (currentScore == values[int(PB::score)])
	{
		if (GetAttributeValue("time", XML) < values[int(PB::time)])
		{
			SaveToFile(XML);
			return true;
		}
	}
	return false;
}

void XMLProcessor::WipeAndCleanSave()
{
	std::ofstream outputFile{ m_FilePath };
	std::string output;
	std::string helper{ '\"' };
	output += "<personalbest\n";
	output += '\t'; // Horizontal tab
	output += "time=" + helper + std::to_string(0) + helper + '\n';
	output += '\t'; // Horizontal tab
	output += "score=" + helper + std::to_string(0) + helper + '\n';
	output += '\t'; // Horizontal tab
	output += "lives=" + helper + std::to_string(0) + helper + '\n';
	output += '\t'; // Horizontal tab
	output += "coins=" + helper + std::to_string(0) + helper + '\n';
	output += '\t'; // Horizontal tab
	output += "bigCoins=" + helper + std::to_string(0) + helper + '\n';
	output += "/>";
	outputFile.write(output.c_str(), output.length());
}

void XMLProcessor::ChangeFilePath(const std::string& filepath)
{
	m_FilePath = filepath;
}

bool XMLProcessor::ReadFile(std::string& output)
{
	std::ifstream file{ m_FilePath };
	if (file.fail()) return false;
	file.seekg(0, file.end);
	int length = int(file.tellg());
	file.seekg(0, file.beg);

	char* buffer = new char[length];
	file.read(buffer, length);

	for (int i{ 0 }; i < length; ++i)
	{
		output += buffer[i];
	}

	delete[] buffer;
	buffer = nullptr;

	return true;
}

bool XMLProcessor::ReadValues(std::vector<int>& output)
{
	std::ifstream file{ m_FilePath };
	if (file.fail()) return false;
	file.seekg(0, file.end);
	int length = int(file.tellg());
	file.seekg(0, file.beg);

	char* buffer = new char[length];
	file.read(buffer, length);
	std::string strBuffer{ buffer };
	output.push_back(GetAttributeValue("time", strBuffer));
	output.push_back(GetAttributeValue("score", strBuffer));
	output.push_back(GetAttributeValue("lives", strBuffer));
	output.push_back(GetAttributeValue("coins", strBuffer));
	output.push_back(GetAttributeValue("bigCoins", strBuffer));

	delete[] buffer;
	buffer = nullptr;

	return true;
}

void XMLProcessor::SaveToFile(const std::string& XML)
{
	std::ofstream outputFile{ m_FilePath };
	outputFile.write(XML.c_str(), XML.length());
}
