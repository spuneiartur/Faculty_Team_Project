#pragma once

int TEXT = -5;
int NUMBER = -10;


enum commandBranches {
	createTable, createIndex, typeDataType, argString, argNumber
};

enum typeCommands {
	create, alter, drop, select, delete_, insert, update, commit, rollback, savepoint, grant, revoke, table, index, where, set, IF
};

enum typeOperators {
	add = '+', sub = '-', mul = '*', div_ = '/', mod = '%', equals = '=', notEqual = '!=', greater = '>', less = '<', greaterEqual = '>=', lessEqual = '<=', notLess = '!<', notGreater = '!>', and_, between, exists, in, notIn, like, glob, not_, or_, isNull, addStrings = '||', unique, l_parentheses = '(', r_parentheses = ')', asterix = '*', 
};

enum typeDataType {
	text = typeCommands::index + 1, integer
};

enum dataTypeValues {
	number = -10, string = -5
};
// TODO
// to build custom throws

// Classes -------------------------------------------------------------------------------------------
class Table {
private:
	bool exists = false;
	char* name = nullptr;
	int noColumns;
	std::string* vNames = nullptr;
	std::string* vTypes = nullptr;
	int* vDimensions = nullptr;
	std::string* vDefaults = nullptr;
	int noData;
	std::string** mData = nullptr;
	static int noOfTables;
	static Table tables[100];

public:
	// Methods
	static void createTable(char* name, int noColumns, std::string* vNames, std::string* vTypes, int* vDimensions, std::string* vDefaults, bool checkIfExists = false) {

		if (checkIfExists)
		{
			for (int i = 0; i <= noOfTables; i++)
			{
				
				if (strcmp(tables[i].name, name) == 0)
				{
					throw std::invalid_argument("A table with such name alreay exists");
				}
			}
		}
		
		tables[++noOfTables] = { Table(name, noColumns, vNames, vTypes, vDimensions, vDefaults) };
		// Checking the name of all existing tables
		/*for (int i = 0; i <= noOfTables; i++)
		{
			std::cout << tables[i].name << std::endl;
		}*/
	}

	//Constructors
	Table() {
		this->exists = false;
		this->name = nullptr;
		this->noColumns = 0;
		this->vNames = nullptr;
		this->vTypes = nullptr;
		this->vDimensions = nullptr;
		this->vDefaults = nullptr;
		this->noData = 0;
		this->mData = nullptr;
	}
	Table(char* name, int noColumns, std::string* vNames, std::string* vTypes, int* vDimensions, std::string* vDefaults) {

		this->exists = true;

		if (name != nullptr)
		{
			this->name = new char[strlen(name) + 1];
			strcpy(this->name, name);
		}
		else
		{
			this->name = nullptr;
		}
		this->noColumns = noColumns;
		// vNames
		if (vNames != nullptr)
		{
			this->vNames = new std::string[noColumns];
			for (int i = 0; i < noColumns; i++)
			{
				this->vNames[i] = vNames[i];
			}
		}

		// vTypes
		if (vTypes != nullptr)
		{
			this->vTypes = new std::string[noColumns];
			for (int i = 0; i < noColumns; i++)
			{
				this->vTypes[i] = vTypes[i];
			}
		}

		// vDimensions
		if (vDimensions != nullptr)
		{
			this->vDimensions = new int[noColumns];
			for (int i = 0; i < noColumns; i++)
			{
				this->vDimensions[i] = vDimensions[i];
			}
		}

		// vDefaults
		if (vDefaults != nullptr)
		{
			this->vDefaults = new std::string[noColumns];
			for (int i = 0; i < noColumns; i++)
			{
				this->vDefaults[i] = vDefaults[i];
			}
		}

		// DATA 
		this->noData = 0;
		this->mData = nullptr;

	}
	// Copy constructor
	Table(const Table& t) {

		this->exists = t.exists;
		// name
		if (this->name != nullptr)
		{
			delete[] this->name;
			this->name = nullptr;
		}
		if (t.name != nullptr)
		{
			this->name = new char[strlen(t.name) + 1];
			strcpy(this->name, t.name);
		}
		else
		{
			this->name = nullptr;
		}

		this->noColumns = t.noColumns;
		// vNames
		if (this->vNames != nullptr)
		{
			delete[] this->vNames;
			this->vNames = nullptr;
		}
		if (t.vNames != nullptr)
		{
			this->vNames = new std::string[noColumns];

			for (int i = 0; i < noColumns; i++)
			{
				this->vNames[i] = t.vNames[i];
			}
		}
		else
		{
			this->vNames = nullptr;
		}
		// vTypes
		if (this->vTypes != nullptr)
		{
			delete[] this->vTypes;
			this->vTypes = nullptr;
		}
		if (t.vTypes != nullptr)
		{
			this->vTypes = new std::string[noColumns];

			for (int i = 0; i < noColumns; i++)
			{
				this->vTypes[i] = t.vTypes[i];
			}
		}
		else
		{
			this->vTypes = nullptr;
		}
		// vDimensions
		if (this->vDimensions != nullptr)
		{
			delete[] this->vDimensions;
			this->vDimensions = nullptr;
		}
		if (t.vDimensions != nullptr)
		{
			this->vDimensions = new int[noColumns];

			for (int i = 0; i < noColumns; i++)
			{
				this->vDimensions[i] = t.vDimensions[i];
			}
		}
		else
		{
			this->vDimensions = nullptr;
		}
		// vDefaults
		if (this->vDefaults != nullptr)
		{
			delete[] this->vDefaults;
			this->vDefaults = nullptr;
		}
		if (t.vDefaults != nullptr)
		{
			this->vDefaults = new std::string[noColumns];

			for (int i = 0; i < noColumns; i++)
			{
				this->vDefaults[i] = t.vDefaults[i];
			}
		}
		else
		{
			this->vDefaults = nullptr;
		}

		// noData
		this->noData = t.noData;

		// mData
		if (this->mData != nullptr)
		{
			for (int i = 0; i < noColumns; i++)
			{
				delete[] this->mData[i];
			}
			delete[] this->mData;
			this->mData = nullptr;
		}
		if (t.mData != nullptr)
		{
			this->mData = new std::string * [noColumns];
			for (int i = 0; i < noColumns; i++)
			{
				this->mData[i] = new std::string[noData];
			}

			for (int i = 0; i < noColumns; i++)
				for (int j = 0; j < noData; j++)
				{
					this->mData[i][j] = t.mData[i][j];
				}
		}
		else
		{
			this->mData = nullptr;
		}


	}
	//Destructor
	~Table() {
		if (this->name != nullptr)
		{
			delete[] this->name;
			this->name = nullptr;
		}

		if (this->vNames != nullptr)
		{
			delete[] this->vNames;
			this->vNames = nullptr;
		}

		if (this->vTypes != nullptr)
		{
			delete[] this->vTypes;
			this->vTypes = nullptr;
		}

		if (this->vDimensions != nullptr)
		{
			delete[] this->vDimensions;
			this->vDimensions = nullptr;
		}

		if (this->vDefaults != nullptr)
		{
			delete[] this->vDefaults;
			this->vDefaults = nullptr;
		}
		if (this->mData != nullptr)
		{
			for (int i = 0; i < noColumns; i++)
			{
				delete[] this->mData[i];
			}
			delete[] this->mData;
			this->mData = nullptr;
		}
	}

