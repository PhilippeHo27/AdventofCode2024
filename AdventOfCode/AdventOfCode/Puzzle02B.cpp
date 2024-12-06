#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;

namespace Puzzle02B
{
	auto ReadInput(const std::filesystem::path& inputFile)
	{
		auto input = ReadAllLinesInFile(inputFile);

		return input;
	}

	void DebugOne(bool a, bool b, std::vector<int> v)
	{
		if (a)
		{
			std::cout << " These values are ascending:  ";
			for (auto v : v)
			{
				std::cout << v << " ";
			}
			std::cout << std::endl;
		}

		if (b)
		{
			std::cout << " These values are descending ";
			for (auto v : v)
			{
				std::cout << v << " ";
			}
			std::cout << std::endl;
		}
	}

	void PrintSolution(const std::filesystem::path& inputFile, bool shouldRender)
	{
		auto input = ReadInput(inputFile);

		int counter = 0;
		int firstTrueCounter = 0;
		int secondTrueCounter = 0;

		for (std::string output : input)
		{
			//extract each line of input, output is an stdvector
			auto values = ExtractInt32s(output);

			//find if either ascending or descending
			bool isAscending = std::is_sorted(values.begin(), values.end(), std::less<>());
			bool isDescending = std::is_sorted(values.begin(), values.end(), std::greater<>());
			bool firstCondition = isAscending || isDescending;
			DebugOne(isAscending, isDescending, values);

			//if neither descending or ascending, find the problematic value
			if (!isAscending && !isDescending)
			{
				std::cout << "I am removing something in: " << output << std::endl;

				for (int i = 1; i < values.size() - 1; i++)
				{
					// Check if value breaks ascending pattern (smaller than both neighbors)
					bool breaksAscending = (values[i] < values[i - 1] && values[i] < values[i + 1]);
					// Check if value breaks descending pattern (bigger than both neighbors)
					bool breaksDescending = (values[i] > values[i - 1] && values[i] > values[i + 1]);

					if (breaksAscending || breaksDescending)
					{
						std::cout << "I have removed this value from values[]:  " << values[i] << std::endl;
						values.erase(values.begin() + i);
						break;
					}
				}
			}

			// check if it's ascending or descending again without the problematic value
			isAscending = std::is_sorted(values.begin(), values.end(), std::less<>());
			isDescending = std::is_sorted(values.begin(), values.end(), std::greater<>());

			// if either is true, the first condition is met for the first row of numbers!
			firstCondition = isAscending || isDescending;
			DebugOne(isAscending, isDescending, values);

			//since we deleted a value, we have to refresh this
			auto valuesAgain = ExtractInt32s(output);


			//find values that don't have an acceptable variance of 1 to 3
			bool secondCondition = true;

			for (int i = 1; i < valuesAgain.size(); i++)
			{
				bool isDifferenceBetweenOneAndThree = 0 < abs((valuesAgain[i] - valuesAgain[i - 1])) && abs((valuesAgain[i] - valuesAgain[i - 1])) < 4;
				std::cout << "The variance is: " << abs(valuesAgain[i] - valuesAgain[i - 1]) << std::endl;

				if (!isDifferenceBetweenOneAndThree)
				{
					// remove that value
					std::cout << "The variance is: " << abs(valuesAgain[i] - valuesAgain[i - 1]) << " and we removed this problematic number: " << valuesAgain[i] << std::endl;
					valuesAgain.erase(valuesAgain.begin() + i);
					break;
				}
			}
			// run it again without the value
			for (int i = 1; i < valuesAgain.size(); i++)
			{
				bool isDifferenceBetweenOneAndThree = 0 < abs((valuesAgain[i] - valuesAgain[i - 1])) && abs((valuesAgain[i] - valuesAgain[i - 1])) < 4;
				if (!isDifferenceBetweenOneAndThree)
				{
					std::cout << "The variance is: "
							  << abs(valuesAgain[i] - valuesAgain[i - 1]) 
						      << "    "
							  << valuesAgain[i]
							  << "<-- This value caused seconCondition to be false " << std::endl;
					secondCondition = false;
					break;
				}
				// if there's no variance outside the range, secondCondition stays true
			}

			if (firstCondition)
			{
				firstTrueCounter++;
			}

			if (secondCondition)
			{
				secondTrueCounter++;
			}

			// if both conditions are true, it means the report is safe!
			if (firstCondition && secondCondition)
			{
				std::cout << " the series of number is truely ascending/descending and the variance is within  0 < x < 4 " << std::endl;
				counter++;
			}
		}
		std::cout << firstTrueCounter << " # of times the 1st condition is met " << std::endl;
		std::cout << secondTrueCounter << " # of times the 2nd condition is met " << std::endl;
		std::cout << counter << " # of times both conditions are met, and is the answer " << std::endl;
	}




} // namespace Puzzle02B
