#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace std::literals::chrono_literals;
using namespace Utilities;

namespace Puzzle03B
{
	auto ReadInput(const std::filesystem::path& inputFile)
	{
		auto input = ReadAllLinesInFile(inputFile);

		return input;
	}

	void PrintSolution(const std::filesystem::path& inputFile, bool shouldRender)
	{
		auto input = ReadInput(inputFile);
		int answer = 0;
		bool shouldMultiply = true;

		std::regex pattern("don't()|do()|mul\\((\\d+),(\\d+)\\)");
		std::smatch matches;

		for (auto output : input)
		{
			std::string::const_iterator searchStart(output.cbegin());
			while (std::regex_search(searchStart, output.cend(), matches, pattern))
			{
				if (matches[1].matched)
				{
					shouldMultiply = false;
				}
				else if (matches[2].matched)
				{
					shouldMultiply = true;
				}
				else if (shouldMultiply)
				{
					int first_num = std::stoi(matches[3]);
					int second_num = std::stoi(matches[4]);
					answer += first_num * second_num;
					//std::cout << first_num << " and " << second_num << std::endl;
				}
				searchStart = matches.suffix().first;
			}
		}
		std::cout << answer << std::endl;
	}
} // namespace Puzzle03B