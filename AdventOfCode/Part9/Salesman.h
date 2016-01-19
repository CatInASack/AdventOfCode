#pragma once

#include "stdafx.h"
#include <list>
#include <limits>
#include "Routes.h"
#include "RouteValue.h"

namespace Part9 
{
    template <class ValueType = RouteValue<std::less<int>, true>, int defaultValue = std::numeric_limits<int>::max()>
    class Salesman
    {
    private:
        static void tourCities_impl(const Routes& routes, const std::vector<std::string>& cityNames, ValueType& currentBest, ValueType currentRun, size_t previousCity, const std::list<size_t>& remainingCities)
        {
            auto stillRemaining = remainingCities;

            for (auto nextCity : remainingCities)
            {
                auto nextHop = routes.findDistance(cityNames[previousCity], cityNames[nextCity]);
                auto candidate = currentRun + nextHop;

                if (nextHop < 0 || currentBest.bounds(candidate))
                {
                    continue;
                }

                stillRemaining.remove(nextCity);

                if (stillRemaining.empty())
                {
                    currentBest = std::min(currentBest, candidate);
                }
                else
                {
                    tourCities_impl(routes, cityNames, currentBest, currentRun + nextHop, nextCity, stillRemaining);
                }

                stillRemaining.push_back(nextCity);
            }
        }

    public:
        static int tourCities(const Routes& routes)
        {
            auto cityNames = routes.getCities();
            auto currentBest = ValueType(defaultValue);

            auto remainingCities = std::list<size_t>();
            for (auto ii = size_t(0); ii < cityNames.size(); ii++)
            {
                remainingCities.push_back(ii);
            }

            for (auto ii = size_t(0); ii < cityNames.size(); ii++)
            {
                remainingCities.remove(ii);
                tourCities_impl(routes, cityNames, currentBest, 0, ii, remainingCities);
                remainingCities.push_back(ii);
            }

            return (int)currentBest;
        }
    };
}