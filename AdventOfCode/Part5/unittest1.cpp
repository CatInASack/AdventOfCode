#include "stdafx.h"
#include "CppUnitTest.h"
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Part5
{
    TEST_CLASS(UnitTest1)
    {
    public:
        const int Has3Vowels            = 0x1;
        const int HasDoubleLetter       = 0x2;
        const int HasNoBannedStrings    = 0x4;
        const int Nice                  = 0x7;
    private:
        int CheckNiceness(const std::string& input)
        {
            int result = HasNoBannedStrings;
            char lastCh = 0;
            int numberOfVowels = 0;

            for (char ch : input)
            {
                if (ch == lastCh)
                {
                    result |= HasDoubleLetter;
                }

                switch (ch)
                {
                case 'a':
                case 'e':
                case 'i':
                case 'o':
                case 'u':
                    numberOfVowels++;
                    break;
                case 'b':
                case 'd':
                case 'q':
                case 'y':
                    // ab, cd, pq, or xy
                    if (lastCh == ch - 1)
                    {
                        result &= ~HasNoBannedStrings;
                    }
                    break;
                }

                lastCh = ch;
            }

            if (numberOfVowels >= 3)
            {
                result |= Has3Vowels;
            }

            return result;
        }
    public:

        TEST_METHOD(TheString_ugknbfddgicrmopn_IsNice)
        {
            Assert::AreEqual(Nice, CheckNiceness("ugknbfddgicrmopn"));
        }

        TEST_METHOD(TheString_aaa_IsNice)
        {
            Assert::AreEqual(Nice, CheckNiceness("aaa"));
        }

        TEST_METHOD(TheString_jchzalrnumimnmhp_IsNaughtyForNoDoubleLetter)
        {
            Assert::AreEqual(Nice ^ HasDoubleLetter, CheckNiceness("jchzalrnumimnmhp"));
        }

        TEST_METHOD(TheString_haegwjzuvuyypxyu_IsNaughtyForBannedString)
        {
            Assert::AreEqual(Nice ^ HasNoBannedStrings, CheckNiceness("haegwjzuvuyypxyu"));
        }

        TEST_METHOD(TheString_dvszwmarrgswjxmb_IsNaughtyForNotEnoughVowels)
        {
            Assert::AreEqual(Nice ^ Has3Vowels, CheckNiceness("dvszwmarrgswjxmb"));
        }

        TEST_METHOD(Part1)
        {
            std::ifstream inputStream(SOLUTION_DIR "Part5\\input.txt");

            int niceWords = 0;

            std::string input;
            while (!(inputStream >> input).eof())
            {
                if (Nice == CheckNiceness(input))
                {
                    niceWords++;
                }
            }

            Assert::AreEqual(238, niceWords);
        }
    };
}