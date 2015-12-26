#pragma once

#include <stdexcept>
#include <memory>

namespace Part7
{
    class SignalCarrier
    {
    public:
        virtual unsigned __int16 value() = 0;
        virtual bool hasValue() const = 0;
        virtual void recalculate() {}
        virtual void connectInputA(const std::shared_ptr<SignalCarrier>&)
        {
            throw std::logic_error("This element does not have an input A.");
        }
        virtual void connectInputB(const std::shared_ptr<SignalCarrier>&)
        {
            throw std::logic_error("This element does not have an input B.");
        }
    };

    class Signal : public SignalCarrier
    {
    public:
        Signal(unsigned __int16 value) : _value(value) {}
        virtual unsigned __int16 value() { return _value; }
        virtual bool hasValue() const { return true; }
    private:
        unsigned __int16 _value;
    };

    class OneInput : public SignalCarrier
    {
    public:
        virtual unsigned __int16 value() = 0;

        virtual bool hasValue() const
        {
            return _a && _a->hasValue();
        }

        virtual void connectInputA(const std::shared_ptr<SignalCarrier>& input)
        {
            _a = input;
        }
    protected:
        std::shared_ptr<SignalCarrier> _a;
    };

    class Wire : public OneInput
    {
    public:
        Wire(const std::string& name) : _name(name), _cachedValue(-1) {}

        virtual unsigned __int16 value()
        {
            if (_cachedValue < 0)
            {
                _cachedValue = _a->value();
            }
            return _cachedValue;
        }

        virtual void recalculate()
        {
            _cachedValue = -1;
        }
    private:
        __int32 _cachedValue;
        std::string _name;
    };

    class Not : public OneInput
    {
    public:
        virtual unsigned __int16 value()
        {
            return ~_a->value();
        }
    };

    class TwoInput : public OneInput
    {
    public:
        virtual unsigned __int16 value() = 0;

        virtual bool hasValue() const
        {
            return _a && _b && _a->hasValue() && _b->hasValue();
        }

        virtual void connectInputB(const std::shared_ptr<SignalCarrier>& input)
        {
            _b = input;
        }
    protected:
        std::shared_ptr<SignalCarrier> _b;
    };

    class And : public TwoInput
    {
    public:
        virtual unsigned __int16 value()
        {
            return _a->value() & _b->value();
        }
    };

    class Or : public TwoInput
    {
    public:
        virtual unsigned __int16 value()
        {
            return _a->value() | _b->value();
        }
    };

    class LShift : public TwoInput
    {
    public:
        virtual unsigned __int16 value()
        {
            return _a->value() << _b->value();
        }
    };

    class RShift : public TwoInput
    {
    public:
        virtual unsigned __int16 value()
        {
            return _a->value() >> _b->value();
        }
    };
}