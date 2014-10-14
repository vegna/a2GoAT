#include "GTreeLinPol.h"

#include <TLeaf.h>


GTreeLinPol::GTreeLinPol(GTreeManager *Manager)    :
    GTree(Manager, TString("treeLinPol"), kTRUE),
    plane(0),
    edge(0),
    edgeSetting(0)
{
    for(int i=0; i<352; i++)
    {
    	polTable[i] = 0;
	enhTable[i] = 0;
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
    tree_in->SetBranchAddress("polTable", polTable);
    tree_in->SetBranchAddress("enhTable", enhTable);
    
}

void    GTreeLinPol::SetBranches()
{
    tree_out->Branch("plane", &plane, "plane/I");
    tree_out->Branch("edge", &edge, "edge/D");
    tree_out->Branch("edgeSetting", &edgeSetting, "edgeSetting/D");
    tree_out->Branch("polTable", polTable, "polTable[352]/D");
    tree_out->Branch("enhTable", enhTable, "enhTable[352]/D");
}
