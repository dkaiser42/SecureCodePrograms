
#include <fstream>
#include "Creature.h"
#include "LinkedList.h"
#include <cstdlib>

using namespace std;

bool binarySearchForNomer(List<Creature>, string);
List<Creature> mergeSort(List<Creature>);
List<Creature> merge(List<Creature>, List<Creature>);
//void mergeSort(string, string, int);
//void merge(string, string, int);

int main(){
	ifstream infile;
	List<Creature> pokeDeck;

	infile.open("creatureFile.txt");
	if(!infile){
		cout << "creatureFile.txt not found, exiting program...\n";
		return 0;
	}
	
	int creatureCount = 0;
	while(!infile.eof()){
		string name;
		string description;
		int lifePoints;
		int hitPoints;
		
		getline(infile, name);
		getline(infile, description);
		infile >> lifePoints;
		infile >> hitPoints;
		infile.ignore();
		
		Creature singularPokemon(name, description, lifePoints, hitPoints);

		//if(binarySearchForNomer(pokeDeck, singularPokemon.getName()))
			//cout << name << " was skipped because it was already in the list.\n";
		//else{
			pokeDeck.appendNode(singularPokemon);
			cout << name << " was added to the list of creatures that can fight.\n";
			//pokeDeck = mergeSort(pokeDeck);
			++creatureCount;
		//}		
	}
	cout << creatureCount << " were added to the list of creatures.\n";
	
	GameStart:
		string user1Name;
		string user2Name;
		cin.ignore();
		cout << "\nPlayer 1 enter your username: ";
		getline(cin, user1Name);
		cout << "\nPlayer 2 enter your username: ";
		getline(cin, user2Name);
		
		char details;
		do{
			cout << "\nBefore you have to select your creatures,\n would you like to see the details of each one? (y/n)\n";
			cin >> details;
			
			if(details == 'y' or details == 'Y'){
				for(int i = 0; i < pokeDeck.getLength(); i++){
					cout << endl;
					pokeDeck.getNodeValue(i)->printCreature(i+1);
					cout << endl;
				}
			}
			else if(details != 'n' and details != 'N')
				cout << "That is not a valid input. Please try again.\n";
			
		}while(details != 'n' and details != 'N' and details != 'y' and details != 'Y');
		
		Player1Menu:
			int player1Choice = 0;
			cout << user1Name << " enter the number of the creature you wish to do combat with!\n";
			cout << "******************************************************************************\n\n";
			for(int i = 0; i < pokeDeck.getLength(); i++){
				cout << i + 1 << "-" << pokeDeck.getNodeValue(i)->getName();
				if(i % 4 == 0)
					cout << endl;
			}
			cout << endl << "******************************************************************************\n\n";
			cin >> player1Choice;
		if(player1Choice > pokeDeck.getLength() or player1Choice < 1){
			cout << "That is an invalid choice. Please try again.\n";
			goto Player1Menu;
		}
		--player1Choice;
		
		Player2Menu:
		int player2Choice = 0;
			cout << user2Name << " enter the number of the creature you wish to do combat with!\n";
			cout << "******************************************************************************\n\n";
			for(int i = 0; i < pokeDeck.getLength(); i++){
				cout << i + 1 << "-" << pokeDeck.getNodeValue(i)->getName();
				if(i % 4 == 0)
					cout << endl;
			}
			cout << endl << "******************************************************************************\n\n";	
			cin >> player2Choice;
		if(player2Choice > pokeDeck.getLength() or player2Choice < 1){
			cout << "That is an invalid choice. Please try again.\n";
			goto Player2Menu;
		}
		--player2Choice;
		
		Creature player1Creature(pokeDeck.getNodeValue(player1Choice)->getName(), pokeDeck.getNodeValue(player1Choice)->getDescription(), pokeDeck.getNodeValue(player1Choice)->getLifePoints(), pokeDeck.getNodeValue(player1Choice)->getHitPoints());
		Creature player2Creature(pokeDeck.getNodeValue(player2Choice)->getName(), pokeDeck.getNodeValue(player2Choice)->getDescription(), pokeDeck.getNodeValue(player2Choice)->getLifePoints(), pokeDeck.getNodeValue(player2Choice)->getHitPoints());
		
		int roundNumber = 1;
		do{
			string enterCheck;
			cout << "********************************* Round " << roundNumber << "*********************************\n";
			cout << user1Name << ", hit Enter to role the die to do damage to " << user2Name << "'s " << player2Creature.getName() << endl;
			getline(cin, enterCheck);
			int hitMultiplicative = rand() % 6 + 1;
			int damage = player1Creature.getHitPoints() * hitMultiplicative;
			player2Creature.setLifePoints(player2Creature.getLifePoints() - damage);
			cout << user1Name << "'s " << player1Creature.getName() << " hit " << user2Name << "'s " << player2Creature.getName() << " for " << damage << " points of damage!\n";
			cout << user2Name <<"'s " << player2Creature.getName() << " now has " << player2Creature.getLifePoints() << " life points.\n";
			
			cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
			
			cout << user2Name << ", hit Enter to role the die to do damage to " << user1Name << "'s " << player1Creature.getName() << endl;
			getline(cin, enterCheck);
			hitMultiplicative = rand() % 6 + 1;
			damage = player2Creature.getHitPoints() * hitMultiplicative;
			player1Creature.setLifePoints(player1Creature.getLifePoints() - damage);
			cout << user2Name << "'s " << player2Creature.getName() << " hit " << user1Name << "'s " << player1Creature.getName() << " for " << damage << " points of damage!\n";
			cout << user1Name <<"'s " << player1Creature.getName() << " now has " << player1Creature.getLifePoints() << " life points.\n";
			
			cout << "VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV\n";
			
			
		}while(roundNumber <= 3 and player1Creature.getLifePoints() > 0 and player2Creature.getLifePoints() > 0);
		
		if(player1Creature.getLifePoints() > player2Creature.getLifePoints()){
			cout << player1Creature.getName() << " has knocked out " << player2Creature.getName() << "!\n";
			cout << user1Name << " has won the game with " << player1Creature.getName() << "!\n";
		}
		else if(player1Creature.getLifePoints() < player2Creature.getLifePoints()){
			cout << player2Creature.getName() << " has knocked out " << player1Creature.getName() << "!\n";
			cout << user2Name << " has won the game with " << player2Creature.getName() << "!\n";
		}
		else if(roundNumber == 3 and player1Creature.getLifePoints() == player2Creature.getLifePoints())
			cout << "The game is a draw!\n";
	
	RestartCheck:
		char restart;
		cout << "Would you like to duel again? (y/n)\n";
		cin >> restart;
		if(restart == 'y' or restart == 'Y')
			goto GameStart;
		else if(restart != 'n' and restart != 'N'){
			cout << "That is not a valid input, please try again.\n";
			goto RestartCheck;
		}
	
	cout << "GOODBYE!\n";
	return 0;
}


