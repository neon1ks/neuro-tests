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

TEST(narray, test03) {
	NArray<int> test_array;
	ASSERT_EQ(int(1), test_array.getBlock());
	test_array.setBlock(-5);
	ASSERT_EQ(int(1), test_array.getBlock());

	const int Len = 5;
	test_array.setBlock(Len);
	ASSERT_EQ(int(Len), test_array.getBlock());
}

// Проверка метода NArray<NType>::resize()
TEST(narray, test04) {
	NArray<int> test_array;
	ASSERT_EQ(int(0), test_array.getSize());
	ASSERT_EQ(int(0), test_array.getLenght());
	int *p = nullptr;
	ASSERT_EQ(p, test_array.getData());

	// Увеличиваем m_size до 5
	const int Five = 5;
	ASSERT_NE(Five, test_array.getSize());
	test_array.resize(Five);
	ASSERT_EQ(Five, test_array.getSize());
	ASSERT_EQ(int(0), test_array.getLenght());
	ASSERT_NE(p, test_array.getData());

	// Увеличиваем m_lenght до 3
	const int Three = 3;
	for (int i = 0; i < Three; ++i) {
		test_array.set(i, i);
		ASSERT_EQ(i, test_array.get(i));
		ASSERT_EQ(i + 1, test_array.getLenght());
	}

	// Пробуем уменьшить m_size до 1
	const int One = 1;
	test_array.resize(One);
	ASSERT_NE(One, test_array.getSize());
	ASSERT_EQ(Three, test_array.getSize());
	ASSERT_NE(Five, test_array.getSize());
}

int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
