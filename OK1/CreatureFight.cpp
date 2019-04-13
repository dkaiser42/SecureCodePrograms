
#include "LinkedListTemplate.h"
#include "Creature.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
	//For when the user wants to play again, or quit
	bool Quit;

	//Creating the list
	LinkedList<Creature> Creatures;

	//User variables
	string Player1name;
	string Player2name;
	char userInput;

	//Variables for file input
	ifstream inFile;
	string name, description, tempName;
	int HP, DPS;
	
	//Variables for the game
	int Player1input, Player2input, totalHitP1, totalHitP2, Player1HP, Player2HP, randomInt;
	int Player1DPS, Player2DPS;
	string tempNameP1, tempNameP2;
	srand(time(NULL));

	Creature oneCreature;
	
	//Counter used when reading the file
	int added = 0;	

	inFile.open("creatureFile.txt");
		if(inFile.good())
		{
			//Gathering data from the file		
			while(!inFile.eof())
			{
				getline(inFile, name);
				getline(inFile, description);
				inFile >> HP;
				inFile >> DPS;
				inFile.ignore();
				/*Couldn't get a recursive Binary Search function to work. Resorted to a simple search instead.
				
				int result = Creatures.binarySearch(Creatures.getLength()-1, 0, Creatures, name);
				
				if (result == 1)
					cout << "\n" << name << " was skipped because it is already in the list.";
				*/

				//Uses a simple search to see if the creature is already in the list.
				//If they are, skip the creature.

				int result = Creatures.simpleSearch(name);
				
				if (result == 1)
					cout << "\n\n----" << name << " was skipped because it is already in the list ----";

				//If not found, it will append the creature to the list
				else
				{
					//Create the creature
					Creature oneCreature(name, description, HP, DPS);

					//Append it to the list
					Creatures.appendNode(oneCreature);

			
				/*	---Had difficulties with merge sort---
					if (Creatures.getLength() >= 2)
						mergeSort();
				*/
					//Update counter
					(added)++;

					cout << "\n\n" << oneCreature.getName();
					cout << " was successfully added.";
				}
			}
		}
		
		else
			cout << "\n\nError accessing file.";

	cout << "\n\nSuccessfully added " << added << " creatures to the list.";
	inFile.close();

//Get the player's names, also the re-start point

cout << "\n\n_________________________";
cout << "\nREADY TO FIGHT!";

while(!Quit)
{
	cout << "\n\nPLAYER 1... Enter your name: ";
	cin >> Player1name;
	cout << "\nPLAYER 2... Enter your name: ";
	cin >> Player2name;

	//Prompt user if they want a detailed list of all creatures
	do
	{
		cout << "\nWould you like to see each creatures stats? (Y/N) ";
		cin >> userInput;
		userInput = toupper(userInput);
		
		if (userInput != 'Y' || userInput != 'N')
			cout << "\nAnswer must be Y (YES) or N (NO)";
	
	}while(userInput != 'Y' && userInput != 'N');

	if (userInput == 'Y')
		Creatures.printCreatures();

	//Players pick their fighters

	cout << "\n\n" << Player1name << ", CHOOSE YOUR FIGHTER!";
	cout << "\n********************************\n";
	Creatures.displayList();
	cout << "\n********************************\n";
	cin >> Player1input;

	//Create temporary variables to hold the data used during the game
	tempNameP1 = Creatures.getNodeValue(Player1input-1)->getName();
	Player1HP = Creatures.getNodeValue(Player1input-1)->getHP();
	Player1DPS = Creatures.getNodeValue(Player1input-1)->getDPS();

	cout << "\n" << Player1name << ", you chose " << tempNameP1;

	cout << "\n\n" << Player2name << ", CHOOSE YOUR FIGHTER!";
	cout << "\n********************************\n";
	Creatures.displayList();
	cout << "\n********************************\n";
	cin >> Player2input;

	//Create temporary variables to hold the data used during the game
	tempNameP2 = Creatures.getNodeValue(Player2input-1)->getName();
	Player2HP = Creatures.getNodeValue(Player2input-1)->getHP();
	Player2DPS = Creatures.getNodeValue(Player2input-1)->getDPS();

	cout << "\n" << Player2name << ", you chose " << tempNameP2;


//					***** The gameplay *****
//	3 rounds, first one to defeat the other wins. If 3 rounds pass and
//	both players are alive, the one with the highest HP wins.
//	Will also check for a tie.

	for(int i=1; i<4; i++)
	{
		cout << "\n\n****** ROUND " << i << " *****\n";
		
		//	If the user doesn't input ENTER, they cannot attack
		do
		{
			cout << "\n" << Player1name << ", hit ENTER to order your attack!\n";
			cin.ignore();
			cin.get();
			
			if (cin.get() != '\n')
				cout << "\nYour creature didn't understand your command. Try again.";
		
		}while(cin.get() != '\n');

		//Generate a random int 1-6
		randomInt = rand() % 6 + 1;

		cout << "\n" << Player1name << " rolled a " << randomInt;

		//Damage done is (randomInt x the creature's damage) , subtract it from the HP
		totalHitP1 = randomInt * Player1DPS;
		Player2HP -= totalHitP1;
		
		//If HP is 0 or below, the creature is dead
		if (Player2HP <= 0)
		{
			cout << "\n\nKnockout!! " << Player2name << " has been defeated!";
			break;
		}
		
		else
		{
			cout << "\n\n" << Player1name << " Hit a " << totalHitP1 << "!\n";
			cout << Player2name << " Now has " << Player2HP << " Hitpoints remaining!\n";
			
			//	If the user doesn't input ENTER, they cannot attack
			do
			{
				cout << "\n" << Player2name << ", hit ENTER to order your attack!\n";
				cin.ignore();
				cin.get();

				if (cin.get() != '\n')
					cout << "\nYour creature didn't understand your command. Try again.";
			
			}while(cin.get() != '\n');

			//Generate a random int 1-6
			randomInt = rand() % 6 + 1;

			cout << "\n" << Player2name << " rolled a " << randomInt;

			//Once again, damage is randomInt x DPS
			totalHitP2 = randomInt * Player2DPS;
			Player1HP -= totalHitP2;
			
			//HP check
			if (Player1HP <=0)
			{
				cout << "\n\nKnockout!! " << Player1name << " has been defeated!";
				break;
			}

			else
			{
				cout << "\n\n" << Player2name << " Hit a " << totalHitP2 << "!\n";
				cout << Player1name << " Now has " << Player1HP << " Hitpoints remaining!\n";
			}

		}

	}

	//If they survived the fight, the player with the most HP left wins
	if (Player1HP >=0 || Player2HP >= 0)
	{
		//If player 1 has more HP, they win
		if (Player1HP > Player2HP)
		{	
			cout << "\n" << tempNameP1 << " had more hitpoints, so they are the winner!";
			cout << "\nCongratulations " << Player1name << ", you have won!";
		}

		//If player 2 has more HP, they win
		else if (Player2HP > Player1HP)
		{
			cout << "\n" << tempNameP2 << " had more hitpoints, so they are the winner!";
			cout << "\nCongratulations " << Player2name << ", you have won!";
		}

		//If neither player's HP is greatest, it must be a tie
		else
			cout << "\n\nIts a tie!	Good fight!";
	}

	cout << "\n\nWould you like to play again? (Y/N) ";
	cin >> userInput;
	userInput = toupper(userInput);

	if (userInput == 'N')
	{
		cout << "\n\nGoodbye!";
		return 0;
	}
}

}