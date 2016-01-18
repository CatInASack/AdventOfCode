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

        explicit operator int() const
        {
            return m_value;
        }

        inline bool operator<(const RouteValue<Ordering>& other) const
        {
            return Ordering()(this->m_value, other.m_value);
        }
        inline bool operator> (const RouteValue<Ordering>& other) { return other < *this; }
        inline bool operator<=(const RouteValue<Ordering>& other) { return !(*this > other); }
        inline bool operator>=(const RouteValue<Ordering>& other) { return !(*this < other); }

        RouteValue operator+(int extra)
        {
            return RouteValue<Ordering>(m_value + extra);
        }
    private:
        int m_value;
    };
}