#include "CTable.h"

CTable::CTable() {
    this->s_name = S_DEFAULT_NAME;
    this->i_length = I_DEFAULT_LENGTH;
    this->pi_table = new int[I_DEFAULT_LENGTH];

    std::cout << "bezp: '" + this->s_name << "'" << std::endl;
}

CTable::CTable(std::string s_name, int i_table_length) {
    this->s_name = s_name;
    this->i_length = i_table_length;
    this->pi_table = new int[i_table_length];

    std::cout << "parametr: '" + s_name << "'" << std::endl;
}

CTable::CTable(const CTable &pc_other) {
    this->s_name = pc_other.s_name + S_COPY_SUFFIX;
    this->i_length = pc_other.i_length;
    this->pi_table = new int[pc_other.i_length];
    for (int i = 0; i < pc_other.i_length; i++) {
        this->pi_table[i] = pc_other.pi_table[i];
    }

	std::cout << "kopiuj: '" + this->s_name << "'" << std::endl;
}

CTable::CTable(bool) {
	this->s_name = S_MODIFICATION_NAME;
	this->i_length = I_MODIFICATION_LENGTH;
	this->pi_table = new int[I_MODIFICATION_LENGTH];
	for (int i = 0; i < I_MODIFICATION_LENGTH; i++) {
		this->pi_table[i] = i + 1;
	}
}

CTable::~CTable() {
    std::cout << "usuwam: '" + this->s_name << "'" << std::endl;

    delete[] this->pi_table;
}

void CTable::vSetName(std::string s_name) {
    this->s_name = s_name;
}

bool CTable::bSetNewSize(int i_table_length) {
    if (i_table_length < 0) {
        return false;
    }

    int *pi_new_table = new int[i_table_length];
    std::copy(this->pi_table, this->pi_table + std::min(i_table_length, this->i_length), pi_new_table);

    delete[] this->pi_table;

    this->pi_table = pi_new_table;
    this->i_length = i_table_length;
    return true;
}

void CTable::vAdd1andCopy(CTable **pc_copy) {
    *pc_copy = this->pcClone();
    (*pc_copy)->vSetName((*pc_copy)->s_name + S_COPY_SUFFIX);
    (*pc_copy)->bSetNewSize(this->i_length + 1);
    (*pc_copy)->pi_table[this->i_length] = 1;
}

CTable *CTable::pcClone() {
    CTable *pi_new_CTable = new CTable(*this);
    pi_new_CTable->vSetName(this->s_name);
    return pi_new_CTable;
}

std::string CTable::sToString() {
    std::string s_out = "";
	s_out += "s_name: " + this->s_name + "\n";
	s_out += "length: " + std::to_string(this->i_length) + "\n";
    s_out += "[";
    for (int i = 0; i < this->i_length; i++) {
        s_out += std::to_string(this->pi_table[i]) + "; ";
	}
    s_out.erase(s_out.end() - 2, s_out.end());
    s_out += "]";
    return s_out;
}
