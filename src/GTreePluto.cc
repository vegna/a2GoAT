#include "GTreePluto.h"

GTreePluto::GTreePluto(GTreeManager* Manager):
    GTree(Manager, TString("data")),
    PlutoMCTrue(NULL),
    plutoID(-1),
    plutoRandomID(-1)
{}


GTreePluto::~GTreePluto()
{}

void    GTreePluto::SetBranchAdresses()
{
    tree_in->SetBranchAddress("Particles", 	&PlutoMCTrue);
    tree_in->SetBranchAddress("plutoID", 	&plutoID);
    tree_in->SetBranchAddress("plutoRandomID", 	&plutoRandomID);
}

void    GTreePluto::SetBranches()
{
    tree_out->Branch("Particles", PlutoMCTrue);
    tree_out->Branch("plutoID", &plutoID);
    tree_out->Branch("plutoRandomID", &plutoRandomID);
}