	Table& operator=(const Table& t) {
		this->exists = t.exists;
		// name
		if (this->name != nullptr)
		{
			delete[] this->name;
			this->name = nullptr;
		}
		if (t.name != nullptr)
		{
			this->name = new char[strlen(t.name) + 1];
			strcpy(this->name, t.name);
		}
		else
		{
			this->name = nullptr;
		}

		this->noColumns = t.noColumns;
		// vNames
		if (this->vNames != nullptr)
		{
			delete[] this->vNames;
			this->vNames = nullptr;
		}
		if (t.vNames != nullptr)
		{
			this->vNames = new std::string[noColumns];

			for (int i = 0; i < noColumns; i++)
			{
				this->vNames[i] = t.vNames[i];
			}
		}
		else
		{
			this->vNames = nullptr;
		}
		// vTypes
		if (this->vTypes != nullptr)
		{
			delete[] this->vTypes;
			this->vTypes = nullptr;
		}
		if (t.vTypes != nullptr)
		{
			this->vTypes = new std::string[noColumns];

			for (int i = 0; i < noColumns; i++)
			{
				this->vTypes[i] = t.vTypes[i];
			}
		}
		else
		{
			this->vTypes = nullptr;
		}
		// vDimensions
		if (this->vDimensions != nullptr)
		{
			delete[] this->vDimensions;
			this->vDimensions = nullptr;
		}
		if (t.vDimensions != nullptr)
		{
			this->vDimensions = new int[noColumns];

			for (int i = 0; i < noColumns; i++)
			{
				this->vDimensions[i] = t.vDimensions[i];
			}
		}
		else
		{
			this->vDimensions = nullptr;
		}
		// vDefaults
		if (this->vDefaults != nullptr)
		{
			delete[] this->vDefaults;
			this->vDefaults = nullptr;
		}
		if (t.vDefaults != nullptr)
		{
			this->vDefaults = new std::string[noColumns];

			for (int i = 0; i < noColumns; i++)
			{
				this->vDefaults[i] = t.vDefaults[i];
			}
		}
		else
		{
			this->vDefaults = nullptr;
		}

		// noData
		this->noData = t.noData;

		// mData
		if (this->mData != nullptr)
		{
			for (int i = 0; i < noColumns; i++)
			{
				delete[] this->mData[i];
			}
			delete[] this->mData;
			this->mData = nullptr;
		}
		if (t.mData != nullptr)
		{
			this->mData = new std::string * [noColumns];
			for (int i = 0; i < noColumns; i++)
			{
				this->mData[i] = new std::string[noData];
			}

			for (int i = 0; i < noColumns; i++)
				for (int j = 0; j < noData; j++)
				{
					this->mData[i][j] = t.mData[i][j];
				}
		}
		else
		{
			this->mData = nullptr;
		}
		return *this;
	}
};
int Table::noOfTables = -1;
Table Table::tables[100];


class Token {
private:
	std::string text;
	std::string type;
	char** tokenizedVector;
	int sizeOfTokenizedVector;
	int* vectorTypeOfToken;
	unsigned int line;
	unsigned int column;
	int iterator;


public:

	// Methods

	// // Getters
	void getVectorTypeOfTokenValues() {
		if (vectorTypeOfToken != nullptr)
		{
			for (int i = 0; i < this->sizeOfTokenizedVector; i++)
			{
				std::cout << this->vectorTypeOfToken[i] << " | ";
			}
			std::cout << std::endl;
		}
		else {
			throw;
		}
	}

	// // Setters


	void parser() {
		lexer();

		if (strcmp(tokenizedVector[0], "create") == 0) {
			parserCreateTable();
		}else throw std::invalid_argument("Wrong first token of the command");
	}

	// Checks this syntax : id = 5 || name = 'Alex'. 
	// HOW TO USE: index (i) should be passed when it is forwarding to first argument (ex. vector[i] == id || vector[i] == name)
	// !!! NOTE: Function accepts only one set of argument (ex. id = 15 -> ok; (id = 15, name = 'Alex') -> not ok) 
	// !!! NOTE: Function accepts empty space as value for text argument (ex. name = '')
	void checkingLexerOfEquality(int& i) {
		if (vectorTypeOfToken[i] != dataTypeValues::string) throw std::invalid_argument("Unexpected token at position iterator; Expected an identifier"); // checking the identifier name of column
		i++;
		if (vectorTypeOfToken[i] != 61) throw std::invalid_argument("Unexpected token at position iterator; Expected token \"=\"");
		i++;
		if (strcmp(tokenizedVector[i], "'") == 0)
		{
			i++;
			if (strcmp(tokenizedVector[i], "'") == 0)
			{
				i++;
			}
			else
			{
				if (strcmp(tokenizedVector[i + 1], "'") < 0) throw std::invalid_argument("Unexpected token at position iterator+1; Expected token \"=\"");
				if (vectorTypeOfToken[i] != dataTypeValues::string && vectorTypeOfToken[i] != dataTypeValues::number) throw std::invalid_argument("Unexpected token at position iterator; Expected a value compatible with the column");
				i += 2;
			}

		}
		else if (vectorTypeOfToken[i] == dataTypeValues::number)
		{
			i++;
		}
		else throw std::invalid_argument("Unexpected token at position iterator+1; Expected a value compatible with the column");
	}
	// Counting from a sequence of paranthesis the no of Columns
	// I: The position of the first paranthesis, not the one including column arguments
	// E: The No of columns
	int countingNoOfColumns(int posOfParanthesis) {
		int counterNoCol = 0;
		int j = NULL;
		for (j = posOfParanthesis + 1; j < sizeOfTokenizedVector; j++)
		{
			if (strcmp(tokenizedVector[j], "(") == 0)
			{
				while (strcmp(tokenizedVector[j], ")") < 0)
				{
					j++;
				}
				counterNoCol++;
			}
		}
		return counterNoCol;
	}

