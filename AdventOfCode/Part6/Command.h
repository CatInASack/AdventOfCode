#pragma once
#include "Operation.h"
#include <string>
#include <map>
#include <algorithm>

namespace Part6
{
    class Command
    {
    private:
        static const std::string Through;
        static const std::map<std::string, Operation> OpMap;
    public:
        Command(const std::string& toParse)
        {
            size_t throughPos = toParse.find(Through);
            std::string opAndPt1 = toParse.substr(0, throughPos);
            std::string pt2 = toParse.substr(throughPos + Through.size());

            size_t opBreak = opAndPt1.find_last_of(' ');
            std::string op = opAndPt1.substr(0, opBreak);
            std::string pt1 = opAndPt1.substr(opBreak + 1);

            auto opIter = OpMap.find(op);
            if (opIter != OpMap.end())
            {
                _op = opIter->second;
            }
            else
            {
                throw std::exception("Unknown operation");
            }

            _pt1 = ParsePoint(pt1);
            _pt2 = ParsePoint(pt2);
        }

        Operation Operation() const
        {
            return _op;
        }

        const std::pair<size_t, size_t>& Point1() const
        {
            return _pt1;
        }

        const std::pair<size_t, size_t>& Point2() const
        {
            return _pt2;
        }
    private:
        std::pair<size_t, size_t> ParsePoint(const std::string& toParse)
        {
            size_t commaPos = toParse.find(',');
            std::string xStr = toParse.substr(0, commaPos);
            std::string yStr = toParse.substr(commaPos + 1);

            char* temp;
            size_t x = std::strtoul(xStr.data(), &temp, 10);
            size_t y = std::strtoul(yStr.data(), &temp, 10);
            return std::make_pair(x, y);
        }
    private:
        Part6::Operation _op;
        std::pair<size_t, size_t> _pt1;
        std::pair<size_t, size_t> _pt2;
    };

    const std::string Command::Through = " through ";

    const std::map<std::string, Operation> Command::OpMap =
    {
        { "turn on", Operation::TurnOn },
        { "turn off", Operation::TurnOff },
        { "toggle", Operation::Toggle },
    };

}