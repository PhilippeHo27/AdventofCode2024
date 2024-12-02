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

    bool IsReportSafe(const std::vector<int>& values)
    {
        if (values.size() < 2) return false;

        bool isAscending = true;
        bool isDescending = true;

        for (size_t i = 1; i < values.size(); i++)
        {
            int diff = values[i] - values[i - 1];
            
            // Check if difference is within valid range (1-3)
            if (abs(diff) < 1 || abs(diff) > 3)
            {
                return false;
            }

            // Check if sequence breaks ascending/descending pattern
            if (diff <= 0) isAscending = false;
            if (diff >= 0) isDescending = false;

            // If neither pattern is possible, return false
            if (!isAscending && !isDescending)
            {
                return false;
            }
        }

        return true;
    }

    bool CanBeMadeSafe(const std::vector<int>& values)
    {
        // First check if it's already safe
        if (IsReportSafe(values)) return true;

        // Try removing each number once and check if resulting sequence is safe
        for (size_t i = 0; i < values.size(); i++)
        {
            std::vector<int> modified = values;
            modified.erase(modified.begin() + i);
            
            if (IsReportSafe(modified))
            {
                return true;
            }
        }

        return false;
    }

    void PrintSolution(const std::filesystem::path& inputFile, bool shouldRender)
    {
        auto input = ReadInput(inputFile);
        int safeReports = 0;

        for (const auto& line : input)
        {
            auto values = ExtractInt32s(line);
            if (CanBeMadeSafe(values))
            {
                safeReports++;
            }
        }

        std::cout << safeReports << " reports are safe with Problem Dampener" << std::endl;
    }
}