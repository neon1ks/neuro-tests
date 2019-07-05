#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include "narray.h"
#include "nmatrix.h"

#define GTEST_COUT std::cerr

void print_array(const NArray<int> &obj) {
	int size = obj.getSize();
	int len = obj.getLenght();
	int *data = obj.getData();

	GTEST_COUT << "============================================================\n";
	GTEST_COUT << "size = " << size;
	GTEST_COUT << ", len = " << len << std::endl;

	std::string out;

	for (int i = 0; i < len; ++i) {
		out += std::to_string(data[i]) + " ";
	}

	GTEST_COUT << out << std::endl;
	GTEST_COUT << "============================================================\n";
}

void print_matrix(const NMatrix<int> &obj) {
	int size_row = obj.getSizeRow();
	int size_column = obj.getSizeColumn();
	int len_row = obj.getLenRow();
	int len_column = obj.getLenColumn();

	int *data = obj.getData();

	GTEST_COUT << "============================================================\n";
	GTEST_COUT << "size_row = " << size_row;
	GTEST_COUT << ", size_column = " << size_column;
	GTEST_COUT << ", len_row = " << len_row;
	GTEST_COUT << ", len_column = " << len_column << std::endl;

	std::string out;

	for (int i = 0; i < len_row; ++i) {
		for (int j = 0; j < len_column; ++j) {
			out += std::to_string(data[i * size_column + j]) + " ";
		}
		out += "\n";
	}
	GTEST_COUT << out;
	GTEST_COUT << "============================================================\n";
}

TEST(narray, test01) {
	NArray<int> test_array;
	ASSERT_EQ(int(0), test_array.getSize());
	ASSERT_EQ(int(0), test_array.getLenght());
	ASSERT_EQ(1, test_array.getBlock());
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
	const int One = 1;
	ASSERT_EQ(One, test_array.getBlock());
	test_array.setBlock(-5);
	ASSERT_EQ(One, test_array.getBlock());

	const int Len = 5;
	test_array.setBlock(Len);
	ASSERT_EQ(Len, test_array.getBlock());
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

	// Проверка на правильное копирование
	for (int i = 0; i < Three; ++i) {
		ASSERT_EQ(i, test_array.get(i));
	}
}

TEST(narray, test05) {
	NArray<int> test_array;
	ASSERT_EQ(int(0), test_array.getSize());
	ASSERT_EQ(int(0), test_array.getLenght());
	int *p = nullptr;
	ASSERT_EQ(p, test_array.getData());

	const int Five = 5;
	test_array.init(Five, Five);
	ASSERT_EQ(Five, test_array.getSize());
	ASSERT_EQ(Five, test_array.getLenght());
	for (int i = 0; i < Five; ++i) {
		ASSERT_EQ(Five, test_array.get(i));
	}

	const int Seven = 7;
	test_array.init(Seven, Seven);
	ASSERT_EQ(Seven, test_array.getSize());
	ASSERT_EQ(Seven, test_array.getLenght());
	for (int i = 0; i < Seven; ++i) {
		ASSERT_EQ(Seven, test_array.get(i));
	}

	const int Three = 3;
	test_array.init(Three, Three);
	ASSERT_NE(Three, test_array.getSize());
	ASSERT_EQ(Seven, test_array.getSize());
	ASSERT_EQ(Three, test_array.getLenght());
	for (int i = 0; i < test_array.getLenght(); ++i) {
		ASSERT_EQ(Three, test_array.get(i));
	}
	// Не совсем правильно, но пусть будет
	for (int i = Three; i < test_array.getSize(); ++i) {
		ASSERT_EQ(Seven, test_array.get(i));
	}
}

