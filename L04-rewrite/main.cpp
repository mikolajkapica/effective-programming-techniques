#pragma once
#include "tests.h"
#include "repl.h"

#include <utility>
#include <iostream>

REPLBase* repl = nullptr;
REPL<int> repl_int;
REPL<double> repl_double;
REPL<std::string> repl_string;
REPL<bool> repl_bool;

void vChangeReplTo() {
	std::cout << "Choose type: int, double, string, bool" << std::endl;
	std::string s_choice;
	std::getline(std::cin, s_choice);

	if (s_choice == "") {
		return vChangeReplTo();
	} else {
		s_choice = vecWords(s_choice, " ")[0];
	}

	if (s_choice == "int") {
		repl = &repl_int;
		std::cout << "Changed to " << s_choice << std::endl;
	} else if (s_choice == "double") {
		repl = &repl_double;
		std::cout << "Changed to " << s_choice << std::endl;
	} else if (s_choice == "string") {
		repl = &repl_string;
		std::cout << "Changed to " << s_choice << std::endl;
	} else if (s_choice == "bool") {
		repl = &repl_bool;
		std::cout << "Changed to " << s_choice << std::endl;
	} else {
		std::cout << "Wrong type" << std::endl;
		return vChangeReplTo();
	}
}

int main(int argc, char** argv) {
	while (true) {
		std::string c_in;
		if (c_in == "change" || repl == nullptr) {
			vChangeReplTo();
		} else {
			std::getline(std::cin, c_in);
			std::pair<bool, std::string> p_out = (*repl).sRun(c_in);
			std::cout << p_out.second << std::endl;
			if (p_out.first) return 0;
		}
	}
}