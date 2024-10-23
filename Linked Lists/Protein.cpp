/*
    sec2-Yunus-Gunay-22203758
*/

#include <iostream>
using namespace std;
#include "Protein.h"

Protein::Protein(int id){
    proteinId = id;
    next = nullptr;
    geneHead = nullptr;
}

Protein::~Protein(){
    Gene* current = geneHead;
    while(current != nullptr){
        Gene* next = current->next;
        delete current;
        current = next;
    }
}

int Protein::getProteinId() const{
    return proteinId;
}
