#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include "string_value.h"

namespace MyLib
{
	using namespace std;

	class String
	{
	public:

		class iterator
		{
		public:
			iterator(const String * string)
				:string(string), pos(0), size(string->string->size()), add_index(0), state(Main)
			{

			}

			iterator(const String * string, int pos)
				: string(string), pos(0), size(string->string->size()), add_index(0), state(Main)
			{
				if (size < pos)
				{
					state = Add;
					pos -= size;
					for each (auto str in string->str_sum)
					{
						size = str->size();
						if (pos < size)
							return;
						pos -= size;
						++add_index;
					}
					state = End;
				}
			}

			static iterator end(const String * string) { iterator i(string); i.state = End; return i; }

			iterator & operator ++() {
				if (++pos == size)
				{
					switch (state)
					{
					case Main:
						if (string->str_sum.size() > 0)
						{
							state = Add;
							size = string->str_sum[add_index]->size();
						}
						else
							state = End;
						break;
					case Add:
						if (++add_index == string->str_sum.size())
							state = End;
						else
							size = string->str_sum[add_index]->size();
						break;
					}
					pos = 0;
				}
				return *this;
			}
			iterator operator++(int) { iterator t = iterator(*this); operator++(); return t; }

			const char operator *() const {
				switch (state)
				{
				case Main:
					return string->string->operator[](pos);
				case Add:
					return string->str_sum[add_index]->operator[](pos);
				case End:
					return 0;
				default:
					break;
				}
			}

			bool operator == (const iterator & ri) const { return state == End && ri.state == End ? true : string == ri.string && state == ri.state && pos == ri.pos && add_index == add_index; }
			bool operator != (const iterator & ri) const { return !(*this == ri); }
		private:
			enum State {
				Main,
				Add,
				End
			};

			State state = Main;
			int size;
			int pos;
			int add_index;

			const String* string;
		};

		String(const char* string);
		String(String &string);
		String(const String &string);
		String(string_value* string);
		template<class TCharCollection>
		String(const TCharCollection & col) : String(new string_value(col)) { }
		~String();

		String& operator = (String & rstr);
		String& operator = (const String & rstr);

		String& operator += (const String& rstr);
		String& operator += (const char *rstr);

		String& operator *= (int value);

		const char operator[](int index) const;

		String get_lower() const { return String(*this).ToLower(); }
		String get_upper() const { return String(*this).ToUpper(); }

		String& ToLower();
		String& ToUpper();

		const int size() const;

		String::iterator begin() const { return String::iterator(this); }
		String::iterator end() const { return String::iterator::end(this); }

		const bool operator < (String &rstr);
		const bool operator > (String & rstr);

		friend int strcmp(String &lstr, String &rstr);

	private:
		shared_ptr<string_value> get_string();
		void rebuild_string();
		void set_string(string_value* string);
		string_value* build_string();


		shared_ptr<string_value> string;
		vector<shared_ptr<string_value> > str_sum;
	};
	
	ostream &operator <<(ostream &cout, const String &string);

	String operator +(const String &lstr, const String &rstr);
	String operator +(const String &lstr, const char* rstr);
	String operator +(const char* lstr, const String &rstr);
	String operator *(const String &str, int value);
}