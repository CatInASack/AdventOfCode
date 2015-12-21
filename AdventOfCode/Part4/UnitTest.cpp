#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include <robuffer.h>
#include <wrl/client.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Windows::Security::Cryptography;
using namespace Windows::Security::Cryptography::Core;
using namespace Windows::Storage::Streams;
using namespace Microsoft::WRL;

namespace Part4
{
    TEST_CLASS(UnitTest4)
    {
    private:
        byte* BufferBytes(IBuffer^ buffer)
        {
            ComPtr<IInspectable> spInsp(reinterpret_cast<IInspectable*>((Platform::Object^)buffer));
            ComPtr<IBufferByteAccess> spByteAccess;
            spInsp.As(&spByteAccess);
            byte* bufferBytes;
            spByteAccess->Buffer(&bufferBytes);
            return bufferBytes;
        }

        unsigned int MineCoin(const std::string& key, int len)
        {
            unsigned int candidate = 0;
            HashAlgorithmProvider^ md5 = HashAlgorithmProvider::OpenAlgorithm(HashAlgorithmNames::Md5);

            while (1)
            {
                std::string candidateString = key + std::to_string(candidate);
                Buffer^ buffer = ref new Buffer((int)candidateString.length());
                buffer->Length = (int)candidateString.length();

                memcpy(BufferBytes(buffer), candidateString.c_str(), candidateString.length());

                IBuffer^ hash = md5->HashData(buffer);

                Platform::String^ hashString = CryptographicBuffer::EncodeToHexString(hash);

                int countZeroes = 0;
                for (wchar_t ch : hashString)
                {
                    if (ch == L'0')
                    {
                        countZeroes++;
                    }
                    else
                    {
                        break;
                    }
                }

                if (countZeroes >= len)
                {
                    return candidate;
                }

                candidate++;
            }

            return -1;
        }

    public:
        TEST_METHOD(TestMethod1)
        {
            //If the secret key is abcdef, the answer is 609043, because the MD5 hash of abcdef609043 starts with five zeroes(000001dbbfa...
            Assert::AreEqual((unsigned int)609043, MineCoin("abcdef", 5));
        }

        TEST_METHOD(TestMethod2)
        {
            // If your secret key is pqrstuv, the lowest number it combines with to make an MD5 hash starting with five zeroes is 1048970
            Assert::AreEqual((unsigned int)1048970, MineCoin("pqrstuv", 5));
        }

        TEST_METHOD(Part1)
        {
            Assert::AreEqual((unsigned int)254575, MineCoin("bgvyzdsv", 5));
        }

        TEST_METHOD(Part2)
        {
            Assert::AreEqual((unsigned int)1038736, MineCoin("bgvyzdsv", 6));
        }
    };
}