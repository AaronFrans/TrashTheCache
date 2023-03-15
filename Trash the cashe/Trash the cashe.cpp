// Trash the cashe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <string>

using namespace std::chrono;
int main()
{

	constexpr unsigned int arrSize = 2'000'000'000;
	int* arr = new int[arrSize];

	for (int steps = 1; steps < 1024; steps *= 2)
	{
		auto start = high_resolution_clock::now();

		for (int i = 0; i < arrSize; i += steps)
		{
			arr[i] *= 2;
		}
		
		auto end = high_resolution_clock::now();

		auto elapsed = duration_cast<milliseconds>(end - start);

		std::cout << "operation took" << elapsed.count() << "ms" << std::endl;
	}
}