// Проверка методов set(), get(), resize()
TEST(nmatrix, test01) {
	NMatrix<int> test_matrix;

	const int size_row = 4;
	const int size_column = 3;
	const int new_size_row = 5;
	const int new_size_column = 4;

	test_matrix.init(size_row, size_column, 0);

	for (int i = 0; i < size_row; ++i) {
		for (int j = 0; j < size_column; ++j) {
			test_matrix.set(i * j, i, j);
		}
	}

	for (int i = 0; i < size_row; ++i) {
		for (int j = 0; j < size_column; ++j) {
			ASSERT_EQ(i * j, test_matrix.get(i, j));
		}
	}
	test_matrix.resize(size_row - 1, size_column - 1);

	ASSERT_EQ(size_row, test_matrix.getSizeRow());
	ASSERT_EQ(size_column, test_matrix.getSizeColumn());
	ASSERT_EQ(size_row, test_matrix.getLenRow());
	ASSERT_EQ(size_column, test_matrix.getLenColumn());

	test_matrix.resize(new_size_row, 0);

	ASSERT_EQ(new_size_row, test_matrix.getSizeRow());
	ASSERT_EQ(size_column, test_matrix.getSizeColumn());
	ASSERT_EQ(size_row, test_matrix.getLenRow());
	ASSERT_EQ(size_column, test_matrix.getLenColumn());

	test_matrix.resize(0, new_size_column);

	ASSERT_EQ(new_size_row, test_matrix.getSizeRow());
	ASSERT_EQ(new_size_column, test_matrix.getSizeColumn());
	ASSERT_EQ(size_row, test_matrix.getLenRow());
	ASSERT_EQ(size_column, test_matrix.getLenColumn());

	test_matrix.resize(new_size_row + 1, new_size_column + 1);

	ASSERT_EQ(new_size_row + 1, test_matrix.getSizeRow());
	ASSERT_EQ(new_size_column + 1, test_matrix.getSizeColumn());
	ASSERT_EQ(size_row, test_matrix.getLenRow());
	ASSERT_EQ(size_column, test_matrix.getLenColumn());

	for (int i = 0; i < size_row; ++i) {
		for (int j = 0; j < size_column; ++j) {
			ASSERT_EQ(i * j, test_matrix.get(i, j));
		}
	}
}

// Проверка метода init()
TEST(nmatrix, test02) {
	NMatrix<int> test_matrix;

	const int Zero = 0;
	const int One = 1;
	const int Two = 2;
	const int Three = 3;
	const int len_row = 4;
	const int len_column = 3;

	test_matrix.init(len_row, len_column, Zero);
	for (int i = 0; i < len_row; ++i) {
		for (int j = 0; j < len_column; ++j) {
			ASSERT_EQ(Zero, test_matrix.get(i, j));
		}
	}
	ASSERT_EQ(len_row, test_matrix.getSizeRow());
	ASSERT_EQ(len_column, test_matrix.getSizeColumn());
	ASSERT_EQ(len_row, test_matrix.getLenRow());
	ASSERT_EQ(len_column, test_matrix.getLenColumn());

	test_matrix.init(len_row + 1, len_column - 1, One);
	for (int i = 0; i < len_row + 1; ++i) {
		for (int j = 0; j < len_column - 1; ++j) {
			ASSERT_EQ(One, test_matrix.get(i, j));
		}
	}
	ASSERT_EQ(len_row + 1, test_matrix.getSizeRow());
	ASSERT_EQ(len_column, test_matrix.getSizeColumn());
	ASSERT_EQ(len_row + 1, test_matrix.getLenRow());
	ASSERT_EQ(len_column - 1, test_matrix.getLenColumn());

	test_matrix.init(len_row - 1, len_column + 1, Two);
	for (int i = 0; i < len_row - 1; ++i) {
		for (int j = 0; j < len_column + 1; ++j) {
			ASSERT_EQ(Two, test_matrix.get(i, j));
		}
	}
	ASSERT_EQ(len_row + 1, test_matrix.getSizeRow());
	ASSERT_EQ(len_column + 1, test_matrix.getSizeColumn());
	ASSERT_EQ(len_row - 1, test_matrix.getLenRow());
	ASSERT_EQ(len_column + 1, test_matrix.getLenColumn());

	test_matrix.init(len_row + 2, len_column + 2, Three);
	for (int i = 0; i < len_row + 2; ++i) {
		for (int j = 0; j < len_column + 2; ++j) {
			ASSERT_EQ(Three, test_matrix.get(i, j));
		}
	}
	ASSERT_EQ(len_row + 2, test_matrix.getSizeRow());
	ASSERT_EQ(len_column + 2, test_matrix.getSizeColumn());
	ASSERT_EQ(len_row + 2, test_matrix.getLenRow());
	ASSERT_EQ(len_column + 2, test_matrix.getLenColumn());
}

