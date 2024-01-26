#include <iostream>
#include <iomanip>

auto add(int a, int b) {
	return a + b;
}

template<typename T>
constexpr T pi = T(3.14159265358979323846);

int main() {
	std::cout << add(3,4) << std::endl;
	int c = 5;
	auto times = [c](auto a, auto b) {
		return a * b * c;
	};
	std::cout << times(3,4) << std::endl;
  std::cout << pi<float> << std::endl;
	std::cout << std::setprecision(10) << pi<long double> << std::endl;
	return 0;
}
