
#ifndef LinkedList_H
#define LinkedList_H

#include <iostream>
#include <iomanip>
#include <string>
#include "Creature.h"

using namespace std;

template <class T>
class LinkedList
{
	private:
		
		struct ListNode
		{
			T *myCreature;
			struct ListNode *next;
			struct ListNode *previous;
		}; 

		ListNode *head;
		ListNode *tail;
		int numNodes;

	public:
		// Constructor
		LinkedList()
		{ 
			head = NULL; 
			tail = NULL;
			numNodes = 0;
		}

		// Destructor
		~LinkedList();

	// Linked list functions
	int getLength();
	T* getNodeValue(int);
	void appendNode(Creature);
	void insertNode(Creature, int);
	void deleteNode(Creature);
	void displayList() const;
	void printCreatures();
	int simpleSearch(string);


//--I couldn't get the merge sort to work--
//	void Merge(T, int, int, int);
//	void mergeSort(T, int, int)

};

template<class T>
LinkedList<T>::~LinkedList()
{
	ListNode *nodePtr;   // To traverse the list
	ListNode *nextNode;  // To point to the next node

	// Position nodePtr at the head of the list.
	nodePtr = head;

	// While nodePtr is not at the end of the list...
	while (nodePtr != NULL)
	{
		// Save a pointer to the next node.
		nextNode = nodePtr->next;

		// Delete the current node.
		delete nodePtr;

		// Position nodePtr at the next node.
		nodePtr = nextNode;
	}
}

template <class T>
int LinkedList<T>::getLength()
{	
	int counter = 0;
	ListNode *nodePtr;

	nodePtr = head;

	while (nodePtr != tail)
	{
		counter++;
		nodePtr = nodePtr->next;
		if (nodePtr == tail)
			counter++;
	}
return counter;
}

template <class T>
T* LinkedList<T>::getNodeValue(int position)		//Should return a creature
{
	ListNode *nodePtr;
			
	if(!head)
		cout << "\nCannot get the Node value.";
			
	else
	{
		if(position == 0)
			return head->myCreature;
			
		nodePtr = head;
			
		int currentPos = 0;
				
		while(position >= currentPos && nodePtr != NULL)
		{
			if(position == currentPos)
				return nodePtr->myCreature;
					
			currentPos++;
			nodePtr = nodePtr->next;
		}
	}
		
}

template <class T>
void LinkedList<T>::appendNode(Creature oneCreature)
{
	ListNode *newNode;
	ListNode *nodePtr;

	// Allocate a new node and store the Creature there.
	newNode = new ListNode;
	newNode->myCreature = new Creature(oneCreature);
	newNode->next = NULL;
	newNode->previous = NULL;

	// If there are no nodes in the list make newNode the first node.
	if (!head) 
	{
		head = newNode;
		tail = newNode;
	}
	
	else  // Otherwise, insert newNode at end.
	{
		//set the current last node's next pointer to the new node
		tail->next = newNode;
		newNode->previous = tail;
		
		//now the tail is the new node
		tail = newNode;
	}
	numNodes++;
}

template <class T>
void LinkedList<T>::insertNode(Creature oneCreature, int position)
{
	ListNode *nodePtr;
	ListNode *newNode;
	
	newNode = new ListNode;
	newNode->myCreature = oneCreature;
	
	if(!head)
	{
		if(position != 0)
		{
			//can't insert node at position (>0) if there is not already a node
			cout << "\n\nUnable to insert a node at position " << position << " because there are currently no nodes in the list. Inserting node at position 0.";
		}
		head = newNode;
		tail = newNode;
	}
			
	else
	{
		nodePtr = head;
		int nodeCount = 0;
				
		if(position == 0)
		{
			newNode->next = head;
			head->previous = newNode;
			head = newNode;
		}
				
		while(nodePtr != tail && nodeCount < position)
		{
			nodeCount++;
			if(nodeCount == position)
				break;
			nodePtr = nodePtr->next;
		}
		
		//now nodePtr is positioned 1 node BEFORE the node we want to insert
		if(nodePtr->next == NULL) //we are appending this node to the end
			tail = newNode;
			
		//set up newNode's links
		newNode->next = nodePtr->next;
		newNode->previous = nodePtr;
		
		//change the node on the left
		nodePtr->next = newNode;
		
		//change the node on the right (if there is a node on the right)
		if(newNode->next)
		{
			nodePtr = newNode->next; 
			nodePtr->previous = newNode;
		}
	}	
numNodes++;

}

