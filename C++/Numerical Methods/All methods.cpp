#include <iostream>
#include <iomanip>
#include <cmath>
#include <locale>

enum method_t {Gausse = 1, Square_Root, Jacobi, Seidel};

void set_conditions(double**& A, double*& b, double*& x, size_t& rank);
// Встановлює початковi значення матрицi A та вектора b

void print_matrix(double**& A, double*& b, const size_t& rank);
void print_matrix(double**& A, const size_t& rank);
void print_matrix(double*& A, const size_t& rank);
// Виводить матрицю на екран

unsigned int find_max(double**& A, const unsigned int& k, const size_t rank);
// Шукає номер рядка (починаючи вiд k), в якому знаходиться найбiльший елемент стовпчика k
void change_order(double**& A, double*& b, const unsigned int& k, const unsigned int& n);
// Мiняє рядки k та n мiсцями
int method_type();

void reverse_Gauss(double**& A, double*& b, double*& x, const size_t& rank);

void Gauss_method(double**& A, double*& b, double*& x, const size_t& rank);
void Square_root_method(double**& A, double*& b, double*& x, const size_t& rank);
void Jacobi_method(double**& A, double*& b, double*& x, const size_t& rank);
void Seidel_method(double**& A, double*& b, double*& x, const size_t& rank);

int main()
{
	setlocale(LC_CTYPE, "ukr");
	//system("color f0");
	double** A;	// Матриця коефiцiєнтiв
	double* b;	// Права частина системи
	double* x;	// Невiдомi
	size_t rank;

	set_conditions(A, b, x, rank);
	std::cout << "Початкова матриця:\n\n";
	print_matrix(A, b, rank);

	switch (method_type())
	{
	case Gausse:
	{
		Gauss_method(A, b, x, rank);
		break;
	}
	case Square_Root:
	{
		Square_root_method(A, b, x, rank);
		break;
	}
	case Jacobi:
	{
		Jacobi_method(A, b, x, rank);
		break;
	}
	case Seidel:
	{
		Seidel_method(A, b, x, rank);
		break;
	}
	default:
	{
		std::cout << "Нема такого методу!\n";
		return 0;
	}
	}

	// Результат
	std::cout << "\n------------Результат------------\n\n";
	for (unsigned int i = 0; i < rank; ++i)
	{
		std::cout << "x[" << i + 1 << "] = " << round(x[i] * 100) / 100 << std::endl << std::endl;
	}
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

	std::cout << "Введiть значення елементiв матрицi:\n";
	for (size_t i = 0; i < rank; ++i)
	{
		for (size_t j = 0; j < rank; ++j)
		{
			std::cout << "a[" << i + 1 << "," << j + 1 << "] = ";
			std::cin >> A[i][j];
		}
		std::cout << "b[" << i << "] = ";
		std::cin >> b[i];
		std::cout << std::endl;
	}
}

