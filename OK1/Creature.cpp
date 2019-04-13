
#include <iostream>
#include <string>
#include "Creature.h"

using namespace std;

//Constructor
Creature::Creature(string n, string d, int H, int D)
{
	name = n;
	description = d;
	HP = H;
	DPS = D;
}

//Deafult Constructor
Creature::Creature()
{

}

//Accessor functions

string Creature::getName()
{
	return name;
}

string Creature::getDescription()
{
	return description;
}

int Creature::getHP()
{
	return HP;
}

int Creature::getDPS()
{
	return DPS;
}

//Mutators

void Creature::setName(string n)
{
	name = n;
}
void Creature::setDescription(string d)
{
	description = d;
}
void Creature::setHP(int h)
{
	HP = h;
}
void Creature::setDPS(int damage)
{
	DPS = damage;
}