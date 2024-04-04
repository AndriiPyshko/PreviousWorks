#include "Generators.h"

void PRNG(int&, int&);

int main()
{
	system("color d");

	std::cout << "Pseudo-random number generator\t\t\t\t\t\t\t\t\tby Pyshko Andriy\n\n";
	std::cout << "What method of generation do you wanna use?\nAnswer: ";
	int number, amount;
	std::cin >> number;
	std::cout << "How many numbers do you wanna get?\nAnswer: ";
	std::cin >> amount;

	PRNG(number, amount);

	system("pause");
	return 0;
}

void PRNG(int& number, int& amount)
{
	switch (number)
	{
	case 1:
	{
		std::cout << "\n-->Linear congruent method\n";
		First_method generator (99,13,101);
		std::cout << "generating...";
		generator.generate(amount);
		std::cout << "OK\n\n";
		generator.print_numbers();
		std::cout << "Statistics:\n";
		generator.stat();
		break;
	}
	case 2:
	{
		std::cout << "\n-->Quadratic congruent method\n";
		Second_method generator(67, 3, 40, 7254697);
		std::cout << "generating...";
		generator.generate(amount);
		std::cout << "OK\n\n";
		generator.print_numbers();
		std::cout << "Statistics:\n";
		generator.stat();
		break;
	}
	case 3:
	{
		std::cout << "\n-->Fibonacci numbers\n";
		Third_method generator(100);
		std::cout << "generating...";
		generator.generate(amount);
		std::cout << "OK\n\n";
		generator.print_numbers();
		std::cout << "Statistics:\n";
		generator.stat();
		break;
	}
	case 4:
	{
		std::cout << "\n-->Inverted congruent sequence\n";
		Fourth_method generator(13,14,157);
		std::cout << "generating...";
		generator.generate(amount);
		std::cout << "OK\n\n";
		generator.print_numbers();
		std::cout << "Statistics:\n";
		generator.stat();
		break;
	}
	case 5:
	{
		std::cout << "\n-->Merge method\n\n";
		Fifth_method generator(101);
		std::cout << "generating...";
		generator.generate(amount);
		std::cout << "OK\n\n";
		generator.print_numbers();
		std::cout << "Statistics:\t\t\t\t\t\t\t\t\t\t	(Sharapov edition)\n";
		generator.stat();
		break;
	}
	case 6:
	{
		std::cout << "\n-->The rule of 3 sigma\n";
		Sixth_method generator(3, 5);
		std::cout << "generating...";
		generator.generate(amount);
		std::cout << "OK\n\n";
		generator.print_numbers();
		std::cout << "Statistics:\n";
		generator.stat();
		break;
	}
	case 7:
	{
		std::cout << "\n-->Polar coordinate method\n";
		Seventh_method generator;
		std::cout << "generating...";
		generator.generate(amount);
		std::cout << "OK\n\n";
		generator.print_numbers();
		std::cout << "Statistics:\n";
		generator.stat();
		break;
	}
	case 8:
	{
		std::cout << "\n-->The ratio method\n";
		Eighth_method generator;
		std::cout << "generating...";
		generator.generate(amount);
		std::cout << "OK\n\n";
		generator.print_numbers();
		std::cout << "Statistics:\n";
		generator.stat();
		break;
	}
	case 9:
	{
		std::cout << "\n-->The logarithm method for generating an exponential distribution\n";
		Ninth_method generator(21);
		std::cout << "generating...";
		generator.generate(amount);
		std::cout << "OK\n\n";
		generator.print_numbers();
		std::cout << "Statistics:\n";
		generator.stat();
		break;
	}
	case 10:
	{
		std::cout << "\n-->The Ahrens method for generating a gamma distribution\n";
		Tenth_method generator(50);
		std::cout << "generating...";
		generator.generate(amount);
		std::cout << "OK\n\n";
		generator.print_numbers();
		std::cout << "Statistics:\n";
		generator.stat();
		break;
	}
	default:
		std::cout << "There's no generator with this number\n";
	}
}