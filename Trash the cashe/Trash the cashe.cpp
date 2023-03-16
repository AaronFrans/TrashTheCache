// Trash the cashe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <string>
#include <vector>

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

	Transform m_Transform{};
	int m_Id{};
};

class GameObject3DAlt
{
public:

	~GameObject3DAlt() { delete m_pTransform; }
	Transform* m_pTransform{};
	int m_Id{};
};



void MeasureInts()
{
	constexpr unsigned int arrSize = 3'000'000'000;
	int* arr = new int[arrSize];

	for (int steps = 1; steps <= 1024; steps *= 2)
	{
		auto start = high_resolution_clock::now();

		for (unsigned int i = 0; i < arrSize; i += steps)
		{
			arr[i] *= 2;
		}

		auto end = high_resolution_clock::now();

		auto elapsed = duration_cast<milliseconds>(end - start);

		std::cout << "operation took " << elapsed.count() << " ms" << std::endl;
	}
	delete[] arr;
}

void MeasureGameObjects3D()
{
	constexpr unsigned int arrSize = 2'000'000'00;
	GameObject3D* arr = new GameObject3D[arrSize];

	for (int steps = 1; steps <= 1024; steps *= 2)
	{
		auto start = high_resolution_clock::now();

		for (unsigned int i = 0; i < arrSize; i += steps)
		{
			arr[i].m_Id *= 2;
		}

		auto end = high_resolution_clock::now();

		auto elapsed = duration_cast<milliseconds>(end - start);

		std::cout << "operation took " << elapsed.count() << " ms" << std::endl;
	}
	delete[] arr;
}

void MeasureGameObject3DAlts()
{
	constexpr unsigned int arrSize = 2'000'000'00;
	GameObject3DAlt* arr = new GameObject3DAlt[arrSize];

	for (int steps = 1; steps <= 1024; steps *= 2)
	{
		auto start = high_resolution_clock::now();

		for (unsigned int i = 0; i < arrSize; i += steps)
		{
			arr[i].m_Id *= 2;
		}

		auto end = high_resolution_clock::now();

		auto elapsed = duration_cast<milliseconds>(end - start);

		std::cout << "operation took " << elapsed.count() << " ms" << std::endl;
	}

	delete[] arr;
}


int main()
{
	std::cout << "----------ints start------------" << std::endl;
	MeasureInts();
	std::cout << "----------ints end--------------" << std::endl;
	std::cout << "----------GameObject3D start------------" << std::endl;
	MeasureGameObjects3D();
	std::cout << "----------GameObject3D end--------------" << std::endl;
	std::cout << "----------GameObject3DAlt start------------" << std::endl;
	MeasureGameObject3DAlts();
	std::cout << "----------GameObject3DAlt end--------------" << std::endl;
}
