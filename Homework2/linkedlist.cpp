#include <iostream>
#include <string>
using namespace std;

typedef string ItemType;

struct Node {
	ItemType value;
	Node *next;
};

class LinkedList {

private:
	Node *head;

public:
    
      // default constructor
    LinkedList() : head(nullptr) { }
    
      // copy constructor
    LinkedList(const LinkedList& rhs);
    
      // Destroys all the dynamically allocated memory
      // in the list.
    ~LinkedList();
    
      // assignment operator
    const LinkedList& operator = (const LinkedList& rhs);
    
      // Inserts val at the front of the list
    void insertToFront(const ItemType &val);
    
      // Prints the LinkedList
    void printList() const;
    
      // Sets item to the value at position i in this
      // LinkedList and return true, returns false if 
      // there is no element i
    bool get(int i, ItemType& item) const;
    
      // Reverses the LinkedList
    void reverseList();
    
      // Prints the LinkedList in reverse order
    void printReverse() const;
    
      // Appends the values of other onto the end of this
      // LinkedList.
    void append(const LinkedList &other);
    
      // Exchange the contents of this LinkedList with the other one.
    void swap(LinkedList &other);
    
      // Returns the number of items in the Linked List.
    int size() const;
};

LinkedList:: LinkedList(const LinkedList& rhs) { //checked
	this->head = nullptr;
	if (rhs.head == nullptr) return;

	Node *p;
	Node *tmp;
	Node *q = rhs.head;

	head = new Node;
	head->value = q->value;
	p = head;
	q = q->next;

	while (q != nullptr) {
		tmp = new Node;
		tmp->value = q->value;
		p->next = tmp;
		p = p->next;
		q = q->next;
	}
	p->next = nullptr;
}

LinkedList:: ~LinkedList() { //checked
	Node *p;
	while (head != nullptr) {
		p = head;
		head = head->next;
		delete p;
	}
}

const LinkedList& LinkedList:: operator=(const LinkedList& rhs) { // checked
	if (this == &rhs) return *this;

	// delete orignal LinkedList, the same as ~LinkedList();
	Node *p;
	while (head != nullptr) {
		p = head;
		head = head->next;
		delete p;
	}

	// create a new LinkedList using the copy constructor
	LinkedList *tmp = new LinkedList(rhs);
	head = tmp->head;
	return *this;
}

void LinkedList:: insertToFront(const ItemType &val) { //checked
	Node *p = new Node;
	p->value = val;
	p->next = head;
	head = p;
}

void LinkedList:: printList() const { //checked
	for (Node *p = head; p != nullptr; p = p->next)
		cout << p->value << " ";
	cout << endl;
}

bool LinkedList:: get(int i, ItemType& item) const { // checked
	if (i < 0 || i >= size()) return false;
	Node *p = head;
	while (i) {
		p = p->next;
		i--;
	}
	item = p->value;
	return true;
}

void LinkedList:: reverseList() { // checked
	if (head == nullptr || head->next == nullptr) return;
	Node *pre = head;
	Node *cur = head->next;
	Node *suc = head->next->next;
	head->next = nullptr;
	cur->next = pre;

	while (suc != nullptr) {
		pre = cur;
		cur = suc;
		suc = suc->next;
		cur->next = pre;
	}
	head = cur;
}

void LinkedList:: printReverse() const { // checked
	LinkedList tmp(*this); // or " LinkedList tmp = *this; "
	tmp.reverseList();
	tmp.printList();
	// tmp.~LinkedList(); tmp.printList();
}

void LinkedList:: append(const LinkedList &other) {
	
	LinkedList *tmp = new LinkedList(other);

	if (head == nullptr) {

		head = tmp->head;
		tmp->head = nullptr;
		return;
	}
	
	Node *p = head;
	for (; p->next != nullptr; p = p->next);
	p->next = tmp->head;
	tmp->head = nullptr;
}

void LinkedList:: swap(LinkedList &other) { // checked
	Node *p = head;
	head = other.head;
	other.head = p;
}

int LinkedList:: size() const{ // checked
	int ret = 0;
	for (Node *p = head; p != nullptr; ++ret, p = p->next);
	return ret;
}


#include <cassert>
int main() {
	LinkedList ls;
    //ls.insertToFront("George");
    //ls.insertToFront("Louise");
    //ls.insertToFront("Lionel");
    //ls.insertToFront("Helen");

    ls.printList();
    ls.printReverse();
    ls.printList();

    LinkedList ls2;
    ls2 = ls;

    ls2.printList();

    cout << ls.size() << "----- ls2 " << ls2.size() << endl; 

    ls2.insertToFront("Hhhh");
    ls.insertToFront("[][][]");

    //ls.swap(ls2);

    ls2.printList();
    ls.printList();

    cout << ls.size() << "----- ls2 " << ls2.size() << endl; 

    /*LinkedList e1;
    e1.insertToFront("bell");
    e1.insertToFront("biv");
    e1.insertToFront("devoe");
    LinkedList e2;
    e2.insertToFront("Andre");
    e2.insertToFront("Big Boi");
    e1.append(e2);  // adds contents of e2 to the end of e1
    string s;
    assert(e1.size() == 5  &&  e1.get(3, s)  &&  s == "Big Boi");
    assert(e2.size() == 2  &&  e2.get(1, s)  &&  s == "Andre");*/

    LinkedList e1;
    e1.insertToFront("A");
    e1.insertToFront("B");
    e1.insertToFront("C");
    e1.insertToFront("D");
    LinkedList e2;
    e2.insertToFront("X");
    e2.insertToFront("Y");
    e2.insertToFront("Z");
    e1.swap(e2);  // exchange contents of e1 and e2
    string s;
    assert(e1.size() == 3  &&  e1.get(0, s)  &&  s == "Z");
    assert(e2.size() == 4  &&  e2.get(2, s)  &&  s == "B");

    return 0;
}