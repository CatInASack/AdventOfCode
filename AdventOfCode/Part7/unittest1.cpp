#include "stdafx.h"
#include "CppUnitTest.h"
#include "SignalCarrier.h"
#include <memory>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft
{
    namespace VisualStudio
    {
        namespace CppUnitTestFramework
        {
            template<>
            std::wstring ToString<unsigned __int16>(const unsigned __int16& value)
            {
                return std::to_wstring(value);
            }
        }
    }
}
namespace Part7
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(SignalHasItsConstructedValue)
        {
            std::shared_ptr<SignalCarrier> spTest(new Signal(42));
            Assert::IsTrue(spTest->hasValue());
            Assert::AreEqual((unsigned short)42, spTest->value());
        }

        TEST_METHOD(EmptyOneInputHasNoValue)
        {
            std::shared_ptr<OneInput> spTest(new Wire());
            Assert::IsFalse(spTest->hasValue());
        }

        TEST_METHOD(WireAttachedToSignalHasSignalsValue)
        {
            std::shared_ptr<SignalCarrier> spSignal(new Signal(42));
            std::shared_ptr<OneInput> spTest(new Wire());
            spTest->connectInputA(spSignal);
            Assert::IsTrue(spTest->hasValue());
            Assert::AreEqual((unsigned __int16)42, spTest->value());
        }

        TEST_METHOD(EmptyTwoInputHasNoValue)
        {
            std::shared_ptr<TwoInput> spTest(new And());
            Assert::IsFalse(spTest->hasValue());
        }

        TEST_METHOD(TwoInputWithOnlyOneAttachedHasNoValue)
        {
            std::shared_ptr<SignalCarrier> spSignal(new Signal(7));
            std::shared_ptr<TwoInput> spTest(new And());
            spTest->connectInputA(spSignal);
            Assert::IsFalse(spTest->hasValue());
        }

        TEST_METHOD(AndWithTwoSignalsAsInputHasTheAndedValue)
        {
            std::shared_ptr<SignalCarrier> spSignal1(new Signal(7));
            std::shared_ptr<SignalCarrier> spSignal2(new Signal(11));
            std::shared_ptr<TwoInput> spTest(new And());
            spTest->connectInputA(spSignal1);
            spTest->connectInputB(spSignal2);
            Assert::IsTrue(spTest->hasValue());
            Assert::AreEqual((unsigned __int16)3, spTest->value());
        }

        TEST_METHOD(OrWithTwoValuesHasTheOredValue)
        {
            std::shared_ptr<SignalCarrier> spSignal1(new Signal(6));
            std::shared_ptr<SignalCarrier> spSignal2(new Signal(3));
            std::shared_ptr<TwoInput> spTest(new Or());
            spTest->connectInputA(spSignal1);
            spTest->connectInputB(spSignal2);
            Assert::IsTrue(spTest->hasValue());
            Assert::AreEqual((unsigned __int16)7, spTest->value());
        }

        TEST_METHOD(NotWithValueHasTheBitwiseNot)
        {
            std::shared_ptr<SignalCarrier> spSignal(new Signal(65534));
            std::shared_ptr<OneInput> spTest(new Not());
            spTest->connectInputA(spSignal);
            Assert::IsTrue(spTest->hasValue());
            Assert::AreEqual((unsigned __int16)1, spTest->value());
        }

        TEST_METHOD(LShiftWithTwoValuesHasTheShiftedValue)
        {
            std::shared_ptr<SignalCarrier> spSignal1(new Signal(3));
            std::shared_ptr<SignalCarrier> spSignal2(new Signal(1));
            std::shared_ptr<TwoInput> spTest(new LShift());
            spTest->connectInputA(spSignal1);
            spTest->connectInputB(spSignal2);
            Assert::IsTrue(spTest->hasValue());
            Assert::AreEqual((unsigned __int16)6, spTest->value());
        }

        TEST_METHOD(RShiftWithTwoValuesHasTheShiftedValue)
        {
            std::shared_ptr<SignalCarrier> spSignal1(new Signal(6));
            std::shared_ptr<SignalCarrier> spSignal2(new Signal(1));
            std::shared_ptr<TwoInput> spTest(new RShift());
            spTest->connectInputA(spSignal1);
            spTest->connectInputB(spSignal2);
            Assert::IsTrue(spTest->hasValue());
            Assert::AreEqual((unsigned __int16)3, spTest->value());
        }

        TEST_METHOD(LackOfValuesPropagate)
        {
            std::shared_ptr<SignalCarrier> spSignal1a(new Signal(6));
            std::shared_ptr<SignalCarrier> spSignal2(new Signal(7));
            std::shared_ptr<TwoInput> spShift(new RShift());
            std::shared_ptr<TwoInput> spAnd(new And());
            spShift->connectInputA(spSignal1a);
            spAnd->connectInputA(spShift);
            spAnd->connectInputB(spSignal2);
            Assert::IsFalse(spShift->hasValue());
            Assert::IsFalse(spAnd->hasValue());
        }

        TEST_METHOD(ValuesPropagate)
        {
            std::shared_ptr<SignalCarrier> spSignal1a(new Signal(6));
            std::shared_ptr<SignalCarrier> spSignal1b(new Signal(1));
            std::shared_ptr<SignalCarrier> spSignal2(new Signal(5));
            std::shared_ptr<TwoInput> spShift(new RShift());
            std::shared_ptr<TwoInput> spOr(new Or());
            spShift->connectInputA(spSignal1a);
            spShift->connectInputB(spSignal1b);
            spOr->connectInputA(spShift);
            spOr->connectInputB(spSignal2);
            Assert::IsTrue(spShift->hasValue());
            Assert::AreEqual((unsigned __int16)3, spShift->value());
            Assert::IsTrue(spOr->hasValue());
            Assert::AreEqual((unsigned __int16)7, spOr->value());
        }
    };
}