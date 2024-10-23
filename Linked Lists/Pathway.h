/*
    sec2-Yunus-Gunay-22203758
*/

#ifndef PATHWAY_H_INCLUDED
#define PATHWAY_H_INCLUDED
#include <iostream>
using namespace std;

#include "Protein.h"

class Pathway{
public:
    Pathway* next;
    Protein* proteinHead;

    Pathway(int id, string name);
    ~Pathway();

    int getPathwayId() const;
    string getPathwayName() const;

private:
    int pathwayId;
    string pathwayName;
};

#endif // PATHWAY_H_INCLUDED
