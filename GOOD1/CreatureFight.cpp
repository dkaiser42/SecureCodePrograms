
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "Creature.h"

/*
    Function Name: addCreaturesFromFile(LinkedList<Creature> *)
    Parameters: Send a Creature template LinkedList.
    Returns: nothing (void)
    Purpose : Loads creature data from text file specified, checks if the
              creature name already exists, and if not, will append it
              to the creature LinkedList.
*/
void addCreaturesFromFile(LinkedList<Creature> *);

/*
    Function Name: printAllCreatures()
    Parameters: Send a Creature template LinkedList and a integer regarding the
                size of that LinkedList.
    Returns: nothing (void)
    Purpose: Iterates through all the creatures and presents their detailed information
*/
void printAllCreatures(LinkedList<Creature> *, int);

/*
    Function Name: chooseCreature()
    Parameters: String of the players name and a Creature template LinkedList.
    Returns: An integer containing the player's creature choice.
    Purpose: Displays quick list of available creatures and lets user choose one of them.
*/
int chooseCreature(string, LinkedList<Creature> *);

/*
    Function Name: startGame()
    Parameters: A Creature template LinkedList and two strings for each players name.
    Returns: nothing (void)
    Purpose: This is the main logic of the "fight game". Takes users creature choices
            and allows them to battle each other.
*/
void startGame(LinkedList<Creature> *, string, string);

/*
    Function Name: searchFor()
    Parameters: A Creature template LinkedList, a start and end integer, and a string
                containing the name of the creature being searched for.
    Returns: An integer containing the position of the creature (if it exists),
                otherwise will return -1.
    Purpose: To get the position of a Creature if it exists
*/
int searchFor(LinkedList<Creature> *, int, int, string);

/*
    Function Name: MergeSort()
    Parameters: A Creature template LinkedList, a start and a end integer.
    Returns: nothing (void)
    Purpose: To break the list into chunks to be sent to Merge().
*/
void MergeSort(LinkedList<Creature> *, int, int);

/*
    Function Name: Merge()
    Parameters: A Creature template LinkedList, a start middle and end integer.
    Returns: nothing (void)
    Purpose: Sorts the array using the mergeSort algorithm
*/
void Merge(LinkedList<Creature> *, int, int, int);


int main() {
    string playerOne, playerTwo;
    LinkedList<Creature> creatureList;

    addCreaturesFromFile(&creatureList);

    string choice;
    cout << "\n\n\n**********************************************************\n";
    cout << "*                  THE GAME IS STARTING                  *\n";
    cout << "**********************************************************\n";
    do {
        cout << "\n\nREADY TO FIGHT!!\n";
        cout << "PLAYER 1 NAME: ";
        getline(cin, playerOne);

        cout << "PLAYER 2 NAME: ";
        getline(cin, playerTwo);

        cout << "\n\nBefore you have to select your creature,\ndo you want to print details about each one? (y/n)\n";
        getline(cin, choice);
        while(choice !=  "y" && choice != "Y" && choice != "n" && choice != "N") {
            cout << "Invalid choice, please try again:\n";
            getline(cin, choice);
        }

        if(choice ==  "y" || choice == "Y") {
            printAllCreatures(&creatureList, creatureList.getLength());
        }

        // Start main game loop!
        startGame(&creatureList, playerOne, playerTwo);

        cout << "Would you like to play again? (y/n): ";

        getline(cin, choice);
        while(choice !=  "y" && choice != "Y" && choice != "n" && choice != "N") {
            cout << "Invalid choice, please try again:\n";
            getline(cin, choice);
        }

    } while (choice ==  "y" || choice == "Y");
    
    cout << "\n\n THANKS FOR PLAYING \n\n";


    return 0;
}


void addCreaturesFromFile(LinkedList<Creature> *creatureList) {
    string temp, name, desc;
    int hit, life;
    ifstream file;
    file.open ("CreatureFile.txt");

    if(!file)
        cout << "\n\nCreatureFile.txt could not be found.\n\n";

    // Loops through the text file, adding new creatures to the creatureList.
    while(getline(file, temp)) {
        name = temp;
        getline(file, temp);
        desc = temp;
        file >> life;
        file >> hit;
        file.ignore();
        Creature newCreature(name, desc, life, hit);

        // Does the creature already exist?
        if(searchFor(creatureList, 0, creatureList->getLength() -1, name) == -1) {
            creatureList->appendNode(newCreature);
            cout << name << " has been added to the list of creatures that can fight.\n";
            // We need to mergeSort the list.
            MergeSort(creatureList, 0, creatureList->getLength() - 1);
        }
        else {
            cout << name << " was skipped because it is already in the list.\n";
        }
    }
    cout << creatureList->getLength() << " creatures from CreatureFile.txt have been added to the zoo.\n";
}

void printAllCreatures(LinkedList<Creature> *creatureList, int size) {
    for(int i = 0; i < size; i++) {
        cout << "\n**********************************************************\n\n";
        cout << "CREATURE " << i+1 << ":\n";
        creatureList->getNodeValue(i).printCreatureDetails();
    }
    cout << "\n**********************************************************\n";
}

