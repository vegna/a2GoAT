#include "GTreeEventParameters.h"



GTreeEventParameters::GTreeEventParameters(GTreeManager* Manager)    :
    GTree(Manager, TString("eventParameters")),
    eventNumber(0),
    nReconstructed(0)
{

}

GTreeEventParameters::~GTreeEventParameters()
{

}

void    GTreeEventParameters::SetBranchAdresses()
{
    tree_in->SetBranchAddress("eventNumber", 	&eventNumber);
    tree_in->SetBranchAddress("nReconstructed", 	&nReconstructed);

}

void    GTreeEventParameters::SetBranches()
{
    tree_out->Branch("eventNumber", &eventNumber, "eventNumber/i");
    tree_out->Branch("nReconstructed", &nReconstructed, "nReconstructed/b");

  }


