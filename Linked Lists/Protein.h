/*
    sec2-Yunus-Gunay-22203758
*/

#ifndef PROTEIN_H_INCLUDED
#define PROTEIN_H_INCLUDED
#include <iostream>
using namespace std;

#include "Gene.h"

class Protein{
public:
    Protein* next;
    Gene* geneHead;

    Protein(int id);
    ~Protein();

    int getProteinId() const;

private:
    int proteinId;
};

#endif // PROTEIN_H_INCLUDED
