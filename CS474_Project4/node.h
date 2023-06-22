//DANIEL DEAN ASUNCION
//dasunc2, 671785728
//CS 474
//PROJECT 4

#ifndef MYSTRUCT_H
#define MYSTRUCT_H

#include <string>
#include <iostream>

using namespace std;

struct node {
    union {
        int ival;
        node* nval = NULL;

    } data;
    string dataType;
    node* next;
};

#endif