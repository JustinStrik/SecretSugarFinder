#include "Header1.h"
#include <vector>
#include <map>
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

private:

};

class Food
{
public:
	int ID;
	string name;
	string ingredients;

	Food() {}
	Food(int ID, string name) {
		this->ID = ID;
		this->name = name;
	}
	~Food() {}

private:

};

class EdgeList
{
public:
	//pair between the food and the sugar
	vector<pair<Food*, Sugar*>> theList;
	EdgeList() {}
	~EdgeList() {}
	

private:
	
};

class AdjacencyList
{
public:

	/*int is the ID, the vector is the complete list of sugars, and when the sugar is in the list of ingredients 
	the number is either 1 (if the graph is unwieghted) or the weight if it is weighted*/
	map<int, vector<int>> theList; 
	AdjacencyMatrix() {}
	~AdjacencyMatrix() {}

private:

};

int main() {

	Food cheeto = Food(1234, "cheetos");

	cout << "Hello world!" << endl;
	cout << cheeto.ID << " " << cheeto.name << endl;
	return 0;
}