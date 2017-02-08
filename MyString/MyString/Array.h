#pragma once
namespace MyLib {

	template<class Telement>
	class Array
	{
	public:
		Array() : arr(NULL), length(0) {}
		Array(Telement* arr, int length) : arr(arr), length(length) {}
		~Array() { delete[] arr; }

		const int get_length() const { return length; }
		const int count() const { return length; }
		const int size() const { return length; }

		Telement* begin() { return arr; }
		Telement* end() { return arr + length; }

		const Telement& operator[](const int index) const { return arr[index]; }
		Telement& operator[] (const int index) { return arr[index]; }

	private:
		Telement* arr;
		int length;
	};

}