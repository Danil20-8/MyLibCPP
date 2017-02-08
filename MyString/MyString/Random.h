#pragma once
#include <random>
#include "Array.h"
namespace MyLib {

	template<class Tvalue>
	struct Range
	{
		Tvalue min;
		Tvalue max;

		inline Tvalue get_len() const { return max - min; }
		inline float get_magnitude() const { return static_cast<float>(max - min); }
		inline int size() const { return get_magnitude(); }

		Range(Tvalue min, Tvalue max)
			:min(min), max(max)
		{
		}

		explicit Range(Tvalue length)
			:min(0), max(length)
		{
		}

		Tvalue operator [] (int index) const { float len = get_magnitude(); return min * ((len - index) / len) + max * (index / len); }
	};

	class Random
	{
	public:
		Random();
		~Random();

		template<class Tvalue>
		Tvalue get_value(const Tvalue &min, const Tvalue &max)
		{
			return rd() % (max - min) + min;
		}
		template<class Tvalue>
		Tvalue get_value(const Tvalue &max)
		{
			return rd() % max;
		}
		template<class Tvalue>
		Tvalue get_value(const Range<Tvalue> &range)
		{
			return range[get_value(range.size())];
		}

		template<class Tvalue>
		const Tvalue &get_value(const Array<Tvalue> & arr)
		{
			return arr[get_value(arr.size())];
		}

		template<class Tcollection, class Tvalue>			// :/
		const Tvalue& get_value(const Tcollection &coll)
		{
			return coll[get_value(coll.size())];
		}

	private:
		std::random_device rd;

	};

}