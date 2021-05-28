#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <filesystem>

class Options
{
public:
	Options(int argc, char** argv);
	
	bool Parse();
	void PrintHelp();
	bool IsPacking() { return needPack; }
	std::string GetInputFile() { return inputFile; }
	std::string GetOutputFile() { return outputFile; }

private:
	int numerOfArguments;
	char** arguments;
	bool needPack{ false };
	std::string inputFile{};
	std::string outputFile{};
};

extern std::unique_ptr<Options> gOptions;
