#include "CTable.h"

CTable::CTable() {
    const std::string S_DEFAULT_NAME = "default";
    const int I_DEFAULT_LENGTH = 10;

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

CTable::CTable(CTable &pc_other) {
    const std::string S_COPY_SUFFIX = "_copy";

    this->s_name = pc_other.s_name + S_COPY_SUFFIX;
    this->i_length = pc_other.i_length;
    this->pi_table = new int[pc_other.i_length];
    for (int i = 0; i < pc_other.i_length; i++) {
        this->pi_table[i] = pc_other.pi_table[i];
    }

    std::cout << "kopiuj: '" + this->s_name << "'" << std::endl;
}

CTable::~CTable() {
    std::cout << "usuwam: '" + this->s_name << "'" << std::endl;

    delete[] this->pi_table;
}

void CTable::vSetName(std::string s_name) {
    this->s_name = s_name;
}

bool CTable::bSetNewSize(int i_table_length) {
    if (i_table_length < 1) {
        return false;
    }

    int *newTable = new int[i_table_length];
    for (int i = 0; i < i_table_length; i++) { 
        newTable[i] = this->pi_table[i];
    }

    delete[] this->pi_table;

    this->pi_table = newTable;
    this->i_length = i_table_length;
    return true;
}

CTable *CTable::pcClone() {
    CTable *new_CTable = new CTable(*this);
    new_CTable->vSetName(this->s_name);
    return new_CTable;
}

void CTable::vModTab(CTable *pcTab, int iNewSize) {
	pcTab->bSetNewSize(iNewSize);
}

// nic nie zmieni, bo to jest kopia
//void vModTab2(CTable cTab, int iNewSize) {
//	cTab.bSetNewSize(iNewSize);
//}

void CTable::vPrintState() {
	std::cout << "s_name: " << this->s_name << std::endl;
	std::cout << "length: " << this->i_length << std::endl;
    for (int i = 0; i < this->i_length; i++) {
		std::cout << this->pi_table[i] << std::endl;
	}
}
