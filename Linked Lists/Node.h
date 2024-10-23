/*
    Name: Yunus Gunay
    Course Code: CS 201
    Section: 2
    Student Number: 22203758
*/

#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <iostream>
using namespace std;

template<class Type>
class Node{
public:
    Node();
    ~Node();
    Node(const Type& value);
    void setItem(const Type& value);
    void setNext(Node<Type>* nextNode);
    Type& getItem();
    Node<Type>* getNext() const;

private:
    Type value;
    Node<Type>* next;
};

#endif // NODE_H_INCLUDED
