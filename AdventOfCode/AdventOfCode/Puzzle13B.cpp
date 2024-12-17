#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;

namespace Puzzle13B
{
	struct ClawMachine
	{
		std::pair<int64_t, int64_t> A;
		std::pair<int64_t, int64_t> B;
		std::pair<int64_t, int64_t> prize;
	};

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

	auto ReadInput(const std::filesystem::path& inputFile)
	{
		auto lines = ReadAllLinesInFile(inputFile);
		std::vector<ClawMachine> machines;

		// We do += 4 since input is in groups of 3 lines and an empty line
		for (size_t i = 0; i < lines.size(); i += 4)
		{
			auto valuesA = ExtractInt32s(lines[i]);
			auto valuesB = ExtractInt32s(lines[i + 1]);
			auto valuesPrize = ExtractInt32s(lines[i + 2]);
			
			auto valluesPrizeOne = ConcatenateNumbers(10000000000000, valuesPrize[0]);
			auto valluesPrizeTwo = ConcatenateNumbers(10000000000000, valuesPrize[1]);


			machines.push_back({ { valuesA[0], valuesA[1] },
			                     { valuesB[0], valuesB[1] },
			                     { 10000000000000 + valuesPrize[0], 10000000000000 + valuesPrize[1] }
				});
		}

		return machines;
	}

	void ClawMachineDebug(const std::vector<ClawMachine>& clawMachines)
	{
		for (const auto& claws : clawMachines)
		{
			std::cout << "Claw Machine Debug Info:\n"
					  << "  A: (" << claws.A.first << ", " << claws.A.second << ")\n"
					  << "  B: (" << claws.B.first << ", " << claws.B.second << ")\n"
					  << "  Prize: (" << claws.prize.first << ", " << claws.prize.second << ")\n"
					  << "-----------------------------\n";
		}
	}

	int64_t Determinant(int64_t a11, int64_t a12, int64_t a21, int64_t a22)
	{
		return (a11 * a22) - (a12 * a21);
	}

	void PrintSolution(const std::filesystem::path& inputFile, bool shouldRender)
	{
		auto clawMachines = ReadInput(inputFile);
		//ClawMachineDebug(clawMachines);

		int64_t acc = 0;
		for (const auto& claws : clawMachines)
		{
			auto D = Determinant(claws.A.first, claws.B.first, claws.A.second, claws.B.second);

			auto Dx = Determinant(claws.prize.first, claws.B.first, claws.prize.second, claws.B.second);

			auto Dy = Determinant(claws.A.first, claws.prize.first, claws.A.second, claws.prize.second);

			if (D == 0 || Dx % D != 0 || Dy % D != 0)
			{
				continue;
			}

			int64_t ButtonAPresses = Dx / D;
			int64_t ButtonBPresses = Dy / D;

			//std::cout << ButtonAPresses << "    " << ButtonBPresses << " \n";
			acc += ButtonAPresses * 3 + ButtonBPresses;
			std::cout << acc << " \n";
		}
	}
} // namespace Puzzle13B