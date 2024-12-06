#include "pch.h"
#include <regex>
#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace std::literals::chrono_literals;
using namespace Utilities;

namespace Puzzle03A
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

		std::regex pattern("mul\\((\\d+),(\\d+)\\)");
		std::smatch matches;

		for (auto output : input)
		{
			std::string::const_iterator searchStart(output.cbegin());
			while (std::regex_search(searchStart, output.cend(), matches, pattern))
			{
				int first_num = std::stoi(matches[1]);
				int second_num = std::stoi(matches[2]);

				answer += first_num * second_num;
				//std::cout << first_num << " and " << second_num << std::endl;
				searchStart = matches.suffix().first;
			}
		}
		std::cout << answer << std::endl;
	}
} // namespace Puzzle03A