#include <modern.h>

struct crow {
	const char* jay;
	const char* magpie;
	const char* raven;
};

int main(int argc, char* argv[]) {
	_unused_(argc);
	_unused_(argv);

	struct crow const crow = {
		.magpie = "magpie",
		.raven = "raven",
		.jay = "jay",
	};	
	_unused_(crow);

	return 0;
}
