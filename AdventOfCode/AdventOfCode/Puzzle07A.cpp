#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;
using namespace std;

namespace Puzzle07A
{
	auto ReadInput(const std::filesystem::path& inputFile)
	{
		auto input = ReadAllLinesInFile(inputFile);

		return input;
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
	}

	void PrintSolution(const std::filesystem::path& inputFile, bool shouldRender)
	{
		auto input = ReadInput(inputFile);
		//std::map<int64_t, std::vector<int64_t>> parsed_data;
		std::unordered_multimap<int64_t, std::vector<int64_t>> parsed_data;
		parsed_data.reserve(1000000);
		parsed_data.max_load_factor(0.1f);

		for (const auto& line : input)
		{
			auto nums = ExtractInt64s(line);
			if (!nums.empty())
			{
				int64_t key = nums[0];
				parsed_data.insert({ key, std::vector<int64_t>(nums.begin() + 1, nums.end()) });
			}
		}


		//	// Old way with pair
		//	for (const auto& pair : parsed_data)
		//	{
		//		//int key = pair.first;
		//		//const std::vector<int>& values = pair.second;
		//	}

		//	// iterator way
		//	for (auto it = parsed_data.begin(); it != parsed_data.end(); ++it)
		//	{
		//		//int key = it->first;                   // get the key
		//		//std::vector<int>& values = it->second; // get the vector
		//	}


		int64_t acc = 0;
		int64_t numberOfMatches = 0;

		for (const auto& [key, set] : parsed_data)
		{
			//std::cout << "Checking key: " << key << ", Set: ";
			for (auto n : set)
			{
				//std::cout << n << " ";
			}
			//std::cout << std::endl;

			std::vector<int64_t> results;
			int64_t firstValue = set[0];
			//std::cout << firstValue << std::endl;
			Dfs(set, 1, firstValue, results);
			//std::cout << "Results for key " << key << ": ";
			bool matchFound = false;
			for (auto r : results)
			{
				//std::cout << r << " ";
			}
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

			//std::cout << "\n-------------------\n";
		}

		std::cout << "Sum of matches " << acc << std::endl;
		std::cout << "# of matches " << numberOfMatches << std::endl;
	}
} // namespace Puzzle07A
