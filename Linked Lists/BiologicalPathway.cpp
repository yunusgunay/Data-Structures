/*
    sec2-Yunus-Gunay-22203758
*/

#include <iostream>
using namespace std;
#include "BiologicalPathway.h"

BiologicalPathway::BiologicalPathway(){
    pathwayHead = nullptr;
}

BiologicalPathway::~BiologicalPathway(){
    Pathway* current = pathwayHead;
    while(current != nullptr){
        Pathway* next = current->next;
        delete current;
        current = next;
    }
}

void BiologicalPathway::addPathway(const int pathwayId, const string pathwayName){
    Pathway* current = pathwayHead;
    for(; current != nullptr; current = current->next){
        if(current->getPathwayId() == pathwayId){
            cout << "Cannot add pathway. There is already a pathway with ID " << pathwayId << "." << endl;
            return;
        }
    }

    Pathway* newPathway = new Pathway(pathwayId, pathwayName);
    if(pathwayHead == nullptr || pathwayHead->getPathwayId() > pathwayId){ // adding to head
        newPathway->next = pathwayHead;
        pathwayHead = newPathway;
        cout << "Added pathway " << pathwayId << "." << endl;
        return;
    }

    current = pathwayHead;
    while(current->next != nullptr && current->next->getPathwayId() < pathwayId){
        current = current->next;
    }
    newPathway->next = current->next;
    current->next = newPathway;
    cout << "Added pathway " << pathwayId << "." << endl;
}


void BiologicalPathway::removePathway(const int pathwayId){
    if(pathwayHead == nullptr){
        cout << "Cannot remove pathway. There is no pathway with ID " << pathwayId << "." << endl;
        return;
    }

    if(pathwayHead->getPathwayId() == pathwayId){ // removing head
        Pathway* toDelete = pathwayHead;
        pathwayHead = pathwayHead->next;
        delete toDelete;
        cout << "Removed pathway " << pathwayId << "." << endl;
        return;
    }

    Pathway* current = pathwayHead;
    Pathway* previous = nullptr;
    while(current != nullptr && current->getPathwayId() != pathwayId){
        previous = current;
        current = current->next;
    }

    if(current == nullptr){
        cout << "Cannot remove pathway. There is no pathway with ID " << pathwayId << "." << endl;
        return;
    }

    previous->next = current->next;
    delete current;
    cout << "Removed pathway " << pathwayId << "." << endl;
}


void BiologicalPathway::printPathways() const{
    if(pathwayHead == nullptr){
        cout << "There are no pathways to show." << endl;
        return;
    }

    cout << "Pathways in the system:" << endl;
    for(Pathway* current = pathwayHead; current != nullptr; current = current->next){
        int proteinCount = 0;
        int geneCount = 0;
        for(Protein* protein = current->proteinHead; protein != nullptr; protein = protein->next){
            proteinCount++;
            for(Gene* gene = protein->geneHead; gene != nullptr; gene = gene->next){
                geneCount++;
            }
        }
        cout << "Pathway " << current->getPathwayId() << " : " << current->getPathwayName()
             << " (" << proteinCount << " Proteins) (" << geneCount << " Genes)" << endl;
    }
}


void BiologicalPathway::addProtein(const int proteinId, const int pathwayId){
    Pathway* pathway = nullptr;
    for(Pathway* current = pathwayHead; current != nullptr; current = current->next){
        if(current->getPathwayId() == pathwayId){
            pathway = current;
            break;
        }
    }

    if(pathway == nullptr){
        cout << "Cannot add protein. There is no pathway with ID " << pathwayId << "." << endl;
        return;
    }

    for(Pathway* current = pathwayHead; current != nullptr; current = current->next){
        for(Protein* protein = current->proteinHead; protein != nullptr; protein = protein->next){
            if(protein->getProteinId() == proteinId){
                cout << "Cannot add protein. There is a pathway having a protein with ID " << proteinId << "." << endl;
                return;
            }
        }
    }

    Protein* newProtein = new Protein(proteinId);
    if(pathway->proteinHead == nullptr || pathway->proteinHead->getProteinId() > proteinId){
        newProtein->next = pathway->proteinHead;
        pathway->proteinHead = newProtein;
    } else {
        Protein* current = pathway->proteinHead;
        while(current->next != nullptr && current->next->getProteinId() < proteinId){
            current = current->next;
        }
        newProtein->next = current->next;
        current->next = newProtein;
    }
    cout << "Added protein " << proteinId << " to pathway " << pathwayId << "." << endl;
}


void BiologicalPathway::removeProtein(const int proteinId, const int pathwayId){
    Pathway* pathway = nullptr;
    for(Pathway* current = pathwayHead; current != nullptr; current = current->next){
        if(current->getPathwayId() == pathwayId){
            pathway = current;
            break;
        }
    }

    if(pathway == nullptr){
        cout << "Cannot remove protein. There is no pathway with ID " << pathwayId << "." << endl;
        return;
    }

    Protein* prevProtein = nullptr;
    Protein* protein = pathway->proteinHead;
    while(protein != nullptr && protein->getProteinId() != proteinId){
        prevProtein = protein;
        protein = protein->next;
    }

    if(protein == nullptr){
        cout << "Cannot remove protein. Pathway " << pathwayId << " does not have a protein with ID " << proteinId << "." << endl;
        return;
    }

    if(prevProtein != nullptr){
        prevProtein->next = protein->next;
    } else {
        pathway->proteinHead = protein->next;
    }
    delete protein;
    cout << "Removed protein " << proteinId << " from pathway " << pathwayId << "." << endl;
}


