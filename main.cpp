#include "packunpack.h"

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");

	gOptions = std::make_unique<Options>(argc, argv);

	if (!gOptions->Parse())
		return 1;

	PackUnpack pu;

	if (gOptions->IsPacking()) {
		std::cout << "Packing " << gOptions->GetInputFile() << " to " << gOptions->GetOutputFile() << std::endl;
		if (!pu.Encode(gOptions->GetInputFile(), gOptions->GetOutputFile())) {
			return 2;
		}
	}
	else {
		std::cout << "Unpacking " << gOptions->GetInputFile() << " to " << gOptions->GetOutputFile() << std::endl;
		if (!pu.Decode(gOptions->GetInputFile(), gOptions->GetOutputFile())) {
			return 3;
		}
	}

	return 0;
}

