#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<algorithm>
#include "Header.h"
/* Deallocation - Do no forget :


*/

int main()
{

	std::string commandLine = " CREATE TABLE Studenteel IF NOT EXISTS ((id, integer, 1000, 0), (nume, text, 128, ''), (grupa, text, 16, '10')); CREATE TABLE students ((id, integer, 1000, 0), (nume, text, 128, ''), (nume, text, 16, '10')); drop index rgrg; Display table studenteel;";
	
	loopingThroughCommands(commandLine);
	/*int maxSize[] = { 3, 128/8, 50/10 };
	int i1 = 3;
	int i2 = 128/8 ;
	int i3 = 3;
	printf("%-*s| %-*s| %-*s|\n",i1 + 10, "id", i2+ 10,  "name", i3 + 10,  "group");
	for (int i = 0; i < i1 + i3 + i2 + 30; i++) printf("-");
	printf("\n\n\n\n\n\n");*/
	
	return 0;
}


// DROP TABLE table_name;

// UPDATE studenti SET nume = 'Alice' WHERE id = 1;
 
// CREATE TABLE students ((id, integer, 1000, 0), (nume, text, 128, ''), (nume, text, 16, '10'));

// SELECT (table_alpha, nr_grupa) FROM spain;


//CREATE TABLE clients ( client_id NUMBER(6) 12.5 CONSTRAINT pk_client PRIMARY KEY, client_name VARCHAR2(20) NOT NULL, client_surname VARCHAR2(20) NOT NULL, telephone VARCHAR2(20), credit_limit NUMBER(9,2), email VARCHAR2(30) CONSTRAINT one_email UNIQUE, birth_date DATE, status VARCHAR2(20), gender CHAR(1), CONSTRAINT ck_email CHECK (email LIKE '%@%.%') );
