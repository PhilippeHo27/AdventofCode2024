#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;
using namespace std;

namespace Puzzle07B
{
	auto ReadInput(const std::filesystem::path& inputFile)
	{
		auto input = ReadAllLinesInFile(inputFile);

		return input;
	}

	int64_t ConcatenateNumbers(int64_t a, int64_t b)
	{
		if (b == 0)
		{
			return a * 10;
		}
		int64_t temp = b;
		while (temp > 0)
		{
			a *= 10;
			temp /= 10;
		}
		return a + b;
	}

	void Dfs(const std::vector<int64_t>& numberSet, int index, int64_t currentResult, std::vector<int64_t>& results)
	{
		if (index == numberSet.size())
		{
			results.push_back(currentResult);
			return;
		}

		// Branch off an addition
		Dfs(numberSet, index + 1, currentResult + numberSet[index], results);

		// Branch off a multiplication
		Dfs(numberSet, index + 1, currentResult * numberSet[index], results);

		// Branch off a concatonation
		//auto s = to_string(currentResult) + to_string(numberSet[index]);
		//int64_t nextResult = std::stoll(s);
		//Dfs(numberSet, index + 1, nextResult, results);

		// ALTERNATE CONCATONATION...
		Dfs(numberSet, index + 1, ConcatenateNumbers(currentResult, numberSet[index]), results);

	}

	void PrintSolution(const std::filesystem::path& inputFile, bool shouldRender)
	{
		auto input = ReadInput(inputFile);
		std::unordered_multimap<int64_t, std::vector<int64_t>> parsed_data;

		for (const auto& line : input)
		{
			auto nums = ExtractInt64s(line);
			if (!nums.empty())
			{
				int64_t key = nums[0];
				parsed_data.insert({ key, std::vector<int64_t>(nums.begin() + 1, nums.end()) });
			}
		}

		int64_t acc = 0;
		int64_t numberOfMatches = 0;

		for (const auto& [key, set] : parsed_data)
		{
			std::vector<int64_t> results;
			int64_t firstValue = set[0];
			Dfs(set, 1, firstValue, results);
			bool matchFound = false;

			for (auto r : results)
			{
				if (r == key && !matchFound)
				{
					acc += key;
					++numberOfMatches;
					matchFound = true;
					//std::cout << "\n" << r;
				}
			}
		}
		std::cout << "Sum of matches " << acc << std::endl;
		std::cout << "# of matches " << numberOfMatches << std::endl;
	}
} // namespace Puzzle07B