void print_matrix(double**& A, double*& b, const size_t& rank)
{
	for (size_t i = 0; i < rank; ++i)
	{
		for (size_t j = 0; j < rank; ++j)
		{
			std::cout << std::setw(6) << round(A[i][j]*100)/100;
		}
		std::cout << "   |  " << round(b[i]*100) / 100 << std::endl << std::endl;
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

void print_matrix(double*& A, const size_t& rank)
{
	for (size_t i = 0; i < rank; ++i)
	{
		for (size_t j = 0; j < rank; ++j)
		{
			if (i == j)
				std::cout << std::setw(6) << round(A[i] * 100) / 100;
			else
				std::cout << std::setw(6) << 0;
		}
		std::cout << std::endl << std::endl;
	}
}

void change_order(double**& A, double*& b, const unsigned int& k, const unsigned int& n)
{
	double* temp = A[k];
	A[k] = A[n];
	A[n] = temp;

	double temp_b = b[k];
	b[k] = b[n];
	b[n] = temp_b;
}

unsigned int find_max(double**& A, const unsigned int& k, const size_t rank)
{
	double max_element = abs(A[k][k]), row = k;
	for (size_t i = k + 1; i < rank; ++i)
	{
		if (abs(A[i][k]) > max_element)
		{
			max_element = abs(A[i][k]);
			row = i;
		}
	}
	return row;
}

void reverse_Gauss(double**& A, double*& b, double*& x, const size_t& rank)
{
	double temp = 0;
	for (int i = rank - 1; i >= 0; --i)
	{
		std::cout << "[Крок №" << i + 1 << "]\n\n";
		temp = 0;
		for (size_t j = i + 1; j < rank; ++j)
		{
			temp += A[i][j] * x[j];
			A[i][j] = 0;
		}
		b[i] = (b[i] - temp) / A[i][i];
		A[i][i] = 1;
		x[i] = b[i];
		print_matrix(A, b, rank);
	}
}

int method_type()
{
	int method_t = 0;
	std::cout << "Який метод використати?\n";
	std::cout << "1 - Метод Гаусса з вибором головного елемента\n2 - Метод квадратного кореня\n3 - Метод Якобi\n4 - Метод Зейделя\n> ";
	std::cin >> method_t;
	return method_t;
}

void Gauss_method(double**& A, double*& b, double*& x, const size_t& rank)
{
	// Прямий хiд
	std::cout << "\n-----------Прямий хiд-----------\n";
	unsigned int max_row;
	double m = 0;
	for (unsigned int k = 0; k < rank - 1; ++k)
	{
		// Знаходження максимального елемента та перенесення його на дiагональ
		std::cout << "\n[Iтерацiя №" << k + 1 << "]\n";
		max_row = find_max(A, k, rank);
		std::cout << "Максимальний елемент у рядку №" << max_row + 1 << std::endl;
		if (max_row != k)
		{
			change_order(A, b, k, max_row);
			std::cout << "(були переставленi рядки : " << k + 1 << " та " << max_row + 1 << ")\n\n";
		}
		else std::cout << "(жодного рядка не було переставлено)\n\n";
		print_matrix(A, b, rank);

		// Приведення до трикутної форми
		std::cout << "Виключення невiдомих...";
		unsigned int row_num, column_num;
		for (row_num = k + 1; row_num < rank; ++row_num)
		{
			double m = A[row_num][k] / A[k][k];
			for (column_num = k; column_num < rank; ++column_num)
			{
				A[row_num][column_num] -= A[k][column_num] * m;
			}
			b[row_num] -= b[k] * m;
		}
		std::cout << " Успiшно!\n\n";
		print_matrix(A, b, rank);
	}

	// Зворотнiй хiд
	std::cout << "\n----------Зворотнiй хiд----------\n";
	reverse_Gauss(A, b, x, rank);
}

void Square_root_method(double**& A, double*& b, double*& x, const size_t& rank)
{
	// Create new D and S matrices
	double* D = new double[rank];
	double** S = new double* [rank];
	for (size_t i = 0; i < rank; ++i)
	{
		S[i] = new double[rank];
	}

	// Fill S and D matrices
	double temp;
	for (size_t i = 0; i < rank; ++i)
	{
		temp = 0;
		for (size_t p = 0; p < i; ++p)
		{
			temp += (S[p][i] * S[p][i] * D[p]);
		}
		temp = A[i][i] - temp;

		// D matrix
		if (temp > 0)	D[i] = 1;
		else
		{
			if (temp < 0)	D[i] = -1;
			else D[i] = 0;
		}

		// Diagonal element S
		S[i][i] = sqrt(abs(temp));

		// Non-diagonal element S
		for (size_t j = 0; j < i; ++j)	S[i][j] = 0;
		for (size_t j = i; j < rank; ++j)
		{
			temp = 0;
			for (size_t p = 0; p < i; ++p)
			{
				temp += S[p][i] * D[p] * S[p][j];
			}
			S[i][j] = (A[i][j] - temp) / D[i] / S[i][i];
		}
	}
	std::cout << "Матриця S має вигляд:\n\n";
	print_matrix(S, rank);
	std::cout << "Матриця D має вигляд:\n\n";
	print_matrix(D, rank);

	// S-transposed * D
	for (size_t i = 0; i < rank; ++i)
	{
		for (size_t j = 0; j < rank; ++j)
		{
			A[i][j] = S[j][i] * D[j];
		}
	}
	std::cout << "Отримаємо S^Dy = b:\n\n";
	print_matrix(A, b, rank);

	// Зворотнiй хiд згори вниз
	std::cout << "Виконаємо зворотнiй хiд методу Гаусса згори вниз:\n\n";
	for (int i = 0; i < rank; ++i)
	{
		std::cout << "[Крок №" << i + 1 << "]\n\n";
		temp = 0;
		for (size_t j = 0; j < i; ++j)
		{
			temp += A[i][j] * x[j];
			A[i][j] = 0;
		}
		b[i] = (b[i] - temp) / A[i][i];
		A[i][i] = 1;
		x[i] = b[i];
		print_matrix(A, b, rank);
	}

	// Зворотнiй хiд знизу вгору
	std::cout << "Виконаємо зворотнiй хiд методу Гаусса знизу вгору матрицi Sx = y:\n\n";
	print_matrix(S, b, rank);
	reverse_Gauss(S, b, x, rank);
}

void Jacobi_method(double**& A, double*& b, double*& x, const size_t& rank)
{
	std::cout << "Скiлькi iтерацiй потрiбно виконати?\n>";
	size_t steps_number;
	std::cin >> steps_number;

	double* x_temp = new double[rank];
	double sum;
	for (size_t i = 0; i < rank; ++i)	x[i] = 0;

	for (size_t current_step = 0; current_step < steps_number; ++current_step)
	{
		for (size_t i = 0; i < rank; ++i)
		{
			sum = 0;
			for (size_t j = 0; j < i; ++j)
			{
				sum += A[i][j] * x[j];
			}
			for (size_t j = i + 1; j < rank; ++j)
			{
				sum += A[i][j] * x[j];
			}
			x_temp[i] = (b[i] - sum) / A[i][i];
		}
		std::cout << std::endl;
		std::cout << "Крок №" << current_step + 1 << std::endl;
		for (size_t i = 0; i < rank; ++i)
		{
			x[i] = x_temp[i];
			std::cout << "x[" << i + 1 << "] = " << round(x[i] * 10000) / 10000 << std::endl;
		}
		std::cout << std::endl;
	}
}

void Seidel_method(double**& A, double*& b, double*& x, const size_t& rank)
{
	std::cout << "Скiлькi iтерацiй потрiбно виконати?\n>";
	size_t steps_number;
	std::cin >> steps_number;

	double sum;
	for (size_t i = 0; i < rank; ++i)	x[i] = 0;

	for (size_t current_step = 0; current_step < steps_number; ++current_step)
	{
		for (size_t i = 0; i < rank; ++i)
		{
			sum = 0;
			for (size_t j = 0; j < i; ++j)
			{
				sum += A[i][j] * x[j];
			}
			for (size_t j = i + 1; j < rank; ++j)
			{
				sum += A[i][j] * x[j];
			}
			x[i] = (b[i] - sum) / A[i][i];
		}
		std::cout << std::endl;
		std::cout << "Крок №" << current_step + 1 << std::endl;
		for (size_t i = 0; i < rank; ++i)
		{
			std::cout << "x[" << i + 1 << "] = " << round(x[i] * 10000) / 10000 << std::endl;
		}
		std::cout << std::endl;
	}
}