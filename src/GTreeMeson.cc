#include "GTreeMeson.h"
#include "GTreeManager.h"


GTreeMeson::GTreeMeson(GTreeManager *Manager, const TString& _Name)    :
    GTreeParticle(Manager, _Name),
    subRootinos(new TClonesArray("TClonesArray", GTreeParticle_MAX)),
    subPhotons(new TClonesArray("TClonesArray", GTreeParticle_MAX)),
    subChargedPions(new TClonesArray("TClonesArray", GTreeParticle_MAX))
{
    for(int i=0; i<GTreeParticle_MAX; i++)
    {
        nSubParticles[i]  = 0;
        nSubRootinos[i]   = 0;
        nSubPhotons[i]    = 0;
        nSubChargedPions[i]  = 0;
    }
}

GTreeMeson::~GTreeMeson()
{
    if (subRootinos)
        delete subRootinos;
    if (subPhotons)
        delete subPhotons;
    if (subChargedPions)
        delete subChargedPions;
}

void    GTreeMeson::Clear()
{
    GTreeParticle::Clear();
    //Cause the stored object(TClonesArray) has allocated memory one has to delete to call the destructor.
    subRootinos->Delete();
    subPhotons->Delete();
    subChargedPions->Delete();
}

void    GTreeMeson::SetBranchAdresses()
{
    GTreeParticle::SetBranchAdresses();
    inputTree->SetBranchAddress("nSubParticles", nSubParticles);
    inputTree->SetBranchAddress("nSubRootinos", nSubRootinos);
    inputTree->SetBranchAddress("nSubPhotons", nSubPhotons);
    inputTree->SetBranchAddress("nSubChargedPions", nSubChargedPions);
    inputTree->SetBranchAddress("subRootinos", &subRootinos);
    inputTree->SetBranchAddress("subPhotons", &subPhotons);
    inputTree->SetBranchAddress("subChargedPions", &subChargedPions);
}

void    GTreeMeson::SetBranches()
{
    GTreeParticle::SetBranches();
    outputTree->Branch("nSubParticles", nSubParticles, "nSubParticles[nParticles]/b");
    outputTree->Branch("nSubRootinos", nSubRootinos,"nSubRootinos[nParticles]/b");
    outputTree->Branch("nSubPhotons", nSubPhotons,"nSubParticles[nParticles]/b");
    outputTree->Branch("nSubChargedPions", nSubChargedPions,"nSubParticles[nParticles]/b");
    outputTree->Branch("subRootinos", &subRootinos, 32, 0);
    outputTree->Branch("subPhotons", &subPhotons, 32, 0);
    outputTree->Branch("subChargedPions", &subChargedPions, 32, 0);
}

void    GTreeMeson::AddParticle(const Int_t _NSubRootinos, Int_t* subRootinos_index, TLorentzVector** subRootinos_list, const Int_t _NSubPhotons, Int_t* subPhotons_index, TLorentzVector** subPhotons_list, const Int_t _NSubChargedPions, Int_t* subChargedPions_index, TLorentzVector** subChargedPions_list)
{
    new((*subRootinos)[nParticles]) TClonesArray("TLorentzVector", _NSubRootinos);
    new((*subPhotons)[nParticles]) TClonesArray("TLorentzVector", _NSubPhotons);
    new((*subChargedPions)[nParticles]) TClonesArray("TLorentzVector", _NSubChargedPions);
    apparatus[nParticles]    = GTreeTrack::APPARATUS_NONE;
    time[nParticles]         = 0;
    clusterSize[nParticles]  = 0;
    vetoEnergy[nParticles]          = 0;
    MWPC0Energy[nParticles]        = 0;
    MWPC1Energy[nParticles]        = 0;

    nSubParticles[nParticles]  = _NSubRootinos + _NSubPhotons + _NSubChargedPions;
    nSubRootinos[nParticles]   = _NSubRootinos;
    nSubPhotons[nParticles]    = _NSubPhotons;
    nSubChargedPions[nParticles]  = _NSubChargedPions;
    TLorentzVector  sum;
    for(int i=0; i<_NSubRootinos; i++)
    {
        sum += *subRootinos_list[i];
        new((*((TClonesArray*)subRootinos->At(nParticles)))[i]) TLorentzVector(*subRootinos_list[i]);
        apparatus[nParticles]    = apparatus[nParticles] | manager->rootinos->GetApparatus(subRootinos_index[i]);
        time[nParticles]         += manager->rootinos->GetTime(subRootinos_index[i]);
        clusterSize[nParticles]  += manager->rootinos->GetClusterSize(subRootinos_index[i]);
        vetoEnergy[nParticles]          += manager->rootinos->GetVetoEnergy(subRootinos_index[i]);
        MWPC0Energy[nParticles]        += manager->rootinos->GetMWPC0Energy(subRootinos_index[i]);
        MWPC1Energy[nParticles]        += manager->rootinos->GetMWPC1Energy(subRootinos_index[i]);
    }
    for(int i=0; i<_NSubPhotons; i++)
    {
        sum += *subPhotons_list[i];
        new((*((TClonesArray*)subPhotons->At(nParticles)))[i]) TLorentzVector(*subPhotons_list[i]);
        apparatus[nParticles]    = apparatus[nParticles] | manager->photons->GetApparatus(subPhotons_index[i]);
        time[nParticles]         += manager->photons->GetTime(subPhotons_index[i]);
        clusterSize[nParticles]  += manager->photons->GetClusterSize(subPhotons_index[i]);
        vetoEnergy[nParticles]          += manager->photons->GetVetoEnergy(subPhotons_index[i]);
        MWPC0Energy[nParticles]        += manager->photons->GetMWPC0Energy(subPhotons_index[i]);
        MWPC1Energy[nParticles]        += manager->photons->GetMWPC1Energy(subPhotons_index[i]);
    }
    for(int i=0; i<_NSubChargedPions; i++)
    {
        sum += *subChargedPions_list[i];
        new((*((TClonesArray*)subChargedPions->At(nParticles)))[i]) TLorentzVector(*subChargedPions_list[i]);
        apparatus[nParticles]    = apparatus[nParticles] | manager->chargedPions->GetApparatus(subChargedPions_index[i]);
        time[nParticles]         += manager->chargedPions->GetTime(subChargedPions_index[i]);
        clusterSize[nParticles]  += manager->chargedPions->GetClusterSize(subChargedPions_index[i]);
        vetoEnergy[nParticles]          += manager->chargedPions->GetVetoEnergy(subChargedPions_index[i]);
        MWPC0Energy[nParticles]        += manager->chargedPions->GetMWPC0Energy(subChargedPions_index[i]);
        MWPC1Energy[nParticles]        += manager->chargedPions->GetMWPC1Energy(subChargedPions_index[i]);
    }
    time[nParticles]         /= nSubParticles[nParticles];
    new((*particles)[nParticles]) TLorentzVector(sum);
    nParticles++;
    manager->countReconstructed++;
}


