#define _USE_MATH_DEFINES
#include "Generators.h"
#include <iomanip>
#include <cmath>

int Generator::return_number(unsigned int i)
{
	return (numbers[i]);
}

void Generator::print_numbers()
{
	if (!numbers.size())
	{
		std::cout << "Numbers are not generated!\n";
		return;
	}

	for (size_t i = 0; i < numbers.size(); ++i)
	{
		std::cout << '|' << std::setw(4) << numbers[i] << std::setw(4);
		if ((i + 1) % 10 == 0) std::cout << "|\n";
	}
	std::cout << std::endl;
}

void Generator::stat()
{
	std::cout << "[0.0; 0.1)\t" << std::setw(10) << double(results[0]) / num_amount << "\t\t(" << results[0] << ")\n";
	std::cout << "[0.1; 0.2)\t" << std::setw(10) << double(results[1]) / num_amount << "\t\t(" << results[1] << ")\n";
	std::cout << "[0.2; 0.3)\t" << std::setw(10) << double(results[2]) / num_amount << "\t\t(" << results[2] << ")\n";
	std::cout << "[0.3; 0.4)\t" << std::setw(10) << double(results[3]) / num_amount << "\t\t(" << results[3] << ")\n";
	std::cout << "[0.4; 0.5)\t" << std::setw(10) << double(results[4]) / num_amount << "\t\t(" << results[4] << ")\n";
	std::cout << "[0.5; 0.6)\t" << std::setw(10) << double(results[5]) / num_amount << "\t\t(" << results[5] << ")\n";
	std::cout << "[0.6; 0.7)\t" << std::setw(10) << double(results[6]) / num_amount << "\t\t(" << results[6] << ")\n";
	std::cout << "[0.7; 0.8)\t" << std::setw(10) << double(results[7]) / num_amount << "\t\t(" << results[7] << ")\n";
	std::cout << "[0.8; 0.9)\t" << std::setw(10) << double(results[8]) / num_amount << "\t\t(" << results[8] << ")\n";
	std::cout << "[0.9; 1.0]\t" << std::setw(10) << double(results[9] + results[10]) / num_amount << "\t\t(" << results[9] + results[10] << ")\n";
}

//****************************************************************

First_method::First_method	(	unsigned int multiplier,
								unsigned int increaser,
								unsigned int module		)
{
	this->multiplier	= multiplier;
	this->increaser		= increaser;
	this->module		= module;
}

void First_method::generate	(	unsigned int num_amount	)
{
	this->num_amount = num_amount;
	unsigned int number = 1;

	for (int i = 1; i <= num_amount; ++i)
	{
		number = (multiplier * number + increaser) % module;
		numbers.push_back(number);
		++results[int((double(number) / (module - 1)) * 10)];
	}
}

//****************************************************************

Second_method::Second_method(	unsigned int multiplier_1, 
								unsigned int multiplier_2,
								unsigned int increaser,
								unsigned int module			)
{
	this->multiplier_1	= multiplier_1;
	this->multiplier_2	= multiplier_2;
	this->increaser		= increaser;
	this->module		= module;
}

void Second_method::generate(	unsigned int num_amount	)
{
	this->num_amount = num_amount;
	unsigned int number = 1;

	for (int i = 1; i <= num_amount; ++i)
	{
		number = (multiplier_1 * number * number + multiplier_2 * number + increaser) % module;
		numbers.push_back(number);
		++results[int((double(number) / (module - 1)) * 10)];
	}
}

//****************************************************************

Third_method::Third_method	(	unsigned int module	)
{
	this->module		= module;
}

void Third_method::generate(	unsigned int num_amount)
{
	this->num_amount = num_amount;
	unsigned int number_1 = 1;
	unsigned int number_2 = 1;
	unsigned int number_3 = 1;

	for (int i = 1; i <= num_amount; ++i)
	{
		number_3 = (number_1 + number_2) % module;
		numbers.push_back(number_3);
		number_1 = number_2;
		number_2 = number_3;
		++results[int((double(number_3) / (module - 1)) * 10)];
	}
}

//****************************************************************

