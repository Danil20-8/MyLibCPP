#pragma once
#include "Comparators.h"

namespace MyLib {

	template<class Tletter>
	class Primer
	{
	public:
		template<class Tcollection>
		Primer(const Tcollection &col)
			: length(col.size()), primer(0)
		{
			primer = new Tletter[length];
			int i = 0;
			for each (Tletter letter in col)
			{
				primer[i++] = letter;
			}
		}
		~Primer() {
			delete[] primer;
		}

		template<class TLeftCollection, class TRightCollection>
		int Compare(const TLeftCollection & lcol, const TRightCollection & rcol) const
		{
			return compare_o(begin(), end(), lcol.begin(), lcol.end(), rcol.begin(), rcol.end());
		}

		int Compare(const Tletter & lv, const Tletter & rv) const
		{
			return compare_o(begin(), end(), lv, rv);
		}

		const Tletter& operator[] (const int index) const { return primer[index]; }
		
		const int size() const { return length; }

		const Tletter* begin() const { return primer; }
		const Tletter* end() const { return primer + length; }

	private:
		Primer() {  }

		Tletter* primer;
		int length;
	};

}

