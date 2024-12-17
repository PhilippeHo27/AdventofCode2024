#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;

namespace Puzzle12B
{
	class Quads
	{
		// A ----- B
		//|       |
		//|       |
		//|       |
		// C ----- D

	public:
		Quads(Vector2d<int> position)
			: position(position)
			, A(position)
			, B(position + Vector2d<int>(1, 0))
			, C(position + Vector2d<int>(0, 1))
			, D(position + Vector2d<int>(1, 1))
		{
		}

		struct Edge
		{
			Vector2d<int> start, end;
			bool active = true;
		};

		Edge edges[4]; // top, right, bottom, left
		void InitializeEdges()
		{
			edges[0] = { A, B }; // top
			edges[1] = { B, D }; // right
			edges[2] = { C, D }; // bottom
			edges[3] = { A, C }; // left
		}
		Vector2d<int> A, B, C, D;

		void CheckAndRemoveEdges(const std::unordered_set<Vector2d<int>>& positionsSet)
		{
			static const Vector2d<int> adjacentPositions[] = {
				{ 1, 0 },  // right
				{ -1, 0 }, // left
				{ 0, 1 },  // down
				{ 0, -1 }  // up
			};

			static const int edgeIndices[] = { 1, 3, 2, 0 }; // maps to right, left, down, up

			for (int i = 0; i < 4; i++)
			{
				if (positionsSet.contains(position + adjacentPositions[i]))
				{
					edges[edgeIndices[i]].active = false;
				}
			}
		}

	private:
		Vector2d<int> position;
	};

	void FloodFill(
		const Vector2d<int>& startPos,
		const std::unordered_set<Vector2d<int>>& allPositions,
		std::unordered_set<Vector2d<int>>& visited,
		std::vector<Vector2d<int>>& currentRegion)
	{
		if (!allPositions.contains(startPos) || visited.contains(startPos))
		{
			return;
		}

		currentRegion.push_back(startPos);
		visited.insert(startPos);

		static const Vector2d<int> directions[] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

		for (const auto& dir : directions)
		{
			FloodFill(startPos + dir, allPositions, visited, currentRegion);
		}
	}

	std::vector<std::vector<Vector2d<int>>> FindRegionsForSymbol(const std::unordered_set<Vector2d<int>>& positions)
	{
		std::vector<std::vector<Vector2d<int>>> regions;
		std::unordered_set<Vector2d<int>> visited;

		for (const auto& pos : positions)
		{
			if (visited.contains(pos))
			{
				continue;
			}

			std::vector<Vector2d<int>> currentRegion;
			FloodFill(pos, positions, visited, currentRegion);
			regions.push_back(currentRegion);
		}

		return regions;
	}

	auto ReadInput(const std::filesystem::path& inputFile)
	{
		auto input = ReadAllLinesInFileAsGrid(inputFile);
		return input;
	}

	void PrintSolution(const std::filesystem::path& inputFile, bool shouldRender)
	{
		auto grid = ReadInput(inputFile);
		std::unordered_map<char, std::unordered_set<Vector2d<int>>> terrains;

		// Group positions by symbol
		for (auto it = grid.begin(); it != grid.end(); ++it)
		{
			int currentIndex = static_cast<int>(std::distance(grid.begin(), it));
			terrains[*it].insert(grid.GetCoordinatesFromIndex(currentIndex));
		}

		int64_t totalSum = 0;

		for (const auto& [symbol, positions] : terrains)
		{
			std::cout << "\nProcessing symbol: " << symbol << std::endl;
			auto regions = FindRegionsForSymbol(positions);
			std::cout << "Found " << regions.size() << " regions" << std::endl;

			// Process each region separately
			for (const auto& region : regions)
			{
				std::vector<Quads> quadsForRegion;
				std::unordered_set<Vector2d<int>> regionSet(region.begin(), region.end());

				// Create and initialize quads for this region
				for (const auto& pos : region)
				{
					Quads quad(pos);
					quad.InitializeEdges();
					quad.CheckAndRemoveEdges(regionSet);
					quadsForRegion.push_back(quad);
				}

				// new algo here


			}
		}

	}
} // namespace Puzzle12B