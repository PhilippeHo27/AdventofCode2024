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

	const Vector2d<int> oneUp(0, -1);
	const Vector2d<int> oneDown(0, +1);
	const Vector2d<int> oneRight(1, 0);
	const Vector2d<int> oneLeft(-1, 0);

	const std::pair<char, Vector2d<int>> moveUp(up, oneUp);
	const std::pair<char, Vector2d<int>> moveDown(down, oneDown);
	const std::pair<char, Vector2d<int>> moveRight(right, oneRight);
	const std::pair<char, Vector2d<int>> moveLeft(left, oneLeft);

	std::unordered_map<char, Vector2d<int>> move = { { up, oneUp }, { down, oneDown }, { right, oneRight }, { left, oneLeft } };

	auto ReadInput(const std::filesystem::path& inputFile)
	{
		auto input = ReadAllLinesInFile(inputFile);

		return input;
	}

	bool CheckObstacle(const Grid2d<char>& grid, char direction, Vector2d<int> currentPosition)
	{
		auto nextPos = currentPosition + move.at(direction);
		if (grid.IsInBounds(nextPos) && grid.at(nextPos.x, nextPos.y) == '#')
		{
			return true;
		}
		return false;
	}

	char Rotate90(char direction)
	{
		switch (direction)
		{
			case up:
				direction = right;
				break;
			case down:
				direction = left;
				break;
			case left:
				direction = up;
				break;
			case right:
				direction = down;
				break;

		}
		return direction;
	}


	// It looks like this function caused a stack overflow in windows... ! ! !
	int Traverse(Grid2d<char>& grid, char direction, Vector2d<int> currentPosition, int acc)
	{
		//if there's the next step is within bounds of grid, and is an obstacle
		if (CheckObstacle(grid, direction, currentPosition))
		{
			// then change direction to right, and move one step forward that way
			//std::cout << " if " << std::endl;
			direction = Rotate90(direction);
			grid.at(currentPosition) = 'X';
			currentPosition += move[direction];
			return Traverse(grid, direction, currentPosition, ++acc);
		}
		//if no obtacles, and we are out of bounds, return the total times we travelled
		else if (!grid.IsInBounds(currentPosition))
		{
			//std::cout << " else if " << acc << std::endl;
			return acc;
		}
		// if we're still in bounds, travel once in the direction want
		else
		{
			//std::cout << " else " << std::endl;
			grid.at(currentPosition) = 'X';
			currentPosition += move[direction];
			std::cout << "Current pos: " << currentPosition << " Direction: " << direction << std::endl;
			return Traverse(grid, direction, currentPosition, ++acc);
		}
		return 0;
	}

	void Traverse(Grid2d<char>& grid, char direction, Vector2d<int> currentPosition)
	{
		while (grid.IsInBounds(currentPosition))
		{
			grid.at(currentPosition) = 'X';
			Vector2d<int> nextPosition = currentPosition + move[direction];

			if (!grid.IsInBounds(nextPosition))
			{
				break;
			}

			if (grid.at(nextPosition.x, nextPosition.y) == '#')
			{
				direction = Rotate90(direction);
				nextPosition = currentPosition + move[direction];

				if (!grid.IsInBounds(nextPosition))
				{
					break;
				}
			}

			currentPosition = nextPosition;
		}
	}

	void PrintSolution(const std::filesystem::path& inputFile, bool shouldRender)
	{
		auto grid = ReadAllLinesInFileAsGrid(inputFile);
		for (int x = 0; x < grid.Width(); ++x)
		{
			for (int y = 0; y < grid.Height(); ++y)
			{
				if (grid.at(x, y) == up || grid.at(x, y) == down || grid.at(x, y) == right ||  grid.at(x, y) == left)
				{
					//std::cout << " found " << grid.at(x, y) << " at  : " << x << ", " << y << std::endl;

					//acc += Traverse(grid, grid.at(x, y) , Vector2d<int>(x, y), 0);
					//TraverseRecursive(grid, grid.at(x, y), Vector2d<int>(x, y));
					Traverse(grid, grid.at(x, y), Vector2d<int>(x, y));
				}
			}
		}

		auto uniqueSteps = std::count(grid.begin(), grid.end(), 'X');
		//std::cout << grid << std::endl;
		//std::cout << uniqueSteps << std::endl;


	}
} // namespace Puzzle06A



		//		// C++ 23 technology here
// for (const auto& [idx, value] : grid | std::views::enumerate)
//{
//	if (value == up)
//	{
//		int x = idx % grid.Width();
//		int y = idx / grid.Width();
//		std::cout << "Found it at: " << x << ", " << y << "\n";
//	}
//}

// for (const auto& n : grid | std::views::filter([up](char n) { return n == up; }))
//{
//	std::cout << "  FOUND IT"; // uhm ok but how do I know where it is doe haha
// }