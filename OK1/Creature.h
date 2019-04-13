
#ifndef Creature_H
#define Creature_H

#include <iostream>
#include <string>

using namespace std;

class Creature
{
	private:
		string name;
		string description;
		int HP;		//Hitpoints, AKA Life points
		int DPS;	//Damage per second, or Damage per attack for this program

	public:

		//Default constructor
		Creature();

		//Constructor
		Creature(string, string, int, int);

		//Accessors for getting HP and DPS
		int getHP();
		int getDPS();

		//Accessors for name and description
		string getName();
		string getDescription();

		//Mutators
		void setName(string);
		void setDescription(string);
		void setHP(int);
		void setDPS(int);
};

#endif