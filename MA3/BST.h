/*
 * Binary Search Tree implementation 
 *  - heavily lifted from https://gist.github.com/mgechev/5911348
 *  - though, very very hacked up since then
 *
 * Simple keys and basic operations BST
 *
 * Aaron Crandall - 2016 - Added / updated:
 *  * Inorder, Preorder, Postorder printouts
 *  * Stubbed in level order printout
 * Aaron Crandall - 2017 - Heavy overhaul of tests & behaviors
 *  * Added BigFive (like we should!)
 *  * Added several public interfaces for tree features
 *
 */

#ifndef __BST_H
#define __BST_H

#include <iostream>
#include <cstring>		// strcmp
#include <vector>
#include <queue>
#include <initializer_list>

using namespace std;

/*
 *  Node datastructure for single tree node
 */ 
template <class T>
struct Node {
    T value;
    Node *left;
    Node *right;

    Node(T val) {
        this->value = val;
        this->left = NULL;
        this->right = NULL;
    }

    Node(T val, Node<T> * left, Node<T> * right) {
        this->value = val;
        this->left = left;
        this->right = right;
    }
};

/*
 * Binary Search Tree (BST) class implementation
 */
template <class T>
class BST {

    private:
    Node<T> *root;

    /* clone a passed in tree, returns pointer to new tree */
    Node<T> * cloneTree(Node<T> *t) {
        if( t == NULL )
            return NULL;
        else
            return new Node<T>( t->value, 
                                cloneTree( t->left ),
                                cloneTree( t->right ) );
    }

    /* Recursively delete the tree nodes */
    void makeEmptyHelper(Node<T> *t) {
        if( t != NULL ) {
            makeEmptyHelper( t->left );
            makeEmptyHelper( t->right );
            delete t;
        }
    }

    /* Add new T val to the tree */
    void addHelper(Node<T> *root, T val) {
        if (root->value > val) {
            if (!root->left) {
                root->left = new Node<T>(val);
            } else {
                addHelper(root->left, val);
            }
        } else {
            if (!root->right) {
                root->right = new Node<T>(val);
            } else {
                addHelper(root->right, val);
            }
        }
    }

    /* Print tree out in inorder (A + B) */
    void printInOrderHelper(Node<T> *root) {
        if (!root) return;
        printInOrderHelper(root->left);
        cout << root->value << ' ';
        printInOrderHelper(root->right);
    }

    /* Print tree out in post order (A B +) */
    void printPostOrderHelper(Node<T> *root) {
        if (!root) return;
        printPostOrderHelper(root->left);
        printPostOrderHelper(root->right);
        cout << root->value << ' ';
    }

    /* Print tree out in pre order (+ A B) */
    void printPreOrderHelper(Node<T> *root) {
        if (!root) return;
        cout << root->value << ' ';
        printPreOrderHelper(root->left);
        printPreOrderHelper(root->right);
    }

    /* Print tree out in level order */
    /* MA TODO: Implement */
	void printLevelOrderHelper(Node<T> *root)
	{
		if (!root) //if empty tree
			return;

		queue<Node<T> *> orderedList; //Queue of pointers to nodes
		orderedList.push(root); //Add the root as the first node in queue
		int counter; //Size of the queue
		
		while (!orderedList.empty())
		{
			counter = orderedList.size(); //Keep track of the size of the queue so we don't pop() an empty queue
			if (counter == 0)
				break;
			while (counter != 0)
			{
				Node<T> * pCur = orderedList.front(); //pCur is assigned a pointer to the first node of the queue
				cout << orderedList.front()->value<< " "; //Prints the first node of the queue
				orderedList.pop(); //Removes first node in the queue
				if (pCur->left != nullptr) //In level order, we start from the left and move to the right in the same level
					orderedList.push(pCur->left);
				if (pCur->right != nullptr)
					orderedList.push(pCur->right);
				counter--;
			}
		}
		cout << endl; //Space
		cout << "end of queue" << endl; 

	}

	vector<T> & returnLevelOrderHelper(Node<T> *root) { //Similar to the printLevelOrderHelper function
		vector<T> * ret = new vector<T>{}; //vector of T values
		if (!root) return(*ret); //check for empty tree

		queue<Node<T> *> orderedList; //queue of node pointers
		orderedList.push(root); //we start the queue with the root
		int counter; //size of the vector
		int vectorCount = 0;

		while (!orderedList.empty())
		{
			counter = orderedList.size();
			if (counter == 0)
				break;
			while (counter != 0)
			{
				Node<T> * pCur = orderedList.front(); //pCur is a pointer to the top node in the queue 
				ret->insert(ret->begin() + vectorCount, pCur->value); //inserts (position, value) in the ret vector 
				//cout << orderedList.front()->value << " "; //Test// To see what values are inserted in the vector
				orderedList.pop(); //removes the front of the queue
				if (pCur->left != nullptr) 
					orderedList.push(pCur->left); //In level order, we start from the left and move to the right in the same level
				if (pCur->right != nullptr)
					orderedList.push(pCur->right);
				counter--; // keeps count of the size of the queue. We don't want to pop() an empty queue
				vectorCount++; //iteration for the position of the vector
			}
		}

		return(*ret);
	}

