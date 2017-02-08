#include "String.h"
#include <algorithm>

namespace MyLib {

	String::String(const char * string)
		:String(new string_value(string))
	{
	}

	String::String(String & string)
	{
		*this = string;
	}
	String::String(const String & string)
	{
		*this = string;
	}
	String::String(string_value * string)
	{
		set_string(string);
	}

	String::~String()
	{
	}

	String & String::operator=(String & rstr)
	{
		this->string = rstr.get_string();
		str_sum.clear();
		return *this;
	}

	String & String::operator=(const String & rstr)
	{
		this->string = rstr.string;
		this->str_sum = rstr.str_sum;
		return *this;
	}

	String& String::operator+=(const String & rstr)
	{
		this->str_sum.push_back(rstr.string);
		for each (auto str in rstr.str_sum)
		{
			this->str_sum.push_back(str);
		}
		return *this;
	}

	String & String::operator+=(const char * rstr)
	{
		this->str_sum.push_back(shared_ptr<string_value>(new string_value(rstr)));
		return *this;
	}

	String & String::operator*=(int value)
	{
		auto old = get_string().get();

		int old_len = old->get_length();

		string_value* result = new string_value(old_len * value);

		int str_pos = 0;

		for (int i = 0; i < value; ++i, str_pos += old_len)
		{
			old->CopyTo(*result, str_pos);
		}

		set_string(result);

		return *this;
	}

	const char String::operator[](int index) const
	{
		int size = string->size();
		if (index > size)
		{
			index -= size;
		}
		else
			return (*string)[index];

		for each (auto s in str_sum)
		{
			size = s->size();
			if (index > size)
				index -= size;
			else
				return (*s)[index];
		}
	}

	String & String::ToLower()
	{
		get_string()->ToLower();
		return *this;
	}

	String & String::ToUpper()
	{
		get_string()->ToUpper();
		return *this;
	}

	const int String::size() const
	{
		int length = this->string->get_length();
		for each (auto str in this->str_sum)
		{
			length += str->get_length();
		}
		return length;
	}

	const bool String::operator<(String & rstr)
	{
		return strcmp(*this, rstr) < 0;
	}

	const bool String::operator>(String & rstr)
	{
		return strcmp(*this, rstr) > 0;
	}

	shared_ptr<string_value> String::get_string()
	{
		rebuild_string();
		return this->string;
	}

	void String::rebuild_string()
	{
		if (str_sum.empty() && string.use_count() == 1)
			return;
		set_string(build_string());
	}

	void String::set_string(string_value * string)
	{
		this->string.reset(string);
		this->str_sum.clear();
	}

	string_value* String::build_string()
	{
		int length = size();
		string_value* result = new string_value(length);

		this->string->CopyTo(*result, 0);

		int str_pos = this->string->get_length();
		for each (auto str in this->str_sum)
		{
			str->CopyTo(*result, str_pos);
			str_pos += str->get_length();
		}

		return result;
	}

	String operator+(const String & lstr, const String & rstr)
	{
		String result = lstr;
		return result += rstr;
	}
	String operator+(const String & lstr, const char * rstr)
	{
		return String(lstr) += rstr;
	}
	String operator+(const char * lstr, const String & rstr)
	{
		return String(lstr) += rstr;
	}
	String operator*(const String & str, int value)
	{
		return String(str) *= value;
	}

	int strcmp(String &lstr, String &rstr)
	{
		return std::strcmp(lstr.get_string()->get_chars(), rstr.get_string()->get_chars());
	}
	ostream & operator<<(ostream & cout, const String & string)
	{
		for each (auto c in string)
		{
			cout << c;
		}
		return cout;
	}
}