Fourth_method::Fourth_method	(	unsigned int multiplier,
									unsigned int increaser,
									unsigned int module		)
{
	this->multiplier	= multiplier;
	this->increaser		= increaser;
	this->module		= module;
}

void Fourth_method::generate	(	unsigned int num_amount	)
{
	this->num_amount = num_amount;
	unsigned int number = 1, reverse_number = 0;

	for (int i = 1; i <= num_amount; ++i)
	{
		int j = 1;
		while ((number*reverse_number) % module != 1)
		{
			reverse_number = (module * j + 1) / number;
			++j;
		}

		number = (multiplier * reverse_number + increaser) % module;
		numbers.push_back(number);
		++results[int((double(number) / (module - 1)) * 10)];
	}

}

//****************************************************************

Fifth_method::Fifth_method		(	unsigned int module	)
{
	this->module = module;
}

void Fifth_method::generate		(	unsigned int num_amount)
{
	this->num_amount = num_amount;
	unsigned int number = 0;

	First_method first(99, 13, 101);
	Third_method second(7);

	first.generate(num_amount);
	second.generate(num_amount);

	for (int i = 0; i < num_amount; ++i)
	{
		number = abs(first.return_number(i) - second.return_number(i)) % module;
		numbers.push_back(number);
		++results[int((double(number) / (module - 1)) * 10)];
	}
}

//****************************************************************

Sixth_method::Sixth_method(unsigned int median, unsigned int dispersion)
{
	this->median = median;
	this->dispersion = dispersion;
}

void Sixth_method::generate(unsigned int num_amount)
{
	this->num_amount = num_amount;

	int number = 0;
	double sum = 0;

	Fifth_method rand(101);
	rand.generate(num_amount * 12);

	for (int i = 0; i < num_amount; ++i)
	{
		sum = double(	rand.return_number(i * 12)
					+ rand.return_number(i * 12 + 1)
					+ rand.return_number(i * 12 + 2)
					+ rand.return_number(i * 12 + 3)
					+ rand.return_number(i * 12 + 4)
					+ rand.return_number(i * 12 + 5)
					+ rand.return_number(i * 12 + 6)
					+ rand.return_number(i * 12 + 7)
					+ rand.return_number(i * 12 + 8)
					+ rand.return_number(i * 12 + 9)
					+ rand.return_number(i * 12 + 10)
					+ rand.return_number(i * 12 + 11)	) / 120 ;
		number = median + (sum - 6) * dispersion;

		numbers.push_back(number);

		if (((number + 3) >= 0) && ((number + 3) <= 6))
		{
			++results[number + 3];
		}
	}
}

void Sixth_method::print_numbers()
{
		if (!numbers.size())
		{
			std::cout << "Numbers are not generated!\n";
			return;
		}
		for (size_t i = 0; i < numbers.size(); ++i)
		{
			std::cout << '|' << std::setw(4) << numbers[i] << std::setw(4);
			if ((i + 1) % 10 == 0) std::cout << "|\n";
		}
		std::cout << std::endl;
}

void Sixth_method::stat()
{
	std::cout << "{-3}\t"	<< std::setw(10) << double(results[0]) / num_amount << "\t\t(" << results[0] << ")\n";
	std::cout << "{-2}\t"	<< std::setw(10) << double(results[1]) / num_amount << "\t\t(" << results[1] << ")\n";
	std::cout << "{-1}\t"	<< std::setw(10) << double(results[2]) / num_amount << "\t\t(" << results[2] << ")\n";
	std::cout << " {0}\t"	<< std::setw(10) << double(results[3]) / num_amount << "\t\t(" << results[3] << ")\n";
	std::cout << " {1}\t"	<< std::setw(10) << double(results[4]) / num_amount << "\t\t(" << results[4] << ")\n";
	std::cout << " {2}\t"	<< std::setw(10) << double(results[5]) / num_amount << "\t\t(" << results[5] << ")\n";
	std::cout << " {3}\t"	<< std::setw(10) << double(results[6]) / num_amount << "\t\t(" << results[6] << ")\n";
}

//****************************************************************

