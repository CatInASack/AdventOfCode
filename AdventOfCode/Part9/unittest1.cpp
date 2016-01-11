#include "stdafx.h"
#include "CppUnitTest.h"
#include "Routes.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Part9
{
    TEST_CLASS(UnitTest1)
    {
    public:
        TEST_METHOD(MissingEdgesAreNegativeOneDistance)
        {
            auto routes = Routes{};
            Assert::AreEqual(-1, routes.findDistance("London", "Dublin"));
        }

        TEST_METHOD(ParseEdge)
        {
            auto routes = Routes{};
            routes.addRoute("London to Dublin = 464");
            Assert::AreEqual(464, routes.findDistance("London", "Dublin"));
        }

        TEST_METHOD(EdgesAreOrderInsensitive)
        {
            auto routes = Routes{};
            routes.addRoute("London to Dublin = 464");
            Assert::AreEqual(464, routes.findDistance("Dublin", "London"));
        }

        TEST_METHOD(ParseMultipleEdges)
        {
            auto routes = Routes{};
            routes.addRoute("London to Dublin = 464");
            routes.addRoute("London to Belfast = 518");
            routes.addRoute("Dublin to Belfast = 141");
            Assert::AreEqual(464, routes.findDistance("London", "Dublin"));
            Assert::AreEqual(518, routes.findDistance("London", "Belfast"));
            Assert::AreEqual(141, routes.findDistance("Dublin", "Belfast"));
        }

        TEST_METHOD(CanGetNamesOfAllCities)
        {
            auto routes = Routes{};
            routes.addRoute("London to Dublin = 464");
            routes.addRoute("London to Belfast = 518");
            routes.addRoute("Dublin to Belfast = 141");
            auto cities = routes.getCities();
            Assert::AreEqual(3, static_cast<int>(cities.size()));
            Assert::AreEqual("Belfast", cities[0].c_str());
            Assert::AreEqual("Dublin", cities[1].c_str());
            Assert::AreEqual("London", cities[2].c_str());
        }
    };
}