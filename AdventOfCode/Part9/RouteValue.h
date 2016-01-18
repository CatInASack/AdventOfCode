#pragma once
#include <functional>

namespace Part9
{
    template <class Ordering = std::less<int>>
    class RouteValue
    {
    public:
        RouteValue(int value) : m_value(value)
        {
        }

        operator int() const
        {
            return m_value;
        }

        bool operator<(const RouteValue& other) const
        {
            return Ordering(this.m_value, other.m_value);
        }

        RouteValue operator+(int extra)
        {
            return RouteValue(m_value + extra);
        }
    private:
        int m_value;
    };
}