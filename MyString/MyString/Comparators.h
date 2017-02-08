#pragma once

namespace MyLib {

	template<class TOrderIterator, class TLeftIterator, class TRightIterator>
	int compare_o(TOrderIterator ob, TOrderIterator oe, TLeftIterator lb, TLeftIterator le, TRightIterator rb, TRightIterator re);

	template<class TOrderIterator, class Tvalue>
	int compare_o(TOrderIterator ob, TOrderIterator oe, const Tvalue & lv, const Tvalue & rv);

	template<class TLeftIterator, class TRightIterator>
	int compare(TLeftIterator lb, TLeftIterator le, TRightIterator rb, TRightIterator re);

	template<class TLeftIterator, class TRightIterator, class TSelectFunc>
	int compare(TLeftIterator lb, TLeftIterator le, TRightIterator rb, TRightIterator re, const TSelectFunc & selector);

	template<class Tvalue>
	inline int compare(const Tvalue & lv, const Tvalue &rv);

	template<class Tcomparer>
	class LessThanComparator
	{
	public:

		LessThanComparator(const Tcomparer* comparer) : comparer(comparer) {}

		template<class TLeftCollection, class TRightCollection>
		bool operator () (const TLeftCollection & lcol, const TRightCollection & rcol)
		{
			return comparer->Compare(lcol, rcol) < 0;
		}
		template<class Tvalue>
		bool operator () (const Tvalue & lv, const Tvalue & rv)
		{
			return comparer->Compare(lv, rv) < 0;
		}
	private:
		const Tcomparer* comparer;
	};

	template<class Tcomparer>
	class GreaterThanComparator
	{
	public:

		GreaterThanComparator(const Tcomparer* comparer) : comparer(comparer) {}

		template<class TLeftCollection, class TRightCollection>
		bool operator () (const TLeftCollection & lcol, const TRightCollection & rcol)
		{
			return comparer->Compare(lcol, rcol) > 0;
		}
		template<class Tvalue>
		bool operator () (const Tvalue & lv, const Tvalue & rv)
		{
			return comparer->Compare(lv, rv) > 0;
		}
	private:
		const Tcomparer* comparer;
	};

	template<class TOrderIterator, class TLeftIterator, class TRightIterator>
	int compare_o(TOrderIterator ob, TOrderIterator oe, TLeftIterator lb, TLeftIterator le, TRightIterator rb, TRightIterator re)
	{
		for (;; ++lb, ++rb)
		{
			if (lb == le && rb == re)
				return 0;
			else if (lb == le)
				return 1;
			else if (rb == re)
				return -1;

			int cmp_result = compare_o(ob, oe, *lb, *rb);  //if li and ri has same types it always invokes compare for values, even if values are collections
														// at least I tried
			if (cmp_result != 0) return cmp_result;
		}
	}

	template<class TOrderIterator, class Tvalue>
	int compare_o(TOrderIterator ob, TOrderIterator oe, const Tvalue & lv, const Tvalue & rv)
	{
		if (lv == rv) return 0;
		for (; ob != oe; ++ob)
		{
			if (lv == *ob)
				return -1;  //left is less than rigth
			if (rv == *ob)
				return 1;  //rigth is less than left
		}
	}

	template<class TLeftIterator, class TRightIterator>
	int compare(TLeftIterator lb, TLeftIterator le, TRightIterator rb, TRightIterator re)
	{
		for (;; ++lb, ++rb)
		{
			if (lb == le && rb == re)
				return 0;
			else if (lb == le)
				return 1;
			else if (rb == re)
				return -1;

			int cmp_result = compare(*lb, *rb);

			if (cmp_result != 0) return cmp_result;
		}
	}
	template<class TLeftIterator, class TRightIterator, class TSelectFunc>
	int compare(TLeftIterator lb, TLeftIterator le, TRightIterator rb, TRightIterator re, const TSelectFunc & selector)
	{
		for (;; ++lb, ++rb)
		{
			if (lb == le && rb == re)
				return 0;
			else if (lb == le)
				return 1;
			else if (rb == re)
				return -1;

			auto lv = selector(*lb);
			auto rv = selector(*rb);

			int cmp_result = compare(lv, rv);

			if (cmp_result != 0) return cmp_result;
		}
	}
	template<class Tvalue>
	inline int compare(const Tvalue & lv, const Tvalue & rv)
	{
		return lv == rv ? 0 : (lv < rv ? -1 : 1);
	}
}