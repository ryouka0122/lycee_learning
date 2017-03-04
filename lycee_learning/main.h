#ifndef __MAIN_HEADER__
#define __MAIN_HEADER__

#include <Windows.h>

#include <iostream>
#include <fstream>

#include <deque>
#include <map>

#include <cmath>
#include <ctime>

#include <string>
#include <sstream>

#if defined(UNICODE) || defined(_UNICODE)
	typedef wchar_t tchar;
	typedef std::basic_string<wchar_t> tstring;
	typedef std::basic_stringstream<wchar_t> tstringstream;
#else
	typedef char tchar;
	typedef std::basic_string<char> tstring;
	typedef std::basic_stringstream<char> tstringstream;
#endif


#endif	// __MAIN_HEADER__
