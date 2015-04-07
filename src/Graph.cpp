
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

Edge::Edge(Vertex* vertex, int& wt)
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
	district = -1;
}

Vertex::Vertex(std::string& nm)
{
	name = nm;
	have_visited = false;
	district = -1;
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

void Graph::add_edge(std::string& v1, std::string& v2, int weight)
{
	Vertex* origin = nullptr;
	Vertex* destination = nullptr;
	int* i = new int(0);	//RAII/fo shits
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

void Graph::add_edge(Vertex* origin, Vertex* destination, int weight)
{
	Edge* new_edge = new Edge(destination, weight);	//make the edge
	origin->edge.push_back(new_edge);				//add to vector
}

void Graph::add_vertex(std::string& name)
{
	Vertex* new_vertex = new Vertex(name);
	vertices.push_back(new_vertex);
}

void Graph::print_vertices()
{
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		std::cout << vertices[i]->district << ":" << vertices[i]->name << "->";
		display_edges(vertices[i]);	//optional, functional implementation
		/*if (vertices[i]->edge.size() > 0)	//if there is an edge (always is, this is for bullet proofing
		{
			std::cout << vertices[i]->edge[0]->v->name;	//cout the first name always
			if (vertices[i]->edge.size() > 1)				//if there is another/more edges, print them in the format.
				for (unsigned int j = 1; j < vertices[i]->edge.size(); j++)	//do all of them.
					std::cout << "**" << vertices[i]->edge[j]->v->name;
		}
		std::cout << std::endl;	*/
	}
}

void Graph::display_edges(Vertex* home)
{
	if (home->edge.size() > 0)	//if there is an edge (always is, this is for 'bullet proofing')
	{
		std::cout << home->edge[0]->v->name;	//cout the first name always
		if (home->edge.size() > 1)				//if there is another/more edges, print them in the format.
			for (unsigned int j = 1; j < home->edge.size(); j++)	//do all of them.
				std::cout << "**" << home->edge[j]->v->name;
	}
}

void Graph::BFTraversal()
{
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
			if (current->edge[i]->v->have_visited == false)
			{
				current->edge[i]->v->have_visited = true;
				std::cout << current->edge[i]->v->name << std::endl;
				q.push(current->edge[i]->v);
			}
		}
	}
	reset_visited();
}

void Graph::BFTraversal(std::string& startingCity)
{
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
		for (unsigned int i = 0; i < current->edge.size(); i++)
		{
			if (current->edge[i]->v->have_visited == false)
			{
				current->edge[i]->v->have_visited = true;
				std::cout << current->edge[i]->v->name << std::endl;
				q.push(current->edge[i]->v);
			}
		}
	}
	reset_visited();
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
			if (current->edge[i]->v->have_visited == false)
			{
				current->edge[i]->v->have_visited = true;
				std::cout << current->edge[i]->v->name << std::endl;
				q.push(current->edge[i]->v);
			}
		}
	}
}

void Graph::shortest_distance(std::string& o, std::string& d)
{
	//Dijakstra's Algorithm
	Vertex* origin = nullptr;
	Vertex* destination = nullptr;

	int f = 0;
	while (origin == nullptr && destination == nullptr)	//finds the vertices associated with the names
	{
		if (vertices[f]->name == o)
			origin = vertices[f];
		if (vertices[f]->name == d)
			destination = vertices[f];
		f++;
	}
	
}

void Graph::shortest_distance(Vertex* origin, Vertex* destination)
{
	//Dijakstra's Algorithm

}

void Graph::assign_districts()
{
	int dist_no = 1;
	int i = 0;

	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i]->district == -1)
		{
			vertices[i]->district = dist_no;
			for (unsigned int j = 0; j < vertices[i]->edge.size(); j++)
				vertices[i]->edge[j]->v->district = dist_no;
			dist_no++;
		}
	}
}

void Graph::reset_visited()
{
	for (unsigned int i = 0; i < vertices.size(); i++)
		vertices[i]->have_visited = false;
}
//****************//
//---END GRAPH--- //
//****************//
