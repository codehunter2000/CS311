
/*
	Author: Gabriel Hunt
	Files: Graph.h, Graph.cpp
	Date Last Modified: December 7, 2017
*/


#include<string>
#include<vector>
#include<iostream>
#include<fstream>

using namespace std;

class Graph
{
	friend class Node;
	friend class Link;
protected:
	vector<Node> verticies;
public:
	Graph();
	~Graph();
	bool addVertex(char name);
	bool removeVertex(char name);
	bool addEdge(char start, char end, int weight);
	bool removeEdge(char start, char end);
	bool vertexExists(char name);
	bool edgeExists(Node start, Node end);
	void findNumBlocks();
	void printGraph();
	void processTransFile();
	void printIncomingEdges(char name);
	void printOutgoingEdges(char name);
	void countIncomingEdges(char name);
	void countOutgoingEdges(char name);
	void checkForCycle();

};

class Node
{
	friend class Link;
protected:
	vector<Link> edges;
	char name;
public:
	Node()
	{
		name = NULL;
	}
	Node(char letter)
	{
		name = letter;
	}
	char getName()
	{
		return name;
	}

	bool findLink(string name);
	bool addLink(Link toAdd);
	bool removeLink(Link toRemove);
	bool isMultiGraph(Link toCheck);
	void printEdges();
	void printIncomingEdges();
	void printOutgoingLinks();
	int getNumIncomingLinks(char name);
	int getNumOutgoingLinks(char name);
	int getNumLinks()
	{
		return edges.size();
	}
};



class Link
{
	friend class Node;
protected:
	Node origin;
	Node destination;
	int weight;
	string name;
public:
	Link()
	{
		origin = destination = NULL;
		weight = 0;
		name = " ";
	}
	Link(Node start, Node end, int weight)
	{
		origin = start;
		destination = end;
		this->weight = weight;
		char letters[2];
		letters[0] = start.name;
		letters[1] = end.name;
		name = letters;
	}

	string getName()
	{
		return name;
	}
};