#pragma once

#include <string>
#include <vector>

std::vector<std::string> vecWords(std::string s_input, std::string s_delim) {
	std::vector<std::string> vec_words;
	std::string s_word;
	for (char c : s_input) {
		if (s_delim.find(c) != std::string::npos) {
			if (!s_word.empty()) {
				vec_words.push_back(s_word);
				s_word.clear();
			}
		} else {
			s_word += c;
		}
	}
	if (!s_word.empty()) {
		vec_words.push_back(s_word);
	}
	return vec_words;
}

std::string sUnwords(std::vector<std::string> vec_words) {
	std::string s_output;
	for (std::string s_word : vec_words) {
		s_output += s_word + " ";
	}
	if (!s_output.empty()) {
		s_output.pop_back();
	}
	return s_output;
}

template<typename T>
std::vector<T> vecSubVector(std::vector<T> vec_input, size_t i_start, size_t i_end) {
	std::vector<T> vec_output;
	if (i_start < 0) {
		i_start = 0;
	}
	if (i_end > vec_input.size()) {
		i_end = vec_input.size();
	}
	for (size_t i = i_start; i < i_end; i++) {
		vec_output.push_back(vec_input[i]);
	}
	return vec_output;
}

bool bStringHaveALetter(std::string s_input) {
	for (char c : s_input) {
		if (isalpha(c)) {
			return true;
		}
	}
	return false;
}
