#pragma once
#include "errors.h"

#include <string>
#include <utility>

// STRING TO TOKEN VALUE
template <typename T>
std::pair<MyError, T> stotv(std::string s_input) {
	throw std::exception("Unknown type");
}

template<>
std::pair<MyError, int> stotv<int>(std::string s_input) {
	try {
		int i_value = std::stoi(s_input);
		return std::make_pair(MyError(), i_value);
	} catch (std::exception e) {
		return std::make_pair(MyError(EError::CANT_CONVERT), 0);
	}
}

template<>
std::pair<MyError, double> stotv<double>(std::string s_input) {
	try {
		double d_value = std::stod(s_input);
		return std::make_pair(MyError(), d_value);
	}
	catch (std::exception e) {
		return std::make_pair(MyError(EError::CANT_CONVERT), 0.0);
	}
}

template<>
std::pair<MyError, std::string> stotv<std::string>(std::string s_input) {
	if (s_input.size() < 2) {
		return std::make_pair(MyError(EError::CANT_CONVERT), "");
	}

	if (s_input[0] == '"' && s_input[s_input.size() - 1] == '"') {
		return std::make_pair(MyError(), s_input.substr(1, s_input.size() - 2));
	}

	return std::make_pair(MyError(EError::CANT_CONVERT), "");
}

template<>
std::pair<MyError, bool> stotv<bool>(std::string s_input) {
	if (s_input == "true") {
		return std::make_pair(MyError(), true);
	} else if (s_input == "false") {
		return std::make_pair(MyError(), false);
	} else {
		return std::make_pair(MyError(EError::CANT_CONVERT), false);
	}
}

// TOKEN VALUE TO STRING
 std::string tvtos(double d_input) {
	return std::to_string(d_input);
}

std::string tvtos(std::string s_input) {
	return s_input;
}

std::string tvtos(int i_input) {
	return std::to_string(i_input);
}

std::string tvtos(bool b_input) {
	return b_input ? "true" : "false";
}
