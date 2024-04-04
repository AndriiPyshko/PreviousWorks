#pragma once
#include <iostream>
#include <vector>

class Generator
{
public:
	unsigned int	num_amount = 0;						//������� ������������ �����

	int return_number(unsigned int);			//������� ����� � ������� ������������ �������
	void print_numbers();								//�������� ������� ������������ �������
	void stat();										//���� �� ������� �������� � ���������

	std::vector <unsigned int> numbers;					//������ ������������ �������
	unsigned int	results[11] = { 0 };				//��������� ����� ������� �������� � ������ ��������
};

class First_method: public Generator
{
public:
	First_method	(	unsigned int multiplier,
						unsigned int increaser,
						unsigned int module		);
	void generate	(	unsigned int num_amount	);

private:
	unsigned int	multiplier,
					increaser,
					module;
};

class Second_method : public Generator
{
public:
	Second_method	(	unsigned int multiplier_1, 
						unsigned int multiplier_2,
						unsigned int increaser,
						unsigned int module		);
	void generate	(	unsigned int num_amount	);

private:
	unsigned int	multiplier_1,
					multiplier_2,
					increaser,
					module;
};

class Third_method : public Generator
{
public:
	Third_method	(	unsigned int module	);
	void generate	(	unsigned int num_amount);

private:
	unsigned int		module;
};

class Fourth_method : public Generator
{
public:
	Fourth_method	(	unsigned int multiplier,
						unsigned int increaser, 
						unsigned int module		);
	void generate	(	unsigned int num_amount	);

private:
	unsigned int		multiplier,
						increaser,
						module;

};

class Fifth_method: public Generator
{
public:
	Fifth_method	(	unsigned int module	);
	void generate	(	unsigned int num_amount);

private:
	unsigned int module;
};

class Sixth_method
{
public:
	Sixth_method(unsigned int median, unsigned int dispersion);
	void generate(unsigned int num_amount);
	void print_numbers();
	void stat();
private:
	unsigned int	median,
					dispersion;
	unsigned int	num_amount;

	std::vector <int> numbers;						//������ ������������ �������
	unsigned int	results[7] = { 0 };				//��������� ����� ������� �������� � ������ ��������
};

class Seventh_method
{
public:
	Seventh_method() {};
	void generate(unsigned int num_amount);
	void print_numbers();
	void stat();

private:
	unsigned int num_amount;

	std::vector <double> numbers_1;
	std::vector <double> numbers_2;

	int results[6] = { 0 };
};

class Eighth_method
{
public:
	Eighth_method() {};
	void generate(unsigned int num_amount);
	void print_numbers();
	void stat();
private:
	unsigned int num_amount;

	std::vector <double> numbers;
	unsigned int results[6] = { 0 };
};

class Ninth_method
{
public:
	Ninth_method(unsigned int multiplier);
	void generate(unsigned int amount);
	void print_numbers();
	void stat();
private:
	unsigned int multiplier;
	unsigned int num_amount;

	std::vector <unsigned int> numbers;
	unsigned int results[10] = { 0 };
};

class Tenth_method
{
public:
	Tenth_method(unsigned int coefficient);
	void generate(unsigned int num_amount);
	void print_numbers();
	void stat();
private:
	unsigned int coefficient;
	unsigned int num_amount;

	std::vector <unsigned int> numbers;
	unsigned int results[10] = { 0 };
};