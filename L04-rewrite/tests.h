#pragma once

#include "lexer.h"
#include "token.h"
#include "errors.h"
#include "parser.h"
#include "evaluator.h"

#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <tuple>

void testVecTokenizeInt() {
	Lexer<int> lexer;

	std::cout << "Testing vecTokenize<int>" << std::endl;

	std::vector<Token<int>> vec_correct_tokens{
		Token<int>(ETokenType::VARIABLE, NULL, "10A"),
		Token<int>(ETokenType::OPERATOR, NULL, "+"),
		Token<int>(ETokenType::CONSTANT, 2, "2"),
		Token<int>(ETokenType::OPERATOR, NULL, "/"),
		Token<int>(ETokenType::CONSTANT, 523, "523"),
		Token<int>(ETokenType::OPERATOR, NULL, "-"),
	};

	std::tuple<MyError, std::vector<Token<int>*>, std::vector<std::string>> vec_tokens_created = lexer.vecTokenize("\"1.0A\" + 2 / 523 -");

	if (std::get<0>(vec_tokens_created).bHasErrors()) {
		std::cout << std::get<0>(vec_tokens_created).toString() << std::endl;
	}

	for (int i = 0; i < std::get<1>(vec_tokens_created).size(); i++) {
		if (*std::get<1>(vec_tokens_created)[i] != vec_correct_tokens[i]) {
			std::cout << "Test failed: " << i << std::endl;
			std::cout << "Expected: " << vec_correct_tokens[i].toString() <<  std::endl;
			std::cout << "Got: " << (*std::get<1>(vec_tokens_created)[i]).toString() << std::endl;
			return;
		}
	}
}

void testVecTokenizeDouble() {
	Lexer<double> lexer;

	std::cout << "Testing vecTokenize<double>" << std::endl;

	std::vector<Token<double>> vec_correct_tokens{
		Token<double>(ETokenType::CONSTANT, 1, "1.0"),
		Token<double>(ETokenType::OPERATOR, NULL, "+"),
		Token<double>(ETokenType::CONSTANT, 2, "2"),
		Token<double>(ETokenType::OPERATOR, NULL, "/"),
		Token<double>(ETokenType::CONSTANT, 523, "523"),
		Token<double>(ETokenType::OPERATOR, NULL, "-"),
	};

	std::tuple<MyError, std::vector<Token<double>*>, std::vector<std::string>> vec_tokens_created = lexer.vecTokenize("1.0 + 2 / 523 -");

	if (std::get<0>(vec_tokens_created).bHasErrors()) {
		std::cout << std::get<0>(vec_tokens_created).toString() << std::endl;
	}

	for (int i = 0; i < std::get<1>(vec_tokens_created).size(); i++) {
		if (*std::get<1>(vec_tokens_created)[i] != vec_correct_tokens[i]) {
			std::cout << "Test failed: " << i << std::endl;
			std::cout << "Expected: " << vec_correct_tokens[i].toString() <<  std::endl;
			std::cout << "Got: " << (*std::get<1>(vec_tokens_created)[i]).toString() << std::endl;
			return;
		}
	}
}

void testVecTokenizeString() {
	Lexer<std::string> lexer;

	std::cout << "Testing vecTokenize<std::string>" << std::endl;

	std::vector<Token<std::string>> vec_correct_tokens{
		Token<std::string>(ETokenType::CONSTANT, "1.0", "\"1.0\""),
		Token<std::string>(ETokenType::OPERATOR, "", "+"),
		Token<std::string>(ETokenType::CONSTANT, "Adam", "\"Adam\""),
		Token<std::string>(ETokenType::OPERATOR, "", "/"),
		Token<std::string>(ETokenType::VARIABLE, "", "var"),
		Token<std::string>(ETokenType::OPERATOR, "", "-"),
	};

	std::tuple<MyError, std::vector<Token<std::string>*>, std::vector<std::string>> vec_tokens_created = lexer.vecTokenize("\"1.0\" + \"Adam\" / var - ");

	if (std::get<0>(vec_tokens_created).bHasErrors()) {
		std::cout << std::get<0>(vec_tokens_created).toString() << std::endl;
	}

	for (int i = 0; i < std::get<1>(vec_tokens_created).size(); i++) {
		if (*std::get<1>(vec_tokens_created)[i] != vec_correct_tokens[i]) {
			std::cout << "Test failed: " << i << std::endl;
			std::cout << "Expected: " << vec_correct_tokens[i].toString() <<  std::endl;
			std::cout << "Got: " << (*std::get<1>(vec_tokens_created)[i]).toString() << std::endl;
			return;
		}
	}
}

void testParsing() {
	Parser<double> parser;

	std::cout << "Testing parsing" << std::endl;

	std::vector<Token<double>*> vec_correct_tokens{
		new Token<double>(ETokenType::OPERATOR, 1, "+", 2),
		new Token<double>(ETokenType::CONSTANT, NULL, "1.0"),
		new Token<double>(ETokenType::CONSTANT, 2, "2.0"),
	};

	std::pair<MyError, Tree<double>*> p_tree = parser.pParse(vec_correct_tokens);

	if (p_tree.first.bHasErrors()) {
		std::cout << p_tree.first.toString() << std::endl;
	}

	std::cout << p_tree.second->toString() << std::endl;

}

void testEvaluation() {
	Parser<double> parser;
	Evaluator<double> evaluator;

	std::cout << "Testing evaluation" << std::endl;

	std::vector<Token<double>*> vec_correct_tokens{
		new Token<double>(ETokenType::OPERATOR, NULL, "+", 2),
		new Token<double>(ETokenType::CONSTANT, 1.0, "1.0"),
		new Token<double>(ETokenType::VARIABLE, NULL, "var"),
	};

	std::pair<MyError, Tree<double>*> p_tree = parser.pParse(vec_correct_tokens);

	if (p_tree.first.bHasErrors()) {
		std::cout << p_tree.first.toString() << std::endl;
	}

	std::cout << p_tree.second->toString() << std::endl;


	std::map<std::string, double> map_variables = {
		{"var", 2.0},
	};

	std::cout << "Result: " << evaluator.tEvaluateTree(p_tree.second, map_variables) << std::endl;

}

void newline() { std::cout << std::endl; }

void tests() {
	testVecTokenizeInt();

	newline();
	testVecTokenizeDouble();

	newline();
	testVecTokenizeString();

	newline();
	testParsing();

	newline();
	testEvaluation();

}



