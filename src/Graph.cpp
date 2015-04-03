
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<queue>
#include"../include/Graph.h"

//****************//
//---EDGE---	  //
//****************//

Edge::Edge()
{

}

Edge::~Edge()
{

}

//****************//
//---END EDGE---  //
//****************//

//****************//
//--VERTEX--	  //
//****************//

Vertex::Vertex()
{

}

Vertex::~Vertex()
{

}

//****************//
//---END VERTEX---//
//****************//

//****************//
//---GRAPH---     //
//****************//

Graph::Graph()
{

}

Graph::~Graph()
{

}

void Graph::BFTraversal(std::string startingCity)
{
	vertex* current = NULL;
	int j = 0;
	while (current == NULL)
	{
		if (vertices[j].name == startingCity)
			current = &vertices[j];
		j++;
	}
	std::queue<vertex*> q;

	std::cout << current->name << atd::endl;
	current->visited = true;
	q.push(current);

	while (!q.empty())
	{
		current = q.front();	//set to oldest
		q.pop();	//remove the oldest to update queue
		for (int i = 0; i < current->adj.size(); i++)
		{
			if (current->adj[i].v->visited == false)
			{
				current->adj[i].v->visited = true;
				std::cout << current->adj[i].v->name << std::endl;
				q.push(current->adj[i].v);
			}
		}
	}
}

//****************//
//---END GRAPH--- //
//****************//
