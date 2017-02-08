#include <conio.h>
#include <iostream>
#include <vector>
#include "StringGenerator.h"
#include "Array.h"
#include "Primer.h"
#include "Comparators.h"
#include <time.h>
#include "CaseString.h"
using namespace MyLib;


// comparing functions
bool less_than(String &lstr, String &rstr);
bool greater_than(String &lstr, String &rstr);

// some helpful functions 

shared_ptr<Primer<char> > get_primer();

template<class Tstr>
void print(Tstr &string);
template<class Titerator>
void print(Titerator begin, Titerator end);

template<class TFunc>
int count_time(TFunc func)
{
	cout << '\n';
	int t = clock();
	func();
	return clock() - t;
}

void main()
{
	// A primer for word generation and for special comparing option
	auto primer = get_primer();

	vector<String> vs;
	StringGenerator sg;
	sg.fill_collection(vs, *primer, Range<int>(5, 50), Range<int>(5, 25));

	print(vs.begin(), vs.end());
	
	print("\n" + (String("/") * 50) + "\n");

	// Each sorting method works. I have found the first implementation is funny.

	sort(vs.begin(), vs.end(), [&primer](String & ls, String & rs) { return primer->Compare(ls, rs) > 0; });
	//sort(vs.begin(), vs.end(), less_than);
	//sort(vs.begin(), vs.end(), greater_than);

	print(vs.begin(), vs.end());

	getch();
}

void generate_random_string(int max_char_amount)
{
	int char_amount = rand() % max_char_amount;
}

bool less_than(String &lstr, String &rstr)
{
	return compare(lstr.begin(), lstr.end(), rstr.begin(), rstr.end(), [](char c) { return tolower(c); }) < 0;
}
bool greater_than(String & lstr, String & rstr)
{
	return compare(lstr.begin(), lstr.end(), rstr.begin(), rstr.end(), [](char c) { return tolower(c); }) > 0;
}

shared_ptr<Primer<char> > get_primer()
{
	//At begin here was vector<char> as a collection, but once I found one more crazy solution
	const String primer(" 0123456789");
	const int size = ('z' - 'a' + 1) * 2 + 1;
	char a[size];
	a[size - 1] = '\0'; //for string concatenation
	int i = 0;
	for (char abc = 'a'; abc <= 'z'; ++abc, i += 2)
	{
		a[i] = abc;
		a[i + 1] = toupper(abc);
	}
	return shared_ptr<Primer<char> >(new Primer<char>(primer + a));
}

template<class Tstr>
void print(Tstr & string)
{
	cout << string << '\n';
}

template<class Titerator>
void print(Titerator begin, Titerator end)
{
	for (; begin != end; ++begin)
		print(*begin);
}
