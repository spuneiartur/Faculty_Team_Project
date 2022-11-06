#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<algorithm>
#include "Header.h"

/* Deallocation - Do no forget :
 1) tokenizedVector
 2) 

*/




int main()
{
	int sizeOfVector;
	char** tokenizedVector = tokenizingFunction("   we wiLl see how to++    REMOVE some   SPACEs from a   String     ", ' ', sizeOfVector);

	for (int i = 0; i< sizeOfVector; i++)
	{
		std::cout << tokenizedVector[i] << std::endl;
	}
	token createTable;

	return 0;
}


// DROP TABLE table_name
//   we wiLl see how to    REMOVE some   SPACEs from a   String       