#include "Graph.h"


Graph::Graph()
{
}


Graph::~Graph()
{
}

bool Graph::vertexExists(char name)
{
	for (Node temp : verticies)
		if (temp.getName() == name)
			return true;
	return false;

}

bool Graph::edgeExists(Node  start, Node  end)
{
	bool found = false;
	char letters[2];
	letters[0] = start.getName();
	letters[1] = end.getName();
	string name(letters);
	for (Node temp : verticies)
		if (temp.findLink(name))
			return true;
	return false;
}

void Graph::findNumBlocks()
{
	cout << "\nDisconected verticies: " << endl;

	for (Node temp : verticies)
	{
		if (temp.getNumLinks() == 0)
		{
			cout << "\n " << temp.getName() << endl;
		}
	}
}

void Graph::printGraph()
{
	for (Node temp : verticies)
	{
		cout << "\nVertex: " << temp.getName() << endl;
		cout << "\n" << temp.getName() << " links to: " << endl;
		temp.printEdges();
	}
}

void Graph::processTransFile()
{
	ifstream fin;
	string command;
	char vName1, vName2;
	int weight;
	fin.open("test.txt");
	while (fin.good())
	{
		command = " ";
		vName1 = vName2 = NULL;
		weight = -1;

		fin >> command;
		if (command == "addVertex")
		{
			fin >> vName1;
			addVertex(vName1);
		}
		else if (command == "removeVertex")
		{
			fin >> vName1;
			removeVertex(vName1);
		}
		else if (command == "addEdge")
		{
			fin >> vName1;
			fin >> vName2;
			fin >> weight;
			addEdge(vName1, vName2, weight);
		}
		else if (command == "removeEdge")
		{
			fin >> vName1;
			fin >> vName2;
			removeEdge(vName1, vName2);
		}
		else if (command == "printIncomingEdges")
		{
			fin >> vName1;
			printIncomingEdges(vName1);
		}
		else if (command == "printOutgoingEdges")
		{
			fin >> vName1;
			printOutgoingEdges(vName1);
		}
		else if (command == "countIncomingEdges")
		{
			fin >> vName1;
			countIncomingEdges(vName1);
		}
		else if (command == "countOutgoingEdges")
		{
			fin >> vName1;
			countOutgoingEdges(vName1);
		}
		else if (command == "countBlocks")
		{
			findNumBlocks();
		}
		else if (command == "printGraph")
		{
			printGraph();
		}
	}
}

void Graph::printIncomingEdges(char name)
{
	Node* vert = NULL;
	for (Node temp : verticies)
	{
		if (temp.getName() == name)
			vert = &temp;
	}
	if (vert == NULL)
		return;
	vert->printIncomingEdges();
}

void Graph::printOutgoingEdges(char name)
{
	Node* vert = NULL;
	for (Node temp : verticies)
	{
		if (temp.getName() == name)
			vert = &temp;
	}
	if (vert == NULL)
		return;
	vert->printOutgoingLinks();
}

void Graph::countIncomingEdges(char name)
{
	int totalLinks = 0;
	for (Node temp : verticies)
		if (temp.getNumLinks() > 0)
			totalLinks += temp.getNumIncomingLinks(name);
	cout << "\nFor vertex " << name << " there are " << totalLinks << " incoming links" << endl;
}

void Graph::countOutgoingEdges(char name)
{
	int totalLinks = 0;
	for (Node temp : verticies)
		if (temp.getNumLinks() > 0)
			totalLinks += temp.getNumOutgoingLinks(name);
	cout << "\nFor vertex " << name << " there are " << totalLinks << " outgoing links" << endl;
		
}


bool Graph::addVertex(char name)
{
	if (!vertexExists(name))
	{
		Node vert(name);
		verticies.push_back(vert);
		return true;
	}

	return false;
}

bool Graph::removeVertex(char name)
{
	if (vertexExists(name))
	{
		Node temp;
		for (int i = 0; i < verticies.size(); i++)
		{
			temp = verticies[i];
			if (temp.getName() == name)
			{
				verticies.erase(verticies.begin() + i);
				return true;
			}
		}
	}
	return false;
}

bool Graph::addEdge(char start, char end, int weight)
{
	Node origin = NULL;
	Node dest = NULL;
	for (Node temp : verticies)
	{
		if (temp.getName() == start)
			origin = temp;
		if (temp.getName() == end)
			dest = temp;
	}

	if (!edgeExists(origin, dest))
		{
			Link edge(origin, dest, weight);
			origin.addLink(edge);
			Node temp;
			for (int i = 0; i < verticies.size(); i++)
			{
				temp = verticies[i];
				if (temp.getName() == start)
				{
					verticies[i] = origin;
					return true;
				}
			}
		}
	
	return false;
}

bool Graph::removeEdge(char start, char end)
{
	Node origin = NULL;
	Node dest = NULL;
	for (Node temp : verticies)
	{
		if (temp.getName() == start)
			origin = temp;
		if (temp.getName() == end)
			dest = temp;
	}

	
	if (edgeExists(origin, dest))
	{
		Link edge(origin, dest, 0);
		origin.removeLink(edge);
		Node temp;
		for (int i = 0; i < verticies.size(); i++)
		{
			temp = verticies[i];
			if (temp.getName() == start)
			{
				verticies[i] = origin;
				return true;
			}
		}
	}
		
	cout << "\nEdge " << start << end << " not found!" << endl;
	return false;
}


bool Node::findLink(string name)
{
	for (Link temp : edges)
		if (temp.name == name)
			return true;
	return false;
}

bool Node::addLink(Link toAdd)
{
	if (!findLink(toAdd.getName()))
	{
		edges.push_back(toAdd);
		return true;

		/*if (!isMultiGraph(toAdd))
		{
			edges.push_back(toAdd);
			return true;
		}
		*/
	}

	return false;
}

bool Node::removeLink(Link toRemove)
{
	if (findLink(toRemove.getName()))
	{
		Link temp;
		for (int i = 0; i < edges.size(); i++)
		{
			temp = edges[i];
			if (temp.name == toRemove.name)
			{
				edges.erase(edges.begin() + i);
				return true;
			}
		}
	}
	return false;
}

bool Node::isMultiGraph(Link toCheck)
{
	if (toCheck.destination.name == toCheck.origin.name)
		return true;
	for (Link temp : edges)
		if (temp.destination.name == toCheck.destination.name
			&& temp.origin.name == toCheck.origin.name)
			return true;
	return false;
}

void Node::printEdges()
{
	for (Link temp : edges)
	{
		cout << "\n" << temp.destination.getName() << endl;
	}
}

void Node::printIncomingEdges()
{
	Node origin = NULL;
	for (Link temp : edges)
	{
		origin = temp.origin;
		cout << "\n" << origin.getName();
	}
}

void Node::printOutgoingLinks()
{
	Node dest = NULL;
	for (Link temp : edges)
	{
		dest = temp.destination;
		cout << "\n" << dest.getName();
	}
}

int Node::getNumIncomingLinks(char name)
{
	int numLinks = 0;
	for (Link temp : edges)
		if (temp.destination.name == name)
			numLinks++;
	return numLinks;
}

int Node::getNumOutgoingLinks(char name)
{
	int numLinks = 0;
	for (Link temp : edges)
		if (temp.origin.name == name)
			numLinks++;
	return numLinks;
}


int main()
{
	Graph test;
	test.processTransFile();
	char letter;
	cout << "\nDo something: " << endl;
	cin >> letter;
}