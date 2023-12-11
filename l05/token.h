#pragma once

#include "utilities.h"
#include "errors.h"
#include "string_operations.h"

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
	ETokenType e_token_type;
	T t_value;
	std::string s_lexeme;
	int i_arguments_quantity;
public:
	Token(ETokenType e_token_type, T t_value, std::string s_lexeme) : e_token_type(e_token_type), t_value(t_value), s_lexeme(s_lexeme), i_arguments_quantity(0) {}
	Token(ETokenType e_token_type, T t_value, std::string s_lexeme, int i_arguments_quantity) : e_token_type(e_token_type), t_value(t_value), s_lexeme(s_lexeme), i_arguments_quantity(i_arguments_quantity) {}
	inline ETokenType eGetTokenType() { return e_token_type; }
	inline T tGetValue() { return t_value; }
	inline std::string sGetLexeme() { return s_lexeme; }
	inline int iGetArgumentsQuantity() { return i_arguments_quantity; }
	inline bool operator==(const Token<T> t_other) { return this->e_token_type == t_other.e_token_type && this->t_value == t_other.t_value && this->s_lexeme == t_other.s_lexeme; }
	inline bool operator!=(const Token<T> t_other) { return !(*this == t_other); }
	std::string toString();
};

template <typename T>
std::string Token<T>::toString() {
	std::string s_type;
	switch (e_token_type) {
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
std::pair<MyError, Token<T>*> pStringToValueToken(std::string s_lexeme) {
	std::pair<MyError, T> p_value = stotv<T>(s_lexeme);
	if (!p_value.first.bHasErrors()) {
		return std::make_pair(p_value.first, new Token<T>(ETokenType::CONSTANT, p_value.second, tvtos(p_value.second)));
	}
	return std::make_pair(p_value.first + MyError(EError::INVALID_VALUE), new Token<T>(ETokenType::NONE, T(), ""));
}

template <typename T>
std::pair<MyError, Token<T>*> pStringToOperatorToken(std::string s_lexeme) {
	if (s_lexeme == "+"   || s_lexeme == "-"   || 
		s_lexeme == "*"   || s_lexeme == "/"   ) {
		return std::make_pair(MyError(), new Token<T>(ETokenType::OPERATOR, T(), s_lexeme, 2));
	}
	if (s_lexeme == "sin" || s_lexeme == "cos") {
		return std::make_pair(MyError(), new Token<T>(ETokenType::OPERATOR, T(), s_lexeme, 1));
	}
	return std::make_pair(MyError(EError::INVALID_OPERATOR), new Token<T>(ETokenType::NONE, T(), ""));
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

template <typename T>
std::pair<MyError, Token<T>*> pStringToVariableToken(std::string s_lexeme) {
	if (s_lexeme.size() < 1) {
		return std::make_pair(MyError(EError::INVALID_VARIABLE), new Token<T>(ETokenType::NONE, T(), ""));
	}
	if (!bStringHaveALetter(s_lexeme)) {
		return std::make_pair(MyError(EError::INVALID_VARIABLE), new Token<T>(ETokenType::NONE, T(), ""));
	}
	for (int i = 0; i < s_lexeme.size(); i++) {
		if (!isalpha(s_lexeme[i]) && !isdigit(s_lexeme[i])) {
			return std::make_pair(MyError(EWarning::VARIABLE_HAD_TO_BE_FIXED), new Token<T>(ETokenType::VARIABLE, T(), sGetFixedVariable(s_lexeme)));
		}
	}
	return std::make_pair(MyError(), new Token<T>(ETokenType::VARIABLE, T(), s_lexeme));
}

template <typename T>
std::pair<MyError, Token<T>*> pStringToToken(std::string s_lexeme) {
	std::pair<MyError, Token<T>*> p_value = pStringToValueToken<T>(s_lexeme);
	if (!p_value.first.bHasErrors()) {
		return p_value;
	}
	delete p_value.second;

	std::pair<MyError, Token<T>*> p_operator = pStringToOperatorToken<T>(s_lexeme);
	if (!p_operator.first.bHasErrors()) {
		return p_operator;
	}
	delete p_operator.second;

	std::pair<MyError, Token<T>*> p_variable = pStringToVariableToken<T>(s_lexeme);
	if (!p_variable.first.bHasErrors()) {
		return p_variable;
	}

	if (p_variable.first.bHasWarnings()) {
		return p_variable;
	}

	delete p_variable.second;

	return std::make_pair(MyError(EError::INVALID_TOKEN), new Token<T>(ETokenType::NONE, NULL, s_lexeme));
}
