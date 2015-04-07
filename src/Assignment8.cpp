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
	if (!in_file.is_open())
	{
		//fail case handling, direct input? 
		 
	}
	else
	{
		//FROM FILE:
		//0 - Boston	| 1 - Boulder
		//2 - Chicago	| 3 - Disneyland
		//4 - Miami		| 5 - New Orleans
		//6 - New York	| 7 - Portland
		//8 - San Fran.	| 9 - Seattle
		struct string_int_array
		{ string city[10]; string edge[10]; } text_info;
		//originally edge was an int, but the getline hated me for it. So now I cast to int when adding edges.
		while (!in_file.eof())
		{
			in_file.ignore(1000, '\n');	//ignore top line - the cities.
			for (int i = 0; i < 10; i++)
			{
				getline(in_file, text_info.city[i], ',');		//grab city name
				for (int j = 0; j < 9; j++)
					getline(in_file, text_info.edge[j], ',');	//grab the comma-deliminated distances
				getline(in_file, text_info.edge[9], '\n');		//lines end in... line endings.
			}
		}
		//now that the file has been parsed, build the graph
		for (int i = 0; i < 10; i++)	//all 10 of them
		{
			g->add_vertex(text_info.city[i]);	//names are in order
			for (int j = 0; j < 10; j++)		//add edges at the same time to take advantage of the existing for loop
			{
				if (std::stoi(text_info.edge[j]) != -1 || std::stoi(text_info.edge[j]) != 0)		//-1 = not connected, 0 = self -- no edge in either case
					g->add_edge(text_info.city[i], text_info.city[j], std::stoi(text_info.edge[j]));//stoi because weight is an int, unfortunately the functional bit makes it so I cant deference it
			}
		}
	}

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
		else	//other/default
		{
			//not an option
			cout << "---That was not an option---" << endl;
		}
	}

	return 0;
}