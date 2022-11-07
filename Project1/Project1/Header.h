#pragma once

enum typesOfToken {
	typeCommands, typeOperators, typeDataType, argString, argNumber
};

enum typeCommands {
	create, alter, drop, select, delete_, insert, update, commit, rollback, savepoint, grant, revoke, table, index
};

enum typeOperators {
	add = '+', sub = '-', mul = '*', div_ = '/', mod = '%', equals = '=', notEqual = '!=', greater = '>', less = '<', greaterEqual = '>=', lessEqual = '<=', notLess = '!<', notGreater = '!>', and_, between, exists, in, notIn, like, glob, not_, or_, isNull, addStrings = '||', unique, l_parentheses = '(', r_parentheses = ')', asterix = '*'
};

enum typeDataType {
	varchar2 = typeCommands::revoke + 1, number, long_, date, raw, long_raw, rowid, char_, blob, bfile
};
// TODO
// TO CREATE A =DEEP COPY, NOT A SHALLOW ONE in the class token of the vector vectorTypeOfToken
// To modify tokenizedVecctor from dinamically allocated to statically
// 
// Classes -------------------------------------------------------------------------------------------
//class token {
//private:
//	std::string text;
//	std::string type;
//	char** tokenizedVector;
//	int sizeOfTokenizedVector;
//	int* vectorTypeOfToken;
//	unsigned int line;
//	unsigned int column;
//
//
//public:
//
//	// Constructors
//	token(char** tokenizedVector, int sizeOfTokenizedVector, int* vectorTypeOfToken, std::string stringText = "", std::string stringType = "", unsigned int line = NULL, unsigned int column = NULL)
//	{
//		this->text = stringText;
//		this->type = stringType;
//		this->sizeOfTokenizedVector = sizeOfTokenizedVector;
//		if (tokenizedVector != nullptr)
//		{
//			this->tokenizedVector = new char*[sizeOfTokenizedVector];
//			for (int i = 0; i < this->sizeOfTokenizedVector; i++)
//			{
//				this->tokenizedVector[i] = new char[strlen(tokenizedVector[i]) + 1];
//				strcpy(this->tokenizedVector[i], tokenizedVector[i]);
//			}
//		}
//		else
//		{
//			this->tokenizedVector = nullptr;
//		}
//
//		if (vectorTypeOfToken != nullptr)
//		{
//			this->vectorTypeOfToken = new int[sizeOfTokenizedVector];
//			for (int i = 0; i < this->sizeOfTokenizedVector; i++)
//			{
//				this->vectorTypeOfToken[i] = vectorTypeOfToken[i];
//
//			}
//		}
//		else
//		{
//			this->vectorTypeOfToken = nullptr;
//		}
//		this->line = line;
//		this->column = column;
//
//
//	}
//
//	//Copy Constructor
//	token(const token& t)
//	{
//		this->text = t.text;
//		this->type = t.type;
//		this->sizeOfTokenizedVector = t.sizeOfTokenizedVector;
//
//		if (t.tokenizedVector != nullptr)
//		{
//			this->tokenizedVector = new char* [this->sizeOfTokenizedVector];
//			for (int i = 0; i < this->sizeOfTokenizedVector; i++)
//			{
//				this->tokenizedVector[i] = new char[strlen(t.tokenizedVector[i]) + 1];
//				strcpy(this->tokenizedVector[i], t.tokenizedVector[i]);
//			}
//		}
//		else
//		{
//			this->tokenizedVector = nullptr;
//		}
//
//		if (t.vectorTypeOfToken != nullptr)
//		{
//			this->vectorTypeOfToken = new int[this->sizeOfTokenizedVector];
//			for (int i = 0; i < this->sizeOfTokenizedVector; i++)
//			{
//				this->vectorTypeOfToken[i] = t.vectorTypeOfToken[i];
//			}
//		}
//		else
//		{
//			this->vectorTypeOfToken = nullptr;
//		}
//
//		this->vectorTypeOfToken = t.vectorTypeOfToken; 
//		this->line = t.line;
//		this->column = t.column;
//	}
//
//	// Destructors
//	~token() {
//		for (int i = 0; i < this->sizeOfTokenizedVector; i++)
//		{
//			delete[] this->tokenizedVector[i];
//		}
//		delete[] this->tokenizedVector;
//		this->tokenizedVector = nullptr;
//
//		delete[] this->vectorTypeOfToken;
//		std::cout << "token object was destructed" << std::endl;
//	}
//	// Methods
//
//	// // Getters
//	void getVectorTypeOfTokenValues() {
//		if (vectorTypeOfToken != nullptr)
//		{
//			for (int i = 0; i < this->sizeOfTokenizedVector; i++)
//			{
//				std::cout << this->vectorTypeOfToken[i] << " | ";
//			}
//			std::cout << std::endl;
//		}
//		else {
//			throw;
//		}
//	}
//
//	// // Setters
//
//
//
//
//
//
//
//
//};
////
////class lexer : public token {
////private:
////	int iterator = -1; // ??
////public:
////	// Constructors
////
////	//Destructors
////	~lexer() {
////		std::cout << "Lexer object was destructed!" << std::endl;
////	}
////
////	void parsingTokenizedVector() {
////		getToken();
////		verifyCompatibilityForNextArg();
////	}
////
////	void getToken()
////	{
////		this->iterator++;
////	};
////
////	void verifyCompatibilityForNextArg()
////	{
////
////	};
////	// create_arg() - create table for ex
////};
////
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
		if (string[i] == '+' || string[i] == '-' || string[i] == '*' || string[i] == '/' || string[i] == '=' || string[i] == '!=' || string[i] == '<' || string[i] == '>' || string[i] == '<=' || string[i] == '>=' || string[i] == '!<' || string[i] == '!>' || string[i] == '(' || string[i] == ')' || string[i] == '*' || string[i] == '&&' || string[i] == '||')
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
		if (tempString == "isnull") vectorTypeOfToken[i] = typeOperators::isNull;
		if (tempString == "||") vectorTypeOfToken[i] = typeOperators::addStrings;
		if (tempString == "unique") vectorTypeOfToken[i] = typeOperators::unique;
		if (tempString == "unique") vectorTypeOfToken[i] = typeOperators::unique;
		if (tempString == "(") vectorTypeOfToken[i] = typeOperators::l_parentheses;
		if (tempString == ")") vectorTypeOfToken[i] = typeOperators::r_parentheses;

		// if not previous 2 we check if the token is a data type identifier
		if (tempString == "varchar2") vectorTypeOfToken[i] = typeDataType::varchar2;
		if (tempString == "number") vectorTypeOfToken[i] = typeDataType::number;
		if (tempString == "long") vectorTypeOfToken[i] = typeDataType::long_;
		if (tempString == "date") vectorTypeOfToken[i] = typeDataType::date;
		if (tempString == "raw") vectorTypeOfToken[i] = typeDataType::raw;
		if (tempString == "long_raw") vectorTypeOfToken[i] = typeDataType::long_raw;
		if (tempString == "rowid") vectorTypeOfToken[i] = typeDataType::rowid;
		if (tempString == "char") vectorTypeOfToken[i] = typeDataType::char_;
		if (tempString == "blob") vectorTypeOfToken[i] = typeDataType::blob;
		if (tempString == "bfile") vectorTypeOfToken[i] = typeDataType::bfile;

		// if not even one of the 3 listed above, then it should be an indentifier, it will be marked with -1 in out vectorTypeOfToken

	}
	return vectorTypeOfToken;
}
