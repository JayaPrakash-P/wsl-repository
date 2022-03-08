#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <iostream>

using namespace std;

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

class IntPtrWrapper
{
	int* intPtr = nullptr;
public:
	IntPtrWrapper()
	{
		cout << "IntPtrWrapper - CTOR\n";
		intPtr = new int(100);
		Display();
	}
	~IntPtrWrapper()
	{
		cout << "IntPtrWrapper - DTOR\n";		
		Display();
		delete intPtr;
		intPtr = nullptr;
	}

	void Display()
	{
		cout << "IntPtrWrapper(*intPtr) = " << (*intPtr) << "\n";
	}

	void SetValue(int value)
	{
		if (intPtr)
			*intPtr = value;
		else
			intPtr = new int(value);
	}
	int GetValue()
	{
		return (*intPtr);
	}
};

struct IntPtrWrapperTest : public testing::Test
{
	IntPtrWrapper* myInt;

	IntPtrWrapperTest()
	{
		cout << "IntPtrWrapperTest - CTOR\n";
		myInt = new IntPtrWrapper();
		myInt->Display();
	}
	
	~IntPtrWrapperTest()
	{
		myInt->Display();
		delete myInt;
		myInt = nullptr;
	}
};

TEST_F(IntPtrWrapperTest, IntPtrWrapperInitTest)
{
	EXPECT_EQ(100, myInt->GetValue());
}

TEST_F(IntPtrWrapperTest, IntPtrWrapperSetTest)
{
	EXPECT_EQ(100, myInt->GetValue());
	myInt->SetValue(200);
	EXPECT_EQ(200, myInt->GetValue());
}

int main(int argc, char** argv)
{
	cout << "Emtering main...\n";
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}