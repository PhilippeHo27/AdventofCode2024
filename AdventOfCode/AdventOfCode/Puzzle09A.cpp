#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;

namespace Puzzle09A
{
	auto ReadInput(const std::filesystem::path& inputFile)
	{
		auto input = ReadAllLinesInFile(inputFile);

		return input;
	}

	void PrintSolution(const std::filesystem::path& inputFile, bool shouldRender)
	{
		auto input = ReadInput(inputFile);
		std::string superLongString;
		int counter = 0;
		int64_t acc = 0;

		std::vector<std::string> parts;
		for (auto it = input[0].begin(); it != input[0].end(); ++it)
		{
			auto index = it - input[0].begin();
			if (index % 2 == 0)
			{
				std::string num = std::to_string(*it - '0');
				parts.push_back(std::string(counter, num[0]));
				++counter;
			}
			else
			{
				parts.push_back(".");
			}
		}

		// Write string to file
		//std::ofstream outFile("E:\\Downloads\\reshuffled_string.txt");
		//if (outFile.is_open())
		//{
		//	outFile << superLongString;
		//	outFile.close();
		//	std::cout << "String written to E:\\Downloads\\reshuffled_string.txt" << std::endl;
		//}
		//else
		//{
		//	std::cout << "Unable to open file for writing" << std::endl;
		//}


		//for (auto it = superLongString.begin(); it < superLongString.end(); ++it)
		//{
		//	if (*it == '.')
		//	{
		//		auto rit = std::find_if(
		//			superLongString.rbegin(),
		//			superLongString.rend() - (it - superLongString.begin()),
		//			[](char c) { return std::isdigit(c); });

		//		if (rit != superLongString.rend() - (it - superLongString.begin()))
		//		{
		//			std::iter_swap(it, rit.base() - 1);
		//		}
		//		else
		//		{
		//			break;
		//		}
		//	}
		//}

		//for (int64_t i = 0; i < static_cast<int64_t>(superLongString.size()); ++i)
		//{
		//	if (std::isdigit(superLongString[i]))
		//	{
		//		int64_t current = i * static_cast<int64_t>(superLongString[i] - '0');
		//		acc += current;
		//	}
		//}
		//std::cout << "Final result: " << acc << std::endl;
	}
} // namespace Puzzle09A



		// C++20 ranges version
// for (auto it = superLongString.begin(); it < superLongString.end(); ++it)
//{
//	if (*it == '.')
//	{
//		// Create a subrange from current position to end, then reverse it
//		auto remaining = std::ranges::subrange(it, superLongString.end());
//		auto digit_view = std::views::reverse(remaining) | std::views::filter([](char c) { return std::isdigit(c); });

//		if (auto digit_it = digit_view.begin(); digit_it != digit_view.end())
//		{
//			std::iter_swap(it, &*digit_it);
//		}
//		else
//		{
//			break;
//		}
//	}
//}

// auto forward_it = superLongString.begin();
// auto reverse_it = superLongString.rbegin();

// while (forward_it < reverse_it.base())
//{
//	if (*forward_it == '.')
//	{
//		while (reverse_it != superLongString.rend() && !std::isdigit(*reverse_it))
//		{
//			++reverse_it;
//		}

//		if (reverse_it != superLongString.rend() && forward_it < reverse_it.base())
//		{
//			std::iter_swap(forward_it, reverse_it.base() - 1);
//			++reverse_it;
//		}
//		else
//		{
//			// No more digits to swap
//			break;
//		}
//	}
//	++forward_it;
//}