#pragma once

namespace MyLib
{
	template<class Titerator>
	class t_iterator
	{
	public:
		t_iterator & operator ++() { ++ti; return *this; }
		t_iterator operator ++(int) { ti++; return *this; }

		const bool operator == (const t_iterator & it) const { return ti == it.ti; }
		const bool operator != (const t_iterator & it) const { return ti != it.ti; }

	protected:
		t_iterator(Titerator it) : ti(it) {}

		Titerator ti;


	};
}