void    GTreeMeson::AddParticle(const Int_t subParticle_index0, const TLorentzVector& subParticle0, const Int_t pdg0, const Int_t subParticle_index1, const TLorentzVector& subParticle1, const Int_t pdg1)
{
    new((*subRootinos)[nParticles]) TClonesArray("TLorentzVector", 2);
    new((*subPhotons)[nParticles]) TClonesArray("TLorentzVector", 2);
    new((*subChargedPions)[nParticles]) TClonesArray("TLorentzVector", 2);

    nSubParticles[nParticles]  = 2;
    nSubRootinos[nParticles]   = 0;
    nSubPhotons[nParticles]    = 0;
    nSubChargedPions[nParticles]  = 0;

    if(pdg0 == manager->pdgDB->GetParticle("gamma")->PdgCode())
    {
        new((*((TClonesArray*)subPhotons->At(nParticles)))[nSubPhotons[nParticles]]) TLorentzVector(subParticle0);
        apparatus[nParticles]    = manager->photons->GetApparatus(subParticle_index0);
        time[nParticles]         = manager->photons->GetTime(subParticle_index0);
        clusterSize[nParticles]  = manager->photons->GetClusterSize(subParticle_index0);
        vetoEnergy[nParticles]          = manager->photons->GetVetoEnergy(subParticle_index0);
        MWPC0Energy[nParticles]        = manager->photons->GetMWPC0Energy(subParticle_index0);
        MWPC1Energy[nParticles]        = manager->photons->GetMWPC1Energy(subParticle_index0);
        nSubPhotons[nParticles]++;
    }
    else if(pdg0 == manager->pdgDB->GetParticle("pi+")->PdgCode())
    {
        new((*((TClonesArray*)subChargedPions->At(nParticles)))[nSubChargedPions[nParticles]]) TLorentzVector(subParticle0);
        apparatus[nParticles]    = manager->chargedPions->GetApparatus(subParticle_index0);
        time[nParticles]         = manager->chargedPions->GetTime(subParticle_index0);
        clusterSize[nParticles]  = manager->chargedPions->GetClusterSize(subParticle_index0);
        vetoEnergy[nParticles]          = manager->chargedPions->GetVetoEnergy(subParticle_index0);
        MWPC0Energy[nParticles]        = manager->chargedPions->GetMWPC0Energy(subParticle_index0);
        MWPC1Energy[nParticles]        = manager->chargedPions->GetMWPC1Energy(subParticle_index0);
        nSubChargedPions[nParticles]++;
    }
    else
    {
        new((*((TClonesArray*)subRootinos->At(nParticles)))[nSubRootinos[nParticles]]) TLorentzVector(subParticle0);
        apparatus[nParticles]    = manager->rootinos->GetApparatus(subParticle_index0);
        time[nParticles]         = manager->rootinos->GetTime(subParticle_index0);
        clusterSize[nParticles]  = manager->rootinos->GetClusterSize(subParticle_index0);
        vetoEnergy[nParticles]          = manager->rootinos->GetVetoEnergy(subParticle_index0);
        MWPC0Energy[nParticles]        = manager->rootinos->GetMWPC0Energy(subParticle_index0);
        MWPC1Energy[nParticles]        = manager->rootinos->GetMWPC1Energy(subParticle_index0);
        nSubRootinos[nParticles]++;
    }
    
    if(pdg1 == manager->pdgDB->GetParticle("gamma")->PdgCode())
    {
        new((*((TClonesArray*)subPhotons->At(nParticles)))[nSubPhotons[nParticles]]) TLorentzVector(subParticle1);
        apparatus[nParticles]    = apparatus[nParticles] | manager->photons->GetApparatus(subParticle_index1);
        time[nParticles]         += manager->photons->GetTime(subParticle_index1);
        clusterSize[nParticles]  += manager->photons->GetClusterSize(subParticle_index1);
        vetoEnergy[nParticles]          += manager->photons->GetVetoEnergy(subParticle_index1);
        MWPC0Energy[nParticles]        += manager->photons->GetMWPC0Energy(subParticle_index1);
        MWPC1Energy[nParticles]        += manager->photons->GetMWPC1Energy(subParticle_index1);
        nSubPhotons[nParticles]++;
    }
    else if(pdg1 == manager->pdgDB->GetParticle("pi+")->PdgCode())
    {
        new((*((TClonesArray*)subChargedPions->At(nParticles)))[nSubChargedPions[nParticles]]) TLorentzVector(subParticle1);
        apparatus[nParticles]    = apparatus[nParticles] | manager->chargedPions->GetApparatus(subParticle_index1);
        time[nParticles]         += manager->chargedPions->GetTime(subParticle_index1);
        clusterSize[nParticles]  += manager->chargedPions->GetClusterSize(subParticle_index1);
        vetoEnergy[nParticles]          += manager->chargedPions->GetVetoEnergy(subParticle_index1);
        MWPC0Energy[nParticles]        += manager->chargedPions->GetMWPC0Energy(subParticle_index1);
        MWPC1Energy[nParticles]        += manager->chargedPions->GetMWPC1Energy(subParticle_index1);
        nSubChargedPions[nParticles]++;
    }
    else
    {
        new((*((TClonesArray*)subRootinos->At(nParticles)))[nSubRootinos[nParticles]]) TLorentzVector(subParticle1);
        apparatus[nParticles]    = apparatus[nParticles] | manager->rootinos->GetApparatus(subParticle_index1);
        time[nParticles]         += manager->rootinos->GetTime(subParticle_index1);
        clusterSize[nParticles]  += manager->rootinos->GetClusterSize(subParticle_index1);
        vetoEnergy[nParticles]          += manager->rootinos->GetVetoEnergy(subParticle_index1);
        MWPC0Energy[nParticles]        += manager->rootinos->GetMWPC0Energy(subParticle_index1);
        MWPC1Energy[nParticles]        += manager->rootinos->GetMWPC1Energy(subParticle_index1);
        nSubRootinos[nParticles]++;
    }
    time[nParticles]         /= 2;
    new((*particles)[nParticles]) TLorentzVector(subParticle0 + subParticle1);
    nParticles++;
    manager->countReconstructed++;
}


