#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;
namespace Puzzle09A
{
	auto ReadInput(const std::filesystem::path& inputFile)
	{
		return ReadAllLinesInFile(inputFile);
	}

	void PrintSolution(const std::filesystem::path& inputFile, bool shouldRender)
	{
		auto input = ReadInput(inputFile);
		std::vector<int> result;
		int currentNumber = 0;

		for (size_t i = 0; i < input[0].length(); i += 2)
		{
			int repeatCount = input[0][i] - '0';
			for (int j = 0; j < repeatCount; j++)
			{
				result.push_back(currentNumber);
			}

			if (i + 1 < input[0].length())
			{
				int dotCount = input[0][i + 1] - '0';
				for (int j = 0; j < dotCount; j++)
				{
					result.push_back(-1);
				}
			}
			currentNumber++;
		}

		// Debug before swapping
		//std::cout << "Before swapping:\n";
		//for (const auto& num : result)
		//{
		//	if (num == -1)
		//	{
		//		std::cout << '.';
		//	}
		//	else
		//	{
		//		std::cout << num;
		//	}
		//}
		//std::cout << "\nSize: " << result.size() << std::endl;

		for (size_t i = 0; i < result.size(); i++)
		{
			if (result[i] == -1)
			{
				auto j = result.size() - 1;
				while (j > i && result[j] == -1)
				{
					j--;
				}

				if (j > i)
				{
					std::swap(result[i], result[j]);
				}
				else
				{
					break;
				}
			}
		}

		// Debug output after swapping
		//std::cout << "\nAfter swapping:\n";
		//for (const auto& num : result)
		//{
		//	if (num == -1)
		//	{
		//		std::cout << '.';
		//	}
		//	else
		//	{
		//		std::cout << num;
		//	}
		//}
		//std::cout << "\nSize: " << result.size() << std::endl;

		int64_t acc = 0;
		for (int64_t i = 0; i < static_cast<int64_t>(result.size()); ++i)
		{
			if (result[i] != -1)
			{
				acc += i * result[i];
			}
		}

		std::cout << "Final result: " << acc << std::endl;
	}
} // namespace Puzzle09A