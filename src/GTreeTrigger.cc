#include "GTreeTrigger.h"



GTreeTrigger::GTreeTrigger(GTreeManager* Manager)    :
    GTree(Manager, TString("trigger")),
    energySum(0),
    multiplicity(0),
    nTriggerPattern(0),
    nErrors(0),
    helicity(0),
    MC_evt_id(-1),
    MC_rnd_id(-1),
    hasHelicity(0),
    hasMCID(0)
{
    for(Int_t i=0; i<GTreeTrigger_MAX; i++)
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
    if(inputTree->GetBranch("energySum")) inputTree->SetBranchAddress("energySum", 	      &energySum);
    if(inputTree->GetBranch("multiplicity")) inputTree->SetBranchAddress("multiplicity", 	  &multiplicity);
    if(inputTree->GetBranch("nTriggerPattern")) inputTree->SetBranchAddress("nTriggerPattern",  &nTriggerPattern);
    if(inputTree->GetBranch("triggerPattern")) inputTree->SetBranchAddress("triggerPattern",   triggerPattern);
    if(inputTree->GetBranch("nErrors")) inputTree->SetBranchAddress("nErrors", 	      &nErrors);
    if(inputTree->GetBranch("errorModuleID")) inputTree->SetBranchAddress("errorModuleID",    errorModuleID);
    if(inputTree->GetBranch("errorModuleIndex")) inputTree->SetBranchAddress("errorModuleIndex", errorModuleIndex);
    if(inputTree->GetBranch("errorCode")) inputTree->SetBranchAddress("errorCode",        errorCode);
    if(inputTree->GetBranch("helicity"))
    {
        inputTree->SetBranchAddress("helicity",  &helicity);
        hasHelicity = true;
    }
    if(inputTree->GetBranch("mc_evt_id"))
    {
        inputTree->SetBranchAddress("mc_evt_id", &MC_evt_id);
        inputTree->SetBranchAddress("mc_rnd_id", &MC_rnd_id);
        hasMCID = true;
    }
}

void    GTreeTrigger::SetBranches()
{
    outputTree = inputTree->CloneTree(0);
}