// Проверка методов addRow и delRow
TEST(nmatrix, test03) {
	NMatrix<int> test_matrix;

	const int Zero = 0;
	const int len_row = 4;
	const int len_column = 3;

	test_matrix.init(len_row + 2, len_column + 2, 0);
	test_matrix.init(len_row, len_column, 0);
	for (int i = 0; i < len_row; ++i) {
		for (int j = 0; j < len_column; ++j) {
			test_matrix.set(i, i, j);
			ASSERT_EQ(i, test_matrix.get(i, j));
		}
	}
	ASSERT_EQ(len_row + 2, test_matrix.getSizeRow());
	ASSERT_EQ(len_column + 2, test_matrix.getSizeColumn());
	ASSERT_EQ(len_row, test_matrix.getLenRow());
	ASSERT_EQ(len_column, test_matrix.getLenColumn());

	test_matrix.addRow(2, 5);
	ASSERT_EQ(len_row + 2, test_matrix.getSizeRow());
	ASSERT_EQ(len_column + 2, test_matrix.getSizeColumn());
	ASSERT_EQ(len_row + 1, test_matrix.getLenRow());
	ASSERT_EQ(len_column, test_matrix.getLenColumn());
	for (int j = 0; j < len_column; ++j) {
		ASSERT_EQ(Zero, test_matrix.get(0, j));
		ASSERT_EQ(1, test_matrix.get(1, j));
		ASSERT_EQ(5, test_matrix.get(2, j));
		ASSERT_EQ(2, test_matrix.get(3, j));
		ASSERT_EQ(3, test_matrix.get(4, j));
	}

	test_matrix.addRow(5, 6);
	ASSERT_EQ(len_row + 2, test_matrix.getSizeRow());
	ASSERT_EQ(len_column + 2, test_matrix.getSizeColumn());
	ASSERT_EQ(len_row + 2, test_matrix.getLenRow());
	ASSERT_EQ(len_column, test_matrix.getLenColumn());
	for (int j = 0; j < len_column; ++j) {
		ASSERT_EQ(Zero, test_matrix.get(0, j));
		ASSERT_EQ(1, test_matrix.get(1, j));
		ASSERT_EQ(5, test_matrix.get(2, j));
		ASSERT_EQ(2, test_matrix.get(3, j));
		ASSERT_EQ(3, test_matrix.get(4, j));
		ASSERT_EQ(6, test_matrix.get(5, j));
	}

	test_matrix.addRow(7, 7);
	ASSERT_EQ(len_row + 4, test_matrix.getSizeRow());
	ASSERT_EQ(len_column + 2, test_matrix.getSizeColumn());
	ASSERT_EQ(len_row + 4, test_matrix.getLenRow());
	ASSERT_EQ(len_column, test_matrix.getLenColumn());
	for (int j = 0; j < len_column; ++j) {
		ASSERT_EQ(Zero, test_matrix.get(0, j));
		ASSERT_EQ(1, test_matrix.get(1, j));
		ASSERT_EQ(5, test_matrix.get(2, j));
		ASSERT_EQ(2, test_matrix.get(3, j));
		ASSERT_EQ(3, test_matrix.get(4, j));
		ASSERT_EQ(6, test_matrix.get(5, j));
		ASSERT_EQ(7, test_matrix.get(6, j));
		ASSERT_EQ(7, test_matrix.get(7, j));
	}

	test_matrix.delRow(8);
	ASSERT_EQ(len_row + 4, test_matrix.getSizeRow());
	ASSERT_EQ(len_column + 2, test_matrix.getSizeColumn());
	ASSERT_EQ(len_row + 4, test_matrix.getLenRow());
	ASSERT_EQ(len_column, test_matrix.getLenColumn());
	for (int j = 0; j < len_column; ++j) {
		ASSERT_EQ(Zero, test_matrix.get(0, j));
		ASSERT_EQ(1, test_matrix.get(1, j));
		ASSERT_EQ(5, test_matrix.get(2, j));
		ASSERT_EQ(2, test_matrix.get(3, j));
		ASSERT_EQ(3, test_matrix.get(4, j));
		ASSERT_EQ(6, test_matrix.get(5, j));
		ASSERT_EQ(7, test_matrix.get(6, j));
		ASSERT_EQ(7, test_matrix.get(7, j));
	}

	test_matrix.delRow(7);
	ASSERT_EQ(len_row + 4, test_matrix.getSizeRow());
	ASSERT_EQ(len_column + 2, test_matrix.getSizeColumn());
	ASSERT_EQ(len_row + 3, test_matrix.getLenRow());
	ASSERT_EQ(len_column, test_matrix.getLenColumn());
	for (int j = 0; j < len_column; ++j) {
		ASSERT_EQ(Zero, test_matrix.get(0, j));
		ASSERT_EQ(1, test_matrix.get(1, j));
		ASSERT_EQ(5, test_matrix.get(2, j));
		ASSERT_EQ(2, test_matrix.get(3, j));
		ASSERT_EQ(3, test_matrix.get(4, j));
		ASSERT_EQ(6, test_matrix.get(5, j));
		ASSERT_EQ(7, test_matrix.get(6, j));
	}

	test_matrix.delRow(4);
	ASSERT_EQ(len_row + 4, test_matrix.getSizeRow());
	ASSERT_EQ(len_column + 2, test_matrix.getSizeColumn());
	ASSERT_EQ(len_row + 2, test_matrix.getLenRow());
	ASSERT_EQ(len_column, test_matrix.getLenColumn());

	for (int j = 0; j < len_column; ++j) {
		ASSERT_EQ(Zero, test_matrix.get(0, j));
		ASSERT_EQ(1, test_matrix.get(1, j));
		ASSERT_EQ(5, test_matrix.get(2, j));
		ASSERT_EQ(2, test_matrix.get(3, j));
		ASSERT_EQ(6, test_matrix.get(4, j));
		ASSERT_EQ(7, test_matrix.get(5, j));
	}

	test_matrix.delRow(0);
	ASSERT_EQ(len_row + 4, test_matrix.getSizeRow());
	ASSERT_EQ(len_column + 2, test_matrix.getSizeColumn());
	ASSERT_EQ(len_row + 1, test_matrix.getLenRow());
	ASSERT_EQ(len_column, test_matrix.getLenColumn());
	for (int j = 0; j < len_column; ++j) {
		ASSERT_EQ(1, test_matrix.get(0, j));
		ASSERT_EQ(5, test_matrix.get(1, j));
		ASSERT_EQ(2, test_matrix.get(2, j));
		ASSERT_EQ(6, test_matrix.get(3, j));
		ASSERT_EQ(7, test_matrix.get(4, j));
	}
}

