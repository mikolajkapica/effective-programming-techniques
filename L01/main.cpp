#include <iostream>
#include "CTable.h"
#include "table_procedures.h"

void vModTab(CTable *pcTab, int iNewSize) {
	pcTab->bSetNewSize(iNewSize);
}

// nic nie zmieni, bo to jest kopia
//void vModTab2(CTable cTab, int iNewSize) {
//	cTab.bSetNewSize(iNewSize);
//}

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
    std::cout << ctab_bezp->sToString() << std::endl;

    std::cout << "#4.2" << std::endl;
    ctab_param = new CTable("tablica z parametrem", 66);
    ctab_param->bSetNewSize(70);
    std::cout << ctab_param->sToString() << std::endl;

    std::cout << "#4.3" << std::endl;
	ctab_kopia = new CTable(*ctab_param);
    std::cout << ctab_kopia->sToString() << std::endl;


    // MODYFIKACJA:
    std::cout << "MODIFICATION" << std::endl;
    CTable c_orig(true);
    CTable *pc_copy;
    c_orig.vAdd1andCopy(&pc_copy);
    std::cout << pc_copy->sToString() << std::endl;
    delete pc_copy;
}
