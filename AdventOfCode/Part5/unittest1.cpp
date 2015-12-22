#include "stdafx.h"
#include "CppUnitTest.h"
#include <fstream>
#include <map>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Part5
{
    TEST_CLASS(UnitTest1)
    {
    public:
        const int Has3Vowels            = 0x01;
        const int HasDoubleLetter       = 0x02;
        const int HasNoBannedStrings    = 0x04;
        const int Nice                  = 0x07;
        const int HasRepeatedPair       = 0x08;
        const int HasSplitRepeat        = 0x10;
        const int NiceEnough            = 0x18;
    private:
        int CheckNiceness(const std::string& input)
        {
            int result = HasNoBannedStrings;
            char lastCh = 0;
            char lastLastCh = 0;
            int numberOfVowels = 0;
            std::map<std::pair<char, char>, int> pairCounts;
            std::pair<char, char> lastPair;

            for (char ch : input)
            {
                if (ch == lastCh)
                {
                    result |= HasDoubleLetter;
                }

                std::pair<char, char> thisPair = std::make_pair(ch, lastCh);

                if (lastPair != thisPair)
                {
                    lastPair = thisPair;

                    if (2 == (++pairCounts[thisPair]))
                    {
                        result |= HasRepeatedPair;
                    }
                }
                else
                {
                    lastPair = std::make_pair(0, 0);
                }

                if (ch == lastLastCh)
                {
                    result |= HasSplitRepeat;
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

                lastLastCh = lastCh;
                lastCh = ch;
            }

            if (numberOfVowels >= 3)
            {
                result |= Has3Vowels;
            }

            return result;
        }

        bool IsNice(const std::string& input)
        {
            int result = CheckNiceness(input);
            return (result & Nice) == Nice;
        }

        bool IsNiceEnough(const std::string& input)
        {
            int result = CheckNiceness(input);
            return (result & NiceEnough) == NiceEnough;
        }

    public:

        TEST_METHOD(TheString_ugknbfddgicrmopn_IsNice)
        {
            Assert::AreEqual(Nice, CheckNiceness("ugknbfddgicrmopn") & Nice);
        }

        TEST_METHOD(TheString_aaa_IsNice)
        {
            Assert::AreEqual(Nice, CheckNiceness("aaa") & Nice);
        }

        TEST_METHOD(TheString_jchzalrnumimnmhp_IsNaughtyForNoDoubleLetter)
        {
            Assert::AreEqual(Nice ^ HasDoubleLetter, CheckNiceness("jchzalrnumimnmhp") & Nice);
        }

        TEST_METHOD(TheString_haegwjzuvuyypxyu_IsNaughtyForBannedString)
        {
            Assert::AreEqual(Nice ^ HasNoBannedStrings, CheckNiceness("haegwjzuvuyypxyu") & Nice);
        }

        TEST_METHOD(TheString_dvszwmarrgswjxmb_IsNaughtyForNotEnoughVowels)
        {
            Assert::AreEqual(Nice ^ Has3Vowels, CheckNiceness("dvszwmarrgswjxmb") & Nice);
        }

        TEST_METHOD(Part1)
        {
            std::ifstream inputStream(SOLUTION_DIR "Part5\\input.txt");

            int niceWords = 0;

            std::string input;
            while (!(inputStream >> input).eof())
            {
                if (IsNice(input))
                {
                    niceWords++;
                }
            }

            Assert::AreEqual(238, niceWords);
        }

        TEST_METHOD(TheString_qjhvhtzxzqqjkmpb_IsNiceEnough)
        {
            Assert::AreEqual(NiceEnough, CheckNiceness("qjhvhtzxzqqjkmpb") & NiceEnough);
        }

        TEST_METHOD(TheString_xxyxx_IsNiceEnough)
        {
            Assert::AreEqual(NiceEnough, CheckNiceness("xxyxx") & NiceEnough);
        }

        TEST_METHOD(TheString_uurcxstgmygtbstg_IsNaughtyForNoSplitDouble)
        {
            Assert::AreEqual(NiceEnough ^ HasSplitRepeat, CheckNiceness("uurcxstgmygtbstg") & NiceEnough);
        }

        TEST_METHOD(TheString_ieodomkazucvgmuy_IsNaughtyForNoRepeatPair)
        {
            Assert::AreEqual(NiceEnough ^ HasRepeatedPair, CheckNiceness("ieodomkazucvgmuy") & NiceEnough);
        }

        TEST_METHOD(Part2)
        {
            std::ifstream inputStream(SOLUTION_DIR "Part5\\input.txt");

            int niceEnoughWords = 0;

            std::string input;
            while (!(inputStream >> input).eof())
            {
                if (IsNiceEnough(input))
                {
                    niceEnoughWords++;
                }
            }

            Assert::AreEqual(69, niceEnoughWords);
        }
    };
}