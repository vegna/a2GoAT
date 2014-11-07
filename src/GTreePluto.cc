#include "GTreePluto.h"

GTreePluto::GTreePluto(GTreeManager* Manager)    :
    GTree(Manager, TString("data")),
    PlutoMCTrue(NULL)
{}


GTreePluto::~GTreePluto()
{}

void    GTreePluto::SetBranchAdresses()
{
    tree_in->SetBranchAddress("Particles", 	&PlutoMCTrue);
}

void    GTreePluto::SetBranches()
{
    tree_out->Branch("Particles", PlutoMCTrue);
}
