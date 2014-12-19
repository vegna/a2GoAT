#include "GTreeLinPol.h"

#include <TLeaf.h>


GTreeLinPol::GTreeLinPol(GTreeManager *Manager)    :
    GTree(Manager, TString("linPol"), kTRUE),
    plane(0),
    edge(0),
    edgeSetting(0)
{
    for(int i=0; i<352; i++)
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
    tree_in->SetBranchAddress("plane", &plane);
    tree_in->SetBranchAddress("edge", &edge);
    tree_in->SetBranchAddress("edgeSetting", &edgeSetting);
    tree_in->SetBranchAddress("polarizationTable", polarizationTable);
    tree_in->SetBranchAddress("enhancementTable", enhancementTable);
    
}

void    GTreeLinPol::SetBranches()
{
    tree_out->Branch("plane", &plane, "plane/I");
    tree_out->Branch("edge", &edge, "edge/D");
    tree_out->Branch("edgeSetting", &edgeSetting, "edgeSetting/D");
    tree_out->Branch("polarizationTable", polarizationTable, "polarizationTable[352]/D");
    tree_out->Branch("enhancementTable", enhancementTable, "enhancementTable[352]/D");
}
