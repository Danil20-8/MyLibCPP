#pragma once
#include "String.h"
#include "Random.h"
#include "Array.h"
namespace MyLib {

	typedef Range<char> CharRange;
	typedef Array<char> CharArray;
	class StringGenerator
	{
	public:
		StringGenerator();
		~StringGenerator();

		String get_string(CharRange range, Range<int> length_range);
		String get_string(CharArray &arr, Range<int> length_range);

		template<class CharSource>
		String get_string(const CharSource &source, Range<int> length_range)
		{
			int length = random.get_value(length_range);

			return get_string(source, length);
		}

		template<class CharSource>
		String get_string(const CharSource &source, int length)
		{
			string_value* sv = new string_value(length);
			auto sv_i = sv->begin();
			for (int i = 0; i < length; ++i, ++sv_i)
				*sv_i = random.get_value<CharSource, char>(source);

			return String(sv);
		}

		template<class Tcollection, class CharSource, class string_length_source, class string_amount_source>
		void fill_collection(Tcollection & col, CharSource &source, const string_length_source & string_length, const string_amount_source & string_amount)
		{
			int amount = random.get_value(string_amount);

			for (int i = 0; i < amount; ++i)
				col.push_back(get_string(source, string_length));
		}
	private:
		Random random;
	};

}