// Проверка методов addColumn и delColumn
TEST(nmatrix, test04) {
	NMatrix<int> test_matrix;

	const int Zero = 0;
	const int len_row = 3;
	const int len_column = 4;

	test_matrix.init(len_row + 2, len_column + 2, 0);
	test_matrix.init(len_row, len_column, 0);
	for (int i = 0; i < len_row; ++i) {
		for (int j = 0; j < len_column; ++j) {
			test_matrix.set(j, i, j);
			ASSERT_EQ(j, test_matrix.get(i, j));
		}
	}
	ASSERT_EQ(len_row + 2, test_matrix.getSizeRow());
	ASSERT_EQ(len_column + 2, test_matrix.getSizeColumn());
	ASSERT_EQ(len_row, test_matrix.getLenRow());
	ASSERT_EQ(len_column, test_matrix.getLenColumn());

	test_matrix.addColumn(1, 5);
	ASSERT_EQ(len_row + 2, test_matrix.getSizeRow());
	ASSERT_EQ(len_column + 2, test_matrix.getSizeColumn());
	ASSERT_EQ(len_row, test_matrix.getLenRow());
	ASSERT_EQ(len_column + 1, test_matrix.getLenColumn());
	for (int i = 0; i < len_row; ++i) {
		ASSERT_EQ(Zero, test_matrix.get(i, 0));
		ASSERT_EQ(5, test_matrix.get(i, 1));
		ASSERT_EQ(1, test_matrix.get(i, 2));
		ASSERT_EQ(2, test_matrix.get(i, 3));
		ASSERT_EQ(3, test_matrix.get(i, 4));
	}

	test_matrix.addColumn(5, 6);
	ASSERT_EQ(len_row + 2, test_matrix.getSizeRow());
	ASSERT_EQ(len_column + 2, test_matrix.getSizeColumn());
	ASSERT_EQ(len_row, test_matrix.getLenRow());
	ASSERT_EQ(len_column + 2, test_matrix.getLenColumn());
	for (int i = 0; i < len_row; ++i) {
		ASSERT_EQ(Zero, test_matrix.get(i, 0));
		ASSERT_EQ(5, test_matrix.get(i, 1));
		ASSERT_EQ(1, test_matrix.get(i, 2));
		ASSERT_EQ(2, test_matrix.get(i, 3));
		ASSERT_EQ(3, test_matrix.get(i, 4));
		ASSERT_EQ(6, test_matrix.get(i, 5));
	}

	test_matrix.addColumn(7, 7);
	ASSERT_EQ(len_row + 2, test_matrix.getSizeRow());
	ASSERT_EQ(len_column + 4, test_matrix.getSizeColumn());
	ASSERT_EQ(len_row, test_matrix.getLenRow());
	ASSERT_EQ(len_column + 4, test_matrix.getLenColumn());
	for (int i = 0; i < len_row; ++i) {
		ASSERT_EQ(Zero, test_matrix.get(i, 0));
		ASSERT_EQ(5, test_matrix.get(i, 1));
		ASSERT_EQ(1, test_matrix.get(i, 2));
		ASSERT_EQ(2, test_matrix.get(i, 3));
		ASSERT_EQ(3, test_matrix.get(i, 4));
		ASSERT_EQ(6, test_matrix.get(i, 5));
		ASSERT_EQ(7, test_matrix.get(i, 6));
		ASSERT_EQ(7, test_matrix.get(i, 7));
	}

	test_matrix.delColumn(8);
	ASSERT_EQ(len_row + 2, test_matrix.getSizeRow());
	ASSERT_EQ(len_column + 4, test_matrix.getSizeColumn());
	ASSERT_EQ(len_row, test_matrix.getLenRow());
	ASSERT_EQ(len_column + 4, test_matrix.getLenColumn());
	for (int i = 0; i < len_row; ++i) {
		ASSERT_EQ(Zero, test_matrix.get(i, 0));
		ASSERT_EQ(5, test_matrix.get(i, 1));
		ASSERT_EQ(1, test_matrix.get(i, 2));
		ASSERT_EQ(2, test_matrix.get(i, 3));
		ASSERT_EQ(3, test_matrix.get(i, 4));
		ASSERT_EQ(6, test_matrix.get(i, 5));
		ASSERT_EQ(7, test_matrix.get(i, 6));
		ASSERT_EQ(7, test_matrix.get(i, 7));
	}

	test_matrix.delColumn(7);
	ASSERT_EQ(len_row + 2, test_matrix.getSizeRow());
	ASSERT_EQ(len_column + 4, test_matrix.getSizeColumn());
	ASSERT_EQ(len_row, test_matrix.getLenRow());
	ASSERT_EQ(len_column + 3, test_matrix.getLenColumn());
	for (int i = 0; i < len_row; ++i) {
		ASSERT_EQ(Zero, test_matrix.get(i, 0));
		ASSERT_EQ(5, test_matrix.get(i, 1));
		ASSERT_EQ(1, test_matrix.get(i, 2));
		ASSERT_EQ(2, test_matrix.get(i, 3));
		ASSERT_EQ(3, test_matrix.get(i, 4));
		ASSERT_EQ(6, test_matrix.get(i, 5));
		ASSERT_EQ(7, test_matrix.get(i, 6));
	}

	test_matrix.delColumn(3);
	ASSERT_EQ(len_row + 2, test_matrix.getSizeRow());
	ASSERT_EQ(len_column + 4, test_matrix.getSizeColumn());
	ASSERT_EQ(len_row, test_matrix.getLenRow());
	ASSERT_EQ(len_column + 2, test_matrix.getLenColumn());
	for (int i = 0; i < len_row; ++i) {
		ASSERT_EQ(Zero, test_matrix.get(i, 0));
		ASSERT_EQ(5, test_matrix.get(i, 1));
		ASSERT_EQ(1, test_matrix.get(i, 2));
		ASSERT_EQ(3, test_matrix.get(i, 3));
		ASSERT_EQ(6, test_matrix.get(i, 4));
		ASSERT_EQ(7, test_matrix.get(i, 5));
	}

	test_matrix.delColumn(0);
	ASSERT_EQ(len_row + 2, test_matrix.getSizeRow());
	ASSERT_EQ(len_column + 4, test_matrix.getSizeColumn());
	ASSERT_EQ(len_row, test_matrix.getLenRow());
	ASSERT_EQ(len_column + 1, test_matrix.getLenColumn());
	for (int i = 0; i < len_row; ++i) {
		ASSERT_EQ(5, test_matrix.get(i, 0));
		ASSERT_EQ(1, test_matrix.get(i, 1));
		ASSERT_EQ(3, test_matrix.get(i, 2));
		ASSERT_EQ(6, test_matrix.get(i, 3));
		ASSERT_EQ(7, test_matrix.get(i, 4));
	}
}

