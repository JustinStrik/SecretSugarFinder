//#include "Header1.h"
#include <vector>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Sugar
{
public:
	string name;
	Sugar(string name_) :name(name_) {}
	Sugar() {}
	~Sugar() {}
};

//class Food
//{
//public:
//	int ID;
//	string name;
//	string ingredients;
//
//	Food() {}
//	Food(int ID, string name) {
//		this->ID = ID;
//		this->name = name;
//	}
//	~Food() {}
//
//private:
//
//};

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
	string tempID;
	string ingredients;

	double ID = 0.0; //read in ID in while loop
	unsigned long long temp;

	ifstream csv_rdr("branded_foods.csv"); // (id,brand,ingredients )-t.txt
	//^reading tab delimited file
	ofstream myfile;

	myfile.open("newFood.csv");

	if (csv_rdr.is_open())
	{
		getline(csv_rdr, header); //skips header

		while (getline(csv_rdr, readInData)) //will be getline
		{

			//read in, FIX
		   //readInData = ""; //read in, FIX

			istringstream stream(readInData);

			getline(stream, tempID, ',');
			getline(stream, ingredients, '\n');

			try
			{
				ID = stod(tempID);
			}
			catch (const std::exception&)
			{
				continue;
			}

			//readInData = readInData.substr(readInData.find_first_of(",") + 2);

			//ingredients = readInData.substr(readInData.find_first_of("\t") + 1);

			adjList.theList[ID] = { };
			temp = ID;

			myfile << temp << ',';

			for (int i = 0; i < sugars.size(); i++)
			{
				if (ingredients.find(sugars.at(i)->name) != string::npos)
				{
					//adjList.theList.at(ID).push_back(sugars.at(i)); //insert sugar in hashmap at ID
					//edList.theList.push_back({ ID, sugars.at(i) }); //insert pair in vector
					myfile << i << ',';
				}
			}
			myfile << '\n';

		}
	}
	csv_rdr.close();
	myfile.close();
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

int main() {


	vector<string> sugars_string = makeSugarVector(); //size = 30

	vector<Sugar*> allSugars;

	for (string s : sugars_string) { //filling allSugars
		allSugars.push_back(new Sugar(s));
	}

	AdjacencyList adjList; //FIX make space for all possible IDs
	EdgeList edgList;

	readInData(adjList, edgList, allSugars);

	unsigned long long searchForID = 0;
	vector<Sugar*> retrievedSugars;

	while (true)
	{
		cout << "Enter the ID: ";

		cin >> searchForID;

		cout << endl;

		if (searchForID == 0)
		{
			break;
		}

		retrievedSugars = adjList.search(searchForID);

		for (auto var : retrievedSugars) {
			cout << var->name << " ";
		}

	}


	return 0;
}