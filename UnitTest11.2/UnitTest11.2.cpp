#include "pch.h"
#include "CppUnitTest.h"
#include "../Project11.2/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest112
{
	TEST_CLASS(UnitTest112)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Specialty specialty = MATH_ECONOMICS;
			const char* str = specialtiesToString(specialty);
			Assert::AreEqual("Mathematics and economics", str);
		}
	};
}
