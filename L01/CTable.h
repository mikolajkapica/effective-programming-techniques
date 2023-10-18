#pragma once
#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

class CTable {
private:
	string s_name;
	int* table;
	int length;
public:
	CTable();
	CTable(string sName, int iTableLen);
	CTable(CTable& pcOther);
	~CTable();
	void vSetName(string sName);
	bool bSetNewSize(int iTableLen);
	CTable* pcClone();
	void printState();
};



