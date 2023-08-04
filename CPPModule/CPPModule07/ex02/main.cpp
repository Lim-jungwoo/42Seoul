#include <iostream>
#include "Array.hpp"

#define MAX_VAL 10
#define T_VAL 3

int main(int, char**)
{
    /*
    int*    new_int = new int[T_VAL]();
    std::string*    new_string = new std::string[T_VAL]();
    
    Array<int>  t_a(T_VAL);
    Array<std::string> t_s(T_VAL);
    for (int i = 0; i < T_VAL; i++)
    {
        std::cout << new_int[i] << std::endl;
        std::cout << new_string[i] << std::endl;
        std::cout << t_a[i] << std::endl;
        std::cout << t_s[i] << std::endl;
    }
    delete[] new_int;
    delete[] new_string;
    */
    Array<int> numbers(MAX_VAL);
    int* mirror = new int[MAX_VAL];
    srand(time(NULL));
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand();
        numbers[i] = value;
        mirror[i] = value;
    }

	std::cout << "numbers : "; 
	for (int i = 0; i < MAX_VAL; i++)
		std::cout << numbers[i] << " ";
	std::cout << std::endl;
	std::cout << "mirror : "; 
	for (int i = 0; i < MAX_VAL; i++)
		std::cout << mirror[i] << " ";
	std::cout << std::endl;

    //SCOPE
    {
        Array<int> tmp = numbers;
        Array<int> test(tmp);

		std::cout << "tmp : "; 
		for (int i = 0; i < MAX_VAL; i++)
			std::cout << tmp[i] << " ";
		std::cout << std::endl;
		std::cout << "test : "; 
		for (int i = 0; i < MAX_VAL; i++)
			std::cout << test[i] << " ";
		std::cout << std::endl;
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        if (mirror[i] != numbers[i])
        {
            std::cerr << "didn't save the same value!!" << std::endl;
            return 1;
        }
    }

    try
    {
        numbers[-2] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        numbers[MAX_VAL] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

	try
	{
		numbers[0] = 0;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	std::cout << "after numbers[0] = 0 -> "; 
	for (int i = 0; i < MAX_VAL; i++)
		std::cout << numbers[i] << " ";
	std::cout << std::endl;
	

    for (int i = 0; i < MAX_VAL; i++)
    {
        numbers[i] = rand();
    }

	std::cout << "change numbers : "; 
	for (int i = 0; i < MAX_VAL; i++)
		std::cout << numbers[i] << " ";
	std::cout << std::endl;
    delete [] mirror;
    return 0;
    
}