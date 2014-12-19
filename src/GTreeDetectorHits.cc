#include "GTreeDetectorHits.h"



GTreeDetectorHits::GTreeDetectorHits(GTreeManager *Manager)    :
    GTree(Manager, TString("detectorHits")),
    nNaIHits(0),
    nPIDHits(0),
    nMWPCHits(0),
    nBaF2PbWO4Hits(0),
    nVetoHits(0)
{
}

GTreeDetectorHits::~GTreeDetectorHits()
{
}

void    GTreeDetectorHits::SetBranchAdresses()
{
    tree_in->SetBranchAddress("nNaIHits", &nNaIHits);
    tree_in->SetBranchAddress("NaIHits", NaIHits);
    tree_in->SetBranchAddress("NaICluster", NaICluster);
    tree_in->SetBranchAddress("nPIDHits", &nPIDHits);
    tree_in->SetBranchAddress("PIDHits", PIDHits);
    tree_in->SetBranchAddress("nMWPCHits", &nMWPCHits);
    tree_in->SetBranchAddress("MWPCHits", MWPCHits);
    tree_in->SetBranchAddress("nBaF2PbWO4Hits", &nBaF2PbWO4Hits);
    tree_in->SetBranchAddress("BaF2PbWO4Hits", BaF2PbWO4Hits);
    tree_in->SetBranchAddress("BaF2PbWO4Cluster", BaF2PbWO4Cluster);
    tree_in->SetBranchAddress("nVetoHits", &nVetoHits);
    tree_in->SetBranchAddress("VetoHits", VetoHits);
}

void    GTreeDetectorHits::SetBranches()
{
    tree_out->Branch("nNaIHits", &nNaIHits, "nNaIHits/I");
    tree_out->Branch("NaIHits", NaIHits, "NaIHits[nNaIHits]/I");
    tree_out->Branch("NaICluster", NaICluster, "NaICluster[nNaIHits]/I");
    tree_out->Branch("nPIDHits", &nPIDHits, "nPIDHits/I");
    tree_out->Branch("PIDHits", PIDHits, "PIDHits[nPIDHits]/I");
    tree_out->Branch("nMWPCHits", &nMWPCHits, "nMWPCHits/I");
    tree_out->Branch("MWPCHits", MWPCHits, "MWPCHits[nMWPCHits]/I");
    tree_out->Branch("nBaF2PbWO4Hits", &nBaF2PbWO4Hits, "nBaF2PbWO4Hits/I");
    tree_out->Branch("BaF2PbWO4Hits", BaF2PbWO4Hits, "BaF2PbWO4Hits[nBaF2PbWO4Hits]/I");
    tree_out->Branch("BaF2PbWO4Cluster", BaF2PbWO4Cluster, "BaF2PbWO4Cluster[nBaF2PbWO4Hits]/I");
    tree_out->Branch("nVetoHits", &nVetoHits, "nVetoHits/I");
    tree_out->Branch("VetoHits", VetoHits, "VetoHits[nVetoHits]/I");
}


