#pragma once
#include <functional>

namespace Part9
{
    template <class Ordering, bool Boundable>
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

        inline bool operator<(const RouteValue<Ordering, Boundable>& other) const
        {
            return Ordering()(this->m_value, other.m_value);
        }

        bool bounds(const RouteValue<Ordering, Boundable>& other) const
        {
            return Boundable ? *this < other : false;
        }

        RouteValue operator+(int extra)
        {
            return RouteValue<Ordering, Boundable>(m_value + extra);
        }
    private:
        int m_value;
    };
}