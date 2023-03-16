// Trash the cashe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <string> 

using namespace std::chrono;

struct Transform
{
	float matrix[16]
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
};


class GameObject3D
{
public:
	Transform* transform{};
	int id{};
};

int main()
{

	constexpr unsigned int arrSize = 1'000'000'00;
	GameObject3D* arr = new GameObject3D[arrSize]{};

	for (int steps = 1; steps < 1024; steps *= 2)
	{
		auto start = high_resolution_clock::now();

		for (int i = 0; i < arrSize; i += steps)
		{
			arr[i].id *= 2;
		}

		auto end = high_resolution_clock::now();

		auto elapsed = duration_cast<milliseconds>(end - start);

		std::cout << "operation took " << elapsed.count() << "ms" << std::endl;
	}
}

