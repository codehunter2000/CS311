

#include<vector>
#include<iostream>

using namespace std;

class Edge
{
	friend class Vertex;
protected:
	int weight;
	Vertex* origin;
	Vertex* dest;
public:
	Edge()
	{weight = 0;}
	Edge(int num, Vertex* start, Vertex* end)
	{
		weight = num; origin = start; dest = end;
	}

	bool Edge::operator==(const Edge& item)
	{
		if (weight == item.weight && origin == item.origin && dest == item.dest)
			return true;
		return false;
	}
};

class Vertex
{
	friend class Edge;
protected:
	char name;
	vector<Edge> incoming, outgoing;
public:
	Vertex()
	{name = NULL;}
	Vertex(char letter)
	{name = letter;}
	char getName()
	{return name;}
	void addIncomingEdge(Edge in)
	{
		incoming.push_back(in);
	}
	void addOutgoingEdge(Edge out)
	{
		outgoing.push_back(out);
	}
	void removeIncomingEdge(Vertex* start, Vertex* end)
	{
		Edge temp;
		for (int i = 0; i < incoming.size(); i++)
		{
			temp = incoming[i];
			if (temp.origin == start && temp.dest == end)
				incoming.erase(incoming.begin() + i);
		}
	}

	void removeOutgoingEdge(Vertex* start, Vertex* end)
	{
		Edge temp;
		for (int i = 0; i < outgoing.size(); i++)
		{
			temp = outgoing[i];
			if (temp.origin == start && temp.dest == end)
				outgoing.erase(outgoing.begin() + i);
		}
	}


	void printBlocks()
	{
		if (incoming.size() == 0 && outgoing.size() == 0)
			cout << "\n" << name << " has no edges \n" << endl;
	}
};

class Graph
{
private:
	vector<Vertex> nodes;
	bool nodeExists(char name);
	bool checkMultiGraph();
	bool checkPseudoGraph();
	bool checkCycle();
	int averageWeightIncoming(char name);
	int averageWeightOutgoing(char name);
public:
	Graph();
	~Graph();
	bool addVertex(char name);
	bool removeVertex(char name);
	bool addEdge(int weight, char start, char end);
	bool removeEdge(char start, char end);
	void numBlocks();
	int numOutgoingEdges(char name);
	int numIncomingEdges(char name);
	void printOutgoingEdges(char name);
	void printIncomingEdges(char name);
	void printGraph();	
};

