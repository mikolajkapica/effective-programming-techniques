#include <iostream>
#include "CTable.h"

using namespace std;

// 1. ##################################################
 // czy moze byc za duza tablica? brak miejsca na stercie
void v_alloc_table_fill_34(int iSize) {
    const int IVALUE = 34;
    if (iSize < 1) {
        return;
    }
    int* tab = new int[iSize];
    for (int i = 0; i < iSize; i++) {
        tab[i] = IVALUE;
    }
    for (int i = 0; i < iSize; i++) {
        cout << tab[i] << endl;
    }
    delete[] tab;
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
    for (int i = 0; i < iSize; i++) {
        cout << tab[i] << endl;
    }
    delete[] tab;
}

// 2. ##################################################
// - Zastanów się jak dokładnie co wstawić zamiast ???, 
// jeżeli użycie referencji jest niemożliwe. 
bool b_alloc_table_2_dim(int*** piTable, int iSizeX, int iSizeY) {
    if (iSizeX < 1 || iSizeY < 1) {
        return false;
    }
    *piTable = new int*[iSizeX];
    for (int i = 0; i < iSizeX; i++) {
		(*piTable)[i] = new int[iSizeY];
    }
    return true;
}


// 3. ##################################################
 //- Zastanów się jak dokładnie co wstawić zamiast ???, jeżeli użycie referencji jest 
 //niemożliwe. Czy będzie jakaś różnica w porównaniu z b_alloc_table_2_dim? 
 //- Czy b_dealloc_table_2_dim może mieć mniej parametrów?
bool b_dealloc_table_2_dim(int*** piTable, int iSizeX) {
    if (iSizeX < 1) {
        return false;
    }
    for (int i = 0; i < iSizeX; i++) {
        delete[] (*piTable)[i];
    }
    delete[] *piTable;
    return true;
}

void v_mod_tab(CTable* pcTab, int iNewSize) {
	pcTab->bSetNewSize(iNewSize);
}

void v_mod_tab2(CTable cTab, int iNewSize) {
	cTab.bSetNewSize(iNewSize);
    // nic nie zmieni, bo to jest kopia
}

int main() {
    printf("Hello, World!\n");

    // 1. 
    v_alloc_table_fill(5, 34);

    // 2. 3.
    int** tab;
    bool a = b_alloc_table_2_dim(&tab, 5, 5);
    bool b = b_dealloc_table_2_dim(&tab, 5);

    // 4.
    CTable *ctab_bezp, *ctab_param, *ctab_kopia;
    ctab_bezp = new CTable();
    ctab_bezp->printState();
    ctab_param = new CTable("tablica z parametrem", 66);
    ctab_param->printState();
	ctab_kopia = new CTable(*ctab_param);
    ctab_kopia->printState();
}
