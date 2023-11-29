#pragma once

#include <string>

enum class EError {
	NO_ERROR,
	INVALID_TOKEN,
	INVALID_VARIABLE,
	INVALID_VALUE,
	INVALID_OPERATOR,
	VARIABLE_HAS_TO_BE_FIXED,
	TREE_INSERT_ERROR,
	PARSING_PROBLEM,
};

class MyError {
private:
	EError e_error;
	std::string s_msg;
public:
	MyError(EError error) : e_error(error), s_msg("") {}
	EError getError() const { return e_error; }
	bool isError() const { return e_error != EError::NO_ERROR; }
	std::string toString();
	MyError addMsg(std::string msg) { s_msg += msg; return *this; }
	bool operator==(const MyError& error) const { return e_error == error.e_error && s_msg == error.s_msg; }
};

std::string MyError::toString() {
	std::string s_error_msg = "Error: ";
	s_error_msg += this->s_msg;
	switch (e_error) {
	case EError::NO_ERROR:
		s_error_msg += "No error";
		break;
	case EError::INVALID_TOKEN:
		s_error_msg += "Invalid token";
		break;
	case EError::INVALID_VARIABLE:
		s_error_msg += "Invalid variable";
		break;
	case EError::VARIABLE_HAS_TO_BE_FIXED:
		s_error_msg += "Variable has to be fixed";
		break;
	case EError::INVALID_VALUE:
		s_error_msg += "Invalid value";
		break;
	case EError::INVALID_OPERATOR:
		s_error_msg += "Invalid operator";
		break;
	case EError::TREE_INSERT_ERROR:
		s_error_msg += "Tree insert error";
		break;
	case EError::PARSING_PROBLEM:
		s_error_msg += "Parsing problem";
		break;
	default:
		s_error_msg += "Unknown error";
	}
	return s_error_msg;
}