TEST(nmatrix, mathematical_operation_1) {
	NMatrix<int> matrix_A;
	NMatrix<int> matrix_B;

	const int len_row = 4;
	const int len_column = 4;

	matrix_A.init(len_row, len_column, 2);
	matrix_B.init(len_row, len_column, 3);

	matrix_A.sum(matrix_B);

	for (int i = 0; i < len_row; ++i) {
		for (int j = 0; j < len_column; ++j) {
			ASSERT_EQ(5, matrix_A.get(i, j));
		}
	}
}

TEST(nmatrix, mathematical_operation_2) {
	NMatrix<int> matrix_A;
	NMatrix<int> matrix_B;
	NMatrix<int> matrix_C;
	NMatrix<int> matrix_D;

	const int len_row = 2;
	const int len_column = 3;

	matrix_A.init(len_row, len_column, 0);
	matrix_B.init(len_column, len_row, 0);

	matrix_A.set(2, 0, 0);
	matrix_A.set(-3, 0, 1);
	matrix_A.set(1, 0, 2);
	matrix_A.set(5, 1, 0);
	matrix_A.set(4, 1, 1);
	matrix_A.set(-2, 1, 2);

	matrix_B.set(-7, 0, 0);
	matrix_B.set(5, 0, 1);
	matrix_B.set(2, 1, 0);
	matrix_B.set(-1, 1, 1);
	matrix_B.set(4, 2, 0);
	matrix_B.set(3, 2, 1);

	matrix_C.mul(matrix_A, matrix_B);

	ASSERT_EQ(-16, matrix_C.get(0, 0));
	ASSERT_EQ(16, matrix_C.get(0, 1));
	ASSERT_EQ(-35, matrix_C.get(1, 0));
	ASSERT_EQ(15, matrix_C.get(1, 1));
}

