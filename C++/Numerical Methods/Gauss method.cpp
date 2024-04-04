#include <iostream>
#include <iomanip>
#include <cmath>
#include <locale>

void set_conditions(double**& A, double*& b, double*& x, size_t& rank);
// Встановлює початковi значення матрицi A та вектора b

void print_matrix(double**& A, double*& b, const size_t& rank);
void print_matrix(double**& A, const size_t& rank);
// Виводить матрицю на екран

void reverse_Gauss(double**& A, double*& b, double*& x, const size_t& rank);
// Зворотнiй хiд методу Гаусса

void Gauss_method(double**& A, double*& b, double*& x, const size_t& rank);

void Discrepancy(double**& A, double*& b, double*& x, const size_t& rank);

void Determinant(double**& A, const size_t& rank);

int main()
{
	setlocale(LC_CTYPE, "ukr");	// Устанавливает укр язык
	double** A;		// Матриця коефiцiєнтiв
	double* b;		// Права частина системи
	double* x;		// Невiдомi
	size_t rank;	// целый беззнаковый тип данных

	set_conditions(A, b, x, rank);
	std::cout << "\nПочаткова матриця:\n\n";
	print_matrix(A, b, rank);

	Gauss_method(A, b, x, rank);

	// Результат
	std::cout << "\n-----------------Результат-----------------\n\n";
	for (unsigned int i = 0; i < rank; ++i)
	{
		std::cout << "x[" << i + 1 << "] = " << round(x[i] * 100) / 100 << std::endl << std::endl;
	}

	Discrepancy(A, b, x, rank);
	Determinant(A, rank);
}

void set_conditions(double**& A, double*& b, double*& x, size_t& rank)
{
	std::cout << "Введiть розмiрнiсть матрицi\n> ";
	std::cin >> rank;

	A = new double* [rank];
	for (size_t i = 0; i < rank; ++i)
	{
		A[i] = new double[rank];
	}

	b = new double[rank];
	x = new double[rank];

	for (size_t i = 0; i < rank; ++i)
	{
		for (size_t j = 0; j < rank; ++j)
		{
			A[i][j] = (100 / (2 * pow((i + 1) * (j + 1), 4) + 3 * pow((i + 1) * (j + 1), 3)));
		}
		b[i] = (i + 1);
	}
}

void print_matrix(double**& A, double*& b, const size_t& rank)
{
	for (size_t i = 0; i < rank; ++i)
	{
		for (size_t j = 0; j < rank; ++j)
		{
			std::cout << std::setw(6) << round(A[i][j] * 100) / 100;
		}
		std::cout << "   |  " << round(b[i] * 100) / 100 << std::endl << std::endl;
	}
}

void print_matrix(double**& A, const size_t& rank)
{
	for (size_t i = 0; i < rank; ++i)
	{
		for (size_t j = 0; j < rank; ++j)
		{
			std::cout << std::setw(6) << round(A[i][j] * 100) / 100;
		}
		std::cout << std::endl << std::endl;
	}
}

void Gauss_method(double**& A, double*& b, double*& x, const size_t& rank)
{
	size_t row, column;

	std::cout << "\n------------------Метод Гаусса------------------\n\n";
	// Прямий хiд
	std::cout << "\n     -------------Прямий хiд-------------     \n\n";
	for (size_t k = 0; k < rank; ++k)
	{
		std::cout << "Крок №" << k + 1 << std::endl << std::endl;
		// Дiлимо на головний елемент
		for (column = k + 1; column < rank; ++column)
		{
			A[k][column] /= A[k][k];
		}
		b[k] /= A[k][k];
		A[k][k] = 1;

		// Вiднiмаємо головну строку
		for (row = k + 1; row < rank; ++row)
		{
			for (column = k + 1; column < rank; ++column)
			{
				A[row][column] = A[row][column] - A[k][column] * A[row][k];
			}
			b[row] = b[row] - b[k] * A[row][k];
			A[row][k] = 0;
		}
		print_matrix(A, b, rank);
	}

	// Зворотнiй хiд
	std::cout << "\n     -------------Зворотнiй хiд-------------     \n\n";
	double temp = 0;
	for (int i = rank - 1; i >= 0; --i)
	{
		std::cout << "Крок №" << i + 1 << "\n\n";
		temp = 0;
		for (size_t j = i + 1; j < rank; ++j)
		{
			temp += A[i][j] * x[j];
			A[i][j] = 0;
		}
		b[i] = (b[i] - temp);
		x[i] = b[i];
		print_matrix(A, b, rank);
	}
}

void Discrepancy(double**& A, double*& b, double*& x, const size_t& rank)
{
	// Повертаємо початковi значення А та b
	for (size_t i = 0; i < rank; ++i)
	{
		for (size_t j = 0; j < rank; ++j)
		{
			A[i][j] = (100 / (2 * pow((i + 1) * (j + 1), 4) + 3 * pow((i + 1) * (j + 1), 3)));
		}
		b[i] = (i + 1);
	}

	// Рахуємо нев'язку
	std::cout << "\n------------Рахуємо нев'язку------------\n\n";
	double* r = new double[rank];
	double temp;
	for (size_t i = 0; i < rank; ++i)
	{
		std::cout << i + 1 << ") ";
		temp = 0;
		for (size_t j = 0; j < rank; ++j)
		{
			if (j != 0) std::cout << "\t+ ";
			std::cout << round(A[i][j] * 10000) / 10000 << " * " << round(x[j] * 10000) / 10000 << std::endl;
			temp += A[i][j] * x[j];
		}
		std::cout << "\t= " << round(b[i] * 10000) / 10000;
		r[i] = temp - b[i];
		std::cout << "\nТодi r[" << i << "] = " << round(r[i] * 10000) / 10000 << std::endl << std::endl;
	}
	std::cout << "\n-----------------Результат-----------------\n";
	for (size_t i = 0; i < rank; ++i)
	{
		std::cout << "\nr[" << i + 1 << "] = " << round(r[i] * 10000) / 10000 << "; ";
	}
	std::cout << std::endl;
}

void Determinant(double**& A, const size_t& rank)
{
	std::cout << "\n------------Рахуємо визначник------------\n\n";
	std::cout << "\n    -------Прямий хiд Гаусса-------\n     (без змiни головної строки)\n\n";
	size_t row, column;
	for (size_t k = 0; k < rank; ++k)
	{
		for (row = k + 1; row < rank; ++row)
		{
			for (column = k + 1; column < rank; ++column)
			{
				A[row][column] = A[row][column] - A[k][column] * A[row][k] / A[k][k];
			}
			A[row][k] = 0;
		}
	}
	print_matrix(A, rank);
	double det = 1;
	for (size_t i = 0; i < rank; ++i)
	{
		det *= A[i][i];
	}
	std::cout << "Визначник : det = " << det << std::endl;
}