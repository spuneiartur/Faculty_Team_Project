#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include "Header.h"

/* Deallocation - Do no forget :


*/

int main()
{
	// All commands can be verified using display table command 
	// Input has to be written in the bellow string


	//processingDbData();

	std::string commandLine = " CREATE TABLE Studenteel IF NOT EXISTS ((id, integer, 1000, 0), (nume, text, 128, ''), (grupa, text, 16, '10')); CREATE TABLE students ((id, integer, 1000, 0), (nume, text, 128, ''), (grupa, text, 16, '10')); INSERT INTO studenteel VALUES(1,'Alex','1068'); display table studenteel;INSERT INTO students VALUES(1,'Alex','1068');  INSERT INTO students VALUES(2,'Danut','1068');  INSERT INTO students VALUES(3,'Artur','1069');  INSERT INTO students VALUES(4,'Roma','1067'); display table students; DELETE FROM studenteel WHERE grupa = '1068g'; update students set nume = 'Bravo' where grupa = '1068'; display table students; DROP TABLE studenteel;    "; 

	
	loopingThroughCommands(commandLine);

	Table::updatingListOfTables();

	// PLAYGROUND

	
	
	

	return 0;
}


// DROP TABLE table_name;

// UPDATE studenti SET nume = 'Alice' WHERE id = 1;
 
// CREATE TABLE students ((id, integer, 1000, 0), (nume, text, 128, ''), (nume, text, 16, '10'));

// SELECT (table_alpha, nr_grupa) FROM spain;




//CREATE TABLE clients ( client_id NUMBER(6) 12.5 CONSTRAINT pk_client PRIMARY KEY, client_name VARCHAR2(20) NOT NULL, client_surname VARCHAR2(20) NOT NULL, telephone VARCHAR2(20), credit_limit NUMBER(9,2), email VARCHAR2(30) CONSTRAINT one_email UNIQUE, birth_date DATE, status VARCHAR2(20), gender CHAR(1), CONSTRAINT ck_email CHECK (email LIKE '%@%.%') );