    /* Return number of nodes in tree */
    int nodesCountHelper(Node<T> *root) {
        if (!root) return 0;
        else return 1 + nodesCountHelper(root->left) + nodesCountHelper(root->right);
    }

    /* Return height of tree (root == NULL -> 0) */
    int heightHelper(Node<T> *root) {
        if (!root) return 0;
        else return 1 + max(heightHelper(root->left), heightHelper(root->right));
    }

    /* Print out longest path from root to a leaf */
    void printMaxPathHelper(Node<T> *root) {
        if (!root) return;
        cout<<root->value<<' ';
        if (heightHelper(root->left) > heightHelper(root->right)) {
            printMaxPathHelper(root->left);
        } else {
            printMaxPathHelper(root->right);
        }
    }

    /* Delete a given T value from tree */
    bool deleteValueHelper(Node<T>* parent, Node<T>* current, T value) {
        if (!current) return false;
        if (current->value == value) {
            if (current->left == NULL || current->right == NULL) {
                Node<T>* temp = current->left;
                if (current->right) temp = current->right;
                if (parent) {
                    if (parent->left == current) {
                        parent->left = temp;
                    } else {
                        parent->right = temp;
                    }
                } else {
                    this->root = temp;
                }
            } else {
                Node<T>* validSubs = current->right;
                while (validSubs->left) {
                    validSubs = validSubs->left;
                }
                T temp = current->value;
                current->value = validSubs->value;
                validSubs->value = temp;
                return deleteValueHelper(current, current->right, temp);
            }
            delete current;
            return true;
        }
        return deleteValueHelper(current, current->left, value) ||
               deleteValueHelper(current, current->right, value);
    }

    bool containsHelper(Node<T> * root, T val) {
        if( root == NULL )
            return( false );
        else if( root->value == val )
            return( true );
        else if( root->value > val ) // Search left
            return( containsHelper(root->left, val) );
        else
            return( containsHelper(root->right, val) );
    }


    public:

    BST( ) : root( NULL ) { }                   // Basic initialization constructor

    BST( initializer_list<T> vals ) : root( NULL ) {   // Vector-based initializer
        for( auto val : vals )
            this->add(val);
    }

    ~BST( ) {                             // Destructor - free all nodes
        makeEmpty( );
    }

	/* Copy constructor */
	/* MA TODO: Implement */
	BST(const BST &other) : root(NULL) {
		cout << " [d] Copy constructor is called" << endl;
		if (other.root == nullptr) //Check for empty tree
			this->root = nullptr; //If other tree is empty, make this tree empty 
		else
			this->root = cloneTree(other.root); //Uses the cloneTree function helper, which makes a copy of the other tree and returns a pointer to the root of the new tree
	}

	/* Move constructor */
	/* MA TODO: Implement */
	BST(BST && other) : root(NULL) {
		cout << " [d] Move construtor called " << endl;
		
		this->root = other.getRoot(); //Assigns this tree's root to other's tree root. We don't need to check for empty tree. If other tree = NULL, this tree will equal NULL
		other.root = nullptr;         //Removes other's tree pointer to the tree, making this tree have the only access to it
	}

	/* Copy assignment operator */
	/* MA TODO: Implement */
	BST& operator=(BST & other) {
		cout << " [d] Copy assignment operator called. " << endl;

		//Making sure this tree is empty before we copy
		makeEmpty(); //Deletes all the nodes in this tree if there are any to avoid accidently losing access to a tree and wasting space
		if (other.getRoot() == nullptr) //If other has empty tree
			this->root = nullptr;
		this->root = cloneTree(other.getRoot()); //Use cloneTree helper function, which returns the pointer to the root of a new tree

		return (*this);
	}

	/* Move assignment operator */
	/* MA TODO: Implement */
	BST& operator=(BST && other) {
		cout << " [d] Move assignment operator called. " << endl;

		//Making sure this tree is empty before we move pointers
		makeEmpty(); //Deletes all the nodes in this tree if there are any to avoid accidently losing access to a tree and wasting space
		this->root = other.getRoot(); //Grabs other's tree root pointer
		other.root = nullptr; //Removes other's access to the tree
		return(*this);
	}


    /* Public API */
    void makeEmpty( ) {
        if (root) 
            this->makeEmptyHelper(root);
    }

    void add(T val) {
        if (root) {
            this->addHelper(root, val);
        } else {
            root = new Node<T>(val);
        }
    }

    bool empty() {
        return( root != NULL );
    }

    void print() {
        printInOrderHelper(this->root); 
    }

    void printInOrder() {
        printInOrderHelper(this->root);
    }

    void printPostOrder() {
        printPostOrderHelper(this->root);
    }

    void printPreOrder() {
        printPreOrderHelper(this->root);
    }

    void printLevelOrder() {
        printLevelOrderHelper(this->root);
    }

    vector<T> & returnLevelOrder() {
        return returnLevelOrderHelper(this->root);
    }

    int nodesCount() {
        return nodesCountHelper(root);
    }

    int height() {
        return heightHelper(this->root);
    }

    void printMaxPath() {
        printMaxPathHelper(this->root);
    }

    bool deleteValue(T value) {
        return this->deleteValueHelper(NULL, this->root, value);
    }

    bool contains( T value ) {
        return this->containsHelper(this->root, value);
    }

    Node<T> * getRoot() { return(root); }  // Gives out our root pointer for testing
};


#endif
