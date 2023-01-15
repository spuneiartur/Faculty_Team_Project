#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include "Header.h"



int main()
{
	// Commands will be written in CommandLine.txt


	Files::extractingDbData();
	try
	{
		Files::deletingPreviousFiles();
	}
	catch (std::invalid_argument x)
	{
		std::cout << x.what() << std::endl;
		Files::updatingListOfTables();
	}
	
	
	std::string commandLine = Files::readingCommandsFromDB(); 

	try
	{
		loopingThroughCommands(commandLine);
	}
	catch (std::invalid_argument x)
	{
		std::cout << x.what() << std::endl;
		Files::updatingListOfTables();

	}

	Files::updatingListOfTables();

	// PLAYGROUND.
	

	return 0;
}


// DROP TABLE table_name;

// UPDATE studenti SET nume = 'Alice' WHERE id = 1;
 
// CREATE TABLE students ((id, integer, 1000, 0), (nume, text, 128, ''), (nume, text, 16, '10'));

// SELECT (table_alpha, nr_grupa) FROM spain;

//  CREATE TABLE Studenteel IF NOT EXISTS ((id, integer, 1000, 0), (nume, text, 128, ''), (grupa, text, 16, '10')); CREATE TABLE students ((id, integer, 1000, 0), (nume, text, 128, ''), (grupa, text, 16, '10')); INSERT INTO studenteel VALUES(1,'Alex','1068'); display table studenteel;INSERT INTO students VALUES(1,'Alex','1068');  INSERT INTO students VALUES(2,'Danut','1068');  INSERT INTO students VALUES(3,'Artur','1069');  INSERT INTO students VALUES(4,'Roma','1067'); display table students; DELETE FROM studenteel WHERE grupa = '1068g'; update students set nume = 'Bravo' where grupa = '1068'; display table students; DROP TABLE studenteel; 

//insert intoo students values(6,'Arturasul','1068');
// 
// 
// 
//CREATE TABLE clients ( client_id NUMBER(6) 12.5 CONSTRAINT pk_client PRIMARY KEY, client_name VARCHAR2(20) NOT NULL, client_surname VARCHAR2(20) NOT NULL, telephone VARCHAR2(20), credit_limit NUMBER(9,2), email VARCHAR2(30) CONSTRAINT one_email UNIQUE, birth_date DATE, status VARCHAR2(20), gender CHAR(1), CONSTRAINT ck_email CHECK (email LIKE '%@%.%') );
