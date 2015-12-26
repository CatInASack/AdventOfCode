#pragma once

#include "SignalCarrier.h"
#include <map>

namespace Part7
{
    class WireRegistry
    {
    public:
        std::shared_ptr<SignalCarrier>& getByName(const std::string& name)
        {
            std::shared_ptr<SignalCarrier>& value = _wires[name];
            if (!value)
            {
                value.reset(new Wire(name));
            }
            return value;
        }

        void Parse(const std::string& input)
        {
            size_t assignPos = input.find(AssignToken);

            std::string lValue = input.substr(0, assignPos);
            std::string rValue = input.substr(assignPos + AssignToken.size());

            std::shared_ptr<SignalCarrier>& spWire = getByName(rValue);

            spWire->connectInputA(ParseLValue(lValue));
        }
    private:
        std::shared_ptr<SignalCarrier> ParseLValue(const std::string& input)
        {
            size_t leftBreak = input.find(' ');
            size_t rightBreak = input.rfind(' ');

            std::shared_ptr<SignalCarrier> spValue;

            if (leftBreak == std::string::npos)
            {
                spValue = ParseSymbol(input);
            }
            else if (leftBreak == rightBreak)
            {
                std::string rightValue = input.substr(leftBreak + 1);
                spValue.reset(new Not());
                std::shared_ptr<SignalCarrier> spA(ParseSymbol(rightValue));
                spValue->connectInputA(spA);
            }
            else
            {
                std::string leftValue = input.substr(0, leftBreak);
                std::string rightValue = input.substr(rightBreak + 1);
                std::string gateName = input.substr(leftBreak + 1, rightBreak - leftBreak - 1);

                if (gateName == "AND")
                {
                    spValue.reset(new And());
                }
                else if (gateName == "OR")
                {
                    spValue.reset(new Or());
                }
                else if (gateName == "LSHIFT")
                {
                    spValue.reset(new LShift());
                }
                else if (gateName == "RSHIFT")
                {
                    spValue.reset(new RShift());
                }

                spValue->connectInputA(ParseSymbol(leftValue));
                spValue->connectInputB(ParseSymbol(rightValue));
            }

            return spValue;
        }

        std::shared_ptr<SignalCarrier> ParseSymbol(const std::string& input)
        {
            if (input.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz") != std::string::npos)
            {
                return std::shared_ptr<SignalCarrier>(new Signal(std::atoi(input.c_str())));
            }

            return getByName(input);
        }
    private:
        std::map<std::string, std::shared_ptr<SignalCarrier>> _wires;
        static const std::string AssignToken;
    };

    const std::string WireRegistry::AssignToken(" -> ");
}