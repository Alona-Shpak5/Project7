#include <iostream>
#include <future>
#include <thread>
#include <atomic>
#include <random>
#include<vector>
#include <numeric>

int sum_vectors(const std::vector<int>& vec, size_t start, size_t end) {
	return std::accumulate(vec.begin() + start, vec.begin() + end, 0);
	
}

int parallel_sum_vectors(const std::vector<int>& vec) {
	size_t size = vec.size();
	size_t mid = size / 2;

	auto future1 = std::async(std::launch::async, [&, mid]() {
		return sum_vectors(vec, 0, mid);
		});

	auto future2 = std::async(std::launch::async, [&, mid, size]() {
		return sum_vectors(vec, mid, size);
		});

	int sum1 = future1.get();
	int sum2 = future2.get();

	return sum1 + sum2;
}

int main() {
	std::vector<int> vec = { 1, 5, 2, 6, 5, 6, 8, 8, 1, 3 };

	int total_sum = parallel_sum_vectors(vec);

	std::cout << "Total sum: " << total_sum << std::endl;

	
	return 0;
}