#include "stdafx.h"
#include "CppUnitTest.h"
#include "Grid.h"
#include "Command.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft {
    namespace VisualStudio {
        namespace CppUnitTestFramework
        {
            template<>
            static std::wstring ToString<std::pair<size_t, size_t>>(const std::pair<size_t, size_t>& point)
            {
                return L"TODO - point";
            }

            template<>
            static std::wstring ToString<::Part6::Operation>(const ::Part6::Operation& point)
            {
                return L"TODO - operation";
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
    };
}