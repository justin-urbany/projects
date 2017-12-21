#define _CRTDB_MAP_ALLOC
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "Graph.h"
using std::setprecision;
using std::ifstream;
using std::getline;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::stod;
#include <crtdbg.h>


template <typename T>
void Display(T data); 
void ReadFile(Graph<string, string> & map);
void Dijkstra(Graph<string, string> & map);
void process(Graph<string, string> & map, string start);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Graph<string, string> som;
	ReadFile(som);
	Dijkstra(som);

	return 0;
}

template<typename T>
void Display(T data)
{
	cout << data << endl;
}

void ReadFile(Graph<string, string> & map)
{
	string vertex1;
	string vertex2;
	string edge;
	string edgeweight;
	double getweight = 0.00;
	ifstream readfile;
	readfile.open("Data.txt");

	if(readfile.is_open())
	{
		while (!readfile.eof())
		{
			getline(readfile, vertex1,',');
			map.InsertVertex(vertex1);
			getline(readfile, vertex2, ',');
			map.InsertVertex(vertex2);
			getline(readfile, edge, ',');
			getline(readfile, edgeweight);
			getweight = stod(edgeweight);
			if(edge=="I-5")
			{
				getweight = getweight / 65;
			}
			else
			{
				getweight = getweight / 55;
			}
			map.InsertEdge(vertex1, vertex2, edge, getweight);
		}
		readfile.close();
	}
	else
	{
		cout << "Error opening File" << endl;
	}
}

void Dijkstra(Graph<string, string>& map)
{
	string startpoint;
	string endpoint;
	int selection = -1;
	list<Vertex<string, string>*> temp = map.getGraph();
	typename list<Vertex<string, string>*>::iterator traversal = temp.begin();
	while(selection != 2)
	{
		if (!map.isEmpty())
		{
			cout << "Here are all the locations on your map"<<endl;
			map.BreadthFirst(Display);
			while (selection != 2 && selection != 1)
			{
				cout << "Enter 1 to get path from a to b or 2 to quit: ";
				cin >> selection;
				if(selection != 2 && selection != 1)
				{
					cout << "Invalid selection" << endl;
				}
			}
			if(selection==1)
			{
				cout << "Enter in starting point: ";
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				getline(cin, startpoint);
				cin.clear();
				while(traversal != temp.end() && (*traversal)->getData() != startpoint)
				{
					++traversal;
				}
				if((*traversal)->getData() == startpoint)
				{

					process(map, startpoint);
				}
				else
				{
					cout << "Invalid startpoint";
				}
				selection = -1;
			}
		}
		else
		{
			cout << "Graph is empty can't use Dijkstras";
			selection = 2;
		}
	}
}

void process(Graph<string, string>& map, string start)
{
	list<Vertex<string, string>*> temp = map.getGraph();
	list<Edge<string, string>*> edgetemp;
	Vertex<string, string> * tempvertex;
	Vertex<string, string> * beingprocessed;
	
	typename list<Vertex<string, string>*>::iterator traversal = temp.begin();
	typename list<Edge<string, string>*>::iterator edgetraversal;
	double distance[36] = { -1 };
	int position = 0;
	Vertex<string, string> * predecessor[36]={nullptr};

	while(traversal!=temp.end() && (*traversal)->getData() != start)
	{
		++position;
		++traversal;
	}

	distance[position] = 0;  //set the starting distance point to 0
	//predecessor[position] = (*traversal); // set starting points predecessor to itself
	//(*traversal)->Setprocessed(true); //set the starting point to processed
	
	beingprocessed = (*traversal); // put the current vertex into a temp
	edgetemp = (*traversal)->getList();  //get the list of edges that are at that vertex
	edgetraversal = edgetemp.begin();  //make a traversal
	
	while(edgetraversal != edgetemp.end())  //go through each element of the edge list
	{
		if((*edgetraversal)->getDest()->Getprocessed()==false) //if the element is not processed
		{
			tempvertex = (*edgetraversal)->getDest(); // put the destination into a temp
			traversal = temp.begin(); // reset traversal
			position = 0; //reset the position
			while((*traversal)->getData() != tempvertex->getData())
			{
				++position; //increment through to find its location
				++traversal;
			}
			distance[position] = (*edgetraversal)->getWeight(); //set the distance of the vertex from previous vertex
			predecessor[position] = beingprocessed; //set the new vertex
		}
	}
	beingprocessed->Setprocessed(true); //set starting vertex to processed
	edgetraversal = edgetemp.begin; // traverse through
}
