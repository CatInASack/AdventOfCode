#pragma once

#include "stdafx.h"
#include <list>
#include <limits>
#include "Routes.h"
#include "RouteValue.h"

namespace Part9 
{
    template <class Ordering = std::less<int>, int defaultValue = std::numeric_limits<int>::max()>
    class Salesman
    {
    private:
        static void tourCities_impl(const Routes& routes, const std::vector<std::string>& cityNames, RouteValue<Ordering>& currentBest, RouteValue<Ordering> currentRun, size_t previousCity, const std::list<size_t>& remainingCities)
        {
            auto stillRemaining = remainingCities;

            for (auto nextCity : remainingCities)
            {
                auto nextHop = routes.findDistance(cityNames[previousCity], cityNames[nextCity]);
                if (nextHop < 0 || currentRun + nextHop >= currentBest)
                {
                    continue;
                }

                stillRemaining.remove(nextCity);

                if (stillRemaining.empty())
                {
                    currentBest = currentRun + nextHop;
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
            auto currentBest = RouteValue<Ordering>(defaultValue);

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

            return currentBest;
        }
    };
}