#include "stdafx.h"
#include "CppUnitTest.h"
#include "Grid.h"
#include "Command.h"
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft {
    namespace VisualStudio {
        namespace CppUnitTestFramework
        {
            template<>
            static std::wstring ToString<std::pair<size_t, size_t>>(const std::pair<size_t, size_t>& point)
            {
                return L"(" + std::to_wstring(point.first) + L", " + std::to_wstring(point.second) + L")";
            }

            template<>
            static std::wstring ToString<::Part6::Operation>(const ::Part6::Operation& op)
            {
                return std::to_wstring((int)op);
            }
        }
    }
}

namespace Part6
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(GridStartsAllOff)
        {
            Grid<3> test;
            Assert::AreEqual(0, test.CountOn());
        }

        TEST_METHOD(TurnOnTwoLights)
        {
            Grid<3> test;
            test.TurnOn(0, 0);
            test.TurnOn(2, 2);
            Assert::AreEqual(2, test.CountOn());
        }

        TEST_METHOD(TurnOnTwoLightsThenTurnOneOff)
        {
            Grid<3> test;
            test.TurnOn(0, 0);
            test.TurnOn(2, 2);
            test.TurnOff(0, 0);
            Assert::AreEqual(1, test.CountOn());
        }

        TEST_METHOD(TurnOffAnOffLightDoesNothing)
        {
            Grid<3> test;
            test.TurnOff(0, 0);
            Assert::AreEqual(0, test.CountOn());
        }

        TEST_METHOD(TurnOnAnOnLightDoesNothing)
        {
            Grid<3> test;
            test.TurnOn(0, 0);
            test.TurnOn(0, 0);
            Assert::AreEqual(1, test.CountOn());
        }

        TEST_METHOD(ToggleAnOffLightTurnsItOn)
        {
            Grid<3> test;
            test.Toggle(0, 0);
            Assert::AreEqual(1, test.CountOn());
        }

        TEST_METHOD(ToggleAnOnLightTurnsItOff)
        {
            Grid<3> test;
            test.TurnOn(0, 0);
            test.Toggle(0, 0);
            Assert::AreEqual(0, test.CountOn());
        }

        TEST_METHOD(ParseTurnOnCommand)
        {
            Command test("turn on 0,0 through 999,999");
            Assert::AreEqual(Operation::TurnOn, test.Operation());
            Assert::AreEqual(std::pair<size_t, size_t>(0, 0), test.Point1());
            Assert::AreEqual(std::pair<size_t, size_t>(999, 999), test.Point2());
        }

        TEST_METHOD(ParseToggleCommand)
        {
            Command test("toggle 0,0 through 999,0");
            Assert::AreEqual(Operation::Toggle, test.Operation());
            Assert::AreEqual(std::pair<size_t, size_t>(0, 0), test.Point1());
            Assert::AreEqual(std::pair<size_t, size_t>(999, 0), test.Point2());
        }

        TEST_METHOD(ParseTurnOffCommand)
        {
            Command test("turn off 499,499 through 500,500");
            Assert::AreEqual(Operation::TurnOff, test.Operation());
            Assert::AreEqual(std::pair<size_t, size_t>(499, 499), test.Point1());
            Assert::AreEqual(std::pair<size_t, size_t>(500, 500), test.Point2());
        }

        TEST_METHOD(TurnOn4LightsWithCommand)
        {
            Command testCmd("turn on 1,1 through 2,2");
            Grid<3> testGrid;
            testGrid.ApplyCommand(testCmd);
            Assert::AreEqual(4, testGrid.CountOn());
        }

        TEST_METHOD(Part1)
        {
            std::ifstream inputStream(SOLUTION_DIR "Part6\\input.txt");

            std::auto_ptr<Grid<1000>> spGrid(new Grid<1000>);

            std::string input;
            while (std::getline(inputStream, input))
            {
                Command cmd(input);
                spGrid->ApplyCommand(cmd);
            }

            Assert::AreEqual(569999, spGrid->CountOn());
        }

        TEST_METHOD(Part2)
        {
            std::ifstream inputStream(SOLUTION_DIR "Part6\\input.txt");

            std::auto_ptr<Grid<1000, Day2>> spGrid(new Grid<1000, Day2>);

            std::string input;
            while (std::getline(inputStream, input))
            {
                Command cmd(input);
                spGrid->ApplyCommand(cmd);
            }

            Assert::AreEqual(17836115, spGrid->TotalBrightness());
        }
    };
}