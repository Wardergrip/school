#pragma once
class json;
class JsonFilehelper
{
public:
	static int SaveJSON(const std::string& jsonDump, const std::string& filePath);
	static int SaveJSON(const json& json, const std::string& filePath);
};

