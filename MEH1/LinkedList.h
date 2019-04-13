
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

using namespace std;

//Struct definition for template list node
template <typename type>
struct lNode{
		type* data;
		lNode* next; 
};


//Template class decleration for Linked List
template  <typename type>
class List{
	private:
		int numNodes;
		lNode<type>* head;
		lNode<type>* tail;
		
	public:
		List(){
			head = NULL;
			tail = NULL;
			numNodes = 0;
		}
		~List(); //implemented
		type* getNodeValue(int); //implemented
		void insertNode(type, int);//implemented
		int getLength(){
			return numNodes;
		}
		void appendNode(type); //implemented
		void deleteNode(int); //implemented
};	

//List destructor
template <typename type>
List<type>::~List(){
	lNode<type>* iterator = head;
	lNode<type>* toBeDeleted;
	
	for(int i = 0; i < numNodes; i++){
		toBeDeleted = iterator;
		iterator = iterator->next;
		delete toBeDeleted;
	}
}

//Function inserts a new node at inputted position
template <typename type>
void List<type>::insertNode(type input, int position){
	lNode<type>* placeToBeInserted = head;
	lNode<type>* ptbiPrefix = head;
	
	if(position == 0){
		head = new lNode<type>;
		head->data = input;
		head->next = ptbiPrefix;
	}
	else if(position == numNodes - 1){		
		tail->next = new lNode<type>;
		tail = tail->next;
		tail->data = input;
		tail->next = NULL;
	}
	else{
		for(int i = 0; i < position; i++)
			placeToBeInserted = placeToBeInserted->next;
		
		for(int i = 0; i < position - 1; i++)
			ptbiPrefix = ptbiPrefix->next;
		
		lNode<type>* newNode = new lNode<type>;
		newNode->data = input;
		newNode->next = placeToBeInserted;
		ptbiPrefix->next = newNode;
	}
}

//Function finds node in the list then returns the data stored
template <typename type>
type* List<type>::getNodeValue(int position){
	lNode<type>* toBeAccessed = head;
	
	for(int i = 0; i < position; i++)
		toBeAccessed = toBeAccessed->next;
	
	return toBeAccessed->data;
}

//Implementation of the template add node function
template <typename type>
void List<type>::appendNode(type input){
	if(numNodes == 0){
		head = new lNode<type>;
		head->data = &input;
		head->next = NULL;
		tail = head;
		numNodes = 1;
	}
	else{
		tail->next = new lNode<type>;
		tail = tail->next;
		tail->data = &input;
		tail->next = NULL;
		++numNodes;
	}
}

//Function removes node from a desired position
template <typename type>
void List<type>::deleteNode(int position){
	lNode<type>* toBeDeleted;
	lNode<type>* tbdPrefix;
	
	toBeDeleted = head;
	for(int i = 0; i < position; i++)
		toBeDeleted = toBeDeleted->next;
	
	
	if(position == 0){
		if(numNodes == 1){
			head = NULL;
			tail = NULL;
		}
		else
			head = head->next;
	}
	else if(position == numNodes - 1){
			tbdPrefix = head;
		for(int i = 0; i < position - 1; i++)
			tbdPrefix = tbdPrefix->next;
		tbdPrefix->next = NULL;
		tail = tbdPrefix;
	}
	else{
		tbdPrefix = head;
		for(int i = 0; i < position - 1; i++)
			tbdPrefix = tbdPrefix->next;
		tbdPrefix->next = toBeDeleted->next;
	}
	
	delete toBeDeleted;
	--numNodes;
}

#endif