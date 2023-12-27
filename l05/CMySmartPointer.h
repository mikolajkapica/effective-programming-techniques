#pragma once

class CRefCounter
{
public:
	CRefCounter() { i_count = 0; }
	int iAdd() { return(++i_count); }
	int iDec() { return(--i_count); };
	int iGet() { return(i_count); }
private:
	int i_count;
};//class CRefCounte

template <typename T>
class CMySmartPointer
{
public:
	CMySmartPointer() {
		pc_pointer = NULL;
		pc_counter = new CRefCounter();
		pc_counter->iAdd();
	}//CMySmartPointer()
	CMySmartPointer(T* pcPointer)
	{
		pc_pointer = pcPointer;
		pc_counter = new CRefCounter();
		pc_counter->iAdd();
	}//CMySmartPointer(T *pcPointer) 
	CMySmartPointer(const CMySmartPointer& pcOther)
	{
		pc_pointer = pcOther.pc_pointer;
		pc_counter = pcOther.pc_counter;
		pc_counter->iAdd();
	}//CMySmartPointer(const CMySmartPointer &pcOther) 
	~CMySmartPointer()
	{
		if (pc_counter->iDec() == 0)
		{
			delete pc_pointer;
			delete pc_counter;
		}//if (pc_counter->iDec())
	}//~CMySmartPointer() 
	T& operator*() { return(*pc_pointer); }
	T* operator->() { return(pc_pointer); }
	void operator=(const CMySmartPointer& pcOther)
	{
		if (pc_counter->iDec() == 0)
		{
			delete pc_pointer;
			delete pc_counter;
		}//if (pc_counter->iDec())
		pc_pointer = pcOther.pc_pointer;
		pc_counter = pcOther.pc_counter;
		pc_counter->iAdd();
	}//void operator=(const CMySmartPointer &pcOther)
	int iGetCounter() { return(pc_counter->iGet()); }
	CMySmartPointer cDuplicate() {
		return CMySmartPointer(*this);
	}
private:
	CRefCounter* pc_counter;
	T* pc_pointer;
};//class CMySmartPointer
