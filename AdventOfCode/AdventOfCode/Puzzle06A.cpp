#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;

namespace Puzzle06A
{
	const auto directions = { '>', 'v', '^', '<' };

	const char up = '^';
	const char down = 'v';
	const char right = '>';
	const char left = '<';

	const Vector2d<int> oneUp(0, 1);
	const Vector2d<int> oneDown(0, -1);
	const Vector2d<int> oneRight(-1, 0);
	const Vector2d<int> oneLeft(-1, 0);

	const std::pair<char, Vector2d<int>> moveUp(up, oneUp);
	const std::pair<char, Vector2d<int>> moveDown(down, oneDown);
	const std::pair<char, Vector2d<int>> moveRight(right, oneRight);
	const std::pair<char, Vector2d<int>> moveLeft(left, oneLeft);

	//const std::unordered_map<char, Vector2d<int>> move = { moveUp, moveDown, moveRight, moveLeft };
	std::unordered_map<char, Vector2d<int>> move = { { up, oneUp }, { down, oneDown }, { right, oneRight }, { left, oneLeft } };



	auto ReadInput(const std::filesystem::path& inputFile)
	{
		auto input = ReadAllLinesInFile(inputFile);

		return input;
	}

	bool CheckObstacle(const Grid2d<char>& grid, char direction, Vector2d<int> position)
	{

		//auto pos = position + move[direction];
		auto pos = position + move.at(direction);
		if (grid.at(pos.x, pos.y) == '#')
		{
			return true;
		}

		return false;
	}
	int Traverse(const Grid2d<char>& grid, char direction, Vector2d<int> position)
	{
		if (CheckObstacle(grid, direction, position))
		{
			direction = right;
			position += move[direction];
			return Traverse(grid, direction, position);
		}
		else if (!grid.IsInBounds(position))
		{
			return 0;
		}
		else
		{
			position += move[direction];
			return Traverse(grid, direction, position);
		}
	}

	void PrintSolution(const std::filesystem::path& inputFile, bool shouldRender)
	{
		 auto grid = ReadAllLinesInFileAsGrid(inputFile);

		int acc = 0;
		for (int x = 0; x < grid.Width(); ++x)
		{
			for (int y = 0; y < grid.Height(); ++y)
			{
				if (grid.at(x, y) == up || grid.at(x, y) == down || grid.at(x, y) == right ||  grid.at(x, y) == left)
				{
					//std::cout << " found it at : " << x << " , " << y << std::endl;

					acc += Traverse(grid, grid.at(x, y) , Vector2d<int>(x, y));

				}
			}
		}



				// C++ 23 technology here O_O
		for (const auto& [idx, value] : grid | std::views::enumerate)
		{
			if (value == up)
			{
				int x = idx % grid.Width();
				int y = idx / grid.Width();
				std::cout << "Found it at: " << x << ", " << y << "\n";
			}
		}

		for (const auto& n : grid | std::views::filter([up](char n) { return n == up; }))
		{
			std::cout << "  FOUND IT"; // uhm ok but how do I know where it is doe haha
		}


		// find the player
		// determine direction the player is facing >v^<
		// grid.at the starting position
	}
} // namespace Puzzle06A