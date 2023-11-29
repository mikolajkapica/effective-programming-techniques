#pragma once

#include <string>
#include <vector>

std::vector<std::string> vecSplit(std::string s_input, std::string s_delim) {
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

bool bStringHaveALetter(std::string s_input) {
	for (char c : s_input) {
		if (isalpha(c)) {
			return true;
		}
	}
	return false;
}
