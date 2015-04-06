#ifndef GRAPH_H
#define GRAPH_H
#include<vector>
#include<string>

struct Vertex;

struct Edge
{
	//construct/destruct
	Edge();
	Edge(Vertex*, int);
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

	std::string name;
	std::vector<Edge*> edge;
};


class Graph
{
public:
	//construct/destruct
	Graph();
	~Graph();

	void add_Edge(std::string&, std::string&, int&);	//v1, v2, weight
	void add_Edge(Vertex*, Vertex*, int&);
	void add_vertex(std::string&);	//name
	void add_vertex(Vertex*);
	void display_edges();
	void BFTraversal();
	void BFTraversal(std::string&);
	void BFTraversal(Vertex*);
	void shortest_path(std::string&, std::string&);
	void shortest_distance(Vertex*, Vertex*);			//return T, distnace?
	void shortest_distance(std::string&, std::string&);	//^^

	void road_trip();	//extra credit search. Probably requires a lot of initial setup to reconnect the vertices after zoombies
						//Starts from Boulder, hard code it? Only 10 vertices in alphabetical, should be fine.

	//Another thing to considder in this is to make a 'get_vertex(std::String name)' function to return a verticie and ditch the expansive search
	//faster way is to compare and hard code an answer for a string character. Alphabetical, after all.
	//ugly though.

protected:

private:
	std::vector<Vertex*> vertices;

};

#endif //GRAPH_H