	void parserCreateTable() {
		int posOfParanthesis;
		// Checking if the condition IF NOT EXISTS is mentioned -----------------------------------??????????????????????????????????
		bool verificationIsNeeded = false;
		for (int i = 1; i < sizeOfTokenizedVector-2; i++)
		{
			if (strcmp(tokenizedVector[i], "if") == 0)
			{
				if(strcmp(tokenizedVector[i + 1], "not") == 0)
				{
					if (strcmp(tokenizedVector[i + 2], "exists") == 0)
					{
						verificationIsNeeded = true;
					}
				}
			}
			// Exiting the for loop if '(' is found
			if (strcmp(tokenizedVector[i], "(") == 0)
			{
				posOfParanthesis = i;
				i = sizeOfTokenizedVector - 2;
				
			}
		}
		// Counting and saving the parameters for columns
		
		// // Getting the No of Columns
		int counterNoCol = countingNoOfColumns(posOfParanthesis);
		std::cout << "The table consists of " << counterNoCol << " columns" << std::endl;
		// // Saving parameters for each column 
		char* tableName = new char[strlen(tokenizedVector[2]) + 1];
		strcpy(tableName, tokenizedVector[2]);
		std::string* vNames = new std::string[counterNoCol];
		std::string* vTypes = new std::string[counterNoCol];
		int* vDimensions = new int[counterNoCol];
		std::string* vDefaults = new std::string[counterNoCol];
		int argType = 0;
		int column = 0;
		int argNo = 4;
		for (int j = posOfParanthesis + 1; j < sizeOfTokenizedVector; j++)
		{
			if (strcmp(tokenizedVector[j], "(") == 0)
			{	
				if (strcmp(tokenizedVector[j + 3], "text") == 0)
				{
					
					vNames[column] = tokenizedVector[j + 1];
					vTypes[column] = tokenizedVector[j + 3];
					vDimensions[column] = atoi(tokenizedVector[j + 5]);
					if (strcmp(tokenizedVector[j + 8], "'") == 0)
					{
						vDefaults[column] = "";
					}
					else
					{
						vDefaults[column] = tokenizedVector[j + 8];
					}
					j += 10;
					column++;
				}
				else if (strcmp(tokenizedVector[j + 3], "integer") == 0)
				{
					vNames[column] = tokenizedVector[j + 1];
					vTypes[column] = tokenizedVector[j + 3];
					vDimensions[column] = atoi(tokenizedVector[j + 5]);
					vDefaults[column] = tokenizedVector[j + 7];
					j += 8;
					column++;
				}
				else throw std::invalid_argument("The type of value is neither an INTEGER nor TEXT");
			}
		}
		/*for (int i = 0; i < counterNoCol; i++) {
			std::cout << vNames[i] << " | " << vTypes[i] << " | " << vDimensions[i] << " | " << vDefaults[i] << std::endl;
		}*/

		// // Creating table
		Table::createTable(tableName, counterNoCol, vNames, vTypes, vDimensions, vDefaults, verificationIsNeeded);

	}

	void lexerCreateTable() {
		int i = 1;
		if (!strcmp(tokenizedVector[i], "table") && vectorTypeOfToken[i + 1] == dataTypeValues::string) {
			i++;
			if (vectorTypeOfToken[i] == dataTypeValues::string) { // if token is an identifier 
				i++;

				if (strcmp(tokenizedVector[i], "(") == 0) { // if token is an identifier and next token is a paranthesis
				}
				else if (strcmp(tokenizedVector[i], "if") == 0 && strcmp(tokenizedVector[i + 1], "not") == 0 && strcmp(tokenizedVector[i + 2], "exists") == 0)
				{
					if(strcmp(tokenizedVector[i+3], "(") < 0) throw std::invalid_argument("Unexpected token at position iterator+1; Expected token \"()\" or \"IF NOT EXISTS\"");
					i += 3;
					
				}
				else throw std::invalid_argument("Unexpected token at position iterator+1; Expected token \"()\" or \"IF NOT EXISTS\"");

				if (strcmp(tokenizedVector[i + 1], ")") == 0) throw; // you should insert at least one column 
				i++;
				// Processing the lexer for all columns' structure 
				while (strcmp(tokenizedVector[i], ")") < 0) {
					while (strcmp(tokenizedVector[i], ")") < 0) { // Here tokenizedVector[i] is pointing to the opening paranthesis of the column
						int maxSize = 0;
						if (strcmp(tokenizedVector[i], "(") < 0) throw; // Missing "(" token at the the position i

						if (vectorTypeOfToken[i + 1] >= 0) throw; // Unexpected argument at position i, expecting an identifier - name for the column;
						if (strcmp(tokenizedVector[i + 2], ",") < 0) throw; // Unexpected argument at position i, expecting a "," - separator;
						switch (vectorTypeOfToken[i + 3]) // Forkifying around 2 cases: if the input is set as integer or as text
						{

						case typeDataType::integer:  // type 14 from enum of data types - INTEGER

							if (strcmp(tokenizedVector[i + 4], ",") < 0) throw; // Expecting a "," - separator;

							if (vectorTypeOfToken[i + 5] != dataTypeValues::number) throw std::invalid_argument("Unexpected token at position in the column arguments; Expected token \",\" ");

							maxSize = atoi(tokenizedVector[i + 5]);

							if (strcmp(tokenizedVector[i + 6], ",") < 0) throw; // Unexpected argument at position i, expecting a "," - separator;

							if (vectorTypeOfToken[i + 7] != dataTypeValues::number || atoi(tokenizedVector[i + 7]) > maxSize) throw; // Token is not of the integer data type or the integer is greater than max size addmissible
							i += 8;
							break;
						case typeDataType::text: // type 15 from enum of data types - TEXT
							if (strcmp(tokenizedVector[i + 4], ",") < 0) throw; // Expecting a "," - separator;

							if (vectorTypeOfToken[i + 5] != dataTypeValues::number) throw; // Expected a 

							maxSize = atoi(tokenizedVector[i + 5]) / 8;

							if (strcmp(tokenizedVector[i + 6], ",") < 0) throw; // Unexpected argument at position i, expecting a "," - separator;

							if (strcmp(tokenizedVector[i + 7], "'") < 0) throw; // Unexpected argument at position i, expecting a "'" - separator;
							if (strcmp(tokenizedVector[i + 7], "'") == 0 && strcmp(tokenizedVector[i + 8], "'") == 0) {
								i += 9;
							}
							else {
								if (strlen(tokenizedVector[i + 8]) > maxSize) throw; // Token is not a text data type or the length of the text is greater than the max size addmissible 

								if (strcmp(tokenizedVector[i + 9], "'") < 0) throw; // Unexpected argument at position i, expecting a "'" - separator;
								i += 10;
							}
							break;
						default:
							throw; // Expected a data type as second argument (text or integer)
						}
						if (strcmp(tokenizedVector[i], ")") < 0) throw; // Expected token ")"

					}
					i++; // Exiting the parameters for processed column
					if (strcmp(tokenizedVector[i], ",") < 0 && strcmp(tokenizedVector[i], ")") < 0) throw; // Expected a separation token - ","
					else if (strcmp(tokenizedVector[i], ",") == 0) i++; // Moving to next column or end of the command

				}

			}
			i++;
			if (strcmp(tokenizedVector[i], ";") < 0) throw std::invalid_argument("Unexpected tokens after \")\"");

			std::cout << "the command is correct!" << std::endl;
		}
		else throw std::invalid_argument("Unexpected token at position iterator+1; Non compatible with token \"CREATE\". Expected token \"Table\" or \"Index\"");

	}

