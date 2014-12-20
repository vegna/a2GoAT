#include "GTreePluto.h"
#include "PParticle.h"

GTreePluto::GTreePluto(GTreeManager* Manager):
    GTree(Manager, TString("data")),
    PlutoMCTrue(NULL),
    plutoID(-1),
    plutoRandomID(-1)
{}


GTreePluto::~GTreePluto()
{}

GTreePluto::ParticleList GTreePluto::GetFinalState() const
{
    ParticleList list;

    for( Long64_t i=0;i<PlutoMCTrue->GetEntries(); ++i) {

        const PParticle* const particle = dynamic_cast<const PParticle*>((*PlutoMCTrue)[i]);

        if(particle && particle->GetDaughterIndex() == -1)
            list.push_back(particle);
    }

    return list;
}

GTreePluto::ParticleList GTreePluto::GetAllParticles() const
{
    ParticleList list;

    for( Long64_t i=0;i<PlutoMCTrue->GetEntries(); ++i) {

        const PParticle* const particle = dynamic_cast<const PParticle*>((*PlutoMCTrue)[i]);

        if(particle)
            list.push_back(particle);
    }

    return list;
}


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
