#include <array>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

constexpr const std::array decimals {
	1000ULL, 900ULL, 500ULL, 400ULL, 100ULL, 90ULL, 50ULL, 40ULL, 10ULL, 9ULL, 5ULL, 4ULL, 1ULL};

constexpr const std::array conversion_letters {
	"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

constexpr const std::array letters {'I', 'V', 'X', 'L', 'C', 'D', 'M'};

bool isDecimal(const char* str)
{
	while(*str != '\0')
		if(!isdigit(*str++))
			return false;
	return true;
}

bool isRomanCharacter(char chr)
{
	return (std::find(letters.begin(), letters.end(), chr) != letters.end());
}

bool isRoman(const char* str)
{
	while(*str != '\0')
		if(!isRomanCharacter(*(str++)))
			return false;
	return true;
}

constexpr uint64_t getDecimalEquivelant(const char chr)
{
	switch(chr)
	{
		case 'I': return decimals[12];
		case 'V': return decimals[10];
		case 'X': return decimals[8];
		case 'L': return decimals[6];
		case 'C': return decimals[4];
		case 'D': return decimals[2];
		case 'M': return decimals[0];

		default: return 0ULL;
	}
}

// Just make a constexpr char* version of this
std::string decimalToRoman(size_t number)
{
	std::string roman_str;
	roman_str.resize(16ULL);

	size_t i = 0ULL;
	while(number > 0ULL)
	{
		size_t div = number / decimals[i];
		number %= decimals[i];

		while(div--)
			roman_str.append(conversion_letters[i]);

		++i;
	}

	return roman_str;
}

constexpr size_t len(const char* str)
{
	size_t length = 0ULL;
	while(*(str++) != '\0')
		++length;

	return length;
}

constexpr uint64_t romanToDecimal(const char* str)
{
	uint64_t result = 0ULL;

	for(size_t i = 0ULL; i < len(str); ++i)
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

// FIXME: 99 is CXIX instead of IC

int main(int argc, char** argv)
{
	// Check if no arguments, go into REPL
	// Cannot accept multiple space/tab seperated numbers, only newlines
	if(argc == 1)
	{
		char* input = nullptr;
		size_t length = 0ULL;
		ssize_t read_size = 0LL;
		std::cout << "> ";
		while((read_size = getline(&input, &length, stdin)) != -1)
		{
			// Remove the last character which is a newline
			input[--read_size] = '\0';

			if(isDecimal(input))
			{
				std::string result = decimalToRoman(static_cast<size_t>(std::atoll(input)));
				std::cout << result << std::endl;
			}
			else if(isRoman(input))
			{
				size_t result = romanToDecimal(input);
				std::cout << result << std::endl;
			}
			else
				std::cerr << "Couldn't recognize number" << std::endl;

			std::cout << "> ";
		}

		free(input);
		std::cout << std::endl;
		return 0;
	}

	// Non REPL, from argv
	for(uint8_t i = 1U; i < static_cast<uint8_t>(argc); ++i)
	{
		if(isDecimal(argv[i]))
		{
			std::string result = decimalToRoman(static_cast<size_t>(std::atoll(argv[i])));
			std::cout << argv[i] << " is " << result << std::endl;
		}
		else if(isRoman(argv[i]))
		{
			size_t result = romanToDecimal(argv[i]);
			std::cout << argv[i] << " is " << result << std::endl;
		}
		else
			std::cerr << "Couldn't recognize number" << std::endl;
	}

	return 0;
}
