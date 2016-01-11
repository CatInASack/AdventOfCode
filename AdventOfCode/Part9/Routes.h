#pragma once

#include "stdafx.h"
#include <map>
#include <vector>
#include <set>
#include "boost/algorithm/string.hpp"

namespace Part9
{
    class Routes
    {
    private:
        auto edgeName(const std::string& city1, const std::string& city2) const
        {
            if (city1 > city2)
            {
                return std::make_pair(city2, city1);
            }
            else
            {
                return std::make_pair(city1, city2);
            }
        }
    public:
        Routes()
        {
        }

        void addRoute(const std::string& newRoute)
        {
            auto tokens = std::vector<std::string>{};
            boost::split(tokens, newRoute, boost::is_any_of(" "));

            if (tokens.size() != 5 || tokens[1] != "to" || tokens[3] != "=")
            {
                throw std::logic_error("Route not in expected format");
            }

            auto city1 = tokens[0];
            auto city2 = tokens[2];
            auto distance = std::atoi(tokens[4].data());

            _citiesCache.insert(city1);
            _citiesCache.insert(city2);

            _distances[edgeName(city1, city2)] = distance;
        }

        auto findDistance(const std::string& city1, const std::string& city2) const
        {
            auto edge = _distances.find(edgeName(city1, city2));
            return edge == _distances.end() ? -1 : edge->second;
        }

        auto getCities() const
        {
            auto cities = std::vector<std::string>{};
            std::copy(_citiesCache.begin(), _citiesCache.end(), std::back_inserter(cities));
            return cities;
        }

    private:
        std::set<std::string> _citiesCache;
        std::map<std::pair<std::string, std::string>, int> _distances;
    };
}