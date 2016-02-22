#include "GTreeTrack.h"

GTreeTrack::GTreeTrack(GTreeManager *Manager, const TString& _Name)    :
    GTree(Manager,_Name),
    nTracks(0),
    targetShift(0),
    TAPSDistance(0),
    CBDistance(45.411)
{
    for(Int_t i=0; i<GTreeTrack_MAX; i++)
    {
        clusterEnergy[i] = 0;
        theta[i] = 0;
        phi[i] = 0;
        time[i] = 0;
        clusterSize[i] = 0;
        centralCrystal[i] = -1;
        centralVeto[i] = -1;
        detectors[i] = 0;
        vetoEnergy[i] = 0;
        MWPC0Energy[i] = 0;
        MWPC1Energy[i] = 0;
        shortEnergy[i] = 0;
        pseudoVertexX[i] = 0;
        pseudoVertexY[i] = 0;
        pseudoVertexZ[i] = 0;
    }
}

GTreeTrack::~GTreeTrack()
{

}

void    GTreeTrack::SetBranchAdresses()
{
    if(inputTree->GetBranch("nTracks")) inputTree->SetBranchAddress("nTracks",&nTracks);
    if(inputTree->GetBranch("clusterEnergy")) inputTree->SetBranchAddress("clusterEnergy",  clusterEnergy);
    if(inputTree->GetBranch("theta")) inputTree->SetBranchAddress("theta", theta);
    if(inputTree->GetBranch("phi")) inputTree->SetBranchAddress("phi",  phi);
    if(inputTree->GetBranch("time")) inputTree->SetBranchAddress("time", time);
    if(inputTree->GetBranch("clusterSize")) inputTree->SetBranchAddress("clusterSize", clusterSize);
    if(inputTree->GetBranch("centralCrystal")) inputTree->SetBranchAddress("centralCrystal", centralCrystal);
    if(inputTree->GetBranch("centralVeto")) inputTree->SetBranchAddress("centralVeto", centralVeto);
    if(inputTree->GetBranch("detectors")) inputTree->SetBranchAddress("detectors", detectors);
    if(inputTree->GetBranch("vetoEnergy")) inputTree->SetBranchAddress("vetoEnergy", vetoEnergy);
    if(inputTree->GetBranch("MWPC0Energy")) inputTree->SetBranchAddress("MWPC0Energy", MWPC0Energy);
    if(inputTree->GetBranch("MWPC1Energy")) inputTree->SetBranchAddress("MWPC1Energy", MWPC1Energy);
    if(inputTree->GetBranch("shortEnergy")) inputTree->SetBranchAddress("shortEnergy", shortEnergy);
    if(inputTree->GetBranch("pseudoVertexX")) inputTree->SetBranchAddress("pseudoVertexX", pseudoVertexX);
    if(inputTree->GetBranch("pseudoVertexY")) inputTree->SetBranchAddress("pseudoVertexY", pseudoVertexY);
    if(inputTree->GetBranch("pseudoVertexZ")) inputTree->SetBranchAddress("pseudoVertexZ", pseudoVertexZ);
}

void    GTreeTrack::SetBranches()
{
    outputTree = inputTree->CloneTree(0);
}

void    GTreeTrack::Print(const Bool_t All) const
{
    std::cout << "GTreeTrack: nTracks->" << nTracks << std::endl;
}
