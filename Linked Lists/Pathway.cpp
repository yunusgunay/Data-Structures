/*
    sec2-Yunus-Gunay-22203758
*/

#include <iostream>
using namespace std;
#include "Pathway.h"

Pathway::Pathway(int id, string name){
    pathwayId = id;
    pathwayName = name;
    next = nullptr;
    proteinHead = nullptr;
}

Pathway::~Pathway(){
    Protein* current = proteinHead;
    while(current != nullptr){
        Protein* next = current->next;
        delete current;
        current = next;
    }
}

int Pathway::getPathwayId() const{
    return pathwayId;
}

string Pathway::getPathwayName() const{
    return pathwayName;
}
