#include "stdafx.h"
#include "CppUnitTest.h"
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Part8
{
    int EscapeDiff(const std::string& input)
    {
        int removed = 2;
        char last = 0;
        for (char ch : input)
        {
            if (last == '\\')
            {
                switch (ch)
                {
                case 'x':
                    removed += 3;
                    break;
                case '\\':
                    removed += 1;
                    ch = 0;
                    break;
                default:
                    removed += 1;
                }
            }
            last = ch;
        }

        return removed;
    }

    int ReescapeDiff(const std::string& input)
    {
        int added = 2;
        for (char ch : input)
        {
            switch (ch)
            {
            case '\\':
            case '"':
                added += 1;
                break;
            }
        }

        return added;
    }

    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(EmptyString)
        {
            Assert::AreEqual(2, EscapeDiff("\"\""));
        }

        TEST_METHOD(NoEscapes)
        {
            Assert::AreEqual(2, EscapeDiff("\"abc\""));
        }

        TEST_METHOD(OneEscapedQuote)
        {
            Assert::AreEqual(3, EscapeDiff("\"aaa\\\"aaa\""));
        }

        TEST_METHOD(HexEscapedChar)
        {
            Assert::AreEqual(5, EscapeDiff("\"\\x27\""));
        }

        TEST_METHOD(Part1)
        {
            std::ifstream inputStream(SOLUTION_DIR "Part8\\input.txt");

            int total = 0;

            std::string input;
            while (std::getline(inputStream, input))
            {
                total += EscapeDiff(input);
            }

            Assert::AreEqual(1350, total);
        }

        TEST_METHOD(EscEmptyString)
        {
            Assert::AreEqual(4, ReescapeDiff("\"\""));
        }

        TEST_METHOD(EscNoEscapes)
        {
            Assert::AreEqual(4, ReescapeDiff("\"abc\""));
        }

        TEST_METHOD(EscOneEscapedQuote)
        {
            Assert::AreEqual(6, ReescapeDiff("\"aaa\\\"aaa\""));
        }

        TEST_METHOD(EscHexEscapedChar)
        {
            Assert::AreEqual(5, ReescapeDiff("\"\\x27\""));
        }

        TEST_METHOD(Part2)
        {
            std::ifstream inputStream(SOLUTION_DIR "Part8\\input.txt");

            int total = 0;

            std::string input;
            while (std::getline(inputStream, input))
            {
                total += ReescapeDiff(input);
            }

            Assert::AreEqual(2085, total);
        }
    };
}