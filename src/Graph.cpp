
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
	v = nullptr;
}

Edge::Edge(Vertex* vertex, int wt)
{
	v = vertex;
	weight = wt;
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
	name = "";
	have_visited = false;
}

Vertex::Vertex(std::string& nm)
{
	name = nm;
	have_visited = false;
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

void Graph::add_Edge(std::string& v1, std::string& v2, int& weight)
{
	Vertex* origin = nullptr;
	Vertex* destination = nullptr;
	int* i = new int(0);
	while (origin == nullptr && destination == nullptr)	//finds the vertices associated with the names
	{
		if (vertices[*i]->name == v1)
			origin = vertices[*i];
		if (vertices[*i]->name == v2)
			destination = vertices[*i];
		i++;
	}
	delete i;

	Edge* new_edge = new Edge(destination, weight);	//make the edge
	origin->edge.push_back(new_edge);				//add to vector

}

void Graph::add_Edge(Vertex* origin, Vertex* destination, int& weight)
{
	Edge* new_edge = new Edge(destination, weight);	//make the edge
	origin->edge.push_back(new_edge);				//add to vector
}

void Graph::add_vertex(std::string& name)
{
	Vertex* new_vertex = new Vertex(name);
	vertices.push_back(new_vertex);

}

void Graph::display_edges()
{

}

void Graph::BFTraversal()
{
	//CHANGING ALL THE BOOLS TO TRUE WILL CAUSE THIS TO FAIL IF RUN AGAIN. Depends on if cog would like to run multiple tests in one go
	Vertex* current = vertices[0];	//start at the start? or boulder? writeup sucks.

	std::queue<Vertex*> q;

	std::cout << current->name << std::endl;
	current->have_visited = true;
	q.push(current);

	while (!q.empty())
	{
		current = q.front();	//set to oldest
		q.pop();	//remove the oldest to update queue
		for (unsigned int i = 0; i < current->edge.size(); i++)
		{
			if (current->edge[i].v->have_visited == false)
			{
				current->edge[i].v->have_visited = true;
				std::cout << current->edge[i].v->name << std::endl;
				q.push(current->edge[i].v);
			}
		}
	}
}

void Graph::BFTraversal(std::string& startingCity)
{
	//CHANGING ALL THE BOOLS TO TRUE WILL CAUSE THIS TO FAIL IF RUN AGAIN. Depends on if cog would like to run multiple tests in one go
	Vertex* current = nullptr;
	int* j = new int(0);
	while (current == nullptr)
	{
		if (vertices[*j]->name == startingCity)
			current = vertices[*j];
		j++;	//*j++; ?? if this errors, try the reference (deference? kill me)
	}
	std::queue<Vertex*> q;

	std::cout << current->name << std::endl;
	current->have_visited = true;
	q.push(current);

	while (!q.empty())
	{
		current = q.front();	//set to oldest
		q.pop();	//remove the oldest to update queue
		for (int i = 0; i < current->edge.size(); i++)
		{
			if (current->edge[i].v->have_visited == false)
			{
				current->edge[i].v->have_visited = true;
				std::cout << current->edge[i].v->name << std::endl;
				q.push(current->edge[i].v);
			}
		}
	}
}

void Graph::BFTraversal(Vertex* startingCity)
{
	Vertex* current = startingCity;
	std::queue<Vertex*> q;

	std::cout << current->name << std::endl;
	current->have_visited = true;
	q.push(current);

	while (!q.empty())
	{
		current = q.front();	//set to oldest
		q.pop();	//remove the oldest to update queue
		for (int i = 0; i < current->edge.size(); i++)
		{
			if (current->edge[i].v->have_visited == false)
			{
				current->edge[i].v->have_visited = true;
				std::cout << current->edge[i].v->name << std::endl;
				q.push(current->edge[i].v);
			}
		}
	}
}

void Graph::shortest_distance(std::string& o, std::string& d)
{
	//Dijakstra's Algorithm
	Vertex* origin = nullptr;
	Vertex* destination = nullptr;

	int* i = new int(0);
	while (origin == nullptr && destination == nullptr)	//finds the vertices associated with the names
	{
		if (vertices[*i]->name == o)
			origin = vertices[*i];
		if (vertices[*i]->name == d)
			destination = vertices[*i];
		i++;
	}
	delete i;
}

void Graph::shortest_distance(Vertex* origin, Vertex* destination)
{
	//Dijakstra's Algorithm

}

//****************//
//---END GRAPH--- //
//****************//
