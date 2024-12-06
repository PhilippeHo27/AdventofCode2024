#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;

namespace Puzzle05A
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

	void ProcessLine(const std::string& line, std::vector<std::pair<int,int>>& setOne, std::vector<std::vector<int>>& setTwo)
	{
		if (ContainsDelimiter(line, '|'))
		{
			auto numbers = SplitLimiterSeparatedInt32s(line, "|");
			setOne.emplace_back(numbers[0], numbers[1]);

		}
		else if (ContainsDelimiter(line, ','))
		{
			auto numbers = SplitCommaSeparatedInt32s(line);
			setTwo.push_back(numbers);

		}
	}

	void PrintSolution(const std::filesystem::path& inputFile, bool shouldRender)
	{
		auto input = ReadInput(inputFile);
		std::vector<std::pair<int, int>> setOne;
		std::vector<std::vector<int>> setTwo;
		int acc = 0;

		// Reads the input file and splits into two containers
		for (const auto& line : input)
		{
			ProcessLine(line, setOne, setTwo);
		}

		// Initialize a flag to see what to remove later
		std::vector<bool> shouldDelete(setTwo.size(), false);

		// For previous sanity checks :X
		std::sort(setOne.begin(), setOne.end());


		//iterate through the container of the numbers to prune
		for (size_t i = 0; i < setTwo.size(); i++)
		{
			auto& lists = setTwo[i];

			//iterate through the numbers, if a number is the same as the 1st pair of setOne, see if on the left there's a matching 2nd pair of setOne
			// if so, set that line for removal
			for (size_t j = 0; j < lists.size(); j++)
			{
				int number = lists[j];
				auto matches = setOne 
					| std::views::filter([number](const auto& p) { return p.first == number; })
				    | std::views::transform([](const auto& p) { return p.second; });

				std::vector<int> matchValues(matches.begin(), matches.end());

				for (size_t index = 0; index < j; index++)
				{
					if (std::find(matchValues.begin(), matchValues.end(), lists[index]) != matchValues.end())
					{
						shouldDelete[i] = true;
						break;
					}
				}
			}
		}


		// prune the lines that were set for deletion with the boolean flag
		std::vector<std::vector<int>> temp;
		for (size_t i = 0; i < setTwo.size(); i++)
		{
			if (!shouldDelete[i])
			{
				temp.push_back(setTwo[i]);
			}
		}
		setTwo = std::move(temp);

		// add the middle values of the remaining set
		for (auto a : setTwo)
		{
			auto middleValue = a.begin() +(a.size()/2);
			//std::cout << *middleValue << std::endl;
			acc += *middleValue;
		}

		std::cout << acc << std::endl;
	}
} // namespace Puzzle05A
