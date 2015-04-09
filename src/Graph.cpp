
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
		std::cout << (*it)->district << ":" << (*it)->name << "->";
		display_edges(*it);	//optional, functional implementation
	}
	std::cout << std::endl;
}

void Graph::display_edges(Vertex* home)
{
	if (home->edge.size() > 0)	//if there is an edge (always is, this is for 'bullet proofing')
	{
		std::cout << home->edge[0]->v->name;	//cout the first name always
		if (home->edge.size() > 1)				//if there is another/more edges, print them in the format.
			for (std::vector<Edge*>::iterator jt = home->edge.begin(); jt != home->edge.end(); jt++)	//do all of them.
				std::cout << "**" << (*jt)->v->name;
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

void Graph::shortest_distance(std::string& o, std::string& d)
{
	//Dijakstra's Algorithm
	Vertex* current = nullptr;
	Vertex* fin = nullptr;

	int f = 0;
	while (current == nullptr || fin == nullptr)	//finds the vertices associated with the names
	{
		if (vertices[f]->name == o)
			current = vertices[f];
		if (vertices[f]->name == d)
			fin = vertices[f];
		f++;
	}
	
	Vertex* min = nullptr;
	int min_dist = INT_MAX;
	std::vector<Vertex*> solved;

	//set all distances to max
	for (unsigned int i = 0; i < vertices.size(); i++)
		vertices[i]->distance = INT_MAX;

	//set unique start properties
	current->previous = nullptr;
	current->distance = 0;
	solved.push_back(current);
		
	//while final has not been visited
	while (fin->have_visited == false)
	{
		//current->have_visited = true;
		min_dist = INT_MAX;
		min = nullptr;

		for (std::vector<Vertex*>::iterator it = solved.begin(); it != solved.end(); it++)
		{
			//current = *it;
			for (std::vector<Edge*>::iterator jt = (*it)->edge.begin(); jt != (*it)->edge.end(); jt++)
			{
				if ((*jt)->v->have_visited == false)
				{
					(*jt)->v->distance = current->distance + (*jt)->weight;
					if ((*jt)->v->distance >((*jt)->weight + current->distance))
						(*jt)->v->distance = ((*jt)->weight + current->distance);
					if ((*jt)->v->distance < min_dist)
					{
						min_dist = (*jt)->v->distance;
						min = (*jt)->v;
					}
				}
			}
		}
		min->previous = current;    //set prev.
		current = min;              //move on to next
		solved.push_back(min);  	//add to solved
	}
	//PRINT path()?
}

void Graph::reset_visited()
{
	for (unsigned int i = 0; i < vertices.size(); i++)
		vertices[i]->have_visited = false;
}

void Graph::assign_districts()
{
	int district_no = 0;	//start at 0 because it incriments it before starting a new district so that I can start in the loop

	std::queue<Vertex*> q;
	Vertex* current = nullptr;

	for (std::vector<Vertex*>::iterator it = vertices.begin(); it != vertices.end(); it++)
	{
		if ((*it)->district < 1)
		{	
			district_no++;
			(*it)->district = district_no;	// = ++district_no?
			q.push(*it);
		}

		while (!q.empty())
		{
			current = q.front();	//set to oldest
			current->district = district_no;
			q.pop();				//remove the oldest to update queue
			for (std::vector<Edge*>::iterator jt = (*it)->edge.begin(); jt != (*it)->edge.end(); jt++)
				q.push((*jt)->v);	//push all edges into the queue
		}
	}

}
//****************//
//---END GRAPH--- //
//****************//
