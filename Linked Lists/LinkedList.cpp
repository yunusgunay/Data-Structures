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
#include "LinkedList.h"

template<class Type>
LinkedList<Type>::LinkedList() {
    head = nullptr;
    itemCount = 0;
}

template<class Type>
LinkedList<Type>::~LinkedList() {
    clean();
}

template<class Type>
void LinkedList<Type>::clean(){
    Node<Type>* current = head;
    while(current != nullptr){
        Node<Type>* next = current->getNext();
        delete current;
        current = next;
    }
    head = nullptr;
    itemCount = 0;
}

template<class Type>
bool LinkedList<Type>::sortedInsert(const Type& value){
    Node<Type>* newNode = new Node<Type>(value);
    if(head == nullptr || head->getItem() > value){
        newNode->setNext(head);
        head = newNode;
        itemCount++;
        return true;
    }

    Node<Type>* current = head;
    Node<Type>* previous = nullptr;
    while(current != nullptr && current->getItem() < value){
        previous = current;
        current = current->getNext();
    }

    if(current != nullptr && current->getItem() == value){
        delete newNode;
        return false;
    }

    newNode->setNext(current);
    if(previous != nullptr){
        previous->setNext(newNode);
    }
    itemCount++;
    return true;
}


template<class Type>
bool LinkedList<Type>::sortedRemove(const Type& value){
    Node<Type>* current = head;
    Node<Type>* previous = nullptr;

    while(current != nullptr && current->getItem() != value){
        previous = current;
        current = current->getNext();
    }

    if(current == nullptr){
        return false;
    }

    if(previous == nullptr){
        head = current->getNext();
    } else {
        previous->setNext(current->getNext());
    }

    delete current;
    itemCount--;
    return true;
}

template<class Type>
int LinkedList<Type>::listSize() const{
    return itemCount;
}

template<class Type>
Node<Type>* LinkedList<Type>::getNodeWithID(int id) const{
    for(Node<Type>* current = head; current != nullptr; current = current->getNext()){
        if(current->getItem().getID() == id){
            return current;
        }
    }
    return nullptr;
}

template class LinkedList<Pathway>;
template class LinkedList<Protein>;
template class LinkedList<Gene>;
