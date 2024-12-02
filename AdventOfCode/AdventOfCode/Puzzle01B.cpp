#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;

namespace Puzzle01B
{
	auto ReadInput(const std::filesystem::path& inputFile)
	{
		auto input = ReadAllLinesInFile(inputFile);

		return input;
	}

	void PrintSolution(const std::filesystem::path& inputFile, bool shouldRender)
	{
		auto input = ReadInput(inputFile);

		std::vector<int> firstRow;
		std::vector<int> secondRow;

		for (std::string output : input)
		{
			std::string first;
			std::string second;

			std::istringstream iss(output);
			iss >> first >> second;

			firstRow.push_back(stoi(first));
			secondRow.push_back(stoi(second));
		}

		int multiplier = 0;
		int total = 0;

		for (int i = 0; i < firstRow.size(); i++)
		{
			for (int j = 0; j < secondRow.size(); j++)
			{
				if (firstRow[i] == secondRow[j])
				{
					multiplier++;
				}
			}
			total += firstRow[i] * multiplier;
			multiplier = 0;
		}

		std::cout << total;
	}
} // namespace Puzzle01B