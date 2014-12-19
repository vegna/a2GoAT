#include "GTreeTrigger.h"



GTreeTrigger::GTreeTrigger(GTreeManager* Manager)    :
    GTree(Manager, TString("trigger")),
    energySum(0),
    multiplicity(0),
    nTriggerPattern(0),
    helicity(0),
    nErrors(0),
    MC_evt_id(-1),
    MC_rnd_id(-1)
{
    for(int i=0; i<GTreeTrigger_MAX; i++)
    {
        triggerPattern[i] = 0;
        errorModuleID[i] = 0;
        errorModuleIndex[i] = 0;
        errorCode[i] = 0;
    }
}

GTreeTrigger::~GTreeTrigger()
{

}

void    GTreeTrigger::SetBranchAdresses()
{
    tree_in->SetBranchAddress("energySum", 	      &energySum);
    tree_in->SetBranchAddress("multiplicity", 	  &multiplicity);
    tree_in->SetBranchAddress("nTriggerPattern",  &nTriggerPattern);
    tree_in->SetBranchAddress("triggerPattern",   triggerPattern);
    tree_in->SetBranchAddress("helicity", 	      &helicity);
    tree_in->SetBranchAddress("nErrors", 	      &nErrors);
    tree_in->SetBranchAddress("errorModuleID",    errorModuleID);
    tree_in->SetBranchAddress("errorModuleIndex", errorModuleIndex);
    tree_in->SetBranchAddress("errorCode",        errorCode);
    tree_in->SetBranchAddress("mc_evt_id",        &MC_evt_id);
    tree_in->SetBranchAddress("mc_rnd_id",        &MC_rnd_id);
}

void    GTreeTrigger::SetBranches()
{
    tree_out->Branch("energySum",        &energySum,       "energySum/D");
    tree_out->Branch("multiplicity",     &multiplicity,    "multiplicity/I");
    tree_out->Branch("helicity",         &helicity,        "helicity/O");
    tree_out->Branch("nTriggerPattern",  &nTriggerPattern, "nTriggerPattern/I");
    tree_out->Branch("triggerPattern",   triggerPattern,   "triggerPattern[nTriggerPattern]/I");
    tree_out->Branch("nErrors",          &nErrors,         "nErrors/I");
    tree_out->Branch("errorModuleID",    errorModuleID,    "errorModuleID[nErrors]/I");
    tree_out->Branch("errorModuleIndex", errorModuleIndex, "errorModuleIndex[nErrors]/I");
    tree_out->Branch("errorCode",        errorCode,        "errorCode[nErrors]/I");
    tree_out->Branch("mc_evt_id",        &MC_evt_id,       "mc_evt_id/L");
    tree_out->Branch("mc_rnd_id",        &MC_rnd_id,       "mc_rnd_id/L");
}


