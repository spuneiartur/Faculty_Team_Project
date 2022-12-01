#pragma once

int TEXT = -5;
int NUMBER = -10;


enum commandBranches {
	createTable, createIndex, typeDataType, argString, argNumber
};

enum typeCommands {
	create, alter, drop, select, delete_, insert, update, commit, rollback, savepoint, grant, revoke, table, index, where, set, IF , ON
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

	void lexerCreateTable() {
		int i = 1;
		if (!strcmp(tokenizedVector[i], "table") && vectorTypeOfToken[i + 1] == dataTypeValues::string) {
			i++;
			if (vectorTypeOfToken[i] == dataTypeValues::string) { // if token is an identifier 
				i++;

				if ( strcmp(tokenizedVector[i], "(") == 0) { // if token is an identifier and next token is a paranthesis
				}
				else if (strcmp(tokenizedVector[i], "if") == 0 && strcmp(tokenizedVector[i + 1], "not") == 0 && strcmp(tokenizedVector[i + 2], "exists") == 0)
				{
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

								if (vectorTypeOfToken[i + 5] != dataTypeValues::number) throw;

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
			if(strcmp(tokenizedVector[i],";") < 0) throw std::invalid_argument("Unexpected tokens after \")\"");

			std::cout << "the command is correct!" << std::endl;
		}
		else throw std::invalid_argument("Unexpected token at position iterator+1; Non compatible with token \"CREATE\". Expected token \"Table\" or \"Index\"");
		
	}

	void lexerCreateIndex() {
		//if (strcmp(tokenizedVector[0], "createtable") == 0) {				//NU IESE ORICUM DIN LEXERUL NORMAL
		//	throw; //wrong keywords
		//}
		int i = 2;		
		if (vectorTypeOfToken[i] == dataTypeValues::string) 
			i++;
		else if (strcmp(tokenizedVector[i], "if") == 0 && strcmp(tokenizedVector[i + 1], "not") == 0 && strcmp(tokenizedVector[i + 2], "exists") == 0)
		{
			i += 3;
			if (vectorTypeOfToken[i] == dataTypeValues::string) {
				i++;
			}
			else throw; // index_name nu este corect dupa IF NOT EXISTS
		}		
		else throw std::invalid_argument("Unexpected token at position iterator+1; Expected token \"()\" or \"IF NOT EXISTS\"");
			 
		if (strcmp(tokenizedVector[i], "on") == 0) {			//ON
			i++;
		}
		else throw;
		if (vectorTypeOfToken[i] == dataTypeValues::string) {	//table_name   //also have to check if the table is valid
			i++;
		}
		else throw;

		if (strcmp(tokenizedVector[i], "(") == 0) {
			i++;
		}
		else throw; //nu se deschide paranteza

		if (vectorTypeOfToken[i] == dataTypeValues::string) {	//column_name	//also have to check if column is valid
			i++;
		}
		else throw; //nu este cuvantul valid

		if (strcmp(tokenizedVector[i], ",") == 0) {
			throw; //too many arguments
		}

		if (vectorTypeOfToken[i] == dataTypeValues::string) {
			throw; //invalid coolumn name
		}

		if (strcmp(tokenizedVector[i], ")") == 0) {
			i++;
		}
		else throw; //nu se inchide paranteza


		if (strcmp(tokenizedVector[i], ";") != 0) {
			throw; // nu s-a pus ; la finalul comenzii
		}
	}

	void lexerDropTable() {
		int i = 2;
		//if (strcmp(tokenizedVector[0], "droptable") == 0) {				//NU IESE ORICUM DIN LEXERUL NORMAL
		//	throw; //wrong keywords
		//}		
		if (vectorTypeOfToken[i] == dataTypeValues::string) {	//table_name   //also have to check if the table exists
			i++;
		}
		else throw; // missing table name
		if (strcmp(tokenizedVector[i], ",") == 0) {
			throw; // too many table names
		}
		if (vectorTypeOfToken[i] == dataTypeValues::string) {	
			throw; //wrong table name - has space
		}
		if (strcmp(tokenizedVector[i], ";") != 0) {
			throw; // nu s-a pus ; la finalul comenzii
		}
	}


	void lexerDropIndex() {
		int i = 2;
		//if (strcmp(tokenizedVector[0], "dropindex") == 0) {				//NU IESE ORICUM DIN LEXERUL NORMAL
		//	throw; //wrong keywords
		//}
		if (vectorTypeOfToken[i] == dataTypeValues::string) {	//index_name   //also have to check if the index exists
			i++;
		}
		else throw; //missing index name
		if (strcmp(tokenizedVector[i], ",") == 0) {
			throw; // too many index names
		}
		if (vectorTypeOfToken[i] == dataTypeValues::string) {
			throw; //wrong index name - has space
		}
		if (strcmp(tokenizedVector[i], ";") != 0) {
			throw; // nu s-a pus ; la finalul comenzii
		}
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

		if(strcmp(tokenizedVector[i], "where") < 0) throw std::invalid_argument("Unexpected token at position iterator; Expected token \"where\"");

		i++;

		checkingLexerOfEquality(i); // Checks this syntax of this type: id = 5 || name = 'Alex'

		if(strcmp(tokenizedVector[i], ";") <0) throw std::invalid_argument("Too many arguments after WHERE or Missing token \";\"");

		std::cout << "The command is correct!" << std::endl;





	}


	void lexerSelect(){
		int i = 0;
		int k;
		int nrColumns = 1; // we must have one column
		if (strcmp(tokenizedVector[i], "select") && vectorTypeOfToken[i + 1] == dataTypeValues::string) { // verifiy for a basic SELECT value
			for (int j = i; j < sizeOfTokenizedVector; j++) { // find all of the columns by adding all of the apperances of "," 
				if (strcmp(tokenizedVector[j], ",")) {
					nrColumns++;
				}else if(tokenizedVector[j]=="FROM") {
					k = j;	// we find the position at which FROM is to use later on
					if (tokenizedVector[j] != "FROM") {
						throw; // in case our command has no FROM we throw and error
					}
				}
			}
			if (nrColumns == 1) { // if columns are equal to one we first check if we want all from the table or if we want one columns since they are both equal to 1 in the code
				if (strcmp(tokenizedVector[i + 1], "ALL") || strcmp(tokenizedVector[i + 1], "*")) {
					if (!strcmp(tokenizedVector[i + 2], tokenizedVector[k])) {
						throw; // SELECT ALL FROM syntax is wrongly written
					}
					else if(vectorTypeOfToken[i+3]!=dataTypeValues::string) {
						throw; // if the 4th place is not a string value , the name of the table we throw error
					}
				}
				else if(vectorTypeOfToken[i + 1] == dataTypeValues::string){ // check if we just want to take a column and if its not a column we throw
					if (!strcmp(tokenizedVector[i + 2], tokenizedVector[k])) {
						throw; // SELECT value FROM syntax is wrongly written
					}
					else if (vectorTypeOfToken[i + 3] != dataTypeValues::string) {
						throw; // if the 4th place is not a string value , the name of the table we throw error
					}
				}
			}// now we check if we want to select more tables
			else if(nrColumns > 1){
				if (!strcmp(tokenizedVector[k], "FROM")) {
					throw;
				}
				else {
					for (int n = 1; n < k; n++) {
						if (strcmp(tokenizedVector[n], ",")) {
							if (!(vectorTypeOfToken[n - 1]==dataTypeValues::string)) { // check if the value before the "," is a string
								throw;
							}
						}
						else {
							throw;
						}
					}
					if (vectorTypeOfToken[k + 1] != dataTypeValues::string) { //check if we have something after FROM and that it is a string
						throw;
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
			if (strcmp(tokenizedVector[1], "table") == 0) {
				lexerCreateTable();
			}
			else if (strcmp(tokenizedVector[1], "index") == 0) {
				lexerCreateIndex();
			}
			else throw;
		}
		else if (strcmp(tokenizedVector[0], "update") == 0) {
			lexerUpdate();
		}
		else if (strcmp(tokenizedVector[0], "select") == 0)
		{
			lexerSelect();
		}
		else if(strcmp(tokenizedVector[0], "drop") == 0)
		{
			if (strcmp(tokenizedVector[1], "table") == 0) {
				lexerDropTable();
			}
			else if (strcmp(tokenizedVector[1], "index") == 0) {
				lexerDropIndex();
			}
			else throw;   //second word is not correct
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


class Table {
private:
	char* name;
	int noColumns;
	int noLines;

public:
	// Methods
	void setData(int noColumns, int noLines, char* name = nullptr) {
		if (this->name != nullptr)
		{
			delete[] this->name;
			this->name = nullptr;
		}
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
		this->noLines = noLines;
	}

	//Constructors
	Table() {
		 this->name = nullptr;
		 this->noColumns= NULL;
		 this->noLines = NULL;
	}
	Table(int noColumns, int noLines, char* name = nullptr) {
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
		this->noLines = noLines;

	}
	 // Copy constructor
	Table(const Table& t) {
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
		this->noLines = t.noLines;
	}
	//Destructor
	~Table() {
		if (this->name != nullptr)
		{
			delete[] this->name;
			this->name = nullptr;
		}
	}
};

//
//class lexer : public Token {
//private:
//	int iterator = -1; // ??
//public:
//	// Constructors
//
//	//Destructors
//	~lexer() {
//		std::cout << "Lexer object was destructed!" << std::endl;
//	}
//
//	void parsingTokenizedVector() {
//		getToken();
//		verifyCompatibilityForNextArg();
//	}
//
//	void getToken()
//	{
//		this->iterator++;
//	};
//
//	void verifyCompatibilityForNextArg()
//	{
//
//	};
//	// create_arg() - create table for ex
//};
//


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
int allocatingMemoryForCharArray( std::string string, char delimiter) {
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

