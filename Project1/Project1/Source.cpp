#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>

// Deallocation - Do no forget:
// tokenizedVector

// Verifying if git is working



class token {
	std::string stringInput = "";
	char delimiter;
	// Methods
	
};

// Function for Deleting Extra Spaces
std::string deletingExtraSpacesString (std::string string) {
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
	if (string[string.length()-1] == ' ')
	{
		string.erase(string.length()-1, 1);
	}
	return string;
}

// Function for computing neccesary memory for the future array of char pointers (char**)
char** allocatingMemoryForCharArray(char** array, std::string string, char delimiter, int &sizeOfVector) {
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


	// Allocating the previous computed memory to out vector of chars
	array = new char* [contorWords];
	for (int i = 0; i < contorWords; i++)
	{
		array[i] = new char[contorLetters + 1];
	}
	sizeOfVector = contorWords;
	return array;
}

char** tokenizingStringIntoVector(char** array, std::string string, char delimiter) {
	int contorAux = 0;
	std::string tempString;
	for (int i = 0; i < string.length(); i++)
	{
		if (string[i] == delimiter)
		{
			strcpy(array[contorAux++], tempString.c_str());
			tempString = "";
		}
		else {
			tempString += string[i];
		}
	}
	strcpy(array[contorAux], tempString.c_str());

	return array;

}

// Tokenizer function (function that separates words into an array of keywords)
char** tokenizingFunction(std::string string, char delimiter, int& sizeOfVector) {
	
	char** tokenizedVector = nullptr;

	// Deleting extra spaces from the string (from the beginning and from the rest part of the string)
	string = deletingExtraSpacesString(string);

	// Computing and allocating memory for the tokenizing vector
	tokenizedVector = allocatingMemoryForCharArray(tokenizedVector, string, delimiter, sizeOfVector);

	// Tokenizing the string by placing each word in the tokenizedVector array
	tokenizedVector = tokenizingStringIntoVector(tokenizedVector, string, delimiter);

	return tokenizedVector;
	
};



int main()
{
	int sizeOfVector;
	char** tokenizedVector = tokenizingFunction("   we will see how to    remove some   spaces from a   string     ", ' ', sizeOfVector);

	for (int i = 0; i< sizeOfVector; i++)
	{
		std::cout << tokenizedVector[i] << std::endl;
	}

	/*std::cout <<  tokenizedVector[0];*/
	return 0;
}


// DROP TABLE table_name
//   we will see how to    remove some   spaces from a   string   