int chooseCreature(string player, LinkedList<Creature> *creatureList) {
    cout << "\n**********************************************************\n";
    cout << player << ", ENTER THE CREATURE NUMBER YOU WISH TO USE TO FIGHT!!\n";
    cout << "**********************************************************\n\n";
    
    // Printing out all the creatures with formatting.
    for(int i = 0; i < creatureList->getLength(); i++) {
        if(i != 0 && i % 3 == 0)
            cout << " " << i+1 << "-" << creatureList->getNodeValue(i).getCreatureName() << "\n";
        else {
            cout << " " << i+1 << "-" << creatureList->getNodeValue(i).getCreatureName() << "\t";
        }
    }

    cout << "\n\n\n" << player << " CREATURE CHOICE (1-" << creatureList->getLength() << "): ";
    int choice;
    cin >> choice;
    while (choice > creatureList->getLength() || choice < 1) {
        cin.clear();
        cin.ignore();
        cout << "You did not enter a valid creature number from 1 to " << creatureList->getLength() << ".\n";
        cout << "Choose a valid number: ";
        cin >> choice;
    }
    return choice;
    
}

void startGame(LinkedList<Creature> *creatureList, string playerOne, string playerTwo) {
    //Calls chooseCreature for both players
    int playerOneAns = chooseCreature(playerOne, creatureList);
    int playerTwoAns = chooseCreature(playerTwo, creatureList);
    cin.ignore();

    //Number of rounds!
    const int NUM_ROUNDS = 3;

    Creature playerOneCreature = creatureList->getNodeValue(playerOneAns-1);
    Creature playerTwoCreature = creatureList->getNodeValue(playerTwoAns-1);

    for(int i = 0; i < NUM_ROUNDS; i++) {
        srand(time(NULL));
        cout << "\n**************************ROUND " << i + 1 << "**************************\n";
        //playerOne attacking playerTwo
        cout << playerOne << ", HIT ENTER TO ROLL THE DIE TO DO DAMAGE TO " << playerTwo << "'s " << playerTwoCreature.getCreatureName() << ".\n";
        cin.ignore();


        int damageDone = (playerOneCreature.getCreatureHit() * (rand() % 6 + 1));
        int newHealth = (playerTwoCreature.getCreatureLife()) - damageDone;

        playerTwoCreature.setCreatureLife(newHealth);
        cout << "\nYOU HIT " << playerTwoCreature.getCreatureName() << " FOR " << damageDone << " POINTS.\n";
        cout << playerTwoCreature.getCreatureName() << " NOW HAS " << playerTwoCreature.getCreatureLife() << "\n";
        if(playerTwoCreature.getCreatureLife() <= 0)
            break;

        //playerTwo attacking playerOne
        cout << playerTwo << ", HIT ENTER TO ROLL THE DIE TO DO DAMAGE TO " << playerOne << "'s " << playerOneCreature.getCreatureName() << ".\n";
        cin.ignore();

        damageDone = (playerTwoCreature.getCreatureHit() * (rand() % 6 + 1));
        newHealth = playerOneCreature.getCreatureLife() - damageDone;

        playerOneCreature.setCreatureLife(newHealth);

        cout << "\nYOU HIT " << playerOneCreature.getCreatureName() << " FOR " << damageDone << " POINTS.\n";
        cout << playerOneCreature.getCreatureName() << " NOW HAS " << playerOneCreature.getCreatureLife() << "\n";
        if(playerOneCreature.getCreatureLife() <= 0)
            break;



        cout << "\n**********************************************************\n";
    }

    if(playerOneCreature.getCreatureLife() < playerTwoCreature.getCreatureLife()) {
        cout << playerTwo << ", " << playerTwoCreature.getCreatureName() << " KNOCKED OUT " << playerOneCreature.getCreatureName() << "\n";
    }
    else {
        cout << playerOne << ", " << playerOneCreature.getCreatureName() << " KNOCKED OUT " << playerTwoCreature.getCreatureName() << "\n";
    }
    cout << "YOU WON!!\n";
}

int searchFor(LinkedList<Creature> *list, int first, int last, string name) {
    int mid = (first+last) / 2;

    if(first > last)
        return -1;
    
    if(name == list->getNodeValue(mid).getCreatureName())
        return mid;
    if(name > (list->getNodeValue(mid).getCreatureName())) 
        return searchFor(list, mid+1, last, name);
    if(name < (list->getNodeValue(mid).getCreatureName())) 
        return searchFor(list, first, mid-1, name);
}

void MergeSort(LinkedList<Creature> *list, int start, int end) {
    int mid = 0;

    if (start < end) {
        mid = (start + end) / 2;

        MergeSort(list, start, mid);
        MergeSort(list, mid + 1, end);
        Merge(list, start, mid, end);
    }
}

void Merge(LinkedList<Creature> *list, int start, int mid, int end) {
    int mergeSize = end - start + 1;
    int mergePos = 0, leftPos = 0, rightPos = 0;
    Creature* tempArray = new Creature[mergeSize];

    leftPos = start, rightPos = mid +1;

    while(leftPos <= mid && rightPos <= end) {
        if(list->getNodeValue(leftPos).getCreatureName() < list->getNodeValue(rightPos).getCreatureName()) {
            tempArray[mergePos] = list->getNodeValue(leftPos);
            ++leftPos;
        }
        else {
            tempArray[mergePos] = list->getNodeValue(rightPos);
            ++rightPos;
        }
        ++mergePos;
    }

    while(leftPos <= mid) {
        tempArray[mergePos] = list->getNodeValue(leftPos);
        ++leftPos;
        ++mergePos;
    }

    while(rightPos <= end) {
        tempArray[mergePos] = list->getNodeValue(rightPos);
        ++rightPos;
        ++mergePos;
    }

    for(mergePos = 0; mergePos < mergeSize; mergePos++) {
        list->deleteNode((start + mergePos));
        list->insertNode(tempArray[mergePos], (start + mergePos));
    }
}
