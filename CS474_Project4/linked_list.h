//DANIEL DEAN ASUNCION
//dasunc2, 671785728
//CS 474
//PROJECT 4
#include "node.h"

using namespace std;

class linked_list {

private:
	node* head;

	//Function called by the destructor to free the linked list.
	node* clear_ll(node* h);

	node* clone(node* h);

public:
	//Default constructor.
	linked_list();

	//Destructor.
	~linked_list();

	//Copy constructor.
	linked_list(linked_list& l);

	//Operator = function.
	linked_list& operator=(linked_list& l);

	void append(int data);

	void append(node* data);

	void prepend(int data);

	void prepend(node* data);

	node* find_tail();

	node* return_head();

	void set_head(node* n);

	bool empty();

	void headless_list();
};

void print(node* h);
