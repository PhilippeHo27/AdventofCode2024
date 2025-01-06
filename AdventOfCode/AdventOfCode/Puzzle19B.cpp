#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;

namespace Puzzle19B
{
	auto ReadInput(const std::filesystem::path& inputFile)
	{
		auto input = ReadAllLinesInFile(inputFile);

		return input;
	}

	bool ContainsDelimiter(std::string_view input, char delimiter)
	{
		return input.find(delimiter) != std::string::npos;
	}

	size_t CountWaysMakeWord(const std::string& design, const std::vector<std::string>& towels)
	{
		std::vector<size_t> dp(design.length() + 1, 0);
		dp[0] = 1;

		for (size_t i = 1; i <= design.length(); i++)
		{
			for (const auto& towel : towels)
			{
				if (i >= towel.length())
				{
					if (design.substr(i - towel.length(), towel.length()) == towel)
					{
						dp[i] += dp[i - towel.length()];
					}
				}
			}
		}
		return dp[design.length()];
	}


	void PrintSolution(const std::filesystem::path& inputFile, bool shouldRender)
	{
		auto input = ReadAllLinesInFile(inputFile);

		std::vector<std::string> towels;
		std::vector<std::string> designs;

		size_t acc = -1;

		for (auto i : input)
		{
			if (ContainsDelimiter(i, ','))
			{
				towels = SplitString(i, ", ");
			}
			else
			{
				designs.push_back(i);
			}
		}

		
		for (auto design : designs)
		{
			acc += CountWaysMakeWord(design, towels);
		}

		std::cout << acc << std::endl;
	}
} // namespace Puzzle19B