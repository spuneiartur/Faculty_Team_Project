#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<algorithm>
#include "Header.h"
/* Deallocation - Do no forget :


*/

int main()
{
	int sizeOfTokenizedVector, i = 0;

	//char** tokenizedVector = tokenizingFunction("CREATE TABLE students ((id, integer, 1000, 0), (nume, text, 128, ''), (nume, text, 16, '10'));", sizeOfTokenizedVector, ' ');

	char** tokenizedVector = tokenizingFunction("CREATE TABLE students ((id, integer, 1000, 0), (nume, text, 128, ''), (grupa, text, 16, '10'));", sizeOfTokenizedVector, ' ');

	int* vectorTypeOfToken = identifyKeywordTypeVector(tokenizedVector, sizeOfTokenizedVector);
	Token token(tokenizedVector, sizeOfTokenizedVector, vectorTypeOfToken);

	token.parser();




	/*token.getVectorTypeOfTokenValues();

	for (int i = 0; i < sizeOfTokenizedVector; i++)
	{
		std::cout << tokenizedVector[i] << "   ||   "<< vectorTypeOfToken[i]<<std::endl;
	}
	*/
	// Deleting previously allocated arrays

	for (int i = 0; i < sizeOfTokenizedVector; i++)
	{
		delete[] tokenizedVector[i];
	}
	delete[] tokenizedVector;
	delete[] vectorTypeOfToken;
	tokenizedVector = nullptr;
	vectorTypeOfToken = nullptr;


	// PLAYGROUND
	/*Table table1(2,2, TESTcHAR);*/
	/*Table tables[2];
	std::string* s1 = new std::string[1];
	s1[0] = "Hello";
	std::string* s2 = new std::string[1];
	s2[0] = s1[0];
	std::cout << s2 << std::endl << s1 << std::endl;*/


	return 0;
}

//cristi new laptopp


// DROP TABLE table_name
//   we wiLl see how to    REMOVE some   SPACEs from a   String       
//CREATE TABLE clients ( client_id NUMBER(6) 12.5 CONSTRAINT pk_client PRIMARY KEY, client_name VARCHAR2(20) NOT NULL, client_surname VARCHAR2(20) NOT NULL, telephone VARCHAR2(20), credit_limit NUMBER(9,2), email VARCHAR2(30) CONSTRAINT one_email UNIQUE, birth_date DATE, status VARCHAR2(20), gender CHAR(1), CONSTRAINT ck_email CHECK (email LIKE '%@%.%') );

// UPDATE studenti SET nume = 'Alice' WHERE id = 1;
 
// CREATE TABLE students ((id, integer, 1000, 0), (nume, text, 128, ''), (nume, text, 16, '10'));

// SELECT (table_alpha, nr_grupa) FROM spain;