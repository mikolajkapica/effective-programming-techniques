#include <stdio.h>
#include <iostream>

using namespace std;

// 1. ##################################################
// czy moze byc za duza tablica? brak miejsca na stercie
void v_alloc_table_fill_34(int iSize) {
    if (iSize < 1) {
        return;
    }
    int* tab = new int[iSize];
    for (int i = 0; i < iSize; i++) {
        tab[i] = 34;
    }
}

// opcja bez bezpośredniej wartości 34
void v_alloc_table_fill(int iSize, int iValue) {
    if (iSize < 1) {
        return;
    }
    int* tab = new int[iSize];
    for (int i = 0; i < iSize; i++) {
        tab[i] = iValue;
    }
}

// 2. ##################################################
// - Zastanów się jak dokładnie co wstawić zamiast ???, 
// jeżeli użycie referencji jest niemożliwe. 
bool b_alloc_table_2_dim(int ***piTable, int iSizeX, int iSizeY) {
    if (iSizeX < 1 || iSizeY < 1) {
        return false;
    }
    *piTable = new int*[iSizeX];
    for (int i = 0; i < iSizeX; i++) {
        *piTable[i] = new int[iSizeY];
    }
    return true;
}

// 3. ##################################################
// - Zastanów się jak dokładnie co wstawić zamiast ???, jeżeli użycie referencji jest 
// niemożliwe. Czy będzie jakaś różnica w porównaniu z b_alloc_table_2_dim? 
// - Czy b_dealloc_table_2_dim może mieć mniej parametrów?
bool b_dealloc_table_2_dim(int ***piTable, int iSizeX) {
    if (iSizeX < 1) {
        return false;
    }
    for (int i = 0; i < iSizeX; i++) {
        delete *piTable[i];
    }
    delete *piTable;
    return true;
}

// 4. ##################################################
class CTable {
private:
    string s_name;
    int *table;
    int length;
public:
    CTable();
    CTable(string sName, int iTableLen);
    CTable(CTable &pcOther);
    ~CTable();
    void vSetName(string sName);
    bool bSetNewSize(int iTableLen);
    CTable *pcClone();
};

CTable::CTable() {
    s_name = "default";
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
    int *newTable = new int[iTableLen];
    for (int i = 0; i < iTableLen; i++) { // length czy iTableLen
        newTable[i] = table[i];
    }
    // delete table;
    table = newTable;
    length = iTableLen;
    return true;
}

CTable *CTable::pcClone() {
    return new CTable(*this);
}

int main() {
    cout << "Compilation successful" << endl;
}
