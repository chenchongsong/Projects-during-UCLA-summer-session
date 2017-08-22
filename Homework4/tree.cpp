#include <iostream>
#include <string>
#include <cassert>
using namespace std;
typedef string ItemType;

struct WordNode {
	ItemType m_data;
	WordNode *m_left;
	WordNode *m_right;
	int m_count;
	// You may add additional data members and member functions in WordNode
};

class WordTree {

public:
	WordNode *root;
	WordNode* NewSubTree(WordNode* nodeptr);
	void Insert(WordNode*& nodeptr, ItemType item);
	int CountSubTree_Distinct(WordNode* nodeptr) const;
	int CountSubTree_Total(WordNode* nodeptr) const;
	void Destroy(WordNode*& nodeptr);

public:
		// default constructor            
	WordTree() : root(nullptr) { };

		// copy constructor
	WordTree(const WordTree& rhs);
		
		// assignment operator
	const WordTree& operator=(const WordTree& rhs);  
		
		// Inserts v into the WordTree    
	void add(ItemType v);

		// Returns the number of distince words / nodes   
	int distinctWords() const;

		// Returns the total number of words inserted, including duplicate
		// values
	int totalWords() const;

		// Prints the LinkedList 
	friend ostream& operator<<(ostream &out, const WordTree& rhs);

		// Destroys all the dynamically allocated memory
		// in the tree.
	~WordTree();
};

//=============== constructor & assignment ===================

WordNode* WordTree::NewSubTree(WordNode* nodeptr) {
	if (nodeptr == nullptr)
		return nullptr;

	WordNode* tmp = new WordNode;
	tmp->m_data = nodeptr->m_data;
	tmp->m_left = NewSubTree(nodeptr->m_left);
	tmp->m_right = NewSubTree(nodeptr->m_right);
	tmp->m_count = nodeptr->m_count;

	return tmp;
}

WordTree::WordTree(const WordTree& rhs) {
	this->root = NewSubTree(rhs.root);
}

const WordTree& WordTree::operator=(const WordTree& rhs) { // assignment operator
	if (this == &rhs) return *this;

	this->~WordTree(); // delete the original tree

	WordTree *tmp = new WordTree(rhs);
	root = tmp->root;
	return *this;
}

//====================== Add ===========================

void WordTree::Insert(WordNode*& nodeptr, ItemType item) {
	if (nodeptr == nullptr) {
		nodeptr = new WordNode;
		nodeptr->m_data = item;
		nodeptr->m_right = nullptr;
		nodeptr->m_left = nullptr;
		nodeptr->m_count = 1;
		return;
	}
	if (item == nodeptr->m_data) {
		nodeptr->m_count++;
		return;
	}
	if (item < nodeptr->m_data)
		Insert(nodeptr->m_left, item);
	else
		Insert(nodeptr->m_right, item);
}

void WordTree::add(ItemType v) {
	Insert(root, v);
}

//====================== count ===========================

int WordTree::CountSubTree_Distinct(WordNode* nodeptr) const {
	if (nodeptr == nullptr)
		return 0;
	return 1+CountSubTree_Distinct(nodeptr->m_left)+CountSubTree_Distinct(nodeptr->m_right);
}

int WordTree::distinctWords() const {
	return CountSubTree_Distinct(root);
}

int WordTree::CountSubTree_Total(WordNode* nodeptr) const {
	if (nodeptr == nullptr)
		return 0;
	return nodeptr->m_count+CountSubTree_Total(nodeptr->m_left)+CountSubTree_Total(nodeptr->m_right);
}


int WordTree::totalWords() const {
	return CountSubTree_Total(root);
}

//====================== Print ===========================

void streamNode(ostream& out, WordNode* nodeptr) {
	if (nodeptr == nullptr) return;
	
	streamNode(out, nodeptr->m_left);
	out << nodeptr->m_data << " " << nodeptr->m_count << endl;
	streamNode(out, nodeptr->m_right);
}

ostream& operator << (ostream& out, const WordTree& rhs) {
	streamNode(out, rhs.root);
	return out;
}

//====================== Delete ===========================

void WordTree::Destroy(WordNode*& nodeptr) {

	if (nodeptr != nullptr) {
		Destroy(nodeptr->m_right);
		Destroy(nodeptr->m_left);
		delete nodeptr;
	}
	nodeptr = nullptr;
}

WordTree::~WordTree() {
	Destroy(root);
}

int main() {
	WordTree t;
    
   	t.add("Skyler");
    t.add("Walter");
    t.add("Walter");
    t.add("Walter");

    assert(t.distinctWords() == 2);
    assert(t.totalWords() == 4);

    WordTree t2(t); //WordTree t2 = t;  // copy constructor
    t2.add("Rick");

    assert(t.distinctWords() == 2);
    assert(t.totalWords() == 4);

    assert(t2.distinctWords() == 3);
    assert(t2.totalWords() == 5);

    
	WordTree t3;
    t3 = t; // assignment operator

    t.add("Chen");

    assert(t.distinctWords() == 3);
    assert(t.totalWords() == 5);

    assert(t3.distinctWords() == 2);
    assert(t3.totalWords() == 4);



    t.~WordTree();
    assert(t.root == nullptr);

    puts("It is OK!! ");
    
    t.add("Skyler");
    t.add("Walter");
    t.add("Walter");
    t.add("Hank");
    t.add("Gus");
    t.add("Walter");
    t.add("Gus");

    cout << t;
	return 0;
}