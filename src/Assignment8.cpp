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

int main(int* argc, char* argv)
{
	Graph* g = new Graph();
	int select = 0;

	cout << "1. Print Verticies" << endl
		<< "2. Find districts" << endl
		<< "3. Find shortest path" << endl
		<< "4. Find shortest distance" << endl
		<< "5. Extra credit" << endl;
	cin >> select;

	switch(select)
	{
	case 1:	//Print Verticies
		//
		break;
	case 2:	//Find Districts
		//
		break;
	case 3:	//Find Shortest Path
		//
		break;
	case 4:	//Find Shortest Distance
		//
		break;
	case 5:	//Extra Credit
		//
		break;
	default:
		//not an option
		cout << "---That was not an option---" << endl;
		break;


	return 0;
}