	void lexerDisplay() {
		int i = 1;
		if (strcmp(tokenizedVector[i], "table") < 0) throw std::invalid_argument("The second token is not compatible with token \"DISPLAY\". Expected token \"TABLE\"");

		if (vectorTypeOfToken[i + 1] != dataTypeValues::string) throw std::invalid_argument("Missing the table name; Expected an identifier - name of an existing table");

		if (strcmp(tokenizedVector[sizeOfTokenizedVector - 1], ";") != 0) throw std::invalid_argument("Expected \";\"");


		if (vectorTypeOfToken[i + 2] == dataTypeValues::string && strcmp(tokenizedVector[sizeOfTokenizedVector - 1], ";") == 0) throw std::invalid_argument("Wrong table name");

		if (strcmp(tokenizedVector[i + 2], ",") == 0) throw std::invalid_argument("Too many arguments. Display accepts only a table as argument");


		std::cout << "The command is correct!" << std::endl;
	}

	void lexerUpdate()
	{
		int i = 1;
		if (vectorTypeOfToken[i] != dataTypeValues::string) throw std::invalid_argument("Unexpected token at position iterator+1; Non compatible with token \"UPDATE\". Expected an identifier"); // checking the identifier name of table
		i++;
		if (strcmp(tokenizedVector[i], "set") < 0) throw std::invalid_argument("Unexpected token at position iterator; Non compatible with token \"UPDATE table_name -\". Expected token \"Set\""); // checking the token SET
		i++;

		checkingLexerOfEquality(i); // Checks this syntax : id = 5 || name = 'Alex'

		if (strcmp(tokenizedVector[i], ",") == 0) throw std::invalid_argument("Too many SET columns ");

		if (strcmp(tokenizedVector[i], "where") < 0) throw std::invalid_argument("Unexpected token at position iterator; Expected token \"where\"");

		i++;

		checkingLexerOfEquality(i); // Checks this syntax of this type: id = 5 || name = 'Alex'

		if (strcmp(tokenizedVector[i], ";") < 0) throw std::invalid_argument("Too many arguments after WHERE or Missing token \";\"");

		std::cout << "The command is correct!" << std::endl;





	}


	void lexerSelect() {
		int i = 0;
		int k, m, n;
		int numberOfCommasIn = 0;
		int nrColumns = 1; // we must have one column
		if ((strcmp(tokenizedVector[i], "select") == 0 && strcmp(tokenizedVector[sizeOfTokenizedVector - 1], ";") == 0) /*&& (vectorTypeOfToken[i + 2] == dataTypeValues::string) /* && strcmp(tokenizedVector[sizeOfTokenizedVector - 1], ";") == 0*/) { // verifiy for a basic SELECT value or a SELECT ALL FROM
			for (int j = i; j < sizeOfTokenizedVector; j++) { // find all of the columns by adding all of the apperances of "," 
				if (!(strcmp(tokenizedVector[i + 1], "("))) { // look for "(" since we one or more attributes that are not ALL
					if (!(strcmp(tokenizedVector[j], ","))) {
						nrColumns++; //count the number of columns / variables
						numberOfCommasIn++;// count the number of "," in the ()
					}
					else if (!(strcmp(tokenizedVector[j], ")"))) {
						k = j;//saved the location of where the parenthisis end
						break;// stop when we get there
					}
				}
			}
			if (nrColumns > 1) {
				for (int j = k + 1; j < sizeOfTokenizedVector; j++) {
					if (!(strcmp(tokenizedVector[j], "from"))) {
						m = j; // save location of from 
					}
				}
				if ((strcmp(tokenizedVector[i + 1], "(")) || (strcmp(tokenizedVector[m - 1], ")"))) {//verify if we have () around the values
					throw;
				}
				for (int j = i + 2; j < nrColumns + numberOfCommasIn + 2; j++) { // check if we have string then "," and end with string
					if (!(strcmp(tokenizedVector[j], tokenizedVector[j + 2]))) {
						throw;//check if the same column isnt used twice
					}
					if (vectorTypeOfToken[j] == dataTypeValues::string) {
						if (!(strcmp(tokenizedVector[j], "all"))) {
							throw;//if user uses all and another value throw an error
						}
						++j;
						if (!(strcmp(tokenizedVector[j], ")"))) {
							break; // stop when we reach the end so we dont look for one more comma that will throw an error
						}
						if ((strcmp(tokenizedVector[j], ","))) {
							throw;//if the values are not comma separated throw a error
						}
					}
				}
				if (strcmp(tokenizedVector[m + 2], ";") || vectorTypeOfToken[m + 1] != dataTypeValues::string || strcmp(tokenizedVector[m - 1], ")") || strcmp(tokenizedVector[m], "from")) {
					throw; //verifiy if after from we have ";" and a string;
				}

			} // for a case where we find FROM but we find it somewhere else then after a ")"

			if (nrColumns == 1) {
				//FOR ONE COLUMN------------------------------------------------------
				if (!(strcmp(tokenizedVector[i + 1], "(")) && !(strcmp(tokenizedVector[i + 3], ")"))) {// check if we only have one argument 
					if (vectorTypeOfToken[i + 2] == dataTypeValues::string && (strcmp(tokenizedVector[i + 2], "all")) && (strcmp(tokenizedVector[i + 2], "*"))) { // check to see if we have a string between the parenthesis and its not all or *
						if (strcmp(tokenizedVector[i + 4], "from")) {
							throw; // SELECT value FROM syntax is wrongly written
						}
						if (vectorTypeOfToken[i + 5] != dataTypeValues::string) {
							throw; // if the 4th place is not a string value , the name of the table we throw error
						}
						if (strcmp(tokenizedVector[i + 6], ";")) {
							throw; // verifiy the we dont have two words after from
						}
						if (!(strcmp(tokenizedVector[i + 2], "all")) || (!(strcmp(tokenizedVector[i + 2], "*")))) {
							throw;
						}
					}
					else {
						throw; //if the value between parenthisis insnt a string throw error
					}
				}
				//FOR ALL COLUMNS-----------------------------------------------------
				else if (!(strcmp(tokenizedVector[i + 1], "all")) || !(strcmp(tokenizedVector[i + 1], "*"))) {//check for ALL or * written after SELECT
					if (strcmp(tokenizedVector[i + 2], "from")) {
						throw; // SELECT ALL FROM syntax is wrongly written
					}
					else if (vectorTypeOfToken[i + 3] != dataTypeValues::string) {
						throw; // if the 4th place is not a string value , the name of the table we throw error
					}
					if (strcmp(tokenizedVector[i + 4], ";")) {
						throw; // verifiy the we dont have two words after from
					}
				}
				else {
					throw;
				}
			}
		}
		else {
			throw std::invalid_argument("The command is missing the token \";\"");;
		}
		std::cout << "Command is correct!" << std::endl;
	}