void Seventh_method::generate(unsigned int num_amount)
{
	this->num_amount = num_amount;
	double num_1, num_2, sum = 1;
	const int module = 101;
	int futhesistem;

	Fifth_method generator(module);
	generator.generate(num_amount * 2);

	for (size_t i = 0; i < num_amount; ++i)
	{
		futhesistem = 0;
		while (sum >= 1 && ((i * 2 + 1 + futhesistem) < (2 * num_amount)))
		{
			num_1 = double(generator.return_number(i * 2 + futhesistem)) / (module - 1);
			num_2 = double(generator.return_number(i * 2 + 1 + futhesistem)) / (module - 1);
			num_1 = 2 * num_1 - 1;
			num_2 = 2 * num_2 - 1;
			sum = num_1 * num_1 + num_2 * num_2;
			++futhesistem;
		}
		if (sum >= 1) { return; }

		num_1 *= sqrt(-2 * log(sum) / sum);
		num_2 *= sqrt(-2 * log(sum) / sum);
		sum = 1;

		numbers_1.push_back(num_1);
		numbers_2.push_back(num_2);

		if ((-3 <= num_1) && (num_1 < -2))	++results[0];
		if ((-2 <= num_1) && (num_1 < -1))	++results[1];
		if ((-1 <= num_1) && (num_1 < 0))	++results[2];
		if (( 0 <= num_1) && (num_1 < 1))	++results[3];
		if (( 1 <= num_1) && (num_1 < 2))	++results[4];
		if (( 2 <= num_1) && (num_1 <= 3))	++results[5];

		if ((-3 <= num_1) && (num_1 < -2))	++results[0];
		if ((-2 <= num_1) && (num_1 < -1))	++results[1];
		if ((-1 <= num_1) && (num_1 < 0))	++results[2];
		if ((0 <= num_1) && (num_1 < 1))	++results[3];
		if ((1 <= num_1) && (num_1 < 2))	++results[4];
		if ((2 <= num_1) && (num_1 <= 3))	++results[5];
	}
}

void Seventh_method::print_numbers()
{
	if (!numbers_1.size())
	{
		std::cout << "Numbers are not generated!\n";
		return;
	}
	for (size_t i = 0; i < numbers_1.size(); ++i)
	{
		std::cout << '|' << std::setw(10) << numbers_1[i] << std::setw(4) << "|" << std::setw(10) << numbers_2[i] << std::endl;
	}
	std::cout << std::endl;
}

void Seventh_method::stat()
{
	std::cout << "[-3; -2)\t"	<< std::setw(10) << double(results[0]) / num_amount << "\t\t(" << results[0] << ")\n";
	std::cout << "[-2; -1)\t"	<< std::setw(10) << double(results[1]) / num_amount << "\t\t(" << results[1] << ")\n";
	std::cout << "[-1;  0)\t"	<< std::setw(10) << double(results[2]) / num_amount << "\t\t(" << results[2] << ")\n";
	std::cout << "[ 0;  1)\t"	<< std::setw(10) << double(results[3]) / num_amount << "\t\t(" << results[3] << ")\n";
	std::cout << "[ 1;  2)\t"	<< std::setw(10) << double(results[4]) / num_amount << "\t\t(" << results[4] << ")\n";
	std::cout << "[ 2;  3]\t"	<< std::setw(10) << double(results[5]) / num_amount << "\t\t(" << results[5] << ")\n";
}

//****************************************************************

void Eighth_method::generate(unsigned int num_amount)
{
	this->num_amount = num_amount;

	double number, temp;
	const int module = 101;
	Fifth_method generator(module);
	generator.generate(num_amount * 2);
	
	for (size_t i = 0; i < num_amount; ++i)
	{
		number	= double(generator.return_number(2*i)) / (module - 1);
		temp	= double(generator.return_number(2*i+1) + 1) / module;		// !=0
		number	= sqrt(8 / exp(1))*(number - 0.5) / temp;

		numbers.push_back(number);

		if ((-3 <= number) && (number < -2))	++results[0];
		if ((-2 <= number) && (number < -1))	++results[1];
		if ((-1 <= number) && (number <  0))	++results[2];
		if (( 0 <= number) && (number <  1))	++results[3];
		if (( 1 <= number) && (number <  2))	++results[4];
		if (( 2 <= number) && (number <=  3))	++results[5];
	}
}

