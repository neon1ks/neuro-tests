#include <gtest/gtest.h>
#include "narray.h"

TEST(narray, test01) {
	NArray<int> test_array;
	ASSERT_EQ(int(0), test_array.getSize());
	ASSERT_EQ(int(0), test_array.getLenght());
	ASSERT_EQ(int(1), test_array.getBlock());
	int *p = nullptr;
	ASSERT_EQ(p, test_array.getData());
}

TEST(narray, test02) {
	const int Len = 5;
	NArray<int> test_array = NArray<int>(Len);
	ASSERT_EQ(Len, test_array.getSize());

	for (int i = 0; i < Len; ++i) {
		test_array.set(i, i);
		ASSERT_EQ(i, test_array.get(i));
		ASSERT_EQ(i + 1, test_array.getLenght());
	}
}

int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
