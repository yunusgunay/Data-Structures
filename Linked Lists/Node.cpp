/*
    Name: Yunus Gunay
    Course Code: CS 201
    Section: 2
    Student Number: 22203758
*/

#include <cstddef>
#include <iostream>
using namespace std;
#include "Pathway.h"
#include "Protein.h"
#include "Gene.h"
#include "Node.h"

template<class Type>
Node<Type>::Node() : next(nullptr) {}

template<class Type>
Node<Type>::~Node() {}

template<class Type>
Node<Type>::Node(const Type& value) : value(value) {}

template<class Type>
void Node<Type>::setItem(const Type& value){
    this->value = value;
}

template<class Type>
void Node<Type>::setNext(Node<Type>* nextNode){
    next = nextNode;
}

template<class Type>
Type& Node<Type>::getItem(){
    return value;
}

template<class Type>
Node<Type>* Node<Type>::getNext() const{
    return next;
}

template class Node<Pathway>;
template class Node<Protein>;
template class Node<Gene>;
