#include "StringGenerator.h"


namespace MyLib {

	StringGenerator::StringGenerator()
	{
	}


	StringGenerator::~StringGenerator()
	{
	}
	String StringGenerator::get_string(CharRange range, Range<int> length_range)
	{
		int length = random.get_value(length_range) + 1;

		return get_string(range, length);
	}

	String StringGenerator::get_string(CharArray &arr, Range<int> length_range)
	{
		int length = random.get_value(length_range) + 1;

		return get_string(arr, length);
	}
}