void Eighth_method::print_numbers()
{
	if (!numbers.size())
	{
		std::cout << "Numbers are not generated!\n";
		return;
	}
	for (size_t i = 0; i < numbers.size(); ++i)
	{
		std::cout << '|' << std::setw(10) << numbers[i] << std::setw(4);
		if ((i + 1) % 5 == 0) std::cout << "|\n";
	}
	std::cout << std::endl;
}

void Eighth_method::stat()
{
	std::cout << "[-3; -2)\t" << std::setw(10) << double(results[0]) / num_amount << "\t\t(" << results[0] << ")\n";
	std::cout << "[-2; -1)\t" << std::setw(10) << double(results[1]) / num_amount << "\t\t(" << results[1] << ")\n";
	std::cout << "[-1;  0)\t" << std::setw(10) << double(results[2]) / num_amount << "\t\t(" << results[2] << ")\n";
	std::cout << "[ 0;  1)\t" << std::setw(10) << double(results[3]) / num_amount << "\t\t(" << results[3] << ")\n";
	std::cout << "[ 1;  2)\t" << std::setw(10) << double(results[4]) / num_amount << "\t\t(" << results[4] << ")\n";
	std::cout << "[ 2;  3]\t" << std::setw(10) << double(results[5]) / num_amount << "\t\t(" << results[5] << ")\n";
}

//****************************************************************

Ninth_method::Ninth_method(unsigned int multiplier) 
{
	this->multiplier = multiplier;
}

