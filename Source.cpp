#include <vector>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <time.h>
#include <chrono>
using namespace std;

class Sugar
{
public:
	string name;
	Sugar(string name_) :name(name_) {}
	Sugar() {}
	~Sugar() {}
};

vector<string> makeSugarVector();

class EdgeList
{
public:
	//pair between the food and the sugar
	vector<pair<unsigned long long, Sugar*>> theList; //ID and sugar
	EdgeList() {}
	~EdgeList() {}

	vector<Sugar*> search(unsigned long long ID);

private:

};

class AdjacencyList
{
public:

	/*int is the ID, the vector is the complete list of sugars, and when the sugar is in the list of ingredients
	the number is either 1 (if the graph is unwieghted) or the weight if it is weighted*/
	unordered_map<unsigned long long, vector<Sugar*>> theList;
	AdjacencyList() { }
	~AdjacencyList() { }

	vector<Sugar*> search(unsigned long long ID);

private:

};

void readInData(AdjacencyList& adjList, EdgeList& edList, vector<Sugar*> sugars) {

	//will have vector with all of the sugars in them
	string readInData; //read in the line in file
	string tempID, tempInt;
	string ingredients;
	int sugarVal;

	unsigned long long ID, temp;

	ifstream csv_rdr("foods.csv"); 

	if (csv_rdr.is_open())
	{
		getline(csv_rdr, readInData); //skips header

		while (getline(csv_rdr, readInData)) //will be getline
		{

			istringstream stream(readInData);

			getline(stream, tempID, ',');


			ID = stoull(tempID);


			adjList.theList[ID] = { };

			while (getline(stream, tempInt, ','))
			{
				if (tempInt != "")
				{
					sugarVal = stoi(tempInt);
					adjList.theList.at(ID).push_back(sugars.at(sugarVal)); //insert sugar in hashmap at ID
					edList.theList.push_back({ ID, sugars.at(sugarVal) }); //insert pair in vector
				}
				else
					break;
			}

		}
	}
	csv_rdr.close();
}


vector<Sugar*> AdjacencyList::search(unsigned long long ID) {
	
	if (this->theList.count(ID) == 0)
	{
		return { nullptr }; //returns a single nullptr vector if the ID is not found
	}
	return this->theList[ID];
}

vector<Sugar*> EdgeList::search(unsigned long long ID) {

	vector<Sugar*> sugarList;
	bool exists = false;

	for (auto var : this->theList)
	{
		if (var.first == ID)
		{
			exists = true;
			sugarList.push_back(var.second);
		}
	}

	if (!exists) //ID does not exist in database
		return { nullptr };

	return sugarList;
}

