#include "Graph.h"



Graph::Graph()
{
}


Graph::~Graph()
{
}

// Add a vertex to the graph
bool Graph::addVertex(char name)
{
	if (!nodeExists(name))
	{
		Vertex node(name);
		nodes.push_back(node);
		return true;
	}
	return false;
}

// Remove vertex from a graph
bool Graph::removeVertex(char name)
{
	if (nodeExists(name))
	{
		Vertex temp;
		for (int i = 0; i < nodes.size(); i++)
		{
			temp = nodes[i];
			if (temp.getName() == name)
			{
				nodes.erase(nodes.begin() + i);
				// REMOVE ANY EDGES
				return true;
			}
		}
	}
	return false;
}

// Check to see if the node is already in the graph
bool Graph::nodeExists(char name)
{
	for (Vertex temp : nodes)
		if (temp.getName() == name)
			return true;
	return false;
}

// Create new edge, linking two nodes
bool Graph::addEdge(int weight, char start, char end)
{
	Vertex* origin = NULL;
	Vertex* dest = NULL;

	for (Vertex temp : nodes)
	{
		if (temp.getName() == start)
			*origin = temp;
		if (temp.getName() == end)
			*dest = temp;
	}

	Edge newEdge(weight, origin, dest);
	origin->addOutgoingEdge(newEdge);
	dest->addIncomingEdge(newEdge);
	return true;
}

bool Graph::removeEdge(char start, char end)
{
	Vertex* origin = NULL;
	Vertex* dest = NULL;

	for (Vertex temp : nodes)
	{
		if (temp.getName() == start)
			*origin = temp;
		if (temp.getName() == end)
			*dest = temp;
	}

	origin->removeOutgoingEdge(origin, dest);
	dest->removeIncomingEdge(origin, dest);

	return true;
}

void Graph::numBlocks()
{
	for (Vertex temp : nodes)
		temp.printBlocks();
}

int main()
{
	return 0;
}