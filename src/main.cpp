#include <iostream>
#include <string_view>
#include <cstring>
#include <array>
#include <vector>
#include <unordered_map>

static constexpr uint64_t getRomanEquivelant(char chr)
{
	switch (chr) {
		case 'I':
			return 1ULL;
		case 'V':
			return 5ULL;
		case 'X':
			return 10ULL;
		case 'L':
			return 50ULL;
		case 'C':
			return 100ULL;
		case 'M':
			return 1000ULL;

		default:
			return -1;
	}
}

int main(int argc, char** argv)
{
	std::cout << "Hello Anan!\n";

	return 0;
}
