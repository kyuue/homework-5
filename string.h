#pragma once

//#define DEBUG

#include <iostream>

#include <wchar.h>


namespace lib
{
	class wstring 
	{
	public:
		wstring();

		wstring(const wchar_t* str);

		wstring(const wstring&);

		wstring(const wstring&&);

		~wstring();
	
		int length() const;
	
		wchar_t*& get();

		wchar_t *& get() const;

		lib::wstring& operator=(const lib::wstring& other);

		lib::wstring& operator=(const lib::wstring&& other);

		lib::wstring operator+(const lib::wstring& other);

		lib::wstring& operator+=(const lib::wstring& other);

		// friend funcs

		friend std::wostream& operator<<(std::wostream& o, const wstring& str);

		friend std::wistream& operator>>(std::wistream& i, wstring& str);

		//
	private:
		int len;
		wchar_t* strArr;
		
	};
}