	void lexerDelete() {//DELETE FROM table_name WHERE column_name = value;
		if (strcmp(tokenizedVector[0], "delete")) {
			throw std::invalid_argument("Wrong format of the keyword!\n");
		}
		else {
			if (strcmp(tokenizedVector[1], "from")) {
				throw std::invalid_argument("Wrong FROM format or position as 2nd argument!");
			}
			else {
				if (vectorTypeOfToken[2] != dataTypeValues::string || !strcmp(tokenizedVector[2], "from") || !strcmp(tokenizedVector[2], "delete") || !strcmp(tokenizedVector[2], "where")) {
					throw std::invalid_argument("Wrong table name or missing!");
				}
				else {
					if (strcmp(tokenizedVector[3], "where")) {
						throw std::invalid_argument("Missing WHERE clause as 4th poisiton in argument");
					}
					else {
						if (vectorTypeOfToken[4] != dataTypeValues::string || !strcmp(tokenizedVector[4], "from") || !strcmp(tokenizedVector[4], "delete") || !strcmp(tokenizedVector[4], "where")) {
							throw std::invalid_argument("Wrong column name or missing!");
						}
						else {
							if (strcmp(tokenizedVector[5], "=")) {
								throw std::invalid_argument("Missing equals operator or wrong position!");
							}
							else {
								if (vectorTypeOfToken[6] != dataTypeValues::string && vectorTypeOfToken[6] != dataTypeValues::number) {
									throw std::invalid_argument("Missing value or wrong type of value!");
								}
								else if (!strcmp(tokenizedVector[6], "from") || !strcmp(tokenizedVector[6], "delete") || !strcmp(tokenizedVector[6], "where")) {
									throw std::invalid_argument("Wrong name of column!");
								}
								else {
									if (strcmp(tokenizedVector[7], ";")) {
										throw std::invalid_argument("Function not ending with ';' or too many arguments");
									}
								}
							}
						}
					}
				}
			}
		}
		std::cout << "Command is correct!" << std::endl;
	}

