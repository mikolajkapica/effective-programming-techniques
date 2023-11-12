#include "Token.h"

std::string Token::sToString() {
	E_TOKEN_TYPE e_type = this->cGetTokenType();
	std::string s_type;
	switch (e_type) {
		case E_TOKEN_TYPE::OPERATOR: s_type = "OPERATOR"; break;
		case E_TOKEN_TYPE::NUMBER: s_type = "NUMBER"; break;
		case E_TOKEN_TYPE::VARIABLE: s_type = "VARIABLE"; break;
	}
	return "Token: [" + this->s_lexeme + "] [" + s_type + "]";
}
