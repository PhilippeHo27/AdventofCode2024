#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;

namespace Puzzle09B
{
	auto ReadInput(const std::filesystem::path& inputFile)
	{
		return ReadAllLinesInFile(inputFile);
	}

	void PrintSolution(const std::filesystem::path& inputFile, bool shouldRender)
	{
		auto input = ReadInput(inputFile);
		std::vector<int> result;
		std::vector<std::pair<int, int>> pairs; // (count, number) pairs
		int currentNumber = 0;

		for (size_t i = 0; i < input[0].length(); i += 2)
		{
			int repeatCount = input[0][i] - '0';
			if (repeatCount > 0)
			{
				pairs.push_back({ currentNumber, repeatCount });
				for (int j = 0; j < repeatCount; j++)
				{
					result.push_back(currentNumber);
				}
			}

			if (i + 1 < input[0].length())
			{
				int dotCount = input[0][i + 1] - '0';
				if (dotCount > 0)
				{
					for (int j = 0; j < dotCount; j++)
					{
						result.push_back(-1);
					}
				}
			}
			currentNumber++;
		}
		std::sort(pairs.rbegin(), pairs.rend());

		for (const auto& num : result)
		{
			if (num == -1)
			{
				std::cout << '.';
			}
			else
			{
				std::cout << num;
			}
		}
		std::cout << "\nSize: " << result.size() << std::endl;

		// Print all pairs
		for (const auto& [number, count] : pairs)
		{
			std::cout << "Number: " << number << ", Count: " << count << "\n";
		}
	}
} // namespace Puzzle09B
