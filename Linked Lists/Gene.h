/*
    sec2-Yunus-Gunay-22203758
*/

#ifndef GENE_H_INCLUDED
#define GENE_H_INCLUDED
#include <iostream>
using namespace std;

class Gene{
public:
    Gene* next;

    Gene(int id, string name);

    int getGeneID() const;
    string getGeneName() const;

private:
    int geneID;
    string geneName;
};

#endif // GENE_H_INCLUDED
