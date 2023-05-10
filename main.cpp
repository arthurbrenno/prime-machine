#include <iostream>
#include <chrono>
#include <bitset>
#include <cmath>
int main() {
	//find primes until the range (2 <= x < range)
	constexpr auto range = 1'000'000;
	
	auto start = std::chrono::steady_clock::now();
	std::bitset<range>* composite = new std::bitset<range>;
	
	//mark all even composite
	for (int i{ 4 }; i < range; i += 2) {
		(*composite)[i] = 1;
	}
	
	//check for odd numbers
	for (int i{ 3 }; i < std::sqrt(range); i += 2) {
		if (!(*composite)[i]) {
			for (int j{ i * i }; j < range; j += 2 * i) { 
				(*composite)[j] = 1; 
			}
		}
	}

	std::cout << "Bytes occupied: " << sizeof * composite << '\n';
	auto end = std::chrono::steady_clock::now();
	auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
	
	std::cout << "Duration: " << elapsed_time << 's' << '\n';
	composite->flip(); 
	size_t num_primes = composite->count() - 2;
	std::cout << "Primes: " << num_primes << '\n' << '\n';
	composite->flip();
	int show_primes{};
	std::cout << "Show prime numbers? (1/0) >>";
	std::cin >> show_primes;

	if (show_primes) {
		for (int i{ 2 }; i < range; ++i) {
			if (!(*composite)[i]) {
				std::cout << i << ' ';
			}
		}
	}
	
	system("pause");
	delete composite;
	return 0;
}
