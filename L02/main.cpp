#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "CNumber.h"

int main()
{
	//CNumber c_num_0, c_num_1; 
	//c_num_0 = -9999; 
	//c_num_1 = 1111; 
	//std::cout << "Solution: " << (c_num_1 - 5).toString() << std::endl;

	CNumber c_num_0, c_num_1; 
	c_num_0 = -5;
	c_num_1 = 45;
	std::cout << "Solution: " << (c_num_0 * c_num_1).toString() << std::endl;
	
	//std::cout << (c_num_0 + c_num_1).sToStr() << std::endl;
	//std::cout << (c_num_0 * c_num_1).sToStr() << std::endl;
	//std::cout << (c_num_0 / c_num_1).sToStr() << std::endl;
}