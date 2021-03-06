#pragma once
#include <vector>
class XMLProcessor final
{
public:
	enum class PBelement {time,score,lives,coins,bigCoins};

	XMLProcessor() = delete;
	XMLProcessor(const XMLProcessor& x) = delete;
	XMLProcessor& operator=(const XMLProcessor& x) = delete;
	XMLProcessor(XMLProcessor&& x) = delete;
	XMLProcessor& operator=(XMLProcessor&& x) = delete;
	~XMLProcessor() = delete;

	// Returns entire file in string format
	static bool ReadFile(std::string& output);
	// Returns a vector with all personalBest values. For an empty vector, use PBelement enum
	// for easy access.
	static bool ReadValues(std::vector<int>& output);
	// Save XML to a file
	static void SaveToFile(const std::string& XML);
	// Get an int value out of a string
	static int GetAttributeValue(const std::string& attrName, const std::string& element);
	// Compare if the new input is better than the saved values. If a new personal best is noticed
	// the file is overwritten.
	static bool SavePersonalBest(const std::string& XML);
	// Will clear the file and write a default file with all values being 0
	static void WipeAndCleanSave();

	static void ChangeFilePath(const std::string& filepath);
	
	static void DisplayPersonalBest();

	static const std::string& GetFilePath();

private:
	static std::string m_FilePath;
};

