#include "Header1.h"
#include <vector>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Sugar
{
public:
	string name;
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

void readInData(AdjacencyList adjList, EdgeList edList, vector<Sugar*> sugars) {

	//will have vector with all of the sugars in them
	string readInData = ""; //read in the ingredients
	int ID = -1; //read in ID in while loop
	bool whatever = true;

	while (whatever) //will be getline
	{
		int ID = -1; //read in, FIX
		readInData = ""; //read in, FIX
		for (int i = 0; i < sugars.size(); i++)
		{
			if (readInData.find(sugars.at(i)->name))
			{
				adjList.theList.at(ID).push_back(sugars.at(i)); //insert sugar in hashmap at ID
				edList.theList.push_back({ ID, sugars.at(i) }); //insert pair in vector
			}
		}

	}
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

	//Food cheeto = Food(1234, "cheetos");

	//cout << "Hello world!" << endl;
	//cout << cheeto.ID << " " << cheeto.name << endl;
	return 0;


}