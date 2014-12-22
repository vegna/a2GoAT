#include "GTreeRawParticle.h"

GTreeRawParticle::GTreeRawParticle(GTreeManager *Manager)    :
    GTree(Manager, TString("rawParticle")),
    nParticles(0)
{
    for(int i=0; i<GTreeRawParticle_MAX; i++)
    {
        clusterEnergy[i] = 0;
        theta[i] = 0;
        phi[i] = 0;
        time[i] = 0;
        clusterSize[i] = 0;
        centralCrystal[i] = 0;
        centralVeto[i] = 0;
        apparatus[i] = 0;
        //Charged detector energies
        vetoEnergy[i] = 0;
        MWPC0Energy[i] = 0;
        MWPC1Energy[i] = 0;
    }
}

GTreeRawParticle::~GTreeRawParticle()
{

}

void    GTreeRawParticle::SetBranchAdresses()
{
    inputTree->SetBranchAddress("nParticles",&nParticles);
    inputTree->SetBranchAddress("clusterEnergy",  clusterEnergy);
    inputTree->SetBranchAddress("theta", theta);
    inputTree->SetBranchAddress("phi",  phi);
    inputTree->SetBranchAddress("time", time);
    inputTree->SetBranchAddress("clusterSize", clusterSize);
    inputTree->SetBranchAddress("centralCrystal", centralCrystal);
    inputTree->SetBranchAddress("centralVeto", centralVeto);
    inputTree->SetBranchAddress("apparatus", apparatus);
    inputTree->SetBranchAddress("vetoEnergy", vetoEnergy);
    inputTree->SetBranchAddress("MWPC0Energy", MWPC0Energy);
    inputTree->SetBranchAddress("MWPC1Energy", MWPC1Energy);
}

void    GTreeRawParticle::SetBranches()
{
    outputTree->Branch("nParticles",&nParticles,"nParticles/I");
    outputTree->Branch("clusterEnergy",  clusterEnergy,  "clusterEnergy[nParticles]/D");
    outputTree->Branch("theta",  theta,  "theta[nParticles]/D");
    outputTree->Branch("phi",  phi,  "phi[nParticles]/D");
    outputTree->Branch("time", time, "time[nParticles]/D");
    outputTree->Branch("clusterSize", clusterSize, "clusterSize[nParticles]/b");
    outputTree->Branch("centralCrystal", centralCrystal, "centralCrystal[nParticles]/I");
    outputTree->Branch("centralVeto", centralVeto, "centralVeto[nParticles]/I");
    outputTree->Branch("apparatus", apparatus, "apparatus[nParticles]/b");
    outputTree->Branch("vetoEnergy", vetoEnergy, "vetoEnergy[nParticles]/D");
    outputTree->Branch("MWPC0Energy", MWPC0Energy, "MWPC0Energy[nParticles]/D");
    outputTree->Branch("MWPC1Energy", MWPC1Energy, "MWPC1Energy[nParticles]/D");
}

void    GTreeRawParticle::Print(const Bool_t All) const
{
    std::cout << "GTreeParticle: nParticles->" << nParticles << std::endl;
}
