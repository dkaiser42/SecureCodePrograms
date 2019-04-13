
#ifndef LinkedList_H
#define LinkedList_H

//Class declaration for LinkedList
template <typename T>
class LinkedList {
    private:
        struct ListNode {
            T value;
            struct ListNode *next;
        };

        ListNode *head, *tail;
        
        int numNodes;

    public:
        //Constructor
        LinkedList() {
            head = NULL;
            tail = NULL;
            numNodes = 0;
        }
        //Destructor
        ~LinkedList();

        
        //list getter functions
        int getLength();
        T getNodeValue(int);

        //list operators
        void appendNode(T);
        void insertNode(T, int);
        void deleteNode(int);

};

template <typename T>
int LinkedList<T>::getLength() {
    return numNodes;
}

template <typename T>
T LinkedList<T>::getNodeValue(int pos) {
    ListNode *nodePtr;
    nodePtr = head;
    int i = 0;
    while(pos >= i) {
        if(pos == i)
            return nodePtr->value;
        i++;
        nodePtr = nodePtr->next;
    }
}

template <typename T>
void LinkedList<T>::appendNode(T val) {
    ListNode *newNode;
    ListNode *nodePtr;

    newNode = new ListNode;
    numNodes++;
    newNode->value = val;
    newNode->next = NULL;

    //Check if list list has no nodes
    if (!head) {
        //make the node the head
        head = newNode;
        tail = newNode;
    }
    else {
        //stick it on the end
        tail->next = newNode;
        tail = newNode;
    }
}

template <typename T>
void LinkedList<T>::insertNode(T val, int pos) {
	ListNode *nodePtr;
	ListNode *newNode;
	
	newNode = new ListNode;
	newNode->value = val;
	// Check if list list has no nodes
	if(!head) {
		head = newNode;
		tail = newNode;
        numNodes++;
	}
	else {
		nodePtr = head;
		int i = 0;
        // Inserting at head?
		if(pos == 0) {
			newNode->next = head;
			head = newNode;
            numNodes++;
		}
		else {
            // Traversal based on position
			while(nodePtr != tail && i < pos) {
				i++;
				if(i == pos)
					break;
				nodePtr = nodePtr->next;
			}
			
			
			if(nodePtr->next == NULL)
				tail = newNode;
				
			newNode->next = nodePtr->next;
			nodePtr->next = newNode;
            numNodes++;
		}
	}	
}


template <typename T>
void LinkedList<T>::deleteNode(int pos) {
    ListNode *nodePtr;
    ListNode *prevNode;

    // Check if list has no nodes
    if(!head)
        return;

    // Are we looking for the head?
	if (pos == 0) {
		nodePtr = head->next;
		delete head;
		head = nodePtr;
        numNodes--;
	}
	else {
		nodePtr = head;

        // Counter and traversal through list based on counter.
        int i = 0;
		while (nodePtr != NULL && i != pos) {  
			prevNode = nodePtr;
			nodePtr = nodePtr->next;
            i++;
		}

		if (nodePtr) {
			if(nodePtr == tail) {
				tail = prevNode;
			}
			prevNode->next = nodePtr->next;
			delete nodePtr;
            numNodes--;
		}
	}
}

//deconstructor
template <typename T>
LinkedList<T>::~LinkedList() {
    ListNode *nodePtr;
    ListNode *nextNode;

    nodePtr = head;
    while(nodePtr) {
        nextNode = nodePtr->next;
        delete nodePtr;
        nodePtr = nextNode;
    }
}

#endif