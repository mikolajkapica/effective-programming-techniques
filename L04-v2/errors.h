#pragma once

#include <string>
#include <iostream>
#include <variant>
#include <vector>


enum class EError {
	INVALID_TOKEN,
	INVALID_VARIABLE,
	INVALID_VALUE,
	INVALID_OPERATOR,
	TREE_INSERT_ERROR,
	PARSING_PROBLEM,
	CANT_CONVERT,
	UNKNOWN_ERROR,
};

enum class EWarning {
	VARIABLE_HAD_TO_BE_FIXED,
	TREE_HAD_TO_BE_FIXED,
};

class MyError {
private:
	std::vector<std::pair<EError, std::string>> vec_errors;
	std::vector<std::pair<EWarning, std::string>> vec_warnings;
public:
	MyError() {}
	MyError(EError e_error) { vec_errors.push_back(std::make_pair(e_error, "")); }
	MyError(EWarning e_warning) { vec_warnings.push_back(std::make_pair(e_warning, "")); }
	MyError(EError e_error, std::string s_msg) { vec_errors.push_back(std::make_pair(e_error, s_msg)); }
	MyError(EWarning e_warning, std::string s_msg) { vec_warnings.push_back(std::make_pair(e_warning, s_msg)); }
	MyError operator+=(MyError e_other);
	MyError operator+(MyError e_other) { return *this += e_other; }
	std::vector<std::pair<EError, std::string>> vecGetErrorsOnly() { return vec_errors; }
	std::vector<std::pair<EWarning, std::string>> vecGetWarningsOnly() { return vec_warnings; }
	std::pair<EError, std::string> cGetLastError() { return vec_errors[vec_errors.size() - 1]; }
	std::pair<EWarning, std::string> cGetLastWarning() { return vec_warnings[vec_warnings.size() - 1]; }
	EError cGetLastErrorType() { return vec_errors[vec_errors.size() - 1].first; }
	EWarning cGetLastWarningType() { return vec_warnings[vec_warnings.size() - 1].first; }
	bool bHasErrors() { return vec_errors.size() > 0; }
	bool bHasWarnings() { return vec_warnings.size() > 0; }
	bool bHasErrorsOrWarnings() { return bHasErrors() || bHasWarnings(); }
	MyError cReplaceLastErrorMessage(std::string s_msg);
	MyError cReplaceLastWarningMessage(std::string s_msg);
	std::string toString();
};

MyError MyError::operator+=(MyError e_other) {
	for (int i = 0; i < e_other.vec_errors.size(); i++) {
		this->vec_errors.push_back(e_other.vec_errors[i]);
	}

	for (int i = 0; i < e_other.vec_warnings.size(); i++) {
		this->vec_warnings.push_back(e_other.vec_warnings[i]);
	}

	return *this;
}

MyError MyError::cReplaceLastErrorMessage(std::string s_msg) {
	vec_errors[vec_errors.size() - 1].second = s_msg;
	return *this;
}

MyError MyError::cReplaceLastWarningMessage(std::string s_msg) {
	vec_warnings[vec_warnings.size() - 1].second = s_msg;
	return *this;
}

std::string MyError::toString() {
	std::string s_error_msg;
	for (int i = 0; i < this->vec_errors.size(); i++) {
		std::variant<EError, EWarning> e_error = vec_errors[i].first;
		std::string s_msg = vec_errors[i].second;

		s_error_msg += "Error: ";

		switch (std::get<0>(e_error)) {
		case EError::INVALID_TOKEN:
			s_error_msg += "Invalid token";
			break;
		case EError::INVALID_VARIABLE:
			s_error_msg += "Invalid variable";
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
		case EError::CANT_CONVERT:
			s_error_msg += "Can't convert";
			break;
		case EError::UNKNOWN_ERROR:
			s_error_msg += "Unknown error";
			break;
		}

		s_error_msg += " ";
		if (s_msg != "") {
			s_error_msg += "- " + s_msg;
		}

		if (i != vec_errors.size() - 1) {
			s_error_msg += "\n";
		}
	}

	if (this->vec_errors.size() != 0 && this->vec_warnings.size() != 0) {
		s_error_msg += "\n";
	}

	for (int i = 0; i < this->vec_warnings.size(); i++) {
		std::string s_msg = vec_warnings[i].second;

		s_error_msg += "Warning: ";

		switch (vec_warnings[i].first) {
		case EWarning::VARIABLE_HAD_TO_BE_FIXED:
			s_error_msg += "Variable had to be fixed";
			break;
		case EWarning::TREE_HAD_TO_BE_FIXED:
			s_error_msg += "Tree had to be fixed";
			break;
		}

		s_error_msg += " ";
		if (s_msg != "") {
			s_error_msg += "- " + s_msg;
		}

		if (i != vec_warnings.size() - 1) {
			s_error_msg += "\n";
		}
	}

	return s_error_msg;
}

