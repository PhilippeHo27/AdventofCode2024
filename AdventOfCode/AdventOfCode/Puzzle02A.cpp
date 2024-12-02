#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace std::chrono_literals;
using namespace Utilities;

namespace Puzzle02A
{
	auto ReadInput(const std::filesystem::path& inputFile)
	{
		auto input = ReadAllLinesInFile(inputFile);

		return input;
	}

	void PrintSolution(const std::filesystem::path& inputFile, bool shouldRender)
	{
		auto input = ReadInput(inputFile);

		int counter = 0;
		int firstTrue = 0;
		int secondTrue = 0;
		for (std::string output : input)
		{
			auto values = ExtractInt32s(output);
			bool firstCondition = std::is_sorted(values.begin(), values.end(), std::less<>()) || std::is_sorted(values.begin(), values.end(), std::greater<>());
			bool secondCondition = true;
			for (int i = 1; i < values.size(); i++)
			{
				bool isDifferenceBetweenOneAndThree = 0 < abs((values[i] - values[i - 1])) && abs((values[i] - values[i - 1])) < 4;
				if (!isDifferenceBetweenOneAndThree)
				{
					secondCondition = false;
					break;
				}
			}
			//std::cout << secondCondition << std::endl;

			if (firstCondition)
			{
				firstTrue++;
			}

			if (secondCondition)
			{
				secondTrue++;
			}

			if (firstCondition && secondCondition)
			{
				counter++;
			}
		}
		//std::cout << firstTrue << std::endl;
		//std::cout << secondTrue << std::endl;
		std::cout << counter << " the answer " << std::endl;

	}
} // namespace Puzzle02A