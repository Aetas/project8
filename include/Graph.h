#ifndef GRAPH_H
#define GRAPH_H
#include<vector>
#include<string>

struct Vertex;

struct Edge
{
	//construct/destruct
	Edge();
	Edge(Vertex*, int&);
	~Edge();

	Vertex* v;
	int weight;
};

struct Vertex
{
	//construct/destruct
	Vertex();
	Vertex(std::string&);	//make with name
	~Vertex();

	bool have_visited;
	int district;

	std::string name;
	std::vector<Edge*> edge;
};

class Graph
{
public:
	//construct/destruct
	Graph();
	~Graph();

	//by name
	void add_edge(std::string&, std::string&, int);	//v1, v2, weight
	void add_vertex(std::string&);	//name
	void print_vertices();
	void display_edges(Vertex*);
	void BFTraversal();
	void BFTraversal(std::string&);
	void shortest_path(std::string&, std::string&);
	void shortest_distance(std::string&, std::string&);	//return T, distnace?
	void assign_districts();

	//from-vertex functions
	void add_edge(Vertex*, Vertex*, int);
	void add_vertex(Vertex*);
	void BFTraversal(Vertex*);
	void shortest_distance(Vertex*, Vertex*);			//return T, distnace?

	//"EEEEEEZ MONEY" - Bizzaro Flame
	void road_trip();	//extra credit search. Probably requires a lot of initial setup to reconnect the vertices after zoombies
						//Starts from Boulder, hard code it? Only 10 vertices in alphabetical, should be fine.

	//Another thing to considder in this is to make a 'get_vertex(std::String name)' function to return a verticie and ditch the expansive search
	//faster way is to compare and hard code an answer for a string character. Alphabetical, after all.
	//ugly though.

protected:

private:
	std::vector<Vertex*> vertices;
	Vertex* district_log[5][10];

	void reset_visited();	//private because why not
};

#endif //GRAPH_H
