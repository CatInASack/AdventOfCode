#include "stdafx.h"
#include "CppUnitTest.h"
#include <algorithm>
#include <tuple>
#include <fstream>
#include <vector>
#include <functional>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Part2
{
    TEST_CLASS(UnitTest2)
    {
    private:
        std::tuple<int, int, int> ExtractSides(std::string line)
        {
            size_t pos = line.find('x');
            int side1 = std::stol(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find('x');
            int side2 = std::stol(line.substr(0, pos));
            line.erase(0, pos + 1);
            int side3 = std::stol(line);

            return std::make_tuple(side1, side2, side3);
        }

        int PaperNeeded(const std::string& input)
        {
            int l, w, h;
            std::tie(l, w, h) = ExtractSides(input);

            int side1 = l * w;
            int side2 = l * h;
            int side3 = w * h;

            int minSide = std::min(side1, std::min(side2, side3));

            return (2 * side1) + (2 * side2) + (2 * side3) + minSide;
        }

        int RibbonNeeded(const std::string& input)
        {
            int l, w, h;
            std::tie(l, w, h) = ExtractSides(input);

            std::vector<int> sides = { l, w, h };
            std::sort(sides.begin(), sides.end(), std::less<int>());

            return (2 * sides[0]) + (2 * sides[1]) + (sides[0] * sides[1] * sides[2]);
        }

    public:
        TEST_METHOD(Need58For2x3x4)
        {
            Assert::AreEqual(58, PaperNeeded("2x3x4"));
        }

        TEST_METHOD(Need43For1x1x10)
        {
            Assert::AreEqual(43, PaperNeeded("1x1x10"));
        }

        TEST_METHOD(Part1)
        {
            std::ifstream inputStream(SOLUTION_DIR "Part2\\input.txt");

            int paperNeeded = 0;

            std::string input;
            while (!(inputStream >> input).eof())
            {
                paperNeeded += PaperNeeded(input);
            }

            Assert::AreEqual(paperNeeded, 1606483);
        }

        TEST_METHOD(Need34RibbonFor2x3x4)
        {
            Assert::AreEqual(34, RibbonNeeded("2x3x4"));
        }

        TEST_METHOD(Need14RibbonFor1x1x10)
        {
            Assert::AreEqual(14, RibbonNeeded("1x1x10"));
        }

        TEST_METHOD(Part2)
        {
            std::ifstream inputStream(SOLUTION_DIR "Part2\\input.txt");

            int ribbonNeeded = 0;

            std::string input;
            while (!(inputStream >> input).eof())
            {
                ribbonNeeded += RibbonNeeded(input);
            }

            Assert::AreEqual(ribbonNeeded, 3842356);
        }
    };
}