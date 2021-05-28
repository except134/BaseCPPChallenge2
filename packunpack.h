#pragma once

#include "options.h"

class PackUnpack
{
public:
	bool Encode(const std::string& inf, const std::string& outf);
	bool Decode(const std::string& inf, const std::string& outf);

private:
	bool IsFileExists(const std::string& var);
	bool CryptDecrypt(const std::string& inf, const std::string& outf, const std::string& cryptKey);
};

