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
	int sizeOfTokenizedVector, i = 0;
	char** tokenizedVector = tokenizingFunction("  we wiLl see how to    REMOVE some   SPACEs from a   String ", sizeOfTokenizedVector, ' ');
	int* vectorTypeOfToken = new int[sizeOfTokenizedVector];
	vectorTypeOfToken = identifyKeywordTypeVector(tokenizedVector, sizeOfTokenizedVector, vectorTypeOfToken);

	/*token token(tokenizedVector, sizeOfTokenizedVector, vectorTypeOfToken);*/

	/*token.getVectorTypeOfTokenValues();*/

	for (int i = 0; i < sizeOfTokenizedVector; i++)
	{
		std::cout << tokenizedVector[i] << std::endl;
	}

	for (int i = 0; i < sizeOfTokenizedVector; i++)
	{
		delete[] tokenizedVector[i];
		
	}

	delete[] tokenizedVector;
	delete[] vectorTypeOfToken;
	tokenizedVector = nullptr;
	vectorTypeOfToken = nullptr;
	return 0;
}


// DROP TABLE table_name
//   we wiLl see how to    REMOVE some   SPACEs from a   String       