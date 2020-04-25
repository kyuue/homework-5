#include <iostream>

#include "string.h"

using namespace std;

void func(lib::wstring& str)
{
	lib::wstring create(L"unique ");

	str = move(create);
}

int main()
{
	lib::wstring str(L"boss ");

	func(str);

	str = (str);

	wcout << str + L"100 hp" << endl;

	return 0;
}