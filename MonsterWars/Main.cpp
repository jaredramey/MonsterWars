#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <list>
#include "Entity .h"

using namespace std;

//Globals
list<Entity> Entities;

//Functions
void ReadFile(string filePath);



/*
SUDO
- Grab first unsigned int in file to see how many times I need to loop
- Loop through x times and make x amount of entities
- Once entities are made have all entities output their information
- Check to see who is overlapping with who and output that list
- Allow user to do FOV test however many times they want
*/
//Main Loop
int main()
{
	bool inFOVTest = true;
	unsigned short IDtoCheck;
	string file = "C:/Users/jared.ramey/Documents/Visual Studio 2015/Projects/MonsterWars/EscalationProgrammerTest.bin";

	ReadFile(file);

	while (inFOVTest == true)
	{
		cout << "If you wish to exit FOV testing please hit ESC" << endl;
		cout << "Please input Unique ID of the monster you wish to FOV test: " << endl;
		cin >> IDtoCheck;
	}

	getchar();
	return 0;
}

//Function defs
//function to open up the file
//TODO: Parse info into an Entity
void ReadFile(string filePath)
{
	unsigned int numberOfEntities;
	//sizes based off of spec
	streampos sizeFor_NumberOfEnteties = 4;
	streampos sizeFor_Entity = 32;
	char* memBlock;

	ifstream file(filePath, ios::in | ios::binary | ios::ate);
	//if (file.is_open())
	//{
	//	streampos size;
	//	char * memBlock;

	//	//how much data you're wanting to read
	//	size = file.tellg();
	//	//variable to store in
	//	memBlock = new char[size];

	//	//seek to pos
	//	file.seekg(0, ios::beg);
	//	//read from starting pos x amount and store to variable
	//	file.read(memBlock, size);

	//	file.close();

	//	cout << "The entire file content is now in memory." << endl;

	//	delete[] memBlock;
	//}
	if (file.is_open())
	{
		file.seekg(0, ios::beg);
		//starting out I don't need to move since i'm at the start
		memBlock = new char[sizeFor_NumberOfEnteties];

		unsigned int numofEnts = 0;

		file.read((char*)&numofEnts, 4);

		cout << "meow";
	}
	else
	{
		cout << "Unable to open file" << endl;
	}
}