	//INSERT INTO table VALUES(...);
	void lexerInsert() {
		int i = 1;
		int nrOfColumns = 0;
		if (strcmp(tokenizedVector[i], "into") || strcmp(tokenizedVector[sizeOfTokenizedVector-1],";") 
			|| strcmp(tokenizedVector[sizeOfTokenizedVector-2],")")) {
			throw;//check if second word is not INTO
		}
		else {
			if (vectorTypeOfToken[i + 1] != dataTypeValues::string) {
				throw; //check if the 3rd value is a table 
			}
			else if (!strcmp(tokenizedVector[i + 1], "insert") || !strcmp(tokenizedVector[i + 1], "into")) {
				throw; //check if there were no misspositionings;
			}
			else {
				if (strcmp(tokenizedVector[i+2], "values")) {
					throw;//check if syntax has values on 4th position
				}
				else {
					if (strcmp(tokenizedVector[i + 3], "(")) {
						throw; // check if we start with a paranthesis
					}
					else {
						if (vectorTypeOfToken[sizeOfTokenizedVector - 3] != dataTypeValues::number && strcmp("'", tokenizedVector[sizeOfTokenizedVector - 3])){
							throw;
						}
						for (int j = i + 4; j < sizeOfTokenizedVector - 4; j++) { // function to find all of the columns
							if (!strcmp(tokenizedVector[j],tokenizedVector[j-1])){
								throw; // case of , ,
							}
							if (!strcmp(tokenizedVector[j + 1], tokenizedVector[j])) {
								throw; // case of , ,
							}
							if (vectorTypeOfToken[j] == dataTypeValues::number || vectorTypeOfToken[j] == dataTypeValues::string) {
								nrOfColumns++;
							}
							if (vectorTypeOfToken[j] == dataTypeValues::number) {
								//verify for first value
								if (!strcmp(tokenizedVector[j - 1], "(")) {
									if (strcmp(tokenizedVector[j + 1], ",")) {
										throw;
									}
								}
								//verify middle value
								else if (!strcmp(tokenizedVector[j - 1], ",") && !strcmp(tokenizedVector[j + 1], ",")) {
									if (!(dataTypeValues::number == vectorTypeOfToken[j-2] && dataTypeValues::number == vectorTypeOfToken[j + 2]) && 
										!(dataTypeValues::number == vectorTypeOfToken[j-2] && !strcmp(tokenizedVector[j+2],"'")) &&
										!(dataTypeValues::number == vectorTypeOfToken[j+2] && !strcmp(tokenizedVector[j-2],"'")) &&
										(strcmp(tokenizedVector[j + 2], "'") && strcmp(tokenizedVector[j - 2], "'"))) {
										throw;
									}
								}
								//verify last value
								else if (!strcmp(tokenizedVector[j + 1], ")")) {
									if (strcmp(tokenizedVector[j - 1], ",")) {
										throw;
									}
									if (strcmp(tokenizedVector[j + 2], ";")) {
										throw;
									}
								}
								else {
									throw;
								}
							
							}
							if (vectorTypeOfToken[j] == dataTypeValues::string) {
								//verify first value
								if (!strcmp(tokenizedVector[j - 2], "(")) {
									if (strcmp(tokenizedVector[j + 2], ",")) {
										throw;
									}
									if (strcmp(tokenizedVector[j - 1], "'") || strcmp(tokenizedVector[j + 1], "'")) {
										throw;
									}
								}
								//verify middle value
								else if (!strcmp(tokenizedVector[j - 2], ",") && !strcmp(tokenizedVector[j + 2], ","))
								{
									if (strcmp(tokenizedVector[j + 1], "'") || strcmp(tokenizedVector[j - 1],"'")) {
										throw;
									}
									if (!(dataTypeValues::number == vectorTypeOfToken[j - 3] && dataTypeValues::number == vectorTypeOfToken[j + 3]) &&
										!(dataTypeValues::number == vectorTypeOfToken[j - 3] && !strcmp(tokenizedVector[j + 3], "'")) &&
										!(dataTypeValues::number == vectorTypeOfToken[j + 3] && !strcmp(tokenizedVector[j - 3], "'")) &&
										(strcmp(tokenizedVector[j + 3], "'") && strcmp(tokenizedVector[j - 3], "'"))) {
										throw;
									}
								}
								//verify last value
								else if (!strcmp(tokenizedVector[j + 2], ")")) {
									if (strcmp(tokenizedVector[j - 2], ",")) {
										throw;
									}
									if (strcmp(tokenizedVector[j + 3], ";")) {
										throw;
									}
									if (strcmp(tokenizedVector[j + 1], "'") || strcmp(tokenizedVector[j - 1], "'")) {
										throw;
									}
								}
								else {
									throw;
								}
							}
						}
					}
				}
			}
		}
	}

	void lexer()
	{
		// To add a lexer function for every command -----------------------------------------------------------------!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		if (strcmp(tokenizedVector[0], "create") == 0)
		{
			lexerCreateTable();
		}
		else if (strcmp(tokenizedVector[0], "display") == 0) {
			lexerDisplay();
		}
		else if (strcmp(tokenizedVector[0], "select") == 0) {
			lexerSelect();
		}
		else if (strcmp(tokenizedVector[0], "update") == 0) {
			lexerUpdate();
		}
		else if (strcmp(tokenizedVector[0], "select") == 0)
		{
			lexerSelect();
		}
		else if (strcmp(tokenizedVector[0], "delete") == 0)
		{
			lexerDelete();
		}
		else if (strcmp(tokenizedVector[0], "insert") == 0)
		{
			lexerInsert();
		}
		else throw std::invalid_argument("First token in the command is wrong"); // First word in the command is wrong

	}

	char* getToken(int iterator) {
		if (iterator <= sizeOfTokenizedVector)
		{
			return tokenizedVector[iterator];
		}
		else
		{
			return nullptr;
		}
	}

	int getTypeOfToken(int iterator) {
		if (iterator <= sizeOfTokenizedVector)
		{
			return vectorTypeOfToken[iterator];
		}
		else
		{
			return NULL;
		}
	}

	// Constructors
	Token(char** tokenizedVector, int sizeOfTokenizedVector, int* vectorTypeOfToken, std::string stringText = "", std::string stringType = "", unsigned int line = NULL, unsigned int column = NULL)
	{

		this->text = stringText;
		this->type = stringType;
		this->sizeOfTokenizedVector = sizeOfTokenizedVector;
		this->iterator = 0;
		if (tokenizedVector != nullptr)
		{
			this->tokenizedVector = new char* [sizeOfTokenizedVector];
			for (int i = 0; i < this->sizeOfTokenizedVector; i++)
			{
				this->tokenizedVector[i] = new char[strlen(tokenizedVector[i]) + 1];
				strcpy(this->tokenizedVector[i], tokenizedVector[i]);
			}
		}
		else
		{
			this->tokenizedVector = nullptr;
		}

		if (vectorTypeOfToken != nullptr)
		{
			this->vectorTypeOfToken = new int[sizeOfTokenizedVector];
			for (int i = 0; i < this->sizeOfTokenizedVector; i++)
			{
				this->vectorTypeOfToken[i] = vectorTypeOfToken[i];

			}
		}
		else
		{
			this->vectorTypeOfToken = nullptr;
		}
		this->line = line;
		this->column = column;


	}

	//Copy Constructor
	Token(const Token& t)
	{
		this->text = t.text;
		this->type = t.type;
		this->sizeOfTokenizedVector = t.sizeOfTokenizedVector;
		this->iterator = t.iterator;
		if (t.tokenizedVector != nullptr)
		{
			this->tokenizedVector = new char* [this->sizeOfTokenizedVector];
			for (int i = 0; i < this->sizeOfTokenizedVector; i++)
			{
				this->tokenizedVector[i] = new char[strlen(t.tokenizedVector[i]) + 1];
				strcpy(this->tokenizedVector[i], t.tokenizedVector[i]);
			}
		}
		else
		{
			this->tokenizedVector = nullptr;
		}

		if (t.vectorTypeOfToken != nullptr)
		{
			this->vectorTypeOfToken = new int[this->sizeOfTokenizedVector];
			for (int i = 0; i < this->sizeOfTokenizedVector; i++)
			{
				this->vectorTypeOfToken[i] = t.vectorTypeOfToken[i];
			}
		}
		else
		{
			this->vectorTypeOfToken = nullptr;
		}

		this->vectorTypeOfToken = t.vectorTypeOfToken;
		this->line = t.line;
		this->column = t.column;
	}

