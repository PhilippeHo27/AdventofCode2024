#include "pch.h"
#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;

namespace Puzzle06B
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

	const int LOOP_THRESHOLD = 10;

	struct State
	{
		Vector2d<int> position;
		char direction;

		bool operator<(const State& other) const
		{
			if (position != other.position)
			{
				return position < other.position;
			}
			return direction < other.direction;
		}
	};

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

	bool Traverse(Grid2d<char>& grid, char direction, Vector2d<int> currentPosition)
	{
		bool isLooping = false;
		std::map<Vector2d<int>, int> visitedPositions;
		std::set<State> visited;
		std::set<Vector2d<int>> wallTurnPoints;

		while (grid.IsInBounds(currentPosition))
		{
			if (grid.at(currentPosition) == '^')
			{
				Vector2d<int> nextPosition = currentPosition + move[direction];
				// Check for obstacles before continuing
				if (grid.IsInBounds(nextPosition) && (grid.at(nextPosition) == '#' || grid.at(nextPosition) == 'O'))
				{
					direction = Rotate90(direction);
					nextPosition = currentPosition + move[direction];

					if (!grid.IsInBounds(nextPosition))
					{
						break;
					}
				}
				currentPosition = nextPosition;
				continue;
			}
			char mark = '|';
			if (direction == left || direction == right)
			{
				mark = '~';
			}
			if (grid.at(currentPosition) == '|' || grid.at(currentPosition) == '~')
			{
				mark = '+';
			}

			grid.at(currentPosition) = mark;
			Vector2d<int> nextPosition = currentPosition + move[direction];

			if (!grid.IsInBounds(nextPosition))
			{
				break;
			}

			if (grid.at(nextPosition) == '+')
			{
				// Only count visits if this + is one of our marked turn points
				if (wallTurnPoints.contains(nextPosition))
				{
					visitedPositions[nextPosition]++;

					if (visitedPositions[nextPosition] >= LOOP_THRESHOLD)
					{
						std::cout << "Found loop! Turn point at: " << nextPosition << std::endl;
						std::cout << "Hit this turn point " << visitedPositions[nextPosition] << " times" << std::endl;
						isLooping = true;
						break;
					}
				}
			}

			//if (grid.at(nextPosition) == '+')
			//{
			//	visitedPositions[nextPosition]++;

			//	if (visitedPositions[nextPosition] >= LOOP_THRESHOLD)
			//	{
			//		std::cout << "i've been at this position: " << nextPosition << std::endl;
			//		std::cout << "for this amount of time: " << visitedPositions[nextPosition] << std::endl;
			//		std::cout << "for the same while loop!, it SHOULD BE A CLOSED LOOP IF I VISIT SAME SPOT THIS MANY TIMES.... "
			//				  << std::endl;
			//		isLooping = true;
			//		break;
			//	}
			//}

			//if (grid.at(nextPosition) == '+')
			//{
			//	State currentState{ nextPosition, direction };
			//	if (visited.contains(currentState))
			//	{
			//		// It's definitely a loop
			//		std::cout << "DEFINITELY A LOOP... " << nextPosition << std::endl;

			//		isLooping = true;
			//		break;
			//	}
			//	visited.insert(currentState);
			//}


			if (grid.at(nextPosition) == '#' || grid.at(nextPosition) == 'O')
			{
				direction = Rotate90(direction);
				grid.at(currentPosition) = '+';
				nextPosition = currentPosition + move[direction];
				wallTurnPoints.insert(currentPosition); // Store this turn point that faces a wall 
				if (!grid.IsInBounds(nextPosition))
				{
					break;
				}
			}

			currentPosition = nextPosition;
		}

		return isLooping;
	}

	void PrintSolution(const std::filesystem::path& inputFile, bool shouldRender)
	{
		auto grid = ReadAllLinesInFileAsGrid(inputFile);
		auto initialGridCached = grid;

		int acc = 0;

		Vector2d<int> StartingPoint;

		for (int x = 0; x < grid.Width(); ++x)
		{
			for (int y = 0; y < grid.Height(); ++y)
			{
				if (grid.at(x, y) == up || grid.at(x, y) == down || grid.at(x, y) == right || grid.at(x, y) == left)
				{
					StartingPoint = Vector2d<int>(x, y);
				}
			}
		}

		std::vector<Grid2d<char>> gridContainers;

		for (int x = 0; x < grid.Width(); ++x)
		{
			for (int y = 0; y < grid.Height(); ++y)
			{
				// something here needs to reset the grid back to its initial condition

				if (grid.at(x, y) == '#')
				{
					continue;
				}
				grid = initialGridCached;
				if (StartingPoint != Vector2d{ x, y })
				{
					grid.at(x, y) = 'O';

				}
				if (Traverse(grid, grid.at(StartingPoint), StartingPoint))
				{
					//grid.at(x, y) = '.';
					//gridContainers.push_back(grid);
					//std::cout << "i pass here" << std::endl;
					acc++;
					//std::cout << grid << std::endl << std::endl;
				}
			}
		}

		//std::sort(gridContainers.begin(), gridContainers.end());
		//auto last = std::unique(gridContainers.begin(), gridContainers.end());
		//gridContainers.erase(last, gridContainers.end());

		//std::cout << gridContainers.size() << std::endl;
		std::cout << acc << std::endl;

	}
} // namespace Puzzle06B

// tried to do turtlehare algo but I think if we go back on a + it means it's immediately a loop
//bool QuickTraverse(Grid2d<char>& grid, char direction, Vector2d<int> currentPosition)
//{
//	bool isLooping = false;
//	int lapse = 0;
//	while (grid.IsInBounds(currentPosition))
//	{
//		Vector2d<int> nextPosition = currentPosition + move[direction];
//
//		if (grid.at(nextPosition) == '#' || grid.at(nextPosition) == 'O')
//		{
//		}
//		if (grid.at(nextPosition) == '#' || grid.at(nextPosition) == 'O')
//		{
//			direction = Rotate90(direction);
//			nextPosition = currentPosition + move[direction];
//
//			if (!grid.IsInBounds(nextPosition))
//			{
//				break;
//			}
//		}
//		currentPosition = nextPosition;
//	}
//	return false;
//}