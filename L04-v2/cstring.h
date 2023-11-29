#pragma once;

#include <string>

class CString {
private:
	std::string s_string;
public:
	CString cFromString(std::string s_string);
	std::string toString();
};
