#ifndef GRAPH_H
#define GRAPH_H
#include<vector>
#include<string>

typedef struct Vertex_ Vertex;

//template<typename T>
struct Edge
{
	//construct/destruct
	Edge();
	~Edge();

	Vertex* v;
	int weight;
};

//template<typename T>
struct Vertex
{
	//construct/destruct
	Vertex();
	~Vertex();

	std::string name;
	std::vector<Edge> edge;
};

//template<typename T>
class Graph
{
public:
	//construct/destruct
	Graph();
	~Graph();

	void add_Edge(std::string, std::string, int);	//v1, v2, weight
	void add_vertex(std::string);	//name
	void display_edges();

protected:

private:
	//std::vector<Edge> edges;
	std::vector<Vertex> verticies;
};

#endif //GRAPH_H