#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;



class Matrix
{
public:
	Matrix();
	Matrix(int, int);
	Matrix(const Matrix &);
	~Matrix();
	void print();
	int gcrow(int);
	int gccolumn(int);
	int gelement(int, int);
	void cmffile(ifstream &);
	Matrix operator+(const Matrix &);
	Matrix *operator=(const Matrix &);
	Matrix operator*(const Matrix &);
	int* operator[](int);
	bool isempty();
	void create_matrix(int n, int m);

private:
	int **array;
	int count_row;
	int count_column;
};

Matrix::Matrix() :
array(nullptr),
count_row(0),
count_column(0)
{}

Matrix::Matrix(int b, int a)
{
	create_matrix(a, b);
}


Matrix::Matrix(const Matrix &mtrx)
{
	count_row = mtrx.count_row;
	count_column = mtrx.count_column;

	create_matrix(count_row, count_column);
	for (int i = 0; i < count_row; ++i)
	{
		for (int j = 0; j < count_column; ++j)
		{
			array[i][j] = mtrx.array[i][j];
		}
	}
}

Matrix::~Matrix() {
	for (int i = 0; i < count_row; i++)
	{
		delete[] array[i];
	}
}

int Matrix::gcrow(int a)
{
	return count_row;
}


int Matrix::gccolumn(int a)
{
	return count_column;
}

void Matrix::print()
{
	for (int i = 0; i < count_row; ++i)
	{
		for (int j = 0; j < count_column; ++j)
		{
			cout << array[i][j] << " ";
		}
		cout << endl;
	}
}

bool Matrix::isempty()
{
	if (count_row == 0 && count_column == 0)
		return true;
	else false;
}

void Matrix::create_matrix(int n, int m)
{
	count_row = n;
	count_column = m;
	array = new int*[count_row];

	for (int i = 0; i < count_row; ++i)
	{
		array[i] = new int[count_column];
	}
}

void Matrix::cmffile(ifstream &file)
{
	int n, m;

	file >> n;
	file >> m;
	create_matrix(n, m);

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			file >> array[i][j];
		}
	}
	file.clear();
	file.seekg(0, ios::beg);
}

Matrix Matrix::operator+(const Matrix &a)
{
	Matrix c;

	if (count_column != a.count_column && count_row != a.count_row)
	{
		cout << "error";
		exit(0);
	}
	c.create_matrix(count_row, count_column);
	for (int i = 0; i < count_row; ++i)
	{
		for (int j = 0; j < count_column; ++j)
		{
			c.array[i][j] = a.array[i][j] + array[i][j];
		}
	}
	return c;
}

Matrix Matrix::operator*(const Matrix &a)
{
	Matrix c;

	if (count_column != a.count_row)
	{
		cout << "error";
		exit(0);
	}
	c.create_matrix(count_row, a.count_column);
	for (int l = 0; l < a.count_column; ++l)
	{
		for (int i = 0; i < count_row; ++i)
		{
			int b = 0, k = 0;
			for (int j = 0; j < count_column; ++j)
			{
				b += array[i][j] * a.array[k++][i];
			}
			c.array[i][l] = b;
		}
	}
	return c;
}

Matrix *Matrix::operator=(const Matrix &mtrx)
{
	count_row = mtrx.count_row;
	count_column = mtrx.count_column;

	create_matrix(count_row, count_column);
	for (int i = 0; i < count_row; ++i)
	{
		for (int j = 0; j < count_column; ++j)
		{
			array[i][j] = mtrx.array[i][j];
		}
	}
	return this;
}

int* Matrix::operator[](int index)
{
	return array[index];
}

int Matrix::gelement(int index1, int index2)
{
	if (index1 >= count_row && index2 >= count_column)
	{
		cout << "error";
		exit(0);
	}
	return array[index1][index2];
}


int main()
{
	
	ifstream file("one1.txt", ios_base::in);

	if (!file.is_open())
	{
		cout << "error";
		return -1;
	}
	Matrix a;
	Matrix b;
	a.cmffile(file);
	b.cmffile(file);
	Matrix c = a + b;
	c.print();
	file.close();

	system("pause");
	return 0;
}