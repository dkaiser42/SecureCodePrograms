
#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

//Decleration for creature class
class Creature{
	private:
		string name;
		string description;
		int lifePoints;
		int hitPoints;
		
	public:
		Creature(string, string, int, int); //implemented
		void printCreature(int); //implemented
		void setName(string n){
			name = n;
		}
		void setDescription(string d){
			description = d;
		}
		void setLifePoints(int l){
			lifePoints = l;
		}
		void setHitPoints(int h){
			hitPoints = h;
		}
		string getName(){
			return name;
		}
		string getDescription(){
			return description;
		}
		int getLifePoints(){
			return lifePoints;
		}
		int getHitPoints(){
			return hitPoints;
		}
};


//Constructor for class
Creature::Creature(string n, string d, int l, int h){
	name = n;
	description = d;
	lifePoints = l;
	hitPoints = h;
}


//Function neatly prints out all of the attributes of the creature
void Creature::printCreature(int number){
	cout << endl << "**********************************************************************************************************************\n\n";
	cout << "CREATURE " << number << ":\n";
	cout << "NAME:\t" << name << endl;
	cout << "DESCRIPTION:\n";
	cout << setw(15) << " " << description << endl;
	cout << "LIFE POINTS:\t\t" << lifePoints << endl;
	cout << "HIT POINTS:\t\t" << hitPoints << endl;
	cout << endl << "**********************************************************************************************************************\n\n";
}
#endif