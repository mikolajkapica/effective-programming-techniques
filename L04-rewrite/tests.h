#pragma once
#include "lexer.h"
#include "token.h"
#include "errors.h"
#include "parser.h"

#include <vector>
#include <string>
#include <iostream>
#include <utility>

void testVecTokenizeInt() {
	std::cout << "Testing vecTokenize<int>" << std::endl;

	std::vector<Token<int>> vec_correct_tokens{
		Token<int>(ETokenType::VARIABLE, NULL, "10A"),
		Token<int>(ETokenType::OPERATOR, NULL, "+"),
		Token<int>(ETokenType::CONSTANT, 2, "2"),
		Token<int>(ETokenType::OPERATOR, NULL, "/"),
		Token<int>(ETokenType::CONSTANT, 523, "523"),
		Token<int>(ETokenType::OPERATOR, NULL, "-"),
	};

	std::pair<MyError, std::vector<Token<int>*>> vec_tokens_created = vecTokenize<int>("\"1.0A\" + 2 / 523 -");

	if (vec_tokens_created.first.isError()) {
		std::cout << vec_tokens_created.first.toString() << std::endl;
	}

	for (int i = 0; i < vec_tokens_created.second.size(); i++) {
		if (*vec_tokens_created.second[i] != vec_correct_tokens[i]) {
			std::cout << "Test failed: " << i << std::endl;
			std::cout << "Expected: " << vec_correct_tokens[i].toString() <<  std::endl;
			std::cout << "Got: " << (*vec_tokens_created.second[i]).toString() << std::endl;
			return;
		}
	}
}

void testVecTokenizeDouble() {
	std::cout << "Testing vecTokenize<double>" << std::endl;

	std::vector<Token<double>> vec_correct_tokens{
		Token<double>(ETokenType::CONSTANT, 1, "1.0"),
		Token<double>(ETokenType::OPERATOR, NULL, "+"),
		Token<double>(ETokenType::CONSTANT, 2, "2"),
		Token<double>(ETokenType::OPERATOR, NULL, "/"),
		Token<double>(ETokenType::CONSTANT, 523, "523"),
		Token<double>(ETokenType::OPERATOR, NULL, "-"),
	};

	std::pair<MyError, std::vector<Token<double>*>> vec_tokens_created = vecTokenize<double>("1.0 + 2 / 523 -");

	if (vec_tokens_created.first.isError()) {
		std::cout << vec_tokens_created.first.toString() << std::endl;
	}

	for (int i = 0; i < vec_tokens_created.second.size(); i++) {
		if (*vec_tokens_created.second[i] != vec_correct_tokens[i]) {
			std::cout << "Test failed: " << i << std::endl;
			std::cout << "Expected: " << vec_correct_tokens[i].toString() <<  std::endl;
			std::cout << "Got: " << (*vec_tokens_created.second[i]).toString() << std::endl;
			return;
		}
	}
}

void testVecTokenizeString() {
	std::cout << "Testing vecTokenize<std::string>" << std::endl;

	std::vector<Token<std::string>> vec_correct_tokens{
		Token<std::string>(ETokenType::CONSTANT, "1.0", "\"1.0\""),
		Token<std::string>(ETokenType::OPERATOR, "", "+"),
		Token<std::string>(ETokenType::CONSTANT, "Adam", "\"Adam\""),
		Token<std::string>(ETokenType::OPERATOR, "", "/"),
		Token<std::string>(ETokenType::VARIABLE, "", "var"),
		Token<std::string>(ETokenType::OPERATOR, "", "-"),
	};

	std::pair<MyError, std::vector<Token<std::string>*>> vec_tokens_created = vecTokenize<std::string>("\"1.0\" + \"Adam\" / var - ");

	if (vec_tokens_created.first.isError()) {
		std::cout << vec_tokens_created.first.toString() << std::endl;
	}

	for (int i = 0; i < vec_tokens_created.second.size(); i++) {
		if (*vec_tokens_created.second[i] != vec_correct_tokens[i]) {
			std::cout << "Test failed: " << i << std::endl;
			std::cout << "Expected: " << vec_correct_tokens[i].toString() <<  std::endl;
			std::cout << "Got: " << (*vec_tokens_created.second[i]).toString() << std::endl;
			return;
		}
	}
}

void testParsing() {
	std::cout << "Testing parsing" << std::endl;

	std::vector<Token<double>*> vec_correct_tokens{
		new Token<double>(ETokenType::OPERATOR, 1, "+", 2),
		new Token<double>(ETokenType::CONSTANT, NULL, "1.0"),
		new Token<double>(ETokenType::CONSTANT, 2, "2.0"),
	};

	std::pair<MyError, Tree<double>*> p_tree = pParse<double>(vec_correct_tokens);

	if (p_tree.first.isError()) {
		std::cout << p_tree.first.toString() << std::endl;
	}

	std::cout << p_tree.second->toString() << std::endl;

}

void tests() {
	testVecTokenizeInt();
	testVecTokenizeDouble();
	testVecTokenizeString();
	testParsing();

}



