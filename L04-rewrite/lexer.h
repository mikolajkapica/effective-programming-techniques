#pragma once

#include "errors.h"
#include "token.h"
#include "utilities.h"

#include <vector>
#include <string>
#include <utility>
#include <regex>

template <typename T>
std::pair<MyError, std::vector<Token<T>*>> vecTokenize(std::string s_input) {
	std::vector<Token<T>*> vec_tokens;
	std::vector<std::string> s_words = vecSplit(s_input, " ");
	for (std::string s_word : s_words) {
		std::pair<MyError, Token<T>*> p_token = pStringToToken<T>(s_word);
		if (p_token.first.isError()) {
			return std::make_pair(p_token.first.addMsg(" " + s_word + ": "), vec_tokens);
		}
		vec_tokens.push_back(p_token.second);
	}
	return std::make_pair(MyError(EError::NO_ERROR), vec_tokens);
}

