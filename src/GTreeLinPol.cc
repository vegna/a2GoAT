#include "GTreeLinPol.h"

#include <TLeaf.h>


GTreeLinPol::GTreeLinPol(GTreeManager *Manager)    :
    GTree(Manager, TString("linPol"), kTRUE),
    plane(0),
    edge(0),
    edgeSetting(0)
{
    for(Int_t i=0; i<352; i++)
    {
        polarizationTable[i] = 0;
        enhancementTable[i] = 0;
    }
    
}

GTreeLinPol::~GTreeLinPol()
{

}

void    GTreeLinPol::SetBranchAdresses()
{
    if(inputTree->GetBranch("plane")) inputTree->SetBranchAddress("plane", &plane);
    if(inputTree->GetBranch("edge")) inputTree->SetBranchAddress("edge", &edge);
    if(inputTree->GetBranch("edgeSetting")) inputTree->SetBranchAddress("edgeSetting", &edgeSetting);
    if(inputTree->GetBranch("polarizationTable")) inputTree->SetBranchAddress("polarizationTable", polarizationTable);
    if(inputTree->GetBranch("enhancementTable")) inputTree->SetBranchAddress("enhancementTable", enhancementTable);
    
}

void    GTreeLinPol::SetBranches()
{
    outputTree = inputTree->CloneTree(0);
}