void Ninth_method::generate(unsigned int num_amount)
{
	this->num_amount = num_amount;

	const int module = 101;
	Fifth_method generator(module);
	generator.generate(num_amount);
	double number = 0;

	for (size_t i = 0; i < num_amount; ++i)
	{
		number = double(generator.return_number(i)) / (module - 1);
		number = (-1) * double(multiplier) * (log(1 - number));
		numbers.push_back(number);

		if (number < 10)	++results[0];
		else
		{
			if (number < 20)	++results[1];
			else
			{
				if (number < 30)	++results[2];
				else
				{
					if (number < 40)	++results[3];
					else
					{
						if (number < 50)	++results[4];
						else
						{
							if (number < 60)	++results[5];
							else
							{
								if (number < 70)	++results[6];
								else
								{
									if (number < 80)	++results[7];
									else
									{
										if (number < 90)	++results[8];
										else
										{
											if (number < 100)	++results[9];
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void Ninth_method::print_numbers()
{
	if (!numbers.size())
	{
		std::cout << "Numbers are not generated!\n";
		return;
	}
	for (size_t i = 0; i < numbers.size(); ++i)
	{
		std::cout << '|' << std::setw(10) << numbers[i] << std::setw(4);
		if ((i + 1) % 5 == 0) std::cout << "|\n";
	}
	std::cout << std::endl;
}

void Ninth_method::stat()
{
	std::cout << "[ 0;  10)\t" << std::setw(10) << double(results[0]) / num_amount << "\t\t(" << results[0] << ")\n";
	std::cout << "[10;  20)\t" << std::setw(10) << double(results[1]) / num_amount << "\t\t(" << results[1] << ")\n";
	std::cout << "[20;  30)\t" << std::setw(10) << double(results[2]) / num_amount << "\t\t(" << results[2] << ")\n";
	std::cout << "[30;  40)\t" << std::setw(10) << double(results[3]) / num_amount << "\t\t(" << results[3] << ")\n";
	std::cout << "[40;  50)\t" << std::setw(10) << double(results[4]) / num_amount << "\t\t(" << results[4] << ")\n";
	std::cout << "[50;  60)\t" << std::setw(10) << double(results[5]) / num_amount << "\t\t(" << results[5] << ")\n";
	std::cout << "[60;  70)\t" << std::setw(10) << double(results[6]) / num_amount << "\t\t(" << results[6] << ")\n";
	std::cout << "[70;  80)\t" << std::setw(10) << double(results[7]) / num_amount << "\t\t(" << results[7] << ")\n";
	std::cout << "[80;  90)\t" << std::setw(10) << double(results[8]) / num_amount << "\t\t(" << results[8] << ")\n";
	std::cout << "[90; 100)\t" << std::setw(10) << double(results[9]) / num_amount << "\t\t(" << results[9] << ")\n";
}

//****************************************************************

Tenth_method::Tenth_method(unsigned int coefficient)
{
	this->coefficient = coefficient;
}

void Tenth_method::generate(unsigned int num_amount)
{
	this->num_amount = num_amount;

	double number = 0, temp = 0;
	unsigned int module = 101, futhesystem = 0;

	Fifth_method generator(module);
	generator.generate(num_amount * 2);

	Fifth_method dop_generator(module);
	dop_generator.generate(module);

	for (size_t i = 0; i < num_amount; ++i)
	{
		futhesystem = 0;
		while (number <= 0)
		{
			temp = double(generator.return_number(i + futhesystem)) / (module - 1);
			temp = tan(M_PI * temp);
			number = sqrt(2 * coefficient - 1) * temp + coefficient - 1;
			//checking
			temp = (1 + temp * temp) * exp((coefficient - 1) * log(number / (coefficient - 1)) - sqrt(2 * coefficient - 1) * temp);
			if ((double(dop_generator.return_number(generator.return_number(i))) / (module - 1)) > temp)
			{
				number = 0;
			}
			++futhesystem;
		}
		numbers.push_back(number);

		if (number < 10)	++results[0];
		else
		{
			if (number < 20)	++results[1];
			else
			{
				if (number < 30)	++results[2];
				else
				{
					if (number < 40)	++results[3];
					else
					{
						if (number < 50)	++results[4];
						else
						{
							if (number < 60)	++results[5];
							else
							{
								if (number < 70)	++results[6];
								else
								{
									if (number < 80)	++results[7];
									else
									{
										if (number < 90)	++results[8];
										else
										{
											if (number < 100)	++results[9];
										}
									}
								}
							}
						}
					}
				}
			}
		}
		number = 0;
	}
}

void Tenth_method::print_numbers()
{
	if (!numbers.size())
	{
		std::cout << "Numbers are not generated!\n";
		return;
	}
	for (size_t i = 0; i < numbers.size(); ++i)
	{
		std::cout << '|' << std::setw(10) << numbers[i] << std::setw(4);
		if ((i + 1) % 5 == 0) std::cout << "|\n";
	}
	std::cout << std::endl;
}

void Tenth_method::stat()
{
	std::cout << "[ 0;  10)\t" << std::setw(10) << double(results[0]) / num_amount << "\t\t(" << results[0] << ")\n";
	std::cout << "[10;  20)\t" << std::setw(10) << double(results[1]) / num_amount << "\t\t(" << results[1] << ")\n";
	std::cout << "[20;  30)\t" << std::setw(10) << double(results[2]) / num_amount << "\t\t(" << results[2] << ")\n";
	std::cout << "[30;  40)\t" << std::setw(10) << double(results[3]) / num_amount << "\t\t(" << results[3] << ")\n";
	std::cout << "[40;  50)\t" << std::setw(10) << double(results[4]) / num_amount << "\t\t(" << results[4] << ")\n";
	std::cout << "[50;  60)\t" << std::setw(10) << double(results[5]) / num_amount << "\t\t(" << results[5] << ")\n";
	std::cout << "[60;  70)\t" << std::setw(10) << double(results[6]) / num_amount << "\t\t(" << results[6] << ")\n";
	std::cout << "[70;  80)\t" << std::setw(10) << double(results[7]) / num_amount << "\t\t(" << results[7] << ")\n";
	std::cout << "[80;  90)\t" << std::setw(10) << double(results[8]) / num_amount << "\t\t(" << results[8] << ")\n";
	std::cout << "[90; 100)\t" << std::setw(10) << double(results[9]) / num_amount << "\t\t(" << results[9] << ")\n";
}