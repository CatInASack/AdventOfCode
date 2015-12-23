#pragma once

namespace Part6
{
    enum Operation
    {
        TurnOn,
        TurnOff,
        Toggle,
    };

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
                    _elements[col][row] = false;
                }
            }
        }

        void UpdateElement(Operation op, size_t x, size_t y)
        {
            bool& value = _elements[x][y];
            switch (op)
            {
            case Operation::TurnOn:
                value = true;
                break;
            case Operation::TurnOff:
                value = false;
                break;
            case Operation::Toggle:
                value = !value;
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
                    if (_elements[row][col])
                    {
                        on++;
                    }
                }
            }

            return on;
        }
    private:
        bool _elements[Size][Size];
    };
}