template <class T>
void LinkedList<T>::deleteNode(Creature myCreature)
{
	ListNode *nodePtr;       // To traverse the list
	ListNode *previousNode;  // To point to the previous node

	// If the list is empty, do nothing.
	if (!head)
	{
		cout << "\n\nThe list is empty.";
		return;
	}
	// Determine if the first node is the one.
	if (head->myCreature == myCreature)
	{
		nodePtr = head->next;
		delete head;
			
		if(nodePtr != NULL)
		{
			head = nodePtr;
			head->previous = NULL;
		}
		else
			head = NULL;
	}
	else
	{
		// Initialize nodePtr to head of list
		nodePtr = head;

		// Skip all nodes whose value member is 
		// not equal to num.
		while (nodePtr && nodePtr->myCreature != myCreature)
		{  
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}

		// If nodePtr is not at the end of the list, 
		// link the previous node to the node after
		// nodePtr, then delete nodePtr.
		if (nodePtr)
		{
			if(nodePtr == tail)
			{
				tail = previousNode;
			}
			previousNode->next = nodePtr->next;
			delete nodePtr;
			
			if(previousNode != tail)
			{
				nodePtr = previousNode->next;
				nodePtr->previous = previousNode;
			}
		}
	}
}

template <class T>
void LinkedList<T>::displayList() const
{
	ListNode *nodePtr;  // To move through the list
	int counter = 1;

	if(head != NULL)
	{
		// Position nodePtr at the head of the list.
		nodePtr = head;
		// While nodePtr points to a node, traverse the list.
		while (nodePtr)
		{
			// Display the creature in this node.
			cout << counter << ": " << nodePtr->myCreature->getName();
			cout << endl;

			// Move to the next node.
			nodePtr = nodePtr->next;

			counter++;
		}
	}
	else
		cout << "\nThere are no creatures in the list.\n\n";
}

/*
Prints all the details of every creature if the user inputs Y.
Had problems formatting the description, which wouldn't let me format the rest.
For some reason setw(x) wasn't working, and I tried many, many different methods
Of formatting
*/

template <class T>
void LinkedList<T>::printCreatures()
{
	ListNode *nodePtr;
	int counter;
	string creatureDescription;

	nodePtr = head;	

	counter = 1;

	while(nodePtr != NULL)
	{
			creatureDescription = nodePtr->myCreature->getDescription();

			cout << endl;
			cout << "*********************************" << endl;
			cout << "Creature " << counter << ":" << endl;
			cout << "Name: " << nodePtr->myCreature->getName() << endl;
			cout << "\nDescription:" << endl;
			cout << creatureDescription << endl;
			cout << "\nLifepoints:  " << nodePtr->myCreature->getHP() << endl;
			cout << "\nHitpoints: " << nodePtr->myCreature->getDPS() << endl;
			cout << "*********************************" << endl;

			nodePtr = nodePtr->next;
			counter++;
	}
}

/*
Simple search. I ran into many problems trying to implement recursive binary search
so I made a simpler search method. It's less efficient than binary but it works
*/

template <class T>
int LinkedList<T>::simpleSearch(string name)
{
	ListNode *nodePtr;
	nodePtr = head;
	int pos = 0;

	while (nodePtr)
	{
		//If creature is found, skip it in Main
		if(nodePtr->myCreature->getName() == name)
			return 1;
		
		pos++;

		nodePtr = nodePtr->next;
	}
	
	//Creature couldn't be found, append it in Main
	return -1;


/*
	--The remnants of my Recursive Binary search--

	int middle = (high+low)/2;

	//Base case, if it can't be found then it will continue and append the creature to the list
	if (nodePtr == NULL)
		return -1;

	//If it is found, returns true and will skip that creature in Main
	if (Creatures.getNodeValue(middle)->getName() == name)
		return 1;
	
	//Recursively search until nodePtr is NULL or NAME is found
	else if (Creatures.getNodeValue(middle)->getName() < name)
		return binarySearch(middle+1, low, Creatures, name);

	//Recursively search until nodePtr is NULL or NAME is found
	else
		return binarySearch(high, middle-1, Creatures, name);*/
}


/*
I wasn't really sure how to approach sorting the Linked List alphabetically
using merge sort, and I ran out of time.


template<class T>
void LinkedList<T>::mergeSort(T Creatures, int beg, int end)
{
	int mid = 0;

	if (beg < end)
	{
		mergeSort(Creatures, beg, mid);
		mergeSort(Creatures, mid+1, end);

		Merge(Creatures, beg, mid, end);
	}
}



template<class T>
void LinkedList<T>::Merge(T Creatures, int beg, int mid, int end)
{
	
	int mergedSize = end - beg + 1;
	int leftPos = Creatures.getLength() - (Creatures.getLength() - 1);
	int rightPos = Creatures.getLength();
	
	LinkedList<Creature> mergedCreatures;

	leftPos = beg;
	rightPos = mid + 1;

	while (leftPos <= mid && rightPos <= end) 
	{
     	if (getNodeValue(leftPos)->getName() < getNodeValue(rightPos)->getName()) 
     	{
        	mergedCreatures.getNodeValue(leftPos) = Creatures.getNodeValue(leftPos);
        	++leftPos;
      	}
    }

}
*/

#endif