int main() {


	vector<string> sugars_string = makeSugarVector(); //size = 30
	vector<Sugar*> allSugars;

	for (string s : sugars_string) { //filling allSugars
		allSugars.push_back(new Sugar(s));
	}

	AdjacencyList adjList; //FIX make space for all possible IDs
	EdgeList edgList;

	cout << "Hold on.." << endl;
	cout << "We are loading in a LOT of data points." << endl;
	cout << "This could take a minute." << endl << endl;
	readInData(adjList, edgList, allSugars);
	cout << "All done!" << endl << endl;

	string tempInput;
	long long searchForID = 0;
	bool validInput = false;
	bool timeAnalysis = false; //whether or not time analysis is being done
	vector<Sugar*> retrievedSugars;
	vector<Sugar*> edgeRetrievedSugars; //only used when analyzing time
	auto startEdg = chrono::steady_clock::now();
	auto endEdg = chrono::steady_clock::now();



	while (true)
	{
		while (!validInput) //while invalid input
		{
			cout << endl;

			if (!timeAnalysis)
				cout << "Enter the ID of your food (or 0 to quit, or -1 to do time analysis): ";
			else
				cout << "Enter the ID of your food (or 0 to quit, or -1 to EXIT time analysis): ";

			cin >> tempInput;
			try //to check if a string is entered
			{
				searchForID = stoll(tempInput);
			}
			catch (const std::exception&)
			{
				cout << "Please enter a valid number." << endl;
				continue;
			}

			if (searchForID == -1) //time analysis mode
			{
				timeAnalysis = !timeAnalysis; //switch T/F

				if (timeAnalysis)
				{
					cout << "You have chosen to do time analysis!" << endl;
					cout << "We will be comparing Adjacency Lists and Edge List execution times" << endl;
					cout << "for your input." << endl;
				}
			}
			else if (searchForID < 0)
			{
				cout << "Barcodes can't be negative, silly!" << endl;
				cout << "Please enter a valid ID." << endl;
			}
			else if (to_string(searchForID).size() > 15) //larger than USDA barcode threshold
			{
				cout << "This number too large." << endl;
				cout << "Please enter a valid ID." << endl;
			}
			else
				validInput = true;
		}
		validInput = false;


		if (searchForID == 0) //quit
			break;

		auto startAdj = chrono::steady_clock::now(); 
		retrievedSugars = adjList.search(searchForID);
		auto endAdj = chrono::steady_clock::now();

		if (timeAnalysis)
		{
			startEdg = chrono::steady_clock::now(); 
			edgeRetrievedSugars = edgList.search(searchForID);
			endEdg = chrono::steady_clock::now();
		}

		
		if (retrievedSugars.size() == 0) //there were no sugars found
		{
			cout << "Our system did not find any hidden sugars!" << endl;
		}
		else if (retrievedSugars[0] == nullptr)
		{
			cout << "That barcode does not appear to exist in our database." << endl;
			cout << "Did you miss some numbers on the end?" << endl;
		}
		else //1 or more sugars found
		{
			if (timeAnalysis)
				cout << "The Adjacency List found that the ingredients contain the following hidden sugar keywords: " << endl;
			else
				cout << "Our system found that the ingredients contain the following hidden sugar keywords: " << endl;
			for (auto sugar : retrievedSugars) {
				cout << sugar->name << endl;
			}

			if (timeAnalysis)
			{
				if (edgeRetrievedSugars.size() == 0)
					cout << "Our system did not find any hidden sugars!" << endl;
				else if (edgeRetrievedSugars[0] == nullptr)
				{
					cout << "That barcode does not appear to exist in our database." << endl;
					cout << "Did you miss some numbers on the end?" << endl;
				}
				else
					cout << "The Edge List found that the ingredients contain the following hidden sugar keywords: " << endl;

				for (auto sugar : edgeRetrievedSugars) {
					cout << sugar->name << endl;
				}
			}
		}
		cout << endl;

		if (timeAnalysis)
		{
			std::cout << "Time taken for adjacency list implementation = " << chrono::duration_cast<std::chrono::microseconds>(endAdj - startAdj).count() << "[microseconds]" << std::endl;
			std::cout << "Time taken for edge list implementation = " << chrono::duration_cast<std::chrono::microseconds>(endEdg - startEdg).count() << "[microseconds]" << std::endl;

		}
	}

	 
	return 0;
}


vector<string> makeSugarVector() {
	return {
		"CORN SWEETENER","ETHYL MALTOL","CORN SYRUP","DEXTROSE","FRUCTOSE","FRUIT JUICE CONCENTRATE"
		"GLUCOSE","HIGH-FRUCTOSE CORN SYRUP", "HIGH FRUCTOSE CORN SYRUP", "INVERT SUGAR","LACTOSE"
		"MALTOSE","MALT SYRUP","RAW SUGAR","SUCROSE","SUGAR SYRUP",
		"FLORIDA CRYSTALS","CANE SUGAR","CRYSTALLINE FRUCTOSE",
		"EVAPORATED CANE JUICE","CORN SYRUP SOLIDS","MALT SYRUP",
		"BARLEY MALT","AGAVE NECTAR","RICE SYRUP","CARAMEL",
		"PANOCHA","MUSCOVADO","MOLASSES","TREACLE","CAROB SYRUP", "SUGAR", "SYRUP"

	};
}