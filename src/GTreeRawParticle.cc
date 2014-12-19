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
    tree_in->SetBranchAddress("nParticles",&nParticles);
    tree_in->SetBranchAddress("clusterEnergy",  clusterEnergy);
    tree_in->SetBranchAddress("theta", theta);
    tree_in->SetBranchAddress("phi",  phi);
    tree_in->SetBranchAddress("time", time);
    tree_in->SetBranchAddress("clusterSize", clusterSize);
    tree_in->SetBranchAddress("centralCrystal", centralCrystal);
    tree_in->SetBranchAddress("centralVeto", centralVeto);
    tree_in->SetBranchAddress("apparatus", apparatus);
    tree_in->SetBranchAddress("vetoEnergy", vetoEnergy);
    tree_in->SetBranchAddress("MWPC0Energy", MWPC0Energy);
    tree_in->SetBranchAddress("MWPC1Energy", MWPC1Energy);
}

void    GTreeRawParticle::SetBranches()
{
    tree_out->Branch("nParticles",&nParticles,"nParticles/I");
    tree_out->Branch("clusterEnergy",  clusterEnergy,  "clusterEnergy[nParticles]/D");
    tree_out->Branch("theta",  theta,  "theta[nParticles]/D");
    tree_out->Branch("phi",  phi,  "phi[nParticles]/D");
    tree_out->Branch("time", time, "time[nParticles]/D");
    tree_out->Branch("clusterSize", clusterSize, "clusterSize[nParticles]/b");
    tree_out->Branch("centralCrystal", centralCrystal, "centralCrystal[nParticles]/I");
    tree_out->Branch("centralVeto", centralVeto, "centralVeto[nParticles]/I");
    tree_out->Branch("apparatus", apparatus, "apparatus[nParticles]/b");
    tree_out->Branch("vetoEnergy", vetoEnergy, "vetoEnergy[nParticles]/D");
    tree_out->Branch("MWPC0Energy", MWPC0Energy, "MWPC0Energy[nParticles]/D");
    tree_out->Branch("MWPC1Energy", MWPC1Energy, "MWPC1Energy[nParticles]/D");
}

void    GTreeRawParticle::Print(const Bool_t All) const
{
    std::cout << "GTreeParticle: nParticles->" << nParticles << std::endl;
}
