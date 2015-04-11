
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<queue>
#include"../include/Graph.h"

#ifndef MAX_INT
#define MAX_INT 999999

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
	previous = nullptr;
}

Vertex::Vertex(std::string& nm)
{
	name = nm;
	have_visited = false;
	district = -1;
	previous = nullptr;
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

void Graph::add_edge(int& key_o, int& key_d, int weight)
{
	Edge* new_edge = new Edge(vertices[key_d], weight);	//make the edge
	vertices[key_o]->edge.push_back(new_edge);			//add to vector
}

void Graph::add_vertex(std::string& name)
{
	Vertex* new_vertex = new Vertex(name);
	vertices.push_back(new_vertex);
}

void Graph::print_vertices()
{
	for (std::vector<Vertex*>::iterator it = vertices.begin(); it != vertices.end(); it++)
	{
		std::cout << (*it)->district << ":" << (*it)->name << "-->";
		display_edges(*it);	//optional, functional implementation
		std::cout << std::endl;
	}
}

void Graph::display_edges(Vertex* home)
{
	if (home->edge.size() > 0)	//if there is an edge (always is, this is for 'bullet proofing')
	{
		std::cout << home->edge[0]->v->name;	//cout the first name always
		if (home->edge.size() > 1)				//if there is another/more edges, print them in the format.
			for (std::vector<Edge*>::iterator jt = home->edge.begin()+1; jt != home->edge.end(); jt++)	//do all of them.
				std::cout << "***" << (*jt)->v->name;
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
	int j = 0;
	std::vector<Vertex*>::iterator jt = vertices.begin();
	while (current == nullptr)
	{
		if ((*jt)->name == startingCity)
			current = *jt;
		jt++;
	}
	std::queue<Vertex*> q;

	std::cout << current->name << std::endl;
	current->have_visited = true;
	q.push(current);

	while (!q.empty())
	{
		current = q.front();	//set to oldest
		q.pop();	//remove the oldest to update queue
		for (std::vector<Edge*>::iterator it = current->edge.begin(); it != current->edge.end(); it++)
		{
			if ((*it)->v->have_visited == false)
			{
				(*it)->v->have_visited = true;
				std::cout << (*it)->v->name << std::endl;
				q.push((*it)->v);
			}
		}
	}
	reset_visited();
}

Vertex* Graph::shortest_path(std::string& o, std::string& d)
{
	Vertex* current = nullptr;
	Vertex* fin = nullptr;

	std::vector<Vertex*>::iterator ft = vertices.begin();
	while ((current == nullptr || fin == nullptr))	//finds the vertices associated with the names
	{
		if ((*ft)->name == o)
			current = *ft;
		if ((*ft)->name == d)
			fin = *ft;
		ft++;
		if (ft == vertices.end())
			break;
	}

	if (current == nullptr || fin == nullptr)
	{
		std::cout << "One or more cities doesn\'t exist" << std::endl; 
		return nullptr;
	}
	if (current->district == -1)
	{
		std::cout << "Please identify the districts before checking distances" << std::endl;
		return nullptr;
	}
	if (current->district != fin->district)	//they cannot be reached if they are not connected
	{
		std::cout << "No safe path between cities" << std::endl;
		return nullptr;
	}

	//ensure defaults
	for (std::vector<Vertex*>::iterator it = vertices.begin(); it != vertices.end(); it++)
		(*it)->distance = MAX_INT, (*it)->previous = nullptr;

	std::queue<Vertex*> path;
	std::queue<Vertex*> q;

	current->have_visited = true;	//initial
	current->distance = 0;			//no edges.
	q.push(current);
	path.push(current);	//path starts 

	while (!q.empty())
	{
		current = q.front();	//set to oldest
		q.pop();				//remove the oldest to update queue
		for (std::vector<Edge*>::iterator it = current->edge.begin(); it != current->edge.end(); it++)
		{
			if ((*it)->v->have_visited == false)
			{
				//(*it)->v->have_visited = true;
				(*it)->v->distance = current->distance + 1;
				(*it)->v->previous = current;
				q.push((*it)->v);
			}
		}
		current->have_visited = true;
	}
	reset_visited();

	return fin;
}

Vertex* Graph::shortest_distance(std::string& o, std::string& d)
{
	//Dijakstra's Algorithm
	Vertex* temp = nullptr;
	Vertex* fin = nullptr;

	std::vector<Vertex*>::iterator ft = vertices.begin();
	while ((temp == nullptr || fin == nullptr))	//finds the vertices associated with the names
	{
		if ((*ft)->name == o)
			temp = *ft;
		if ((*ft)->name == d)
			fin = *ft;
		ft++;
		if (ft == vertices.end())
			break;
	}
	if (temp == nullptr || fin == nullptr)
	{
		std::cout << "One or more cities doesn\'t exist" << std::endl;
		return nullptr;
	}
	if (temp->district == -1)
	{
		std::cout << "Please identify the districts before checking distances" << std::endl;
		return nullptr;
	}
	if (temp->district != fin->district)	//they cannot be reached if they are not connected
	{
		std::cout << "No safe path between cities" << std::endl;
		return nullptr;
	}
	
	Vertex* min = nullptr;
	int min_dist = MAX_INT;
	std::vector<Vertex*> solved;

	//set all distances to max, all previous to null
	for (std::vector<Vertex*>::iterator it = vertices.begin(); it != vertices.end(); it++)
		(*it)->distance = MAX_INT, (*it)->previous = nullptr;

	//set unique start properties
	temp->previous = nullptr;
	temp->distance = 0;
	temp->have_visited = true;
	solved.push_back(temp);

	while (fin->have_visited == false)
	{
		min_dist = MAX_INT;	//to next city from previous min
		min = nullptr;

		for (std::vector<Vertex*>::iterator it = solved.begin(); it != solved.end(); it++)	//each vertex in solved
		{
			for (std::vector<Edge*>::iterator jt = (*it)->edge.begin(); jt != (*it)->edge.end(); jt++)	//each edge of that vertex (from solved)
			{
				if ((*jt)->v->have_visited == false)	//never visited, setup
				{
					(*jt)->v->distance = (*it)->distance + (*jt)->weight;
					if ((*jt)->v->distance < min_dist)
					{
						min_dist = (*jt)->v->distance;
						min = (*jt)->v;
						temp = *it;
					}
				}
			}
		}
		min->have_visited = true;
		solved.push_back(min);
		min->previous = temp;		//have to assign this after the best case/true min has been found.
	}
	reset_visited();
	return fin;
}

void Graph::reset_visited()
{
	for (std::vector<Vertex*>::iterator it = vertices.begin(); it != vertices.end(); it++)
		(*it)->have_visited = false;
}

void Graph::assign_districts()
{
	int district_no = 0;	//start at 0 because it incriments it before starting a new district so that I can start in the loop

	std::queue<Vertex*> q;
	Vertex* current = nullptr;

	for (std::vector<Vertex*>::iterator it = vertices.begin(); it != vertices.end(); it++)
	{
		if ((*it)->district < 0)
		{	
			district_no++;
			(*it)->district = district_no;	// = ++district_no; (?)
			q.push(*it);
		}

		while (!q.empty())	//this serves to assign the same district no. to every edge in the queue
		{
			current = q.front();	//set to oldest
			current->district = district_no;
			for (std::vector<Edge*>::iterator jt = current->edge.begin(); jt != current->edge.end(); jt++)
			{
				if ((*jt)->v->district < 0)
				{
					//(*jt)->v->district = district_no;
					//add a push cycle here? the one below may be excessive
					q.push((*jt)->v);
				}
			}
			q.pop();				//remove the oldest to update queue
		}
	}

}
//****************//
//---END GRAPH--- //
//****************//

#endif	//MAX_INT