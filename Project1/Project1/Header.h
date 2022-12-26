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
	static int noOfTables; // it starts with 0 !!!
	static Table tables[100];

public:
	// Methods
	
	// Reading from text file listOfTables.txt the list of all tables
	static void processingDbData()
	{
		std::ifstream iFile("listOfTables.txt");

		if (!iFile)
		{
			return;
		}

		std::string s;
		noOfTables = -1;
		while (iFile >> s)
		{
			tables[++noOfTables].setByReadingFromFileDB(s.c_str());
		}


		iFile.close();

	}

	// Writing into files the names of all existing tables
	static void updatingListOfTables()
	{
		std::ofstream oFile("listOfTables.txt");

		for (int i = 0; i <= noOfTables; i++)
		{
			oFile << tables[i].name << std::endl;
		}

		oFile.close();
	}

	void setByReadingFromFileDB(const char* fName)
	{
		
		bool existsCopy = false;
		char* nameCopy = nullptr;
		int noColumnsCopy;
		std::string* vNamesCopy = nullptr;
		std::string* vTypesCopy = nullptr;
		int* vDimensionsCopy = nullptr;
		std::string* vDefaultsCopy = nullptr;
		int noDataCopy;
		std::string** mDataCopy = nullptr;

		std::ifstream iFile(fName);


		iFile >> existsCopy;

		if (!iFile) return;

		iFile >> noColumnsCopy;
		vNamesCopy = new std::string[noColumnsCopy];
		for (int i = 0; i < noColumnsCopy; i++)
		{
			iFile >> vNamesCopy[i];
		}

		vTypesCopy = new std::string[noColumnsCopy];
		for (int i = 0; i < noColumnsCopy; i++)
		{
			iFile >> vTypesCopy[i];
		}

		vDimensionsCopy = new int[noColumnsCopy];
		for (int i = 0; i < noColumnsCopy; i++)
		{
			iFile >> vDimensionsCopy[i];
		}

		vDefaultsCopy = new std::string[noColumnsCopy];
		for (int i = 0; i < noColumnsCopy; i++)
		{
			
			iFile >> vDefaultsCopy[i];
			if (vDefaultsCopy[i] == "$space") vDefaultsCopy[i] = "";

		}

		iFile >> noDataCopy;


		mDataCopy = new std::string*[noDataCopy];
		for (int i = 0; i < noDataCopy; i++)
		{
			mDataCopy[i] = new std::string[noColumnsCopy];

		}

		for (int i = 0; i < noDataCopy; i++)
		{
			for (int j = 0; j < noColumnsCopy; j++)
			{
				iFile >> mDataCopy[i][j];
			}
		}


		//========------------------------------------------Complete with seting the table with the read values !!!!!!!!!!!!!!!!!!!--------------------------==============

		Table tempTable(nameCopy, noColumnsCopy, vNamesCopy, vTypesCopy, vDimensionsCopy, vDefaultsCopy, noDataCopy, mDataCopy);
		*this = tempTable;

		iFile.close();


		// Deleting all dinamically alocated arrays
		delete[] vNamesCopy;
		vNamesCopy = nullptr;

		delete[] vTypesCopy;
		vTypesCopy = nullptr;

		delete[] vDimensionsCopy;
		vDimensionsCopy = nullptr;

		delete[] vDefaultsCopy;
		vDefaultsCopy = nullptr;

	}

	void writingTableToFileDB()
	{
		std::ofstream oFile(this->name);
		//bool - exists or not
		oFile << this->exists << std::endl;
		//noColumns
		oFile << this->noColumns << std::endl;
		// vNames
		for (int i = 0; i < noColumns; i++)
		{
			oFile << vNames[i] << " ";
		}
		oFile << std::endl;
		// vTypes
		for (int i = 0; i < noColumns; i++)
		{
			oFile << vTypes[i] << " ";
		}
		oFile << std::endl;
		// vDimensions
		for (int i = 0; i < noColumns; i++)
		{
			oFile << vDimensions[i] << " ";
		}
		oFile << std::endl;
		// vDefaults
		for (int i = 0; i < noColumns; i++)
		{
			if (vDefaults[i] == " " || vDefaults[i] == "")
			{
				oFile << "$space" << " ";
			}
			else
			{
				oFile << vDefaults[i] << " ";
			}
		}
		oFile << std::endl;
		// noData
		oFile << this->noData << std::endl;
		// mData
		for (int i = 0; i < noData; i++) {
			for (int j = 0; j < noColumns; j++)
			{
				oFile << this->mData[i][j] << " ";
			}
			oFile << std::endl;
		}
		// noOfTables
		oFile << noOfTables << std::endl;

		oFile.close();

	}


	// I: table name
	// E: table index
	static void dropTable(char* nume) {
		int poz = -1;
		for (int i = 0; i <= noOfTables && poz==-1; i++) {
			if (strcmp(tables[i].name, nume) == 0) {
				poz = i;
			}

			for (int i = poz; i < noOfTables; i++) {
				tables[i] = tables[i + 1];
				if (i + 1 == noOfTables) {
					tables[i + 1].setToInexistent();
				}
			}
			i--;
			noOfTables--;
		}
		
		
	}


	static Table& findTableByName(char* name) {
		for (int i = 0; i <= noOfTables; i++)
		{
			if (strcmp(tables[i].name, name) == 0 && tables[i].exists) return tables[i];
		}
		throw std::invalid_argument("Table with such a name does not exists; Please input a name for existing table");
			
	}
	
	void updateTable(std::string columnNameChange, std::string valueChange, std::string columnNameCondition, std::string valueCondition) {
		// Check if both columns exist
		int checkCond = 0, posOfColumnCondition;
		int checkChange = 0, posOfColumnChange;
		if(columnNameChange == columnNameCondition) throw std::invalid_argument("The condition column and the column to be changed must be different ");
		for (int i = 0; i < noColumns; i++)
		{
			if (vNames[i] == columnNameCondition) { checkCond++; posOfColumnCondition = i; }
			if (vNames[i] == columnNameChange) { checkChange++; posOfColumnChange = i; }
		}
		if (checkChange == 0 || checkCond == 0)
		{
			throw std::invalid_argument("Such a column does not exist. Please input a valid names for columns ");
		}
		if (noData == 0)
		{
			std::cout << "The table has no data. Nothing has changed." << std::endl;
			return;
		}
		else
		{	
			for (int i = 0; i < noData; i++)
			{
				if (mData[i][posOfColumnCondition] == valueCondition)
				{
					mData[i][posOfColumnChange] = valueChange;
				}
				
			}
		}
		std::cout << std::endl << "Table updated" << std::endl;
		 
	}

	void setToInexistent() {
		this->exists = false;
	}

	char* getTableName() {
		char* nameCopy = new char[strlen(this->name)+1];
		strcpy(nameCopy, this->name);
		return nameCopy;
	}

	std::string getColumnNameByIndex(int index)
	{
		return this->vNames[index];
	}

	std::string getColumnTypeByIndex(int index)
	{
		return this->vTypes[index];
	}

	int getColumnDimensionByIndex(int index)
	{
		return this->vDimensions[index];
	}

	std::string getColumnDefaultValueByIndex(int index)
	{
		return this->vDefaults[index];
	}

	static void createTable(char* name, int noColumns, std::string* vNames, std::string* vTypes, int* vDimensions, std::string* vDefaults, bool checkIfExists = false) {

		if (checkIfExists)
		{
			for (int i = 0; i <= noOfTables; i++)
			{
				
				if (strcmp(tables[i].name, name) == 0)
				{
					throw std::invalid_argument("A table with such name already exists");
				}
			}
		}
		/*if(tables[noOfTables + 1].getExistitngStatus() == false)*/
		if (noOfTables == 99) throw std::invalid_argument("To many tables; Your data base may contain max 100 tables");
		tables[++noOfTables] = { Table(name, noColumns, vNames, vTypes, vDimensions, vDefaults) };
		// Checking the name of all existing tables
		/*for (int i = 0; i <= noOfTables; i++)
		{
			std::cout << tables[i].name << std::endl;
		}*/
	}
	bool getExistitngStatus()
	{
		return this->exists;
	}
	void insertRow(std::string* row) {
		//mdata = datele sub forma de string
		//nodata = nr de randuri
		//nocolumns = nr de coloane
		//i different data i = noData
		//j have the same type of data j = noColumns
		//create a deep copy and increment the nodata to add the new row inserted

		this->noData += 1;
		if (noData == 1)
		{
			mData = new std::string * [this->noData];
			for (int i = 0; i < this->noData; ++i) {
				mData[i] = new std::string[this->noColumns];
			}
			//insert in the new row;
			for (int j = 0; j < this->noColumns; j++) {
				mData[this->noData - 1][j] = row[j];
			}
		}
		else
		{
		std::string** mDataCopy = new std::string*[this->noData-1];
		for (int i = 0; i < this->noData-1; ++i) {
			mDataCopy[i] = new std::string[this->noColumns];
		}
		//deep copy with new values
		for (int i = 0; i < this->noData - 1; i++) {
			for (int j = 0; j < this->noColumns; j++) {
				mDataCopy[i][j] = mData[i][j];
			}
		}

		//delete previous table
		for (int i = 0; i < this->noData-1; ++i)
			delete[] mData[i];
		delete[] mData;
		

		//remake mData based on auxiliary copy
		mData = new std::string*[this->noData];
		for (int i = 0; i < this->noData; ++i) {
			mData[i] = new std::string[this->noColumns];
		}

		for (int i = 0; i < this->noData - 1; i++) {
			for (int j = 0; j < this->noColumns; j++) {
				mData[i][j] = mDataCopy[i][j];
			}
		}
		//insert in the new row;
		for (int j = 0; j< this->noColumns; j++) {
			mData[this->noData-1][j] = row[j];
		}

		// Deleting the allocating copy
		for (int i = 0; i < this->noData - 1; ++i)
			delete[] mDataCopy[i];
		delete[] mDataCopy;
		mDataCopy = nullptr;
		}

	}

	void selectAll() {
		displayTable();
	}

	void selectValues(std::string* values, int noColumns) {
		//check if values elemts are the same as column vNames
		int* savingPositions = new int[noColumns];
		int k = 0;
		for (int i = 0; i < noColumns; i++) {
			for (int j = 0; j < this->noColumns;j++) {
				if (values[i] == vNames[j]) {
					savingPositions[k] = j;
					k++;
				}
			}
		 }

		int maxSize;
		printf("Table name: %s\n\n", this->name);

		int counterForUnerline = 0;
		// Displaying headers
		for (int i = 0; i < noColumns; i++)
		{
			maxSize = computingDimensionForColumns(i);
			printf("%-*s|", maxSize, this->vNames[savingPositions[i]].c_str());
			counterForUnerline += maxSize;
		}
		printf("\n");
		for (int i = 0; i < counterForUnerline; i++)
			printf("-");
		printf("\n");


		for (int i = 0; i < this->noData; i++)
		{
			for (int j = 0; j < noColumns; j++)
			{
				maxSize = computingDimensionForColumns(j);
				printf("%-*s|", maxSize, mData[i][j].c_str());

			}
			printf("\n");
		}
	}

	void deleteValues(std::string value, std::string column_name) {
		//Delete from table_name where = column_name = value;
		std::string** mDataCopy = new std::string*[this->noData];
		for (int i = 0; i < this->noData; ++i) {
			mDataCopy[i] = new std::string[noColumns];
		}

		//deep copy with new values
		for (int i = 0; i < this->noData; i++) {
			for (int j = 0; j < noColumns; j++) {
				mDataCopy[i][j] = mData[i][j];
			}
		}

		//delete previous table
		for (int i = 0; i < this->noData; ++i)
			delete[] mData[i];
		delete[] mData;

		//save the positions of the vectors we want to delete
		int* posVectorToDelete = new int [this->noData];
		int k = 0;
		for (int i = 0; i < this->noData; i++) {
			for (int j = 0; j < this->noColumns; j++) {
				if (mDataCopy[i][j] == value) {
					posVectorToDelete[k] = j;
					k++;
				}
			}
		}

		int counter = 0, copyOf_k = k;
		k = 0;
		while (counter < copyOf_k) {
			for (int i = 0; i < this->noData; i++) {
				for (int j = 0; j < this->noColumns; j++) {
					if (mDataCopy[i][j] == mDataCopy[i][posVectorToDelete[k]]) {
						for (int m = posVectorToDelete[k]; m < noData - 1; m++) {
							mDataCopy[i][j] = mDataCopy[i+1][j+1];
						}
					}
				}
			}
			k++;
			counter++;
		}

		if (noData - copyOf_k == 0)
		{
			mData = nullptr;
		}
		else
		{
			mData = new std::string * [this->noData - copyOf_k];
			for (int i = 0; i < this->noData - copyOf_k; ++i) {
				mData[i] = new std::string[noColumns];
			}

			//deep copy with new values
			for (int i = 0; i < this->noData - copyOf_k; i++) {
				for (int j = 0; j < noColumns; j++) {
					mData[i][j] = mDataCopy[i][j];
				}
			}
		}
		
		//delete previous table
		for (int i = 0; i < this->noData; ++i)
			delete[] mDataCopy[i];
		delete[] mDataCopy;
		noData = noData - copyOf_k;
		
	}

	int computingDimensionForColumns(int i) {
		int maxSize;
		if (this->vTypes[i] == "integer")
		{
			int  counter = 0;
			int dimensionCopy = this->vDimensions[i];
			while (dimensionCopy != 0)
			{
				dimensionCopy = dimensionCopy / 10;
				counter++;
			}
			maxSize = counter + 10;
		}
		else
		{
			maxSize = this->vDimensions[i] / 8 + 15;
		}
		return maxSize;
	}
	void displayTable()
	{
		int maxSize;
		printf("Table name: %s\n\n", this->name);
		
		int counterForUnerline = 0;
		// Displaying headers
		for (int i = 0; i < noColumns; i++)
		{
		    maxSize = computingDimensionForColumns(i);
			printf("%-*s|", maxSize, this->vNames[i].c_str());
			counterForUnerline += maxSize;
		}
		printf("\n");
		for(int i =0; i < counterForUnerline; i++)
			printf("-");
		printf("\n");
		
		
		for (int i = 0; i < this->noData; i++)
		{
			for (int j = 0; j < this->noColumns; j++)
			{
				maxSize = computingDimensionForColumns(j);
				printf("%-*s|", maxSize, mData[i][j].c_str());

			}
			printf("\n");
		}
		
	}

	

	std::string getColumnTypeByName(std::string s) {
		for (int i = 0; i < noColumns; i++)
		{
			if (s == vNames[i]) return vTypes[i];
		} 
		throw std::invalid_argument("Invalid name for column. Input a valid one");
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

	Table(char* name, int noColumns, std::string* vNames, std::string* vTypes, int* vDimensions, std::string* vDefaults, int noData, std::string** mData) {

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
		this->noData = noData;
		// // Allocating memory
		this->mData = new std::string*[noData];
		for (int i = 0; i < noData; i++)
		{
			this->mData[i] = new std::string[noColumns];
		}
		// Setting values
		for (int i = 0; i < noData; i++)
		{
			for (int j = 0; j < noColumns; j++)
			{
				this->mData[i][j] = mData[i][j];
			}
		}

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
			for (int i = 0; i < noData; i++)
			{
				delete[] this->mData[i];
			}
			delete[] this->mData;
			this->mData = nullptr;
		}
		if (t.mData != nullptr)
		{
			this->mData = new std::string * [noData];
			for (int i = 0; i < noData; i++)
			{
				this->mData[i] = new std::string[noColumns];
			}

			for (int i = 0; i < noData; i++)
				for (int j = 0; j < noColumns; j++)
				{
					this->mData[i][j] = t.mData[i][j];
				}
		}
		else
		{
			this->mData = nullptr;
		}


	}

	//get number of columns
	int getNoColums() {
		return this->noColumns;
	}

	//Destructor
	~Table() {
		this->exists = false;
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
			for (int i = 0; i < this->noData; i++)
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

		

		// mData
		if (this->mData != nullptr)
		{
			for (int i = 0; i < noData; i++)
			{
				delete[] this->mData[i];
			}
			delete[] this->mData;
			this->mData = nullptr;
		}
		if (t.mData != nullptr)
		{
			this->mData = new std::string * [t.noData];
			for (int i = 0; i < t.noData; i++)
			{
				this->mData[i] = new std::string[t.noColumns];
			}

			for (int i = 0; i < t.noData; i++)
				for (int j = 0; j < t.noColumns; j++)
				{
					this->mData[i][j] = t.mData[i][j];
				}
		}
		else
		{
			this->mData = nullptr;
		}

		// noData
		this->noData = t.noData;

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
			if (strcmp(tokenizedVector[1], "table") == 0) {
				parserCreateTable();
			}
			else if (strcmp(tokenizedVector[1], "index") == 0) {
				/*parserCreateIndex();*/
			}
		}
		else if (strcmp(tokenizedVector[0], "display") == 0) {
			parserDisplayTable();
		}
		else if (strcmp(tokenizedVector[0], "drop") == 0)
		{
			if (strcmp(tokenizedVector[1], "table") == 0)
			{
				parserDropTable();
			}
			else if (strcmp(tokenizedVector[1], "index") == 0)
			{
				/*parserDropIndex();*/
			}
		}
		else if (strcmp(tokenizedVector[0], "insert") == 0) 
		{
			parserInsertRow();
		}
		else if (strcmp(tokenizedVector[0], "select") == 0)
		{
			parserSelect();
		}
		else if (strcmp(tokenizedVector[0],"delete") == 0) 
		{
			parserDelete();
		}
		else if (strcmp(tokenizedVector[0], "update") == 0)
		{
			parserUpdate();
		}
		else throw std::invalid_argument("Wrong first token of the command");
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

	void parserDisplayTable() {
		Table::findTableByName(tokenizedVector[2]).displayTable();
		
		
	}

	void parserSelect() {
		int noValues = 0;
		int counter = 0;
		//save the number of columns we want to print out
		for (int i = 1; i < sizeOfTokenizedVector - 3;i++) {
			if (dataTypeValues::string == vectorTypeOfToken[i]) {
				noValues++;
			}
			if (!(strcmp(")", tokenizedVector[i]))) {
				break;
			}
		}

		std::string* values = new std::string[noValues];
		//save the name of the columns we want to print out
		for (int i = 1; i < sizeOfTokenizedVector - 3; i++) {
			if (dataTypeValues::string == vectorTypeOfToken[i]) {
				values[counter] = tokenizedVector[i];
				counter++;
			}
			if (!(strcmp(")", tokenizedVector[i]))) {
				break;
			}
		}

		if(!strcmp(tokenizedVector[1],"all")|| !strcmp(tokenizedVector[1], "*"))
			Table::findTableByName(tokenizedVector[sizeOfTokenizedVector - 2]).selectAll();
		else {
			Table::findTableByName(tokenizedVector[sizeOfTokenizedVector - 2]).selectValues(values, counter);
		}
	}
	
	//delete from table where column = value;
	void parserDelete() {
		//value column name
		Table::findTableByName(tokenizedVector[2]).deleteValues(tokenizedVector[sizeOfTokenizedVector-2],tokenizedVector[sizeOfTokenizedVector-4]);
		
	}

	void parserInsertRow() {
		
		int counter = 0;
		std::string* value = new std::string[Table::findTableByName(tokenizedVector[2]).getNoColums()];
		for (int i = 5; i < sizeOfTokenizedVector - 3; i++) {
			if (vectorTypeOfToken[i] == dataTypeValues::string || vectorTypeOfToken[i] == dataTypeValues::number) {
				value[counter]=tokenizedVector[i];
				counter++;
			}
		}	
		Table::findTableByName(tokenizedVector[2]).insertRow(value);
	}



	void parserDropTable() {
		Table::findTableByName(tokenizedVector[2]).setToInexistent();
		Table::dropTable(tokenizedVector[2]);
	}

	void parserUpdate() {
		int i = 3; // position for filter column name
		std::string changeColumnName = tokenizedVector[i];
		std::string changeColumnValue;
		std::string filterName;
		std::string filterValue;
		
		if ("text" == Table::findTableByName(tokenizedVector[i-2]).getColumnTypeByName(changeColumnName))
		{
			changeColumnValue = tokenizedVector[i + 3];
			filterName = tokenizedVector[i + 6];
			if ("text" == Table::findTableByName(tokenizedVector[i - 2]).getColumnTypeByName(filterName))
			{
				filterValue = tokenizedVector[i + 9];
			}
			else
			{
				filterValue = tokenizedVector[i + 8];

			}
		}
		else {
			changeColumnValue = tokenizedVector[i + 2];
			filterName = tokenizedVector[i + 5];
			if ("text" == Table::findTableByName(tokenizedVector[i - 2]).getColumnTypeByName(filterName))
			{
				filterValue = tokenizedVector[i+8];
			}
			else
			{
				filterValue = tokenizedVector[i+7];

			}
		}
		Table::findTableByName(tokenizedVector[1]).updateTable(changeColumnName, changeColumnValue, filterName, filterValue);

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
					if (vectorTypeOfToken[j] == dataTypeValues::string || vectorTypeOfToken[j] == dataTypeValues::number) {
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
								if (strcmp(tokenizedVector[sizeOfTokenizedVector - 1], ";")) {
									throw;
								}
								if (!strcmp(tokenizedVector[sizeOfTokenizedVector - 2], "'")) {
									if (strcmp(tokenizedVector[sizeOfTokenizedVector - 4], "'")) {
										throw;
									}
									if (dataTypeValues::string != vectorTypeOfToken[sizeOfTokenizedVector - 3] && dataTypeValues::number != vectorTypeOfToken[sizeOfTokenizedVector - 3]) {
										throw;
									}
								}
								else if (dataTypeValues::number == vectorTypeOfToken[sizeOfTokenizedVector - 2]) {
									if (!strcmp(tokenizedVector[sizeOfTokenizedVector - 3], "'") || !strcmp(tokenizedVector[sizeOfTokenizedVector - 1], "'")) {
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
								if (!strcmp(tokenizedVector[j + 1], "'") && !strcmp(tokenizedVector[j - 1], "'")) {
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
										if (strcmp(tokenizedVector[j + 1], "'") || strcmp(tokenizedVector[j - 1], "'")) {
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
								else {
									//verify first value
									if (!strcmp(tokenizedVector[j - 1], "(")) {
										if (strcmp(tokenizedVector[j + 1], ",")) {
											throw;
										}
									}
									//verify middle value
									else if (!strcmp(tokenizedVector[j - 1], ",") && !strcmp(tokenizedVector[j + 1], ",")) {
										if (!(dataTypeValues::number == vectorTypeOfToken[j - 2] && dataTypeValues::number == vectorTypeOfToken[j + 2]) &&
											!(dataTypeValues::number == vectorTypeOfToken[j - 2] && !strcmp(tokenizedVector[j + 2], "'")) &&
											!(dataTypeValues::number == vectorTypeOfToken[j + 2] && !strcmp(tokenizedVector[j - 2], "'")) &&
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
			if (strcmp(tokenizedVector[1], "table") == 0) {
				lexerCreateTable();
			}
			else if (strcmp(tokenizedVector[1], "index") == 0) {
				lexerCreateIndex();
			}
			else throw; //second word is not correct
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
		else if (strcmp(tokenizedVector[0], "display") == 0)
		{
			lexerDisplay();
		}
		else if (strcmp(tokenizedVector[0], "insert") == 0)
		{
			lexerInsert();
		}
		else if (strcmp(tokenizedVector[0], "delete") == 0) {
			lexerDelete();
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
		//std::cout << "token object was destructed" << std::endl;
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
	int counter = 1;
	while (commandLine[commandLine.length() - counter] == ' ')
	{
		counter++;
	}
	if (commandLine[commandLine.length() - counter] != ';')  throw std::invalid_argument("Missing \";\" at the end of the command line");
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
			/*for (int i = 0; i < sizeOfTokenizedVector; i++)
			{
				std::cout << tokenizedVector[i] << "   ||   " << vectorTypeOfToken[i] << std::endl;
			}*/
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
