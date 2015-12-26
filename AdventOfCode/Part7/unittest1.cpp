#include "stdafx.h"
#include "CppUnitTest.h"
#include "WireRegistry.h"

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
            std::shared_ptr<SignalCarrier> spTest(new Wire());
            Assert::IsFalse(spTest->hasValue());
        }

        TEST_METHOD(WireAttachedToSignalHasSignalsValue)
        {
            std::shared_ptr<SignalCarrier> spSignal(new Signal(42));
            std::shared_ptr<SignalCarrier> spTest(new Wire());
            spTest->connectInputA(spSignal);
            Assert::IsTrue(spTest->hasValue());
            Assert::AreEqual((unsigned __int16)42, spTest->value());
        }

        TEST_METHOD(EmptyTwoInputHasNoValue)
        {
            std::shared_ptr<SignalCarrier> spTest(new And());
            Assert::IsFalse(spTest->hasValue());
        }

        TEST_METHOD(TwoInputWithOnlyOneAttachedHasNoValue)
        {
            std::shared_ptr<SignalCarrier> spSignal(new Signal(7));
            std::shared_ptr<SignalCarrier> spTest(new And());
            spTest->connectInputA(spSignal);
            Assert::IsFalse(spTest->hasValue());
        }

        TEST_METHOD(AndWithTwoSignalsAsInputHasTheAndedValue)
        {
            std::shared_ptr<SignalCarrier> spSignal1(new Signal(7));
            std::shared_ptr<SignalCarrier> spSignal2(new Signal(11));
            std::shared_ptr<SignalCarrier> spTest(new And());
            spTest->connectInputA(spSignal1);
            spTest->connectInputB(spSignal2);
            Assert::IsTrue(spTest->hasValue());
            Assert::AreEqual((unsigned __int16)3, spTest->value());
        }

        TEST_METHOD(OrWithTwoValuesHasTheOredValue)
        {
            std::shared_ptr<SignalCarrier> spSignal1(new Signal(6));
            std::shared_ptr<SignalCarrier> spSignal2(new Signal(3));
            std::shared_ptr<SignalCarrier> spTest(new Or());
            spTest->connectInputA(spSignal1);
            spTest->connectInputB(spSignal2);
            Assert::IsTrue(spTest->hasValue());
            Assert::AreEqual((unsigned __int16)7, spTest->value());
        }

        TEST_METHOD(NotWithValueHasTheBitwiseNot)
        {
            std::shared_ptr<SignalCarrier> spSignal(new Signal(65534));
            std::shared_ptr<SignalCarrier> spTest(new Not());
            spTest->connectInputA(spSignal);
            Assert::IsTrue(spTest->hasValue());
            Assert::AreEqual((unsigned __int16)1, spTest->value());
        }

        TEST_METHOD(LShiftWithTwoValuesHasTheShiftedValue)
        {
            std::shared_ptr<SignalCarrier> spSignal1(new Signal(3));
            std::shared_ptr<SignalCarrier> spSignal2(new Signal(1));
            std::shared_ptr<SignalCarrier> spTest(new LShift());
            spTest->connectInputA(spSignal1);
            spTest->connectInputB(spSignal2);
            Assert::IsTrue(spTest->hasValue());
            Assert::AreEqual((unsigned __int16)6, spTest->value());
        }

        TEST_METHOD(RShiftWithTwoValuesHasTheShiftedValue)
        {
            std::shared_ptr<SignalCarrier> spSignal1(new Signal(6));
            std::shared_ptr<SignalCarrier> spSignal2(new Signal(1));
            std::shared_ptr<SignalCarrier> spTest(new RShift());
            spTest->connectInputA(spSignal1);
            spTest->connectInputB(spSignal2);
            Assert::IsTrue(spTest->hasValue());
            Assert::AreEqual((unsigned __int16)3, spTest->value());
        }

        TEST_METHOD(LackOfValuesPropagate)
        {
            std::shared_ptr<SignalCarrier> spSignal1a(new Signal(6));
            std::shared_ptr<SignalCarrier> spSignal2(new Signal(7));
            std::shared_ptr<SignalCarrier> spShift(new RShift());
            std::shared_ptr<SignalCarrier> spAnd(new And());
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
            std::shared_ptr<SignalCarrier> spShift(new RShift());
            std::shared_ptr<SignalCarrier> spOr(new Or());
            spShift->connectInputA(spSignal1a);
            spShift->connectInputB(spSignal1b);
            spOr->connectInputA(spShift);
            spOr->connectInputB(spSignal2);
            Assert::IsTrue(spShift->hasValue());
            Assert::AreEqual((unsigned __int16)3, spShift->value());
            Assert::IsTrue(spOr->hasValue());
            Assert::AreEqual((unsigned __int16)7, spOr->value());
        }

        TEST_METHOD(WireRegistryCreatesWiresWithNoValues)
        {
            WireRegistry registry;
            std::shared_ptr<SignalCarrier> spWire = registry.getByName("a");
            Assert::IsFalse(spWire->hasValue());
        }

        TEST_METHOD(WireRegistryRemembersWiresItCreates)
        {
            WireRegistry registry;
            std::shared_ptr<SignalCarrier> spWire = registry.getByName("a");
            Assert::IsFalse(spWire->hasValue());
            std::shared_ptr<SignalCarrier> spSignal(new Signal(42));
            spWire->connectInputA(spSignal);
            std::shared_ptr<SignalCarrier> spWireAgainLol = registry.getByName("a");
            Assert::IsTrue(spWire->hasValue());
            Assert::AreEqual(spWire->value(), spWireAgainLol->value());
        }

        TEST_METHOD(ParseSimpleWire)
        {
            WireRegistry registry;
            registry.Parse("123 -> x");
            std::shared_ptr<SignalCarrier> spWireX = registry.getByName("x");
            Assert::AreEqual((unsigned __int16)123, spWireX->value());
        }

        TEST_METHOD(ParseSimpleAndGate)
        {
            WireRegistry registry;
            registry.Parse("123 AND 456 -> d");
            std::shared_ptr<SignalCarrier> spWireD = registry.getByName("d");
            Assert::AreEqual((unsigned __int16)72, spWireD->value());
        }

        TEST_METHOD(ParseSimpleOrGate)
        {
            WireRegistry registry;
            registry.Parse("1 OR 2 -> x");
            std::shared_ptr<SignalCarrier> spWireX = registry.getByName("x");
            Assert::AreEqual((unsigned __int16)3, spWireX->value());
        }

        TEST_METHOD(ParseSimpleLShiftGate)
        {
            WireRegistry registry;
            registry.Parse("1 LSHIFT 2 -> x");
            std::shared_ptr<SignalCarrier> spWireX = registry.getByName("x");
            Assert::AreEqual((unsigned __int16)4, spWireX->value());
        }

        TEST_METHOD(ParseSimpleRShiftGate)
        {
            WireRegistry registry;
            registry.Parse("15 RSHIFT 2 -> x");
            std::shared_ptr<SignalCarrier> spWireX = registry.getByName("x");
            Assert::AreEqual((unsigned __int16)3, spWireX->value());
        }

        TEST_METHOD(ParseSimpleNotGate)
        {
            WireRegistry registry;
            registry.Parse("NOT 65530 -> x");
            std::shared_ptr<SignalCarrier> spWireX = registry.getByName("x");
            Assert::AreEqual((unsigned __int16)5, spWireX->value());
        }

        TEST_METHOD(ParseVarNotGate)
        {
            WireRegistry registry;
            registry.Parse("65530 -> y");
            registry.Parse("NOT y -> x");
            std::shared_ptr<SignalCarrier> spWireX = registry.getByName("x");
            Assert::AreEqual((unsigned __int16)5, spWireX->value());
        }

        TEST_METHOD(ParseVarRShiftGate)
        {
            WireRegistry registry;
            registry.Parse("15 -> y");
            registry.Parse("2 -> z");
            registry.Parse("y RSHIFT z -> x");
            std::shared_ptr<SignalCarrier> spWireX = registry.getByName("x");
            Assert::AreEqual((unsigned __int16)3, spWireX->value());
        }

        TEST_METHOD(ParseVarLShiftGate)
        {
            WireRegistry registry;
            registry.Parse("1 -> y");
            registry.Parse("2 -> z");
            registry.Parse("y LSHIFT z -> x");
            std::shared_ptr<SignalCarrier> spWireX = registry.getByName("x");
            Assert::AreEqual((unsigned __int16)4, spWireX->value());
        }

        TEST_METHOD(ParseVarOrGate)
        {
            WireRegistry registry;
            registry.Parse("1 -> y");
            registry.Parse("2 -> z");
            registry.Parse("y OR z -> x");
            std::shared_ptr<SignalCarrier> spWireX = registry.getByName("x");
            Assert::AreEqual((unsigned __int16)3, spWireX->value());
        }

        TEST_METHOD(ParseVarAndGate)
        {
            WireRegistry registry;
            registry.Parse("123 -> y");
            registry.Parse("456 -> z");
            registry.Parse("y AND z -> d");
            std::shared_ptr<SignalCarrier> spWireD = registry.getByName("d");
            Assert::AreEqual((unsigned __int16)72, spWireD->value());
        }

        TEST_METHOD(ParseLongName)
        {
            WireRegistry registry;
            registry.Parse("123 -> myLongName");
            registry.Parse("myLongName -> x");
            std::shared_ptr<SignalCarrier> spWireX = registry.getByName("x");
            Assert::AreEqual((unsigned __int16)123, spWireX->value());
        }

        TEST_METHOD(DefinitionDoesntNeedToHappenInOrder)
        {
            WireRegistry registry;
            registry.Parse("y AND z -> d");
            registry.Parse("123 -> y");
            registry.Parse("456 -> z");
            std::shared_ptr<SignalCarrier> spWireD = registry.getByName("d");
            Assert::AreEqual((unsigned __int16)72, spWireD->value());
        }

        TEST_METHOD(LongExample)
        {
            WireRegistry registry;
            registry.Parse("123 -> x");
            registry.Parse("456 -> y");
            registry.Parse("x AND y -> d");
            registry.Parse("x OR y -> e");
            registry.Parse("x LSHIFT 2 -> f");
            registry.Parse("y RSHIFT 2 -> g");
            registry.Parse("NOT x -> h");
            registry.Parse("NOT y -> i");
            Assert::AreEqual((unsigned __int16)72, registry.getByName("d")->value());
            Assert::AreEqual((unsigned __int16)507, registry.getByName("e")->value());
            Assert::AreEqual((unsigned __int16)492, registry.getByName("f")->value());
            Assert::AreEqual((unsigned __int16)114, registry.getByName("g")->value());
            Assert::AreEqual((unsigned __int16)65412, registry.getByName("h")->value());
            Assert::AreEqual((unsigned __int16)65079, registry.getByName("i")->value());
            Assert::AreEqual((unsigned __int16)123, registry.getByName("x")->value());
            Assert::AreEqual((unsigned __int16)456, registry.getByName("y")->value());
        }
    };
}