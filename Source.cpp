#include "Header1.h"
#include <vector>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
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
	vector<pair<int, Sugar*>> theList; //ID and sugar
	EdgeList() {}
	~EdgeList() {}

	vector<Sugar*> search(int ID);

private:

};

class AdjacencyList
{
public:

	/*int is the ID, the vector is the complete list of sugars, and when the sugar is in the list of ingredients
	the number is either 1 (if the graph is unwieghted) or the weight if it is weighted*/
	unordered_map<int, vector<Sugar*>> theList;
	AdjacencyList() { }
	~AdjacencyList() { }

	vector<Sugar*> search(int ID);

private:

};

void readInData(AdjacencyList& adjList, EdgeList& edList, vector<Sugar*> sugars) {

	//will have vector with all of the sugars in them
	string readInData; //read in the line in file

	string ingredients;

	int ID = -1; //read in ID in while loop
	

	ifstream csv_rdr("branded_foods (id,brand,ingredients )-t.txt");
	//^reading tab delimited file

	bool header = true;//skip first line(header) when looping 

	while (getline(csv_rdr, readInData)) //will be getline
	{

		//read in, FIX
	   //readInData = ""; //read in, FIX
		if (header == true) {
			header = false;
			continue;
		}
		ID = stoi(readInData.substr(0, readInData.find_first_of("\t")));//			
		readInData = readInData.substr(readInData.find_first_of("\t") + 2);

		ingredients = readInData.substr(readInData.find_first_of("\t") + 1);
		
		for (int i = 0; i < ingredients.length(); i++) {//tolower to make find simpler
			ingredients[i] = tolower(ingredients[i]);
		}


		for (int i = 0; i < sugars.size(); i++)
		{
			if (ingredients.find(sugars.at(i)->name) != string::npos)
			{
				adjList.theList.at(ID).push_back(sugars.at(i)); //insert sugar in hashmap at ID
				edList.theList.push_back({ ID, sugars.at(i) }); //insert pair in vector
			}
		}

	}

	csv_rdr.close();
}


vector<Sugar*> AdjacencyList::search(int ID) {
	return this->theList[ID];
}

vector<Sugar*> EdgeList::search(int ID) {

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

	
	vector<string> sugars_string = {
		"corn sweetener","ethyl maltol","corn syrup","dextrose","fructose","fruit juice concentrate"
		"glucose","high-fructose corn syrup","invert sugar","lactose"
		"maltose","malt syrup","raw sugar","sucrose","sugar syrup",
		"florida crystals","cane sugar","crystalline fructose",
		"evaporated cane juice","corn syrup solids","malt syrup",
		"barley malt","agave nectar","rice syrup","caramel",
		"panocha","muscovado","molasses","treacle","carob syrup"

	};//size = 30

	vector<Sugar*> allSugars;

	for (string s : sugars_string) { //filling allSugars
		allSugars.push_back(new Sugar(s));
	}


	return 0;


}