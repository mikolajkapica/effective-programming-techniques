#include "CTable.h"

CTable::CTable() {
    this->s_name = "default";
    cout << "bezp: " + s_name << endl;
    length = 10;
    table = new int[length];
}

CTable::CTable(string sName, int iTableLen) {
    s_name = sName;
    cout << "parametr: " + s_name << endl;
    length = iTableLen;
    table = new int[iTableLen];
}

CTable::CTable(CTable &pcOther) {
    s_name = pcOther.s_name + "_copy";
    length = pcOther.length;
    table = new int[length];
    for (int i = 0; i < length; i++) {
        table[i] = pcOther.table[i];
    }
    cout << "kopiuj: " + s_name << endl;
}

CTable::~CTable() {
    cout << "usuwam: " + s_name << endl;
    delete table; // nie jestem pewny czy nie []
}

void CTable::vSetName(string sName) {
    s_name = sName;
}

bool CTable::bSetNewSize(int iTableLen) {
    if (iTableLen < 1) {
        return false;
    }
    int* newTable = new int[iTableLen];
    for (int i = 0; i < iTableLen; i++) { // length czy iTableLen
        newTable[i] = table[i];
    }
    delete table;
    table = newTable;
    length = iTableLen;
    return true;
}

CTable* CTable::pcClone() {
    CTable *newCTable = new CTable(*this);
    newCTable->vSetName(this->s_name);
    return newCTable;
}

void CTable::printState() {
	cout << "s_name:" << s_name << endl;
	cout << "length" << length << endl;
    for (int i = 0; i < length; i++) {
		cout << table[i] << endl;
	}
}
