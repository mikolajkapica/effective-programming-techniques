#pragma once
#include <iostream>
#include <stdio.h>
#include <string>

const std::string S_DEFAULT_NAME = "default";
const std::string S_COPY_SUFFIX = "_copy";
const int I_DEFAULT_LENGTH = 10;

const std::string S_MODIFICATION_NAME = "modification";
const int I_MODIFICATION_LENGTH = 4;

class CTable {
public:
	CTable();
	CTable(std::string s_name, int i_table_length);
	CTable(const CTable &pc_other);
	CTable(bool b_modification);
	~CTable();
	CTable *pcClone();

	void vSetName(std::string s_name);
	bool bSetNewSize(int i_table_length);

	void vAdd1andCopy(CTable **pc_copy);

	std::string sToString();
private:
	std::string s_name;
	int *pi_table;
	int i_length;
};



