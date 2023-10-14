#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "CNumber.h"

int main()
{
	CNumber c_num_0, c_num_1; 
	c_num_0 = 3622253252; 
	c_num_1 = 1567; 
	std::cout << (c_num_1 * c_num_0).sToStr() << std::endl;
	std::cout << (c_num_1 - c_num_0).sToStr() << std::endl;
	
}