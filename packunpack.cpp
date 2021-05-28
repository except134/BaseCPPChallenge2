#include "packunpack.h"
#include "random.h"
#include <fstream>

bool PackUnpack::IsFileExists(const std::string& var)
{
	return std::filesystem::exists(var);
}

bool PackUnpack::CryptDecrypt(const std::string& inf, const std::string& outf, const std::string& cryptKey)
{
	if (!IsFileExists(inf)) {
		std::cout << "Error: Input file \"" << inf << "\" not exists." << std::endl;
		return false;
	}

	if (IsFileExists(outf)) {
		std::cout << "Warning: output file \"" << outf << "\" exists. Overwrite it? (Y/N)" << std::endl;
		char yn;
		std::cin >> yn;
		if (yn != 'y' && yn != 'Y')
			return false;
	}

	size_t keyLength = cryptKey.size();

	FILE* infile = nullptr;
	FILE* outfile = nullptr;

	errno_t errin = fopen_s(&infile, inf.c_str(), "rb");
	size_t infilelength = std::filesystem::file_size(inf);

	errno_t errout = fopen_s(&outfile, outf.c_str(), "wb");

	char* buf = new char[infilelength];

	if (!errin) {
		fread_s(buf, infilelength, 1, infilelength, infile);
	}
	else {
		delete[] buf;
		std::cout << "Error: Something wrong with input file \"" << inf << "\"" << std::endl;
		return false;
	}

	std::string outbuf{};

	for (int i = 0; i < infilelength; i++) {
		outbuf += buf[i] ^ cryptKey[i % keyLength];
	}

	delete[] buf;

	if (!errout) {
		fwrite(outbuf.c_str(), infilelength, 1, outfile);
	}
	else {
		std::cout << "Error: Something wrong with output file \"" << outf << "\"" << std::endl;
		return false;
	}

	fclose(infile);
	fclose(outfile);

	return true;
}

bool PackUnpack::Encode(const std::string& inf, const std::string& outf)
{
	std::string cryptKey = GetRandomKey(10);
	std::cout << "Using key: " << cryptKey << std::endl;

	bool ret = CryptDecrypt(inf, outf, cryptKey);

	std::ofstream outkeyfile(outf + ".key");
	if (!outkeyfile.bad()) {
		outkeyfile << cryptKey;
	}
	outkeyfile.close();

	return ret;
}

bool PackUnpack::Decode(const std::string& inf, const std::string& outf)
{
	std::stringstream cryptKeyStream;

	std::ifstream inkeyfile(inf + ".key");
	if (!inkeyfile.bad()) {
		cryptKeyStream << inkeyfile.rdbuf();
	}
	inkeyfile.close();

	std::string cryptKey = cryptKeyStream.str();
	std::cout << "Using key: " << cryptKey << std::endl;

	return CryptDecrypt(inf, outf, cryptKey);
}


