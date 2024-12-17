#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;

namespace Puzzle10A
{
	auto ReadInput(const std::filesystem::path& inputFile)
	{
		auto input = ReadAllLinesInFile(inputFile);

		return input;
	}

	void PrintSolution(const std::filesystem::path& inputFile, bool shouldRender)
	{
		auto grid = ReadAllLinesInFileAsGrid(inputFile);

		std::cout << grid << std::endl;

		auto starts = std::count(grid.begin(), grid.end(), '0');

		std::cout << starts << std::endl;

	}
} // namespace Puzzle10A