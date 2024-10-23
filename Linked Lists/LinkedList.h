/*
    Name: Yunus Gunay
    Course Code: CS 201
    Section: 2
    Student Number: 22203758
*/

#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

#include <iostream>
using namespace std;
#include "Node.h"

template<class Type>
class LinkedList{
public:
    LinkedList();
    ~LinkedList();
    void clean();
    bool sortedInsert(const Type& value);
    bool sortedRemove(const Type& value);
    int listSize() const;
    Node<Type>* getNodeWithID(int id) const;
    Node<Type>* head;

private:
    int itemCount;
};

#endif // LINKEDLIST_H_INCLUDED