void    GTreeMeson::Print() const
{
    GTree::Print();
    cout << "nParticles: " << nParticles << endl;
    for(int i=0; i<nParticles; i++)
    {
        GTreeParticle::PrintParticle(i);
        cout << "nSubParticles: " << (Int_t)nSubParticles[i] << "   nSubRootinos: " << (Int_t)nSubRootinos[i] << "   nSubPhotons: " << (Int_t)nSubPhotons[i] << "   nSubChargedPions: " << (Int_t)nSubChargedPions[i] << endl;
        for(int l=0; l<nSubRootinos[i]; l++)
            cout << "\t\tPx: " << SubRootinos(i, l).Px() << "   Py: " << SubRootinos(i, l).Py() << "   Pz: " << SubRootinos(i, l).Pz() << "   E: " << SubRootinos(i, l).E()<< endl;
        for(int l=0; l<nSubPhotons[i]; l++)
            cout << "\t\tPx: " << SubPhotons(i, l).Px() << "   Py: " << SubPhotons(i, l).Py() << "   Pz: " << SubPhotons(i, l).Pz() << "   E: " << SubPhotons(i, l).E()<< endl;
        for(int l=0; l<nSubChargedPions[i]; l++)
            cout << "\t\tPx: " << SubChargedPions(i, l).Px() << "   Py: " << SubChargedPions(i, l).Py() << "   Pz: " << SubChargedPions(i, l).Pz() << "   E: " << SubChargedPions(i, l).E()<< endl;
    }
}

UChar_t             nSubParticles[GTreeParticle_MAX];
UChar_t             nSubRootinos[GTreeParticle_MAX];
UChar_t             nSubPhotons[GTreeParticle_MAX];
UChar_t             nSubChargedPions[GTreeParticle_MAX];
TClonesArray*       subRootinos;
TClonesArray*       subPhotons;
TClonesArray*       subChargedPions;
