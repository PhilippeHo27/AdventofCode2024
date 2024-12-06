#include "pch.h"

#include <typeinfo>

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;

namespace Puzzle04A
{
	const std::regex pattern("XMAS|SAMX");

	int FindSanta(const Grid2d<char>& grid)
	{
		int count = 0;
		std::smatch matches;
		for (const auto& row : grid.GetRows())
		{
			std::string concaconatedString;
			for (const auto& positions : row)
			{
				concaconatedString += positions;
			}
			//std::cout << "Scanning string: " << concaconatedString << std::endl;

			std::string::const_iterator searchStart(concaconatedString.cbegin());
			while (std::regex_search(searchStart, concaconatedString.cend(), matches, pattern))
			{
				count++;
				//std::cout << "Found match: " << matches[0] << " in string!" << std::endl;
				searchStart = matches.suffix().first - 1;
			}
		}
		return count;
	}

	int FindXmas(const std::string& s)
	{
		int count = 0;
		std::smatch matches;

		std::cout << "Scanning string: " << s << std::endl;

		std::string::const_iterator searchStart(s.cbegin());
		while (std::regex_search(searchStart, s.cend(), matches, pattern))
		{
			count++;
			std::cout << "Found match: " << matches[0] << " in string!" << std::endl;

			searchStart = matches.suffix().first - 1;
		}
		return count;
	}

	std::string ScanDiagonal(const Grid2d<char>& grid, int startX, int startY, int dx, int dy)
	{
		std::string diagonal;
		int x = startX;
		int y = startY;
		while (grid.IsInBounds(x, y))
		{
			diagonal += grid.at(x, y);
			x += dx;
			y += dy;
		}
		return diagonal;
	}

	int ScanAllDiagonals(const Grid2d<char>& grid)
	{
		int count = 0;

		// Main diagonals (↘)
		// From top row
		for (int x = 0; x < grid.Width(); ++x)
		{
			count += FindXmas(ScanDiagonal(grid, x, 0, 1, 1));
		}
		// From left column (excluding 0,0)
		for (int y = 1; y < grid.Height(); ++y)
		{
			count += FindXmas(ScanDiagonal(grid, 0, y, 1, 1));
		}

		// Anti-diagonals (↙)
		// From top row
		for (int x = 0; x < grid.Width(); ++x)
		{
			count += FindXmas(ScanDiagonal(grid, x, 0, -1, 1));
		}
		// From right column (excluding top-right)
		for (int y = 1; y < grid.Height(); ++y)
		{
			count += FindXmas(ScanDiagonal(grid, grid.Width() - 1, y, -1, 1));
		}

		return count;
	}


	void PrintSolution(const std::filesystem::path& inputFile, bool shouldRender)
	{
		auto grid = ReadAllLinesInFileAsGrid(inputFile);
		int horizontal = 0;
		int veritcal  = 0;
		int diagonal = 0;
		int total = 0;

		// Scan rows
		horizontal += FindSanta(grid);
		total += FindSanta(grid);

		// Create rotated grid for columns
		Grid2d<char> rotated(grid.Height(), grid.Width());
		for (int y = 0; y < grid.Height(); ++y)
		{
			for (int x = 0; x < grid.Width(); ++x)
			{
				rotated.at(grid.Height() - 1 - y, x) = grid.at(x, y);
			}
		}

		std::cout << "Original:\n" << grid << "\n\n";
		std::cout << "Rotated:\n" << rotated << "\n";

		// Scan columns (using rotated grid)
		veritcal += FindSanta(rotated);
		total += FindSanta(rotated);

		// Scan diagonals
		diagonal += ScanAllDiagonals(grid);
		total += ScanAllDiagonals(grid);

		std::cout << horizontal << std::endl;
		std::cout << veritcal << std::endl;
		std::cout << diagonal << std::endl;
		std::cout << total << std::endl;
	}
} // namespace Puzzle04A