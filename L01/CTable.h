#pragma once
#include <iostream>
#include <stdio.h>
#include <string>

class CTable {
public:
	CTable();
	CTable(std::string sName, int iTableLen);
	CTable(CTable &pcOther);
	~CTable();
	CTable *pcClone();

	void vSetName(std::string sName);
	bool bSetNewSize(int iTableLen);
	void vModTab(CTable *pcTab, int iNewSize);

	void vPrintState();
private:
	std::string s_name;
	int *pi_table;
	int i_length;
};



