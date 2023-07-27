#include <bits/stdc++.h>
void sieve_bool(size_t n);
void sieve_char(size_t n);

template<typename Function>
double benchmark(Function&& func, int argument, int num_iterations) {
    auto start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_iterations; ++i) {
        func(argument);
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end_time - start_time).count() / num_iterations;
}

int main() {
    std::cout << "Finding primes (1 Billion range)" << '\n';
    double t = benchmark(sieve_bool, 1'000'000'000, 1);
    std::cout << "Average using C++ std::vector<bool>: " << t/1000 << " seconds\n";
    double v = benchmark(sieve_char, 1'000'000'000, 1);
    std::cout << "Average using C char* + malloc: " << v/1000 << " seconds";
}

void sieve_bool(size_t n) {
    static std::vector<bool> composite_vec(n, false);
    for (size_t i {4}; i < n; i += 2) {
        composite_vec[i] = true;
    }
    const auto sqrtn = static_cast<size_t>(std::sqrt(n));
    for (size_t i {3}; i < sqrtn; i += 2) {
        if (!composite_vec[i]) {
            for (size_t j { i * i }; j < n; j += i << 1) {
                composite_vec[i] = true;
            }
        }
    }
}

void sieve_char(size_t n) {
    char* composite_list = (char*) malloc(n);
    memset(composite_list, 0, n);
    composite[0] = 1;
    composite[1] = 1;
    for (size_t i {4}; i < n; i += 2) {
        composite_list[i] = 1;
    }
    const auto sqrtn = static_cast<size_t>(std::sqrt(n));
    for (size_t i {3}; i < sqrtn; i += 2) {
        if (!composite_list[i]) {
            for (size_t j { i * i }; j < n; j += i << 1) {
                composite_list[j] = 1;
            }
        }
    }
    free(composite_list);
}