// operators

TEST(narray, operator_01) {
	const int Len = 5;
	NArray<int> test_array = NArray<int>(Len);
	ASSERT_EQ(Len, test_array.getSize());

	for (int i = 0; i < Len; ++i) {
		test_array.set(i, i);
		ASSERT_EQ(i, test_array.get(i));
	}

	NArray<int> array2 = NArray<int>(Len);
	array2 = test_array + 2;
	for (int i = 0; i < Len; ++i) {
		ASSERT_EQ(i + 2, array2.get(i));
	}
}

TEST(narray, operator_02) {
	const int Len = 5;
	NArray<int> test_array = NArray<int>(Len);
	ASSERT_EQ(Len, test_array.getSize());

	for (int i = 0; i < Len; ++i) {
		test_array.set(i + 2, i);
	}

	NArray<int> array2 = NArray<int>(Len);
	array2 = test_array - 2;
	for (int i = 0; i < Len; ++i) {
		ASSERT_EQ(i, array2.get(i));
	}
}

TEST(narray, operator_03) {
	const int Len = 5;
	NArray<int> test_array = NArray<int>(Len);
	ASSERT_EQ(Len, test_array.getSize());

	for (int i = 0; i < Len; ++i) {
		test_array.set(i, i);
	}

	NArray<int> array2 = NArray<int>(Len);
	array2 = test_array * 2;
	for (int i = 0; i < Len; ++i) {
		ASSERT_EQ(i * 2, array2.get(i));
	}
}

