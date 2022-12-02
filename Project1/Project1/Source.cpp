#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<algorithm>
#include "Header.h"
/* Deallocation - Do no forget :


*/

int main()
{

	//std::string commandLine = " CREATE TABLE Studenteel IF NOT EXISTS ((id, integer, 1000, 0), (nume, text, 128, ''), (nume, text, 16, '10')); CREATE TABLE students ((id, integer, 1000, 0), (nume, text, 128, ''), (nume, text, 16, '10'));";
	
	//loopingThroughCommands(commandLine);

//-------------------------------------------------------------------------------------------------------------------------------------------------
	int sizeOfTokenizedVector, i = 0;

	//char** tokenizedVector = tokenizingFunction("CREATE TABLE students ((id, integer, 1000, 0), (nume, text, 128, ''), (nume, text, 16, '10'));", sizeOfTokenizedVector, ' ');
	char** tokenizedVector = tokenizingFunction("INSERT INTO studenti VALUES(500,'Ion', 'Mihai', 43 , 500, 'Mihai', 500,'Mihai');", sizeOfTokenizedVector, ' ');
	int* vectorTypeOfToken = identifyKeywordTypeVector(tokenizedVector, sizeOfTokenizedVector);
	Token token(tokenizedVector, sizeOfTokenizedVector, vectorTypeOfToken);

	token.getVectorTypeOfTokenValues();

	for (int i = 0; i < sizeOfTokenizedVector; i++)
	{
		std::cout << tokenizedVector[i] << "   ||   " << vectorTypeOfToken[i] << std::endl;
	}

	token.lexer();

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


// DROP TABLE table_name;

// UPDATE studenti SET nume = 'Alice' WHERE id = 1;
 
// CREATE TABLE students ((id, integer, 1000, 0), (nume, text, 128, ''), (nume, text, 16, '10'));

// SELECT (table_alpha, nr_grupa) FROM spain;


//CREATE TABLE clients ( client_id NUMBER(6) 12.5 CONSTRAINT pk_client PRIMARY KEY, client_name VARCHAR2(20) NOT NULL, client_surname VARCHAR2(20) NOT NULL, telephone VARCHAR2(20), credit_limit NUMBER(9,2), email VARCHAR2(30) CONSTRAINT one_email UNIQUE, birth_date DATE, status VARCHAR2(20), gender CHAR(1), CONSTRAINT ck_email CHECK (email LIKE '%@%.%') );
