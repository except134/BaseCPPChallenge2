#include "options.h"

std::unique_ptr<Options> gOptions;

Options::Options(int argc, char** argv)
{
	numerOfArguments = argc;
	arguments = argv;
}

void Options::PrintHelp()
{
	std::cout << "Usage:" << std::endl;
	std::cout << "\t" << std::filesystem::path(arguments[0]).filename().string() << " [option] <inputfile> <outputfile>" << std::endl << std::endl;
	std::cout << "Where option:" << std::endl;
	std::cout << "\t-p, -P\tPack file" << std::endl;
	std::cout << "\t-u, -U\tUnpack file" << std::endl;
}

bool Options::Parse()
{
	if (numerOfArguments < 4) {
		PrintHelp();
		return false;
	}

	switch (arguments[1][0]) {
		case '-':
		case '//':
			switch (arguments[1][1]) {
				case 'p':
				case 'P':
					needPack = true;
				break;
				case 'u':
				case 'U':
					needPack = false;
				break;
				default: {
					std::cout << "Error: Unknown option." << std::endl << std::endl;
					PrintHelp();
					return false;
				}
			}
		break;
	}

	inputFile = arguments[2];
	outputFile = arguments[3];

	return true;
}
