//DANIEL DEAN ASUNCION
//dasunc2, 671785728
//CS 474
//PROJECT 4
#include "node.h"
#include "linked_list.h"
#include <iostream>


node* linked_list::clear_ll(node* h) {
	if (h == NULL)
		return NULL;
	{
		clear_ll(h->next);
		delete h;
	}
	return NULL;
}

node* linked_list::clone(node* h) {
	if (h == NULL) {
		return NULL;
	}

	node* n = new node;
	if (h->dataType == "int") {
		n->data.ival = h->data.ival;
		n->dataType = "int";
		n->next = clone(h->next);
	}
	else if (h->dataType == "struct node *") {
		n->data.nval = h->data.nval;
		n->dataType = "struct node *";
		n->next = clone(h->next);
	}
	return n;
}

//////////////PUBLIC FUNCTIONS BELOW//////////////

//Default constructor.
linked_list::linked_list() {
	head = NULL;
}

//Destructor.
linked_list::~linked_list() {
	head = clear_ll(head);
}

//Copy constructor.
linked_list::linked_list(linked_list& l) {
	head = clone(l.return_head());
}

//Operator = function.

linked_list& linked_list::operator=(linked_list& l) {
	if (&l != this) {
		linked_list temp(l);

		node* t = temp.return_head();
		temp.set_head(head);
		head = t;
	}
	return *this;
}

void linked_list::append(int data) {
	node* n = new node;
	n->data.ival = data;
	n->dataType = "int";
	n->next = NULL;

	node* head_ref = head;

	if (head == NULL) {
		head = n;
		return;
	}
	while (head_ref->next != NULL) {
		head_ref = head_ref->next;
	}
	head_ref->next = n;
}

void linked_list::append(node* data) {
	node* n = new node;
	n->data.nval = data;
	n->dataType = "struct node *";
	n->next = NULL;

	node* head_ref = head;

	if (head == NULL) {
		head = n;
		return;
	}
	while (head_ref->next != NULL) {
		head_ref = head_ref->next;
	}
	head_ref->next = n;
}

void linked_list::prepend(int data) {
	node* n = new node;
	n->data.ival = data;
	n->dataType = "int";
	n->next = NULL;

	if (head == NULL) {
		head = n;
	}
	else {
		n->next = head;
		head = n;
	}
}

void linked_list::prepend(node* data) {
	node* n = new node;
	n->data.nval = data;
	n->dataType = "struct node *";
	n->next = NULL;

	if (head == NULL) {
		head = n;
	}
	else {
		n->next = head;
		head = n;
	}
}

node* linked_list::find_tail() {
	node* temp = head;

	if (!temp->next) {
		return temp;
	}
	while (temp != NULL) {
		if (!temp->next) {
			return temp;
		}
		temp = temp->next;
	}
}

node* linked_list::return_head() {
	return head;
}

void linked_list::set_head(node* n) {
	this->head = n;
}

bool linked_list::empty() {
	if (head == NULL) {
		return true;
	}
	else {
		return false;
	}
}

void linked_list::headless_list() {
	if (head == NULL) {
		return;
	}

	node* temp = head;
	head = head->next;

	delete temp;
}


void print(node* h) {
	node* temp = new node;
	temp = h;
	cout << "[ ";
	while (temp != NULL) {
		if (temp->dataType == "int") {
			cout << temp->data.ival << " ";
		}
		else if (temp->dataType == "struct node *") {
			print(temp->data.nval);
		}
		temp = temp->next;
	}
	cout << "] ";
}