#pragma once

#include "Operation.h"
#include "Command.h"

namespace Part6
{
    template <size_t Size>
    class Grid
    {
    public:
        Grid()
        {
            for (size_t col = 0; col < Size; col++)
            {
                for (size_t row = 0; row < Size; row++)
                {
                    _elements[col][row] = 0;
                }
            }
        }

        void ApplyCommand(const Command& command)
        {
            size_t lowX = std::min(command.Point1().first, command.Point2().first);
            size_t highX = std::max(command.Point1().first, command.Point2().first);
            size_t lowY = std::min(command.Point1().second, command.Point2().second);
            size_t highY = std::max(command.Point1().second, command.Point2().second);

            for (size_t x = lowX; x <= highX; x++)
            {
                for (size_t y = lowY; y <= highY; y++)
                {
                    UpdateElement(command.Operation(), x, y);
                }
            }
        }

        void UpdateElement(Operation op, size_t x, size_t y)
        {
            int& value = _elements[x][y];
            switch (op)
            {
            case Operation::TurnOn:
                value = 1;
                break;
            case Operation::TurnOff:
                value = 0;
                break;
            case Operation::Toggle:
                value = value ? 0 : 1;
                break;
            }
        }

        void TurnOn(size_t x, size_t y)
        {
            UpdateElement(Operation::TurnOn, x, y);
        }

        void TurnOff(size_t x, size_t y)
        {
            UpdateElement(Operation::TurnOff, x, y);
        }

        void Toggle(size_t x, size_t y)
        {
            UpdateElement(Operation::Toggle, x, y);
        }

        int CountOn() const
        {
            int on = 0;
            for (size_t col = 0; col < Size; col++)
            {
                for (size_t row = 0; row < Size; row++)
                {
                    if (_elements[row][col] > 0)
                    {
                        on++;
                    }
                }
            }

            return on;
        }
    private:
        int _elements[Size][Size];
    };
}