#include "stdafx.h"
#include "CppUnitTest.h"
#include <map>
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Part3
{
    TEST_CLASS(UnitTest3)
    {
    private:
        void ProcessMove(
            char move,
            std::pair<int, int>& pos,
            std::map<std::pair<int, int>, int>& visited)
        {
            switch (move)
            {
            case '^':
                pos.second++;
                break;
            case 'v':
                pos.second--;
                break;
            case '<':
                pos.first--;
                break;
            case '>':
                pos.first++;
                break;
            }

            visited[pos]++;
        }

        int CountHouses(const std::string& input)
        {
            std::map<std::pair<int, int>, int> visited;
            std::pair<int, int> santa = std::make_pair(0, 0);

            visited[santa]++;

            for (char direction : input)
            {
                ProcessMove(direction, santa, visited);
            }

            return (int)visited.size();
        }

        int CountHousesEx(const std::string& input)
        {
            std::map<std::pair<int, int>, int> visited;
            std::pair<int, int> activeSanta = std::make_pair(0, 0);
            std::pair<int, int> reserveSanta = std::make_pair(0, 0);

            visited[activeSanta]++;
            visited[reserveSanta]++;

            for (char direction : input)
            {
                ProcessMove(direction, activeSanta, visited);
                std::swap(activeSanta, reserveSanta);
            }

            return (int)visited.size();
        }
    public:

        TEST_METHOD(Move1EastEquals2Houses)
        {
            Assert::AreEqual(2, CountHouses(">"));
        }

        TEST_METHOD(MoveInUnitCircleEquals4Houses)
        {
            Assert::AreEqual(4, CountHouses("^>v<"));
        }

        TEST_METHOD(MoveUpAndDownInPlaceEquals2houses)
        {
            Assert::AreEqual(2, CountHouses("^v^v^v^v^v"));
        }

        TEST_METHOD(Part1)
        {
            std::string input;
            std::ifstream inputStream(SOLUTION_DIR "Part3\\input.txt");
            inputStream >> input;
            Assert::AreEqual(2565, CountHouses(input));
        }

        TEST_METHOD(MoveOnceEachEquals3Houses)
        {
            Assert::AreEqual(3, CountHousesEx("^v"));
        }

        TEST_METHOD(MoveInNotReallyCircleEquals3Houses)
        {
            Assert::AreEqual(3, CountHousesEx("^>v<"));
        }

        TEST_METHOD(Move5EachInDifferentDirectionsEquals11Houses)
        {
            Assert::AreEqual(11, CountHousesEx("^v^v^v^v^v"));
        }

        TEST_METHOD(Part2)
        {
            std::string input;
            std::ifstream inputStream(SOLUTION_DIR "Part3\\input.txt");
            inputStream >> input;
            Assert::AreEqual(2639, CountHousesEx(input));
        }
    };
}