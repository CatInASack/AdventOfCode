#include "stdafx.h"
#include "CppUnitTest.h"
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace My1_1
{
    TEST_CLASS(UnitTest1)
    {
    private:
        void ProcessInput(char input, int& floor)
        {
            switch (input)
            {
            case '(':
                floor++;
                break;
            case ')':
                floor--;
                break;
            }
        }

        int FindFloor(const std::string& input)
        {
            int result = 0;
            for (char ch : input)
            {
                ProcessInput(ch, result);
            }
            return result;
        }

        int FindBasement(const std::string& input)
        {
            int floor = 0;
            for (int ii = 0; ii < (int)input.length(); ii++)
            {
                ProcessInput(input[ii], floor);
                if (floor == -1)
                {
                    return ii + 1;
                }
            }

            return -1;
        }
    public:
        TEST_METHOD(ResultInFloor0)
        {
            Assert::AreEqual(FindFloor("(())"), 0, L"A");
            Assert::AreEqual(FindFloor("()()"), 0, L"B");
        }

        TEST_METHOD(ResultInFloor3)
        {
            Assert::AreEqual(FindFloor("((("), 3, L"A");
            Assert::AreEqual(FindFloor("(()(()("), 3, L"B");
        }

        TEST_METHOD(ResultsInFloor3Again)
        {
            Assert::AreEqual(FindFloor("))(((((AndSoOn"), 3);
        }

        TEST_METHOD(Part1)
        {
            std::string input;
            std::ifstream inputStream("C:\\Users\\r00t\\Documents\\AdventOfCode\\AdventOfCode\\Part1\\input.txt");
            inputStream >> input;
            Assert::AreEqual(FindFloor(input), 232);
        }

        TEST_METHOD(StraightToBasement)
        {
            Assert::AreEqual(FindBasement(")"), 1);
        }

        TEST_METHOD(BasementOnChar5)
        {
            Assert::AreEqual(FindBasement("()())"), 5);
        }

        TEST_METHOD(Part2)
        {
            std::string input;
            std::ifstream inputStream("C:\\Users\\r00t\\Documents\\AdventOfCode\\AdventOfCode\\Part1\\input.txt");
            inputStream >> input;
            Assert::AreEqual(FindBasement(input), 1783);
        }
    };
}