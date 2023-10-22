#include <iostream>

// 1. ##################################################
// czy moze byc za duza tablica? brak miejsca na stercie
void vAllocTableFill34(int i_size) {
    const int I_VALUE = 34;
    if (i_size < 1) {
        return;
    }

    int *pi_tab = new int[i_size];
    for (int i = 0; i < i_size; i++) {
        pi_tab[i] = I_VALUE;
    }

    for (int i = 0; i < i_size; i++) {
        std::cout << pi_tab[i] << std::endl;
    }

    delete[] pi_tab;
}

// opcja bez bezpoœredniej wartoœci 34
void vAllocTableFill(int i_size, int i_value) {
    if (i_size < 1) {
        return;
    }

    int *pi_tab = new int[i_size];
    for (int i = 0; i < i_size; i++) {
        pi_tab[i] = i_value;
    }

    for (int i = 0; i < i_size; i++) {
        std::cout << pi_tab[i] << std::endl;
    }

    delete[] pi_tab;
}

// 2. ##################################################
// - Zastanów siê jak dok³adnie co wstawiæ zamiast ???, 
// je¿eli u¿ycie referencji jest niemo¿liwe. 
bool bAllocTable2Dim(int ***pi_table, int i_size_x, int i_size_y) {
    if (i_size_x < 1 || i_size_y < 1) {
        return false;
    }

    *pi_table = new int* [i_size_x];
    for (int i = 0; i < i_size_x; i++) {
		(*pi_table)[i] = new int[i_size_y];
    }

    return true;
}


// 3. ##################################################
 //- Zastanów siê jak dok³adnie co wstawiæ zamiast ???, je¿eli u¿ycie referencji jest 
 //niemo¿liwe. Czy bêdzie jakaœ ró¿nica w porównaniu z bAllocTable2Dim? 
 //- Czy bDeallocTable2Dim mo¿e mieæ mniej parametrów?
bool bDeallocTable2Dim(int ***piTable, int iSizeX) {
    if (iSizeX < 1) {
        return false;
    }

    for (int i = 0; i < iSizeX; i++) {
        delete[] (*piTable)[i];
    }

    delete[] *piTable;

    return true;
}

