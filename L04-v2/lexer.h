#pragma once

#include "errors.h"
#include "token.h"
#include "utilities.h"

#include <vector>
#include <tuple>
#include <string>
#include <utility>
#include <regex>

template <typename T>
class Lexer {
public:
	std::tuple<MyError, std::vector<Token<T>*>, std::vector<std::string>> vecTokenize(std::string s_input);

};

template <typename T>
std::tuple<MyError, std::vector<Token<T>*>, std::vector<std::string>> Lexer<T>::vecTokenize(std::string s_input) {
	std::vector<Token<T>*> vec_tokens;
	std::vector<std::string> vec_variables;
	std::vector<std::string> s_words = vecWords(s_input, " ");
	MyError e_error;
	for (std::string s_word : s_words) {
		std::pair<MyError, Token<T>*> p_token = pStringToToken<T>(s_word);

		if (p_token.first.bHasErrors()) {
			return std::make_tuple(p_token.first, vec_tokens, vec_variables);
		}

		if (p_token.first.bHasWarnings()) {
			if (p_token.first.cGetLastWarningType() == EWarning::VARIABLE_HAD_TO_BE_FIXED) {
				e_error += p_token.first.cReplaceLastWarningMessage("Value of [" + s_word + "] had to be fixed to [" + p_token.second->sGetLexeme() + "]");
			}
		}

		if (p_token.second->eGetTokenType() == ETokenType::VARIABLE) {
			vec_variables.push_back(p_token.second->sGetLexeme());
		}

		vec_tokens.push_back(p_token.second);
	}
	return std::make_tuple(e_error, vec_tokens, vec_variables);
}

