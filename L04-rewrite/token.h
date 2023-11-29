#pragma once

#include "utilities.h"
#include "errors.h"

#include <iostream>
#include <string>
#include <utility>

enum class ETokenType {
	OPERATOR,
	VARIABLE,
	CONSTANT,
	NONE
};

template <typename T>
class Token {
private:
	ETokenType e_type;
	T t_value;
	std::string s_lexeme;
	int i_arguments_quantity;
public:
	Token(ETokenType e_type, T t_value, std::string s_lexeme) : e_type(e_type), t_value(t_value), s_lexeme(s_lexeme), i_arguments_quantity(0) {}
	Token(ETokenType e_type, T t_value, std::string s_lexeme, int i_arguments_quantity) : e_type(e_type), t_value(t_value), s_lexeme(s_lexeme), i_arguments_quantity(i_arguments_quantity) {}
	inline ETokenType eGetType() { return e_type; }
	inline T tGetValue() { return t_value; }
	inline std::string sGetLexeme() { return s_lexeme; }
	inline int iGetArgumentsQuantity() { return i_arguments_quantity; }
	inline bool operator==(const Token<T> t_other) { return this->e_type == t_other.e_type && this->t_value == t_other.t_value && this->s_lexeme == t_other.s_lexeme; }
	inline bool operator!=(const Token<T> t_other) { return !(*this == t_other); }
	std::string toString();
};

template <typename T>
std::string Token<T>::toString() {
	std::string s_type;
	switch (e_type) {
	case ETokenType::OPERATOR:
		s_type = "OPERATOR";
		break;
	case ETokenType::VARIABLE:
		s_type = "VARIABLE";
		break;
	case ETokenType::CONSTANT:
		s_type = "CONSTANT";
		break;
	}
	return "Token(" + s_type + ", " + s_lexeme + ", " + std::to_string(i_arguments_quantity) + ")";
}

template <typename T>
std::pair<MyError, T> pStringToValue(std::string s_lexeme) {
	return std::make_pair(MyError(EError::INVALID_TOKEN), T());
}

template <>
std::pair<MyError, std::string> pStringToValue<std::string>(std::string s_lexeme) {
	if (s_lexeme.size() < 2) {
		return std::make_pair(MyError(EError::INVALID_TOKEN), "");
	}
	if (s_lexeme[0] == '"' && s_lexeme[s_lexeme.size() - 1] == '"') {
		return std::make_pair(MyError(EError::NO_ERROR), s_lexeme.substr(1, s_lexeme.size() - 2));
	}
	return std::make_pair(MyError(EError::INVALID_VALUE), "");
}

template <>
std::pair<MyError, int> pStringToValue<int>(std::string s_lexeme) {
	int i_value;
	try {
		i_value = std::stoi(s_lexeme);
		return std::make_pair(MyError(EError::NO_ERROR), i_value);
	} catch (...) {
		return std::make_pair(MyError(EError::INVALID_VALUE), 0);
	}
}

template <>
std::pair<MyError, double> pStringToValue<double>(std::string s_lexeme) {
	double d_value;
	try {
		d_value = std::stod(s_lexeme);
		return std::make_pair(MyError(EError::NO_ERROR), d_value);
	} catch (...) {
		return std::make_pair(MyError(EError::INVALID_VALUE), 0.0);
	}
}

std::pair<MyError, std::string> pStringToOperator(std::string s_lexeme) {
	if (s_lexeme == "+"   || 
		s_lexeme == "-"   || 
		s_lexeme == "*"   || 
		s_lexeme == "/"   ||
		s_lexeme == "sin" ||
		s_lexeme == "cos") {
		return std::make_pair(MyError(EError::NO_ERROR), s_lexeme);
	}
	return std::make_pair(MyError(EError::INVALID_OPERATOR), "");
}

std::pair<MyError, std::string> pStringToVariable(std::string s_lexeme) {
	if (s_lexeme.size() < 1) {
		return std::make_pair(MyError(EError::INVALID_VARIABLE), "");
	}
	if (!bStringHaveALetter(s_lexeme)) {
		return std::make_pair(MyError(EError::INVALID_VARIABLE), "");
	}
	for (int i = 0; i < s_lexeme.size(); i++) {
		if (!isalpha(s_lexeme[i]) && !isdigit(s_lexeme[i])) {
			return std::make_pair(MyError(EError::VARIABLE_HAS_TO_BE_FIXED), "");
		}
	}
	return std::make_pair(MyError(EError::NO_ERROR), s_lexeme);
}

std::string sGetFixedVariable(std::string s_lexeme) {
	std::string s_fixed = "";
	for (int i = 0; i < s_lexeme.size(); i++) {
		if (isalpha(s_lexeme[i]) || isdigit(s_lexeme[i])) {
			s_fixed += s_lexeme[i];
		}
	}
	return s_fixed;
}

int iOperatorArgumentsQuantity(std::string s_lexeme) {
	if (s_lexeme == "+" || s_lexeme == "-" || s_lexeme == "*" || s_lexeme == "/") {
		return 2;
	}
	if (s_lexeme == "sin" || s_lexeme == "cos") {
		return 1;
	}
	throw std::exception("Invalid operator, cannot get arguments quantity");
}

template <typename T>
std::pair<MyError, Token<T>*> pStringToToken(std::string s_lexeme) {
	std::pair<MyError, T> p_value = pStringToValue<T>(s_lexeme);
	if (!p_value.first.isError()) {
		return std::make_pair(MyError(EError::NO_ERROR), new Token<T>(ETokenType::CONSTANT, p_value.second, s_lexeme));
	}
	std::pair<MyError, std::string> p_operator = pStringToOperator(s_lexeme);
	if (!p_operator.first.isError()) {
		return std::make_pair(MyError(EError::NO_ERROR), new Token<T>(ETokenType::OPERATOR, T(), p_operator.second, iOperatorArgumentsQuantity(s_lexeme)));
	}
	std::pair<MyError, std::string> p_variable = pStringToVariable(s_lexeme);
	if (!p_variable.first.isError()) {
		return std::make_pair(MyError(EError::NO_ERROR), new Token<T>(ETokenType::VARIABLE, T(), p_variable.second));
	}
	if (p_variable.first == MyError(EError::VARIABLE_HAS_TO_BE_FIXED)) {
		return std::make_pair(MyError(EError::NO_ERROR), new Token<T>(ETokenType::VARIABLE, T(), sGetFixedVariable(s_lexeme)));
	}
	return std::make_pair(MyError(EError::INVALID_TOKEN), new Token<T>(ETokenType::NONE, T(), s_lexeme));
}
