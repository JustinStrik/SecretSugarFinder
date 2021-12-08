//#include "Header1.h"
#include <vector>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
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
	string header;//skip first line(header) when looping 
	string tempID, tempInt;
	string ingredients;
	int sugarVal;

	//double ID = 0.0; //read in ID in while loop
	unsigned long long ID, temp;

	ifstream csv_rdr("newFood.csv"); // (id,brand,ingredients )-t.txt
	//^reading tab delimited file
	//ofstream myfile;

	//csv_rdr.open("newFood.csv");

	if (csv_rdr.is_open())
	{
		getline(csv_rdr, header); //skips header

		while (getline(csv_rdr, readInData)) //will be getline
		{

			//read in, FIX
		   //readInData = ""; //read in, FIX

			istringstream stream(readInData);

			getline(stream, tempID, ',');
			//getline(stream, ingredients, '\n');

			/*try
			{*/
			ID = stoull(tempID);
			/*}
			catch (const std::exception&)
			{
				continue;
			}*/

			//readInData = readInData.substr(readInData.find_first_of(",") + 2);

			//ingredients = readInData.substr(readInData.find_first_of("\t") + 1);

			adjList.theList[ID] = { };
			//temp = ID;

			//myfile << temp << ',';
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

		//	for (int i = 0; i < sugars.size(); i++)
		//	{
		//		if (ingredients.find(sugars.at(i)->name) != string::npos)
		//		{
		//			//adjList.theList.at(ID).push_back(sugars.at(i)); //insert sugar in hashmap at ID
		//			//edList.theList.push_back({ ID, sugars.at(i) }); //insert pair in vector
		//			myfile << i << ',';
		//		}
		//	}
		//	myfile << '\n';

		}
	}
	csv_rdr.close();
	//myfile.close();
}


vector<Sugar*> AdjacencyList::search(unsigned long long ID) {
	return this->theList[ID];
}

vector<Sugar*> EdgeList::search(unsigned long long ID) {

	vector<Sugar*> sugarList;

	for (auto var : this->theList)
	{
		if (var.first == ID)
		{
			sugarList.push_back(var.second);
		}
	}

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
	cout << "This could take a minute." << endl;
	readInData(adjList, edgList, allSugars);
	cout << "All done!" << endl << endl;

	unsigned long long searchForID = 0;
	vector<Sugar*> retrievedSugars;

	while (true)
	{
		cout << "Enter the ID of your food (or 0 to quit): ";

		cin >> searchForID;

		if (searchForID == 0)
		{
			break;
		}

		if (to_string(searchForID).length() < 11) //to make it 11 digits
		{
			searchForID *= pow(10.0, 11 - to_string(searchForID).length());
		}

		cout << endl;

		retrievedSugars = adjList.search(searchForID);

		if (retrievedSugars.size() == 0) //there were no sugars found
		{
			cout << "Our system did not find any hidden sugars!" << endl;
		}
		else //1 or more sugars found
		{
			cout << "Our system found that the ingredients contain the following hidden sugar keywords: " << endl;
			for (auto sugar : retrievedSugars) {
				cout << sugar->name << endl;
			}
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
		"PANOCHA","MUSCOVADO","MOLASSES","TREACLE","CAROB SYRUP"

	};
}