TEST(narray, operator_04) {
	const int Len = 5;
	NArray<int> test_array = NArray<int>(Len);
	ASSERT_EQ(Len, test_array.getSize());

	for (int i = 0; i < Len; ++i) {
		test_array.set(i * 2, i);
	}

	NArray<int> array2 = NArray<int>(Len);
	array2 = test_array / 2;
	for (int i = 0; i < Len; ++i) {
		ASSERT_EQ(i, array2.get(i));
	}
}

TEST(narray, operator_05) {
	const int Len = 5;
	NArray<int> array1 = NArray<int>(Len);
	NArray<int> array2 = NArray<int>(Len);
	ASSERT_EQ(Len, array1.getSize());
	ASSERT_EQ(Len, array2.getSize());

	for (int i = 0; i < Len; ++i) {
		array1.set(i * 2, i);
		array2.set(i * 2 + 1, i);
	}

	NArray<int> array3 = NArray<int>(Len);
	array3 = array1 + array2;
	for (int i = 0; i < Len; ++i) {
		ASSERT_EQ(i * 4 + 1, array3.get(i));
	}
}

TEST(narray, operator_06) {
	const int Len = 5;
	NArray<int> array1 = NArray<int>(Len);
	NArray<int> array2 = NArray<int>(Len);
	ASSERT_EQ(Len, array1.getSize());
	ASSERT_EQ(Len, array2.getSize());

	for (int i = 0; i < Len; ++i) {
		array1.set(i * 2 + 1, i);
		array2.set(i * 2, i);
	}

	NArray<int> array3 = NArray<int>(Len);
	array3 = array1 - array2;
	for (int i = 0; i < Len; ++i) {
		ASSERT_EQ(1, array3.get(i));
	}
}

TEST(narray, operator_07) {
	const int Len = 5;
	NArray<int> array1 = NArray<int>(Len);
	NArray<int> array2 = NArray<int>(Len);
	ASSERT_EQ(Len, array1.getSize());
	ASSERT_EQ(Len, array2.getSize());

	for (int i = 0; i < Len; ++i) {
		array1.set(i, i);
		array2.set(i * 2, i);
	}

	NArray<int> array3 = NArray<int>(Len);
	array3 = array1 * array2;

	for (int i = 0; i < Len; ++i) {
		ASSERT_EQ(i * i * 2, array3.get(i));
	}
}

TEST(narray, operator_08) {
	const int Row = 3;
	const int Column = 4;
	NArray<int> array;
	NMatrix<int> matrix;

	int value = 0;

	array.init(Row, value);
	matrix.init(Row, Column, value);

	// 4 3 7  *  1 4 7 5  = 78 29 89 92
	//           6 2 4 3
	//           8 1 7 9

	array.set(4, 0);
	array.set(3, 1);
	array.set(7, 2);

	matrix.set(1, 0, 0);
	matrix.set(4, 0, 1);
	matrix.set(7, 0, 2);
	matrix.set(5, 0, 3);

	matrix.set(6, 1, 0);
	matrix.set(2, 1, 1);
	matrix.set(4, 1, 2);
	matrix.set(3, 1, 3);

	matrix.set(8, 2, 0);
	matrix.set(1, 2, 1);
	matrix.set(7, 2, 2);
	matrix.set(9, 2, 3);

	NArray<int> result = NArray<int>(Column);
	result = array * matrix;

	ASSERT_EQ(78, result.get(0));
	ASSERT_EQ(29, result.get(1));
	ASSERT_EQ(89, result.get(2));
	ASSERT_EQ(92, result.get(3));
}

int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
