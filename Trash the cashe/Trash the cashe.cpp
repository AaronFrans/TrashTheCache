// Trash the cashe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <vector>
#include <map>
#include <numeric>

using namespace std::chrono;

constexpr unsigned int ARRAY_SIZE = 20'000'000;

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

// function via : https://stackoverflow.com/questions/3452712/how-do-i-remove-the-smallest-and-largest-element-in-an-array-in-a-manner-thats
std::vector<int> WithoutHiLo(const std::vector<int>& orig)
{
	//taking copy to keep original vector the same
	std::vector<int> copy = orig;

	std::sort(copy.begin(), copy.end());
	return std::vector(&copy[1], &copy[copy.size() - 1]);
}


float Average(const std::vector<int>& v) {
	if (v.empty()) {
		return 0;
	}

	auto const count = static_cast<float>(v.size());

	return std::reduce(v.begin(), v.end()) / count;
}

void HandleTimings(const std::map<unsigned int, std::vector<int>>& timings)
{
	for (auto& timing : timings)
	{
		auto data = WithoutHiLo(timing.second);
		auto average = Average(data);

		std::cout << "average for " << timing.first << " steps took " << average << " microseconds" << std::endl;
	}
}

void MeasureInts()
{

	int* arr = new int[ARRAY_SIZE];

	std::map<unsigned int, std::vector<int>> timings{};

	for (size_t sample = 0; sample < 20; sample++)
	{
		for (int steps = 1; steps <= 1024; steps *= 2)
		{
			auto start = high_resolution_clock::now();

			for (unsigned int i = 0; i < ARRAY_SIZE; i += steps)
			{
				arr[i] *= 2;
			}

			auto end = high_resolution_clock::now();

			auto elapsed = duration_cast<microseconds>(end - start);

			timings[steps].push_back(static_cast<int>(elapsed.count()));
		}

	}

	HandleTimings(timings);

	delete[] arr;
}

void MeasureGameObjects3D()
{
	GameObject3D* arr = new GameObject3D[ARRAY_SIZE];

	std::map<unsigned int, std::vector<int>> timings{};

	for (size_t sample = 0; sample < 20; sample++)
	{
		for (int steps = 1; steps <= 1024; steps *= 2)
		{
			auto start = high_resolution_clock::now();

			for (unsigned int i = 0; i < ARRAY_SIZE; i += steps)
			{
				arr[i].m_Id *= 2;
			}

			auto end = high_resolution_clock::now();

			auto elapsed = duration_cast<microseconds>(end - start);

			timings[steps].push_back(static_cast<int>(elapsed.count()));
		}

	}

	HandleTimings(timings);
	delete[] arr;
}

void MeasureGameObject3DAlts()
{
	GameObject3DAlt* arr = new GameObject3DAlt[ARRAY_SIZE];

	std::map<unsigned int, std::vector<int>> timings{};

	for (size_t sample = 0; sample < 20; sample++)
	{
		for (int steps = 1; steps <= 1024; steps *= 2)
		{
			auto start = high_resolution_clock::now();

			for (unsigned int i = 0; i < ARRAY_SIZE; i += steps)
			{
				arr[i].m_Id *= 2;
			}

			auto end = high_resolution_clock::now();

			auto elapsed = duration_cast<microseconds>(end - start);

			timings[steps].push_back(static_cast<int>(elapsed.count()));
		}


	}

	HandleTimings(timings);
	delete[] arr;
}


int main()
{
	std::cout << "\n----------ints start------------\n" << std::endl;
	MeasureInts();
	std::cout << "\n----------ints end--------------\n" << std::endl;
	std::cout << "\n----------GameObject3D start------------\n" << std::endl;
	MeasureGameObjects3D();
	std::cout << "\n----------GameObject3D end--------------\n" << std::endl;
	std::cout << "\n----------GameObject3DAlt start------------\n" << std::endl;
	MeasureGameObject3DAlts();
	std::cout << "\n----------GameObject3DAlt end--------------\n" << std::endl;
}
