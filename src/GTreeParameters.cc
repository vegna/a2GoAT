#include "GTreeParameters.h"
#include "GTreeManager.h"

GTreeParameters::GTreeParameters(GTreeManager *Manager)    :
    GTree(Manager, TString("parameters"), kFALSE, kTRUE),
    nTagger(0)
{
    for(Int_t i=0; i<352; i++)
    {
        TaggerElectronEnergy[i] = 0;
        TaggerPhotonEnergy[i]   = 0;
        TaggerEnergyWidth[i]    = 0;
    }
}

GTreeParameters::~GTreeParameters()
{

}

void    GTreeParameters::SetBranchAdresses()
{
    inputTree->SetBranchAddress("nTagger", 	            &nTagger);
    inputTree->SetBranchAddress("TaggerElectronEnergy", TaggerElectronEnergy);
    inputTree->SetBranchAddress("TaggerPhotonEnergy",   TaggerPhotonEnergy);
    inputTree->SetBranchAddress("TaggerEnergyWidth",    TaggerEnergyWidth);
}

void    GTreeParameters::SetBranches()
{
    outputTree->Branch("nTagger",              &nTagger,             "nTagger/I");
    outputTree->Branch("TaggerElectronEnergy", TaggerElectronEnergy, "TaggerElectronEnergy[nTagger]/D");
    outputTree->Branch("TaggerPhotonEnergy",   TaggerPhotonEnergy,   "TaggerPhotonEnergy[nTagger]/D");
    outputTree->Branch("TaggerEnergyWidth",    TaggerEnergyWidth,    "TaggerEnergyWidth[nTagger]/D");
}
