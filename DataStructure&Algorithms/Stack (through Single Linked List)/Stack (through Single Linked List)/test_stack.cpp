#include "gtest/gtest.h"
#include "stack.h"


// parameters: name of group of tests the second one name of specific test
TEST(StackTest1, PushDoesNotCrash) {
	Stack<int> s;
	s.push(4);
	SUCCEED(); // if code abov without errors then test passed
}

TEST(StackTest1, GetMinAfterPush) {
	Stack<int> s;
	s.push(10);
	s.push(3);
	s.push(7);

	EXPECT_EQ(s.getMin(), 3); // l am expacting that s.getMin() returns 3
}

TEST(StackTest1, MinAfterPop) {
	Stack<int> s;
	s.push(10);
	s.push(2);
	s.push(5);
	EXPECT_EQ(s.getMin(), 2);
	s.pop();
	EXPECT_EQ(s.getMin(), 2);
	s.pop();
	EXPECT_EQ(s.getMin(), 10);
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
