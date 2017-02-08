#pragma once
#include <algorithm>
namespace MyLib {

	class string_value
	{
	public:
		const char* get_chars() const { return string; }
		const int get_length() const { return length; }

		string_value(const char* string)
			: length(strlen(string)), string(new char[length + 1])
		{
			strcpy(this->string, string);
		}

		string_value(int length)
			:length(length), string(new char[length + 1])
		{
			string[length] = '\0';
		}

		template<class Tcollection>
		string_value(const Tcollection & col)
			:string_value(col.size())
		{
			int i = 0;
			for each (char c in col)
			{
				string[i++] = c;
			}
		}

		void ToUpper()
		{
			for (int i = 0; i < length + 1; ++i)
				string[i] = toupper(string[i]);
		}
		void ToLower()
		{
			for (int i = 0; i < length + 1; ++i)
				string[i] = tolower(string[i]);
		}

		void CopyTo(string_value &sv, int start_index)
		{
			auto t_pos = sv.begin() + start_index;
			for (auto s_pos = begin(); s_pos != end() && t_pos != sv.end(); ++s_pos, ++t_pos)
				*t_pos = *s_pos;
		}

		char& operator [](int index) { return string[index]; }
		char operator [](int index) const { return string[index]; }

		int size() { return length; }

		char* begin() { return string; }
		char* end() { return string + length; }

		~string_value()
		{
			delete[] string;
		}
	private:

		string_value() {}

		int length;
		char* string;
	};
}