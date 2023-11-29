#pragma once

#include "lexer.h"
#include "parser.h"
#include "evaluator.h"
#include "errors.h"
#include "utilities.h"
#include "token.h"
#include "string_operations.h"

#include <string>
#include <vector>
#include <map>

class REPLBase {
public:
	virtual std::pair<bool, std::string> sRun(std::string s_user_input) = 0;
};

template <typename T>
class REPL : public REPLBase {
private:
	Lexer<T> *pc_lexer;
	Parser<T> *pc_parser;
	Evaluator<T> *pc_evaluator;

	Tree<T> *pc_tree;

	std::vector<std::string> vec_variables;
private:
	std::pair<MyError, Tree<T>*> pEnter(std::string s_input);
	std::string sEnter(std::string s_input);
	std::string sVariables();
	std::string sPrint();
	std::string sComp(std::string s_input);
	std::string sJoin(std::string s_input);
	std::string sExit();
public:
	REPL() : pc_lexer(new Lexer<T>()), pc_parser(new Parser<T>()), pc_evaluator(new Evaluator<T>()), pc_tree(NULL) {}
	std::pair<bool, std::string> sRun(std::string s_user_input);
};


template <typename T>
std::pair<MyError, Tree<T>*> REPL<T>::pEnter(std::string s_input) {
	std::tuple<MyError, std::vector<Token<T>*>, std::vector<std::string>> p_tokens_with_vars = this->pc_lexer->vecTokenize(s_input);

	MyError e_error = std::get<0>(p_tokens_with_vars);
	std::vector<Token<T>*> vec_tokens = std::get<1>(p_tokens_with_vars);
	std::vector<std::string> vec_variables = std::get<2>(p_tokens_with_vars);

	if (e_error.bHasErrors()) {
		for (Token<T>* pc_token : vec_tokens) {
			delete pc_token;
		}
		return std::make_pair(e_error, nullptr);
	}

	std::pair<MyError, Tree<T>*> p_tree = this->pc_parser->pParse(vec_tokens);
	
	if (p_tree.first.bHasErrors()) {
		for (Token<T>* pc_token : vec_tokens) {
			delete pc_token;
		}
		return p_tree;
	}

	return std::make_pair(e_error + p_tree.first, p_tree.second);
}

template <typename T>
std::string REPL<T>::sEnter(std::string s_input) {
	std::pair<MyError, Tree<T>*> p_entered = this->pEnter(s_input);
	if (p_entered.first.bHasErrors()) {
		delete p_entered.second;
		return p_entered.first.toString() + "\n";
	}
	
	if (this->pc_tree != NULL) {
		delete this->pc_tree;
	}

	this->pc_tree = p_entered.second;
	this->vec_variables = p_entered.second->vecGetVariables();

	if (p_entered.first.bHasErrors()) {
		delete p_entered.second;
		return p_entered.first.toString() + "\n" + this->sPrint();
	}

	if (p_entered.first.bHasWarnings()) {
		return p_entered.first.toString() + "\n" + this->sPrint();
	}

	return this->sPrint();
}

template <typename T>
std::string REPL<T>::sVariables() {
	if (this->pc_tree == NULL) {
		return "No tree entered";
	}
	std::string s_out = "Variables: ";
	std::vector<std::string> vec_variables = this->vec_variables;
	for (std::string s_variable : vec_variables) {
		s_out += s_variable + " ";
	}
	return s_out;
}

template <typename T>
std::string REPL<T>::sPrint() {
	if (this->pc_tree == NULL) {
		return "No tree entered";
	}
	return this->pc_tree->toString();
}

template <typename T>
std::string REPL<T>::sComp(std::string s_input) {
	if (this->pc_tree == NULL) {
		return "No tree entered";
	}

	std::vector<std::string> vec_words = vecWords(s_input, " ");
	if (vec_words.size() != this->vec_variables.size()) {
		return "Invalid number of variables";
	}
	std::map<std::string, T> map_variables;

	for (int i = 0; i < vec_words.size(); i += 1) {
		std::string s_value = vec_words[i];
		std::string s_variable = this->vec_variables[i];
		std::pair<MyError, T> p_value = stotv<T>(s_value);
		if (p_value.first.bHasErrors()) {
			return p_value.first.cReplaceLastErrorMessage("Invalid value for variable " + s_variable).toString();
		}
		map_variables[s_variable] = p_value.second;
	}

	T t_evaluation = this->pc_evaluator->tEvaluateTree(this->pc_tree, map_variables);
	
	return tvtos(t_evaluation);
}

template <typename T>
std::string REPL<T>::sJoin(std::string s_input) {
	if (this->pc_tree == NULL) {
		return "No tree entered";
	}
	std::vector<std::string> vec_words = vecWords(s_input, " ");
	std::pair<MyError, Tree<T>*> p_entered = this->pEnter(s_input);

	if (p_entered.first.bHasErrors()) {
		delete p_entered.second;
		return p_entered.first.toString();
	}

	*this->pc_tree += p_entered.second;
	this->vec_variables = this->pc_tree->vecGetVariables();

	return this->sPrint();
}

template <typename T>
std::string REPL<T>::sExit() {
	delete this->pc_lexer;
	delete this->pc_parser;
	delete this->pc_evaluator;
	delete this->pc_tree;
	return "Exiting...\n";
}


template <typename T>
std::pair<bool, std::string> REPL<T>::sRun(std::string s_user_input) {
	std::string s_out;
	const std::string s_enter = "enter";
	const std::string s_vars = "vars";
	const std::string s_print = "print";
	const std::string s_comp = "comp";
	const std::string s_join = "join";
	const std::string s_exit = "exit";

	if (s_user_input == "") return std::make_pair(false, s_out);
	std::vector<std::string> vec_words = vecWords(s_user_input, " ");
	std::string s_action = vec_words[0];
	std::string s_input = sUnwords(vecSubVector(vec_words, 1, vec_words.size()));

	if (s_action == s_enter && s_input != "") s_out += sEnter(s_input);
	else if (s_action == s_vars && s_input == "") s_out += sVariables();
	else if (s_action == s_print) s_out += sPrint();
	else if (s_action == s_comp) s_out += sComp(s_input);
	else if (s_action == s_join) s_out += sJoin(s_input);
	else if (s_action == s_exit) { return std::make_pair(true, sExit()); }
	else s_out += "Invalid command";

	return std::make_pair(false, s_out);
}