List<Creature> mergeSort(List<Creature> TBS){
	cout << "in merge sort \n"; 
	
	if(TBS.getLength() == 0 or TBS.getLength() == 1)
		return TBS;
	
	else{// if(TBS.getNodeValue(0)->getName() < TBS.getNodeValue(TBS.getLength() - 1)->getName()){
		int mid = TBS.getLength()/2;
		
		List<Creature> lower;
		List<Creature> higher;
		
		for(int i = 0; i < mid; i++)
			lower.appendNode(*TBS.getNodeValue(i));
			
		for(int i = mid; i < TBS.getLength(); i++)
			higher.appendNode(*TBS.getNodeValue(i));
		
		return merge(lower, higher);
	}
	
	cout << "outside sort statement\n";
}

List<Creature> merge(List<Creature> low, List<Creature> high){
	cout << "in merge function\n";
	List<Creature>* mergedList = new List<Creature>;
	
	int lCount = 0;
	int hCount = 0;
		
	while(lCount + hCount < low.getLength() + high.getLength() - 1){
		if(low.getNodeValue(lCount)->getName() < high.getNodeValue(hCount)->getName()){
			mergedList->appendNode(*low.getNodeValue(lCount));
			++lCount;
		}
		else{
			mergedList->appendNode(*high.getNodeValue(hCount));
			++hCount;
		}	
	}
	
	cout << "preparing to leave merge function\n";
	
	return *mergedList;
}

bool binarySearchForNomer(List<Creature> TBS, string name){
	
	if(TBS.getLength() == 1){
		if(TBS.getNodeValue(0)->getName() == name)
			return true;
		else
			return false;
	}
	
	else if(TBS.getLength() == 0)
		return false;
	
	else{
		int mid = TBS.getLength() / 2;

		
		if(TBS.getNodeValue(mid)->getName() == name)
			return true;
		
		else if(name < TBS.getNodeValue(mid)->getName()){
			List<Creature> nextSearch;
			
			for(int i = 0; i <= mid; i++)
				nextSearch.appendNode(*TBS.getNodeValue(i));
			
			return binarySearchForNomer(nextSearch, name);
		}
		
		else{
			List<Creature> nextSearch;
			
			for(int i = mid + 1; i < TBS.getLength(); i++)
				nextSearch.appendNode(*TBS.getNodeValue(i));
			
			return binarySearchForNomer(nextSearch, name);
		}
	}
}

/*
void mergeSort(string low, string high, int nodeNum){
	int mid;
	
	if (low < high)
	{
		mid= nodeNum/2;
		// Split the data into two half.
		MergeSort(pokeDeck.getNodeValue(0)->getName(), pokeDeck.getNodeValue(mid)->getName(), mid);
		MergeSort(pokeDeck.getNodeValue(mid+1)->getName(), pokeDeck.getNodeValue(mid+2)->getName(), nodeNum);
 
		// Merge them to get sorted output.
		Merge(low, high, nodeNum);
	}
	
	
}


void merge(string low, string high, int mid)
{
	// We have low to mid and mid+1 to high already sorted.
	int i, j, k,;
	i = low;
	k = 0;
	j = mid + 1;
	lNode* search;
 
	// Merge the two parts into temp[].
	while (i <= mid && j <= high)
	{
		if (a[i] < a[j])
		{
			
			k++;
			i++;
		}
		else
		{
			temp[k] = a[j];
			k++;
			j++;
		}
	}
 
	// Insert all the remaining values from i to mid into temp[].
	while (i <= mid)
	{
		temp[k] = a[i];
		k++;
		i++;
	}
 
	// Insert all the remaining values from j to high into temp[].
	while (j <= high)
	{
		temp[k] = a[j];
		k++;
		j++;
	}
 
 
	// Assign sorted data stored in temp[] to a[].
	for (i = low; i <= high; i++)
	{
		a[i] = temp[i-low];
	}
}
*/ 