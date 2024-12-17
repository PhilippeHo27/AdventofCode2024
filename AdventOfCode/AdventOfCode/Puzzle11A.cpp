#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;

namespace Puzzle11A
{
	auto ReadInput(const std::filesystem::path& inputFile)
	{
		auto input = ReadAllLinesInFile(inputFile);

		return input;
	}

	void PrintSolution(const std::filesystem::path& inputFile, bool shouldRender)
	{
		//auto input = ReadInput(inputFile);
		auto grid = ReadAllLinesInFileAsGrid(inputFile);

		std::cout << grid << std::endl;
	}
} // namespace Puzzle11A