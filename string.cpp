#include "string.h"

#include <exception>

#include <string>

#include <sstream>

lib::wstring::wstring()
{
#ifdef DEBUG
	std::cout << "DEFAULT CONSTRUCTOR" << std::endl;
#endif

	this->len = 0;

	this->strArr = nullptr;
}

lib::wstring::wstring(const wchar_t* str)
{
#ifdef DEBUG
	std::cout << "CONVERSION CONSTRUCTOR" << std::endl;
#endif
	this->len = wcslen(str);

	this->strArr = new wchar_t[this->len + 1];

	memcpy(this->strArr, str, (this->len + 1) * sizeof(wchar_t));
}

lib::wstring::wstring(const wstring & other)
{
#ifdef DEBUG
	std::cout << "COPY CONSTRUCTOR" << std::endl;
#endif

	*this = other;
}

lib::wstring::wstring(const wstring && other)
{
#ifdef DEBUG
	std::cout << "MOVE CONSTRUCTOR" << std::endl;
#endif
	
	*this = std::move(other);
}

lib::wstring::~wstring()
{
#ifdef DEBUG
	std::cout << "DESTRUCTOR" << std::endl;
#endif
	this->len = 0;

	delete[] strArr;

	strArr = nullptr;
}


int lib::wstring::length() const
{
	return len;
}

wchar_t*& lib::wstring::get()
{
	return strArr;
}

wchar_t*& lib::wstring::get() const
{
	return (wchar_t*&)strArr;
}

lib::wstring & lib::wstring::operator=(const lib::wstring & other)
{
#ifdef DEBUG
	std::cout << "COPY OPERATOR=" << std::endl;
#endif

	if (this->strArr == other.strArr)
		return *this;

	this->~wstring();

	this->len = other.length();

	this->get() = new wchar_t[this->len + 1];

	memcpy(this->strArr, other.get(), sizeof(wchar_t) * (this->len + 1));

	return *this;
}

lib::wstring & lib::wstring::operator=(const lib::wstring && other)
{
#ifdef DEBUG
	std::cout << "MOVE OPERATOR=" << std::endl;
#endif

	if (this->strArr == other.strArr)
		return *this;

	this->~wstring();

	this->len = other.length();

	this->strArr = other.get();

	other.get() = nullptr; // prevent other's destructor to destroy array

	return *this;
}

lib::wstring lib::wstring::operator+(const lib::wstring & other)
{
	int newLength = this->len + other.len;

	auto newPtr = new wchar_t[newLength + 1];

	wcscpy(newPtr, this->strArr);

	wcscat(newPtr, other.strArr);

	return { newPtr };
}

lib::wstring & lib::wstring::operator+=(const lib::wstring & other)
{
	auto temp = std::move(*this + other);

	this->~wstring(); // prevent memory leak

	*this = std::move(temp);

	return *this;
}

std::wostream & lib::operator<<(std::wostream & o, const wstring & str)
{
	if (str.len <= 0)
		return o;

	o << str.get();

	return o;
}

std::wistream & lib::operator>>(std::wistream & i, wstring & str)
{
	str.~wstring();
	
	wchar_t*& ptr = str.get();

	ptr = new wchar_t[lib::wstring::MAX_SIZE]; // hard coded, 

	std::wcin >> ptr;

	str.len = wcslen(ptr);

	return i;
}
