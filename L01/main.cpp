#include <iostream>
#include "CTable.h"
#include "table_procedures.cpp"

int main() {
    std::cout << "#1" << std::endl;
    vAllocTableFill(5, 34);

    std::cout << "#2 i #3" << std::endl;
    int **tab;
    bool a = bAllocTable2Dim(&tab, 5, 5);
    bool b = bDeallocTable2Dim(&tab, 5);

    std::cout << "#4" << std::endl;
    CTable *ctab_bezp, *ctab_param, *ctab_kopia;

    std::cout << "#4.1" << std::endl;
    ctab_bezp = new CTable();
    ctab_bezp->vPrintState();

    std::cout << "#4.2" << std::endl;
    ctab_param = new CTable("tablica z parametrem", 66);
    ctab_param->vPrintState();

    std::cout << "#4.3" << std::endl;
	ctab_kopia = new CTable(*ctab_param);
    ctab_kopia->vPrintState();
}
