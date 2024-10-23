/*
    sec2-Yunus-Gunay-22203758
*/

#ifndef BIOLOGICALPATHWAY_H_INCLUDED
#define BIOLOGICALPATHWAY_H_INCLUDED
#include <iostream>
using namespace std;

#include "Pathway.h"

class BiologicalPathway{
public:
    BiologicalPathway();
    ~BiologicalPathway();

    void addPathway(const int pathwayId, const string pathwayName);
    void removePathway(const int pathwayId);
    void printPathways() const;

    void addProtein(const int proteinId, const int pathwayId);
    void removeProtein(const int proteinId, const int pathwayId);
    void printProteinsInPathway(const int pathwayId) const;

    void addGene(const int geneID, const string geneName, const int proteinId);
    void removeGene(const int geneID, const int proteinId);
    void printGenesOfProtein(const int proteinId) const;

private:
    Pathway* pathwayHead;
};

#endif // BIOLOGICALPATHWAY_H_INCLUDED
