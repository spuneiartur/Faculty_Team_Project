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
	char** tokenizedVector = tokenizingFunction("CREATE TABLE clients ( client_id NUMBER(6) 12.5 CONSTRAINT pk_client PRIMARY KEY, client_name VARCHAR2(20) NOT NULL, client_surname VARCHAR2(20) NOT NULL, telephone VARCHAR2(20), credit_limit NUMBER(9,2), email VARCHAR2(30) CONSTRAINT one_email UNIQUE, birth_date DATE, status VARCHAR2(20), gender CHAR(1), CONSTRAINT ck_email CHECK (email LIKE '%@%.%') );", sizeOfTokenizedVector, ' ');
	
	int* vectorTypeOfToken = identifyKeywordTypeVector(tokenizedVector, sizeOfTokenizedVector);

	Token token(tokenizedVector, sizeOfTokenizedVector, vectorTypeOfToken);

	token.getVectorTypeOfTokenValues();

	for (int i = 0; i < sizeOfTokenizedVector; i++)
	{
		std::cout << tokenizedVector[i] << "   ||   "<< vectorTypeOfToken[i]<<std::endl;
	}

	
	// Deleting previously allocated arrays

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
//CREATE TABLE clients ( client_id NUMBER(6) 12.5 CONSTRAINT pk_client PRIMARY KEY, client_name VARCHAR2(20) NOT NULL, client_surname VARCHAR2(20) NOT NULL, telephone VARCHAR2(20), credit_limit NUMBER(9,2), email VARCHAR2(30) CONSTRAINT one_email UNIQUE, birth_date DATE, status VARCHAR2(20), gender CHAR(1), CONSTRAINT ck_email CHECK (email LIKE '%@%.%') );