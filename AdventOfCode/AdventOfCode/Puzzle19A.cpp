#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;

namespace Puzzle19A
{
	//auto ReadInput(const std::filesystem::path& inputFile)
	//{
	//	auto input = ReadAllLinesInFile(inputFile);
	//	return input;
	//}	

	bool ContainsDelimiter(std::string_view input, char delimiter)
	{
		return input.find(delimiter) != std::string::npos;
	}

	bool CanMakeWord(const std::string& design, const std::vector<std::string>& towels)
	{
		std::vector<bool> dp(design.length() + 1, false);
		dp[0] = true;
		for (size_t i = 1; i <= design.length(); i++)
		{
			for (const auto& towel : towels)
			{
				if (i >= towel.length())
				{
					if (design.substr(i - towel.length(), towel.length()) == towel && dp[i - towel.length()])
					{
						dp[i] = true;
						break;
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

		int acc = -1;

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

		//for (auto t : towels)
		//{
		//	std::cout << t << std::endl;
		//}
		//for (auto d : designs)
		//{
		//	std::cout << d << std::endl;
		//}

		//for (const auto& design : designs)
		//{
		//	std::cout << "'" << design << "' is " << (CanMakeWord(design, towels) ? "possible" : "impossible") << " to make\n";
		//}


		std::cout << acc << std::endl;
	}
} // namespace Puzzle19A