	// Destructors
	~Token() {
		// tokenizedVector
		for (int i = 0; i < this->sizeOfTokenizedVector; i++)
		{
			delete[] this->tokenizedVector[i];
		}
		delete[] this->tokenizedVector;
		this->tokenizedVector = nullptr;
		// vectorTypeOfToken
		delete[] this->vectorTypeOfToken;
		std::cout << "token object was destructed" << std::endl;
	}


};



// Functions -------------------------------------------------------------------------------------------

// Function for converting to lowerCase
std::string stringToLowerCase(std::string string) {
	std::transform(string.begin(), string.end(), string.begin(), ::tolower);
	return string;
}

// Function for inserting space  between operators and other arguments (ex: 12 +5 -> 12 + 5)

std::string insertingExtraSpacesforOperators(std::string string) {
	for (int i = 0; i < string.length(); i++)
	{
	

		if (string[i] == '+' || string[i] == '-' || string[i] == '*' || string[i] == '/' || string[i] == '=' || string[i] == '!=' || string[i] == '<' || string[i] == '>' || string[i] == '<=' || string[i] == '>=' || string[i] == '!<' || string[i] == '!>' || string[i] == '(' || string[i] == ')' || string[i] == ',' || string[i] == '&&' || string[i] == '||' || string[i] == '\'' || string[i] == ';')
		{
			if (string[i - 1] != ' ')
			{
				string.insert(i, " ");
			}
			if (string[i + 1] != ' ')
			{
				string.insert(i + 1, " ");
			}
			
		}
	}
	return string;
}

// Function for Deleting Extra Spaces
std::string deletingExtraSpacesString(std::string string) {
	for (int i = 0; i < string.length(); i++)
	{
		// Deleting extra spaces from the string (from the beginning and from the rest part of the string)
		while (string[0] == ' ')
		{
			string.erase(0, 1);
		}
		while (string[i] == string[i + 1] && string[i] == ' ')
		{
			string.erase(i + 1, 1);
		}
	}
	if (string[string.length() - 1] == ' ')
	{
		string.erase(string.length() - 1, 1);
	}
	return string;
}

// Function for computing neccesary memory for the future array of char pointers (char**)
int allocatingMemoryForCharArray(std::string string, char delimiter) {
	int contorWords = 0;
	int contorLetters = 0;
	int maxNoLetters = 0;
	// Computing the size of the tokenizedVector through getting the max size among all words and the number of words in string
	for (int i = 0; i < string.length(); i++)
	{
		// Computing the size of tokenizedVector
		if (string[i] == delimiter)
		{

			contorWords++;
			maxNoLetters = maxNoLetters < contorLetters ? contorLetters : maxNoLetters;
			contorLetters = 0;
		}
		else
		{
			contorLetters++;
		}

	}
	contorWords++;
	maxNoLetters = maxNoLetters < contorLetters ? contorLetters : maxNoLetters;
	
	return contorWords;
	
}

char** tokenizingStringIntoVector(int sizeOfTokenizedVector, std::string string, char delimiter) {
	int contorAux = 0;
	std::string tempString;
	char** arrayForChars = new char*[sizeOfTokenizedVector];
	for (int i = 0; i < string.length(); i++)
	{
		if (string[i] == delimiter)
		{
			arrayForChars[contorAux] = new char[tempString.length() + 1];
			strcpy(arrayForChars[contorAux++], tempString.c_str());
			tempString = "";
		}
		else {
			tempString += string[i];
		}
	}
	arrayForChars[contorAux] = new char[tempString.length() + 1];
	strcpy(arrayForChars[contorAux], tempString.c_str());

	return arrayForChars;
	

}

// Tokenizer function (function that separates words into an array of keywords)
char** tokenizingFunction(std::string string, int &sizeOfTokenizedVector, char delimiter) {
	
	// Converting string to LowerCase
	string = stringToLowerCase(string);

	// Inserting space  between operators and other arguments (ex: 12 +5 -> 12 + 5)
	string = insertingExtraSpacesforOperators(string);

	// Deleting extra spaces from the string (from the beginning and from the rest part of the string)
	string = deletingExtraSpacesString(string);

	// Computing and allocating memory for the tokenizing vector
	sizeOfTokenizedVector = allocatingMemoryForCharArray(string, delimiter);

	// Tokenizing the string by placing each word in the tokenizedVector array
	return tokenizingStringIntoVector(sizeOfTokenizedVector, string, delimiter);

};


