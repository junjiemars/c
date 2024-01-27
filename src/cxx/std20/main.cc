#include <atomic>
#include <iomanip>
#include <iostream>

#ifdef __cpp_lib_concepts
#include <concepts>

template <typename T> concept Addable = •requires (T a, T b)
{
	{ a + b } -> std::same_as<T>;
};

template <Addable T>
T
add (T a, T b)
{
	return a + b;
}
#endif

int
main ()
{
#ifdef __cpp_lib_concepts
	std::cout << add(3, 4) << std::endl;
#endif



  return 0;
}
