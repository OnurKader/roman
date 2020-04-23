#include <array>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

template<typename T, size_t S>
std::ostream& operator<<(std::ostream& os, const std::array<T, S> array)
{
	os << "( ";
	for(size_t i = 0ULL; i < array.size() - 1; ++i)
		os << array[i] << ", ";
	os << array.back();
	os << " )";
	return os;
}

template<size_t S>
std::ostream& operator<<(std::ostream& os, const std::array<char, S> array)
{
	for(const char& chr: array)
		os << chr;
	return os;
}

constexpr uint64_t getDecimalEquivelant(const char chr)
{
	switch(chr)
	{
		case 'I': return 1ULL;
		case 'V': return 5ULL;
		case 'X': return 10ULL;
		case 'L': return 50ULL;
		case 'C': return 100ULL;
		case 'D': return 500ULL;
		case 'M': return 1000ULL;

		default: return 0ULL;
	}
}

std::string decimalToRoman(size_t number)
{
	std::string roman_str;
	roman_str.resize(16ULL);
	constexpr const size_t decimals[] = {
		7000, 6000, 5000, 4000, 3000, 2000, 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

	constexpr const char* letters[] = {"MMMMMMM",
									   "MMMMMM",
									   "MMMMM",
									   "MMMM",
									   "MMM",
									   "MM",
									   "M",
									   "CM",
									   "D",
									   "CD",
									   "C",
									   "XC",
									   "L",
									   "XL",
									   "X",
									   "IX",
									   "V",
									   "IV",
									   "I"};

	size_t i = 0ULL;
	while(number > 0ULL)
	{
		size_t div = number / decimals[i];
		number %= decimals[i];

		while(div--)
			roman_str.append(letters[i]);

		++i;
	}

	return roman_str;
}

constexpr uint64_t romanToDecimal(std::string_view str)
{
	uint64_t result = 0ULL;

	for(size_t i = 0ULL; i < str.length(); ++i)
	{
		uint64_t first = getDecimalEquivelant(str[i]);
		uint64_t second = getDecimalEquivelant(str[i + 1]);
		if(first < second)
		{
			result += (second - first);
			++i;
		}
		else
			result += first;
	}

	return result;
}

// 4269 -> MMMMCCLXIX

int main(int argc, char** argv)
{
	// Check if no arguments, go into REPL
	// Cannot accept multiple space/tab seperated numbers, only newlines
	if(argc == 1)
	{
		char* input = nullptr;
		size_t len = 0ULL;
		ssize_t read_size = 0LL;
		while((read_size = getline(&input, &len, stdin)) != -1)
		{
			// Remove the last character which is a newline
			input[--read_size] = '\0';

			// Determine if the input is a decimal or roman
		}

		free(input);
		return 0;
	}

	// Non REPL, the rest of the arguments are the numbers, if there are multiple do them
	// seperately and don't require a new line, just whitespace
	for(size_t i = 1ULL; i < static_cast<size_t>(argc); ++i)
	{
		// Determine if the input is a decimal or roman

		std::string result = decimalToRoman(static_cast<size_t>(std::atoll(argv[i])));
		//		uint64_t result = romanToDecimal(argv[i]);
		std::cout << "My Guess: " << result << std::endl;
		std::cout << "Result:   MMMMCCLXIX" << std::endl;
	}

	return 0;
}
