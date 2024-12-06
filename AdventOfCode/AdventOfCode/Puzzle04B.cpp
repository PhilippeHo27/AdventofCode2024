#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;

namespace Puzzle04B
{
	auto ReadInput(const std::filesystem::path& inputFile)
	{
		auto input = ReadAllLinesInFile(inputFile);

		return input;
	}

	void PrintSolution(const std::filesystem::path& inputFile, bool shouldRender)
	{
		auto grid = ReadAllLinesInFileAsGrid(inputFile);
		int answer = 0;

		for (int x = 1; x < grid.Width() - 1; ++x)
		{
			for (int y = 1; y < grid.Height() - 1; ++y)
			{
				char middle = grid.at(x, y);
				if (middle != 'A') continue;


				char topLeft = grid.at(x - 1, y - 1);
				char topRight = grid.at(x + 1, y - 1);
				char bottomLeft = grid.at(x - 1, y + 1);
				char bottomRight = grid.at(x + 1, y + 1);

				//int lol = topLeft + topRight + bottomLeft + bottomRight;
				//if (lol > 264 || lol > 231 || lol > 249) continue;

				std::string first = std::string() + topLeft + middle + bottomRight;
				std::string second = std::string() + topRight + middle + bottomLeft;
				std::string third = std::string() + bottomLeft + middle + topRight;
				std::string forth = std::string() + bottomRight + middle + topLeft;

				int count = 0;

				std::vector<std::string> words;
				words.push_back(first);
				words.push_back(second);
				words.push_back(third);
				words.push_back(forth);


				//std::cout << first << std::endl;
				//std::cout << second << std::endl;
				//std::cout << third << std::endl;
				//std::cout << forth << std::endl;

				for (std::string s : words)
				{
					if (s == "MAS")
					{
						count++;
					}
				}

				//std::cout << count << std::endl;

				if (count == 2)
				{
					answer++;
				}
			}
		}
		std::cout << answer << std::endl;

	}
} // namespace Puzzle04B