void BiologicalPathway::printProteinsInPathway(const int pathwayId) const{
    const Pathway* pathway = nullptr;
    for(const Pathway* current = pathwayHead; current != nullptr; current = current->next){
        if(current->getPathwayId() == pathwayId){
            pathway = current;
            break;
        }
    }

    if(pathway == nullptr){
        cout << "Cannot print proteins. There is no pathway with ID " << pathwayId << "." << endl;
        return;
    }

    if(pathway->proteinHead == nullptr){
        cout << "There are no proteins to show in pathway " << pathwayId << "." << endl;
        return;
    }

    cout << "Proteins in pathway " << pathwayId << ":" << endl;
    for(const Protein* protein = pathway->proteinHead; protein != nullptr; protein = protein->next){
        cout << "Protein ID : " << protein->getProteinId() << ", Gene IDs : ";
        if(protein->geneHead == nullptr){
            cout << "None" << endl;
        } else {
            cout << "[";
            const Gene* gene = protein->geneHead;
            while(gene != nullptr){
                cout << gene->getGeneID();
                if(gene->next != nullptr) {cout << ", ";}
                gene = gene->next;
            }
            cout << "]" << endl;
        }
    }
}


void BiologicalPathway::addGene(const int geneID, const string geneName, const int proteinId){
    for(Pathway* p = pathwayHead; p != nullptr; p = p->next){
        for(Protein* prot = p->proteinHead; prot != nullptr; prot = prot->next){
            for(Gene* g = prot->geneHead; g != nullptr; g = g->next){
                if(g->getGeneID() == geneID){
                    cout << "Cannot add gene. Gene " << geneID << " is already in use." << endl;
                    return;
                }
            }
        }
    }

    bool found = false;
    Protein* target = nullptr;
    for(Pathway* p = pathwayHead; p != nullptr && !found; p = p->next){
        for(Protein* prot = p->proteinHead; prot != nullptr; prot = prot->next){
            if(prot->getProteinId() == proteinId){
                target = prot;
                found = true;
                break;
            }
        }
    }

    if(target == nullptr){
        cout << "Cannot add gene. There is no protein with ID " << proteinId << "." << endl;
        return;
    }

    Gene* newGene = new Gene(geneID, geneName);
    if(target->geneHead == nullptr || target->geneHead->getGeneID() > geneID){
        newGene->next = target->geneHead;
        target->geneHead = newGene;
    } else {
        Gene* current = target->geneHead;
        while(current->next != nullptr && current->next->getGeneID() < geneID){
            current = current->next;
        }
        newGene->next = current->next;
        current->next = newGene;
    }

    cout << "Added gene " << geneID << " to protein " << proteinId << "." << endl;
}


void BiologicalPathway::removeGene(const int geneID, const int proteinId){
    Protein* target = nullptr;
    for(Pathway* p = pathwayHead; p != nullptr; p = p->next){
        for(Protein* prot = p->proteinHead; prot != nullptr; prot = prot->next){
            if(prot->getProteinId() == proteinId){
                target = prot;
                break;
            }
        }
    }

    if(target == nullptr){
        cout << "Cannot remove gene. There is no protein with ID " << proteinId << "." << endl;
        return;
    }

    Gene* prevGene = nullptr;
    Gene* gene = target->geneHead;
    while(gene != nullptr && gene->getGeneID() != geneID){
        prevGene = gene;
        gene = gene->next;
    }

    if(gene == nullptr){
        cout << "Cannot remove gene. There is no gene " << geneID << " encoding protein " << proteinId << "." << endl;
        return;
    }

    if(prevGene != nullptr){
        prevGene->next = gene->next;
    } else {
        target->geneHead = gene->next;
    }
    delete gene;
    cout << "Removed gene " << geneID << " from protein " << proteinId << "." << endl;
}


void BiologicalPathway::printGenesOfProtein(const int proteinId) const{
    bool proteinFound = false;
    bool hasGenes = false;

    for(const Pathway* p = pathwayHead; p != nullptr && !proteinFound; p = p->next){
        for(const Protein* prot = p->proteinHead; prot != nullptr; prot = prot->next){
            if(prot->getProteinId() == proteinId){
                proteinFound = true;
                const Gene* gene = prot->geneHead;
                if(gene != nullptr){
                    cout << "Genes in protein " << proteinId << ":" << endl;
                }

                for(; gene != nullptr; gene = gene->next){
                    cout << "GENE " << gene->getGeneID() << " : " << gene->getGeneName() << endl;
                    hasGenes = true;
                }
                break;
            }
        }
    }

    if(!proteinFound){
        cout << "Cannot print genes. There is no protein with ID " << proteinId << "." << endl;
        return;
    } else if (!hasGenes){
        cout << "There are no genes to show in protein " << proteinId << "." << endl;
    }
}

