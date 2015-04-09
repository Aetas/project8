/*
// Derek Prince
// 4/1/15
// Program 8
// CSCI 2270 - CU Boulder
// Stupid Zombies and ****.
// Introduction to graphs - breadth-first searching

// Instructions and specifications in writeup/Assignment8Writeup.pdf
// Read file in doc/zombieCities.txt
*/
#ifndef NO_OF_CITIES
#define NO_OF_CITIES 15

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<queue>
#include"../include/Graph.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main(int argc, char* argv[])
{
	Graph* g = new Graph();

	std::ifstream in_file;
	in_file.open(argv[1]);

	if (in_file.is_open())	//START READ AND BUILD
	{
		//FROM FILE:
		//0  - Atlanta			| 1  - Boston
		//2  - Boulder			| 3  - Cheyenne
		//4  - Chicago			| 5  - Cleveland
		//6  - Disneyland		| 7  - Key West
		//8  - Miami			| 9  - New Orleans
		//10 - New York			| 11 - Portland
		//12 - San Francisco	| 13 - Seattle
		//14 - Yakima
		struct Text_info
		{ std::string city[NO_OF_CITIES]; std::string edge_weight[NO_OF_CITIES][NO_OF_CITIES]; } text_info;

		do
		{
			in_file.ignore(1000, '\n');						//ignore top line of all the names
			for (int i = 0; i < NO_OF_CITIES; i++)
			{
				getline(in_file, text_info.city[i], ',');	//grab city name
				g->add_vertex(text_info.city[i]);			//this has to be added first so that edges can have a destination
				for (int j = 0; j < NO_OF_CITIES-1; j++)
				{
					getline(in_file, text_info.edge_weight[i][j], ',');	//grab all comma-delim weights
				}
				getline(in_file, text_info.edge_weight[i][NO_OF_CITIES-1]);	//grab last weight that is delim. by \n
			}
			in_file.ignore(256);	//set eof bit so there are no longer 30 sets
		} while (!in_file.eof());
		//Connect vertices w/ edges
		for (int i = 0; i < NO_OF_CITIES; i++)
			for (int j = 0; j < NO_OF_CITIES; j++)	//go through the edges
				if (std::stoi(text_info.edge_weight[i][j]) > 0)	//dont add edges that don't exist
					g->add_edge(i, j, std::stoi(text_info.edge_weight[i][j]));	//pass origin key, destination key, weight
	}	//END READ AND BUILD

	int select = 0;

	while (select != 6)
	{
		cout << "1. Print Verticies" << endl
			<< "2. Find districts" << endl
			<< "3. Find shortest path" << endl
			<< "4. Find shortest distance" << endl
			<< "5. Extra credit" << endl
			<< "6. Quit" << endl;
		cin >> select;

		if (select == 1)	//Print Verticies
			g->print_vertices();
		
		if (select == 2)	//Find Districts
			g->assign_districts();

		if (select == 3)	//Find Shortest Path
		{
			std::string origin = "";
			std::string destination = "";

			cout << "Starting City?" << endl;
			//cin.ignore(1000, \n);
			getline(cin, origin);
			cout << "Ending city?" << endl;
			getline(cin, destination);
			//g->shortest_path(origin, destination);
		}
		if (select == 4)	//Find Shortest Distance
		{
			std::string origin = "";
			std::string destination = "";

			cout << "Starting City?" << endl;
			//cin.ignore(1000, \n);
			getline(cin, origin);
			cout << "Ending city?" << endl;
			getline(cin, destination);
			//g->shortest_distance(origin, destination);
		}
		if (select == 5)	//Extra Credit
		{
			//
		}
		if (select == 6)	//Quit
			cout << "Goodbye!" << endl;
		if (select > 6)
			cout << "---That was not an option.---\n\n";
	}

	return 0;
}

#endif //NO_OF_CITIES
