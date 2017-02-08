#pragma once
#include "String.h"
#include "t_iterator.h"
namespace MyLib
{

	class LowercaseString
	{
	public:
		template<class Tcollection>
		LowercaseString(const Tcollection & col)
			:string(col)
		{
		}
		LowercaseString(const String & string)
			:string(string)
		{
		}

		class iterator : public t_iterator<String::iterator>
		{
		public:
			iterator(String::iterator it) : t_iterator(it) {}

			const char operator *() const { return tolower(*ti); }
		};

		int size() const { return string.size(); }

		iterator begin() const { return iterator(string.begin()); }
		iterator end() const { return iterator(string.end()); }

	private:
		String string;
	};


	class UppercaseString
	{
	public:
		template<class Tcollection>
		UppercaseString(const Tcollection & col)
			:string(col)
		{
		}
		UppercaseString(const String & string)
			:string(string)
		{
		}

		class iterator : public t_iterator<String::iterator>
		{
		public:
			iterator(String::iterator it) : t_iterator(it) {}

			const char operator *() const { return toupper(*ti); }
		};

		int size() const { return string.size(); }

		iterator begin() const { return iterator(string.begin()); }
		iterator end() const { return iterator(string.end()); }

	private:
		String string;
	};
}