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

static constexpr uint64_t getDecimalEquivelant(char chr)
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

static constexpr char getRomanEquivelant(uint64_t num)
{
	switch(num)
	{
		case 1U: return 'I';
		case 5U: return 'V';
		case 10U: return 'X';
		case 50U: return 'L';
		case 100U: return 'C';
		case 500U: return 'D';
		case 1000U: return 'M';

		default: return '\0';
	}
}

// static constexpr const std::array roman_numerals {'I', 'V', 'X', 'L', 'C', 'D', 'M'};

std::string decimalToRoman(size_t number)
{
	std::string roman_str;
	roman_str.resize(16ULL);

	// Fill the start with the appropriate number of M's
	if(number >= 1000ULL)
	{
		memset(roman_str.data(), 'M', number / 1000ULL);
		number -= (number / 1000ULL) * 1000ULL;	   // Remove the thousands digit
		std::cout << number << std::endl;
	}

	// For some reason I decided to just say number -= 500, I mean it won't have 2 500's that's a
	// thousand, but it will be consistent with others and can be recursed
	if(number >= 500ULL)
	{
		const size_t ratio = number / 500ULL;
		for(size_t i = 0ULL; i < ratio; ++i)
			roman_str += 'D';
		number -= 500ULL;
		std::cout << number << std::endl;
	}

	// These ifs call for recursion with the 1000 | 100 passed in
	if(number >= 100ULL)
	{
		// Keep a count here cus 400 == CD
		const size_t ratio = number / 100ULL;
		for(size_t i = 0ULL; i < ratio; ++i)
			roman_str += 'C';
		number -= (number / 100ULL) * 100ULL;
		std::cout << number << std::endl;
	}

	if(number >= 50ULL)
	{
		const size_t ratio = number / 50ULL;
		for(size_t i = 0ULL; i < ratio; ++i)
			roman_str += 'L';
		number -= (number / 50ULL) * 50ULL;
		std::cout << number << std::endl;
	}

	if(number >= 10ULL)
	{
		const size_t ratio = number / 10ULL;
		for(size_t i = 0ULL; i < ratio; ++i)
			roman_str += 'X';
		number -= (number / 10ULL) * 10ULL;
		std::cout << number << std::endl;
	}

	if(number >= 5ULL)
	{
		const size_t ratio = number / 5ULL;
		for(size_t i = 0ULL; i < ratio; ++i)
			roman_str += 'V';
		number -= (number / 5ULL) * 5ULL;
		std::cout << number << std::endl;
	}

	if(number >= 1ULL)
	{
		const size_t ratio = number / 1ULL;
		for(size_t i = 0ULL; i < ratio; ++i)
			roman_str += 'I';
		number -= (number / 1ULL) * 1ULL;
		std::cout << number << std::endl;
	}

	// TODO: Later on add more restrictions to the ranges, like 50 < x < 80 cause 90 would be XC and
	// not LXXXX

	return roman_str;
}

uint64_t romanToDecimal(std::string_view str)
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
		//		std::string result = decimalToRoman(static_cast<size_t>(std::atoll(argv[i])));
		uint64_t result = romanToDecimal(argv[i]);
		std::cout << "My Guess: " << result << std::endl;
		std::cout << "Result:   4269" << std::endl;
	}

	return 0;
}