int* identifyKeywordTypeVector(char** tokenizedVector, int sizeOfTokenizedVector) {
	// First allocating memory for vectorTypeOfToken
	int* vectorTypeOfToken = new int[sizeOfTokenizedVector];
	for (int i = 0; i < sizeOfTokenizedVector; i++)
	{
		vectorTypeOfToken[i] = -1; // default value for unfilled indexes
	}

	// For each token we allocate a type
	std::string tempString;
	for (int i = 0; i < sizeOfTokenizedVector; i++)
	{
		tempString = tokenizedVector[i];

		// Checking if token is a command 
		if (tempString == "create") vectorTypeOfToken[i] = typeCommands::create;
		if (tempString == "alter") vectorTypeOfToken[i] = typeCommands::alter;
		if (tempString == "drop") vectorTypeOfToken[i] = typeCommands::drop;
		if (tempString == "select") vectorTypeOfToken[i] = typeCommands::select;
		if (tempString == "delete") vectorTypeOfToken[i] = typeCommands::delete_;
		if (tempString == "insert") vectorTypeOfToken[i] = typeCommands::insert;
		if (tempString == "update") vectorTypeOfToken[i] = typeCommands::update;
		if (tempString == "commit") vectorTypeOfToken[i] = typeCommands::commit;
		if (tempString == "rollback") vectorTypeOfToken[i] = typeCommands::rollback;
		if (tempString == "savepoint") vectorTypeOfToken[i] = typeCommands::savepoint;
		if (tempString == "grant") vectorTypeOfToken[i] = typeCommands::grant;
		if (tempString == "revoke") vectorTypeOfToken[i] = typeCommands::revoke;
		if (tempString == "table") vectorTypeOfToken[i] = typeCommands::table;
		if (tempString == "index") vectorTypeOfToken[i] = typeCommands::index;
		if (tempString == "if") vectorTypeOfToken[i] = typeCommands::IF;
		if (tempString == "where") vectorTypeOfToken[i] = typeCommands::where;
		if (tempString == "set") vectorTypeOfToken[i] = typeCommands::set;

		// if not a command, we check if the token is an operator
		if (tempString == "+") vectorTypeOfToken[i] = typeOperators::add;
		if (tempString == "-") vectorTypeOfToken[i] = typeOperators::sub;
		if (tempString == "*") vectorTypeOfToken[i] = typeOperators::mul;
		if (tempString == "/") vectorTypeOfToken[i] = typeOperators::div_;
		if (tempString == "%") vectorTypeOfToken[i] = typeOperators::mod;
		if (tempString == "=") vectorTypeOfToken[i] = typeOperators::equals;
		if (tempString == "!=") vectorTypeOfToken[i] = typeOperators::notEqual;
		if (tempString == ">") vectorTypeOfToken[i] = typeOperators::greater;
		if (tempString == "<") vectorTypeOfToken[i] = typeOperators::less;
		if (tempString == "<") vectorTypeOfToken[i] = typeOperators::less;
		if (tempString == "<=") vectorTypeOfToken[i] = typeOperators::lessEqual;
		if (tempString == ">=") vectorTypeOfToken[i] = typeOperators::greaterEqual;
		if (tempString == "!<") vectorTypeOfToken[i] = typeOperators::notLess;
		if (tempString == "!>") vectorTypeOfToken[i] = typeOperators::notGreater;
		if (tempString == "!>") vectorTypeOfToken[i] = typeOperators::notGreater;
		if (tempString == "and") vectorTypeOfToken[i] = typeOperators::and_;
		if (tempString == "&&") vectorTypeOfToken[i] = typeOperators::and_;
		if (tempString == "between") vectorTypeOfToken[i] = typeOperators::between;
		if (tempString == "exists") vectorTypeOfToken[i] = typeOperators::exists;
		if (tempString == "notIn") vectorTypeOfToken[i] = typeOperators::notIn;
		if (tempString == "like") vectorTypeOfToken[i] = typeOperators::like;
		if (tempString == "glob") vectorTypeOfToken[i] = typeOperators::glob;
		if (tempString == "not") vectorTypeOfToken[i] = typeOperators::not_;
		if (tempString == "or") vectorTypeOfToken[i] = typeOperators::or_;
		if (tempString == "isnull") vectorTypeOfToken[i] = typeOperators::isNull;
		if (tempString == "||") vectorTypeOfToken[i] = typeOperators::addStrings;
		if (tempString == "unique") vectorTypeOfToken[i] = typeOperators::unique;
		if (tempString == "(") vectorTypeOfToken[i] = typeOperators::l_parentheses;
		if (tempString == ")") vectorTypeOfToken[i] = typeOperators::r_parentheses;
		if (tempString == "if") vectorTypeOfToken[i] = typeCommands::IF;

		// if not previous 2 we check if the token is a data type identifier
		std::string tempPartialString;
		int j = 0;
		// Checking only the type without its parameters (ex. varchar2 instead of the passed token varchar2(20) etc.)
		while ( j  < tempString.length() && tempString[j] != '(')
		{
			tempPartialString += tempString[j++];
		}
		if (tempPartialString == "text") vectorTypeOfToken[i] = typeDataType::text;
		if (tempPartialString == "integer") vectorTypeOfToken[i] = typeDataType::integer;
		

		// if not even one of the 3 listed above, then it should be an indentifier, it will be marked with -1 in out vectorTypeOfToken
		if (vectorTypeOfToken[i] < 0)
		{
			// Getting the type of the identifier (VARCHAR2 | INT | FLOAT)
			bool intBool = true, floatBool = true, varchar2Bool = true;
			for (int i = 0; i < tempString.length(); i++)
			{
				//ASCII
				// if the element is not a digit or - or .
				if ((tempString[i] < 48 || tempString[i] > 57 ) && tempString[i] != '-' && tempString[i] != '.')
				{ 
					intBool = false;
					floatBool = false;
					// if the element is not a letter or an underscore
					if ((tempString[i] < 97 || tempString[i] > 122) && tempString[i] != '_')
					{
						varchar2Bool = false;
					}
				}
				// if the number is a float
				else if(tempString[i] == '.')
				{
					intBool = false;
					varchar2Bool = false;
				}
				
			}
			// if the dot wasn t located, then we don t have a float
			
			if (intBool)
			{ 
				floatBool = false;
				varchar2Bool = false;
			}
			if (intBool) vectorTypeOfToken[i] = NUMBER;
			if (floatBool) vectorTypeOfToken[i] = NUMBER;
			if (varchar2Bool) vectorTypeOfToken[i] = TEXT;
		}

	}
	return vectorTypeOfToken;
}

// Function for looping through command line 
// I: Entire command line (string)
// E: -
void loopingThroughCommands(std::string commandLine) {
	int i = 0;
	int sizeOfTokenizedVector = NULL;
	char** tokenizedVector = nullptr;
	int* vectorTypeOfToken = nullptr;
	while (i < commandLine.length())
	{
		if (commandLine[i] == ';')
		{
			if (tokenizedVector != nullptr)
			{
				for (int i = 0; i < sizeOfTokenizedVector; i++)
				{
					delete[] tokenizedVector[i];
				}
				delete[] tokenizedVector;
				tokenizedVector = nullptr;
			}
			tokenizedVector = tokenizingFunction(commandLine.substr(0, i + 1), sizeOfTokenizedVector, ' ');
			if (vectorTypeOfToken != nullptr)
			{
				delete[] vectorTypeOfToken;
				vectorTypeOfToken = nullptr;
			}
			vectorTypeOfToken = identifyKeywordTypeVector(tokenizedVector, sizeOfTokenizedVector);
			for (int i = 0; i < sizeOfTokenizedVector; i++)
			{
				std::cout << tokenizedVector[i] << "   ||   " << vectorTypeOfToken[i] << std::endl;
			}
			Token token(tokenizedVector, sizeOfTokenizedVector, vectorTypeOfToken);
			token.parser();
			commandLine = commandLine.substr(i + 1);
			std::cout << std::endl << std::endl << std::endl;
			i = 0;
		}
		else
		{
			i++;

		}
	}
	if (tokenizedVector != nullptr)
	{
		for (int i = 0; i < sizeOfTokenizedVector; i++)
		{
			delete[] tokenizedVector[i];
		}
		delete[] tokenizedVector;
		tokenizedVector = nullptr;
	}

	if (vectorTypeOfToken != nullptr)
	{
		delete[] vectorTypeOfToken;
		vectorTypeOfToken = nullptr;
	}



}
