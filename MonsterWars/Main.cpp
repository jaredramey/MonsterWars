#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <list>
#include <Windows.h>
#include "Entity .h"
#include "MWMath.h"

using namespace std;

//Globals
list<Entity> Entities = list<Entity>();

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

	//Parse .bin file
	ReadFile(file);

	//Output all names
	for (list<Entity>::iterator it = Entities.begin(); it != Entities.end(); it++)
	{
		unsigned short curEntTypeID = -1;
		curEntTypeID = it->EntityTypeID;

		switch (curEntTypeID)
		{
		case 0:
			cout << "Health Pickup" << endl;
			it->CollisionRadius = 10;
			it->FOV = 0;
			break;
		case 1:
			cout << "Chest" << endl;
			it->CollisionRadius = 20;
			it->FOV = 0;
			break;
		case 2:
			cout << "Trap" << endl;
			it->CollisionRadius = 64;
			it->FOV = 0;
			break;
		case 3:
			cout << "Troll" << endl;
			it->CollisionRadius = 12;
			it->FOV = 45;
			break;
		case 4:
			cout << "Imp" << endl;
			it->CollisionRadius = 10;
			it->FOV = 65;
			break;
		case 5:
			cout << "Ogre" << endl;
			it->CollisionRadius = 25;
			it->FOV = 90;
			break;
		default:
			cout << "Error: Invalid Entity Type ID" << endl;
			break;
		}
	}

	for (list<Entity>::iterator it = Entities.begin(); it != Entities.end(); it++)
	{
		//Check collisions
		for (list<Entity>::iterator iv = Entities.begin(); iv != Entities.end(); iv++)
		{
			if (IsOverlapping(it->Pos, it->CollisionRadius, iv->Pos, iv->CollisionRadius))
			{
				cout << it->UniqueID << " and " << iv->UniqueID << " are overlapping" << endl;
			}
		}
	}

	while (inFOVTest == true)
	{
		cout << "Please input Unique ID of the monster you wish to FOV test: " << endl;
		cin >> IDtoCheck;
		for (list<Entity>::iterator it = Entities.begin(); it != Entities.end(); it++)
		{
			if (it->UniqueID == IDtoCheck)
			{
				for (list<Entity>::iterator iv = Entities.begin(); iv != Entities.end(); iv++)
				{
					if (CanSee(it->Pos, it->Fwd, iv->Pos, it->FOV))
					{
						cout << it->UniqueID << " can see " << iv->UniqueID << endl;
					}
				}
			}
		}
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

	ifstream file(filePath, ios::in | ios::binary | ios::ate);

	if (file.is_open())
	{
		//start at the begining of the file
		file.seekg(0, ios::beg);

		file.read((char*)&numberOfEntities, sizeFor_NumberOfEnteties);
		cout << "Creating " << numberOfEntities << " enteties." << endl;
		for (int i = 0; i < numberOfEntities; i++)
		{
			//create a new temp entity to store info in
			Entity entity = Entity();
			//move to the start of the new entity
			file.seekg(4 + (32 * i), ios::beg);
			//Take in the unique ID
			file.read((char*)&entity.UniqueID, 2);

			//Move up two bytes as per spec
			file.seekg(4 + (32 * i) + 2, ios::beg);
			//Grab Entity Type ID
			file.read((char*)&entity.EntityTypeID, 2);

			//Move up four bytes as per spec
			file.seekg(4 + (32 * i) + 4, ios::beg);
			//Grab the position x coord
			file.read((char*)&entity.Pos.x, 4);
			//do the same thing for Y
			file.seekg(4 + (32 * i) + 8, ios::beg);
			file.read((char*)&entity.Pos.y, 4);

			//repeat what was done for pos for foward
			//Move up four bytes as per spec
			file.seekg(4 + (32 * i) + 12, ios::beg);
			//Grab the position x forward
			file.read((char*)&entity.Fwd.x, 4);
			//do the same thing for Y
			file.seekg(4 + (32 * i) + 16, ios::beg);
			file.read((char*)&entity.Fwd.y, 4);

			Entities.push_back(entity);
		}
	}
	else
	{
		cout << "Unable to open file" << endl;
	}
}

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