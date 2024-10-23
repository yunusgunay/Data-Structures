/*
    sec2-Yunus-Gunay-22203758
*/

#include <iostream>
using namespace std;
#include "Gene.h"

Gene::Gene(int id, string name){
    geneID = id;
    geneName = name;
    next = nullptr;
}

int Gene::getGeneID() const{
    return geneID;
}

string Gene::getGeneName() const{
    return geneName;
}
