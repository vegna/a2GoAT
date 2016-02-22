#include "GTreeSetupParameters.h"
#include "GTreeManager.h"

GTreeSetupParameters::GTreeSetupParameters(GTreeManager *Manager)    :
    GTree(Manager, TString("setupParameters"), kFALSE, kTRUE),
    nTagger(0),
    TaggerGlobalOffset(0),
    nNaI(0),
    NaIGlobalOffset(0),
    NaIGlobalScale(0),
    NaIMaxClusters(0),
    NaIClusterThr(0),
    nPID(0),
    PIDGlobalOffset(0),
    nBaF2(0),
    BaF2GlobalOffset(0),
    BaF2GlobalScale(0),
    BaF2Distance(0),
    BaF2MaxClusters(0),
    BaF2ClusterThr(0),
    nVeto(0),
    VetoGlobalOffset(0),
    VetoDistance(0),
    hasOverlaps(0)
{
    for(Int_t i=0; i<352; i++)
    {
        TaggerTDCLoThr[i] = 0;
        TaggerTDCHiThr[i] = 0;
        TaggerTDCOffset[i] = 0;
        TaggerElectronEnergy[i] = 0;
        TaggerPhotonEnergy[i]   = 0;
        TaggerEnergyWidth[i]    = 0;
    }
    for(Int_t i=0; i<720; i++)
    {
        NaIADCLoThr[i] = 0;
        NaIADCHiThr[i] = 0;
        NaIADCGain[i] = 0;
        NaITDCLoThr[i] = 0;
        NaITDCHiThr[i] = 0;
        NaITDCOffset[i] = 0;
    }
    for(Int_t i=0; i<24; i++)
    {
        PIDADCLoThr[i] = 0;
        PIDADCHiThr[i] = 0;
        PIDADCPedestal[i] = 0;
        PIDADCGain[i] = 0;
        PIDTDCLoThr[i] = 0;
        PIDTDCHiThr[i] = 0;
        PIDTDCOffset[i] = 0;
        PIDPhi[i] = 0;
    }
    for(Int_t i=0; i<438; i++)
    {
        BaF2ADCLoThr[i] = 0;
        BaF2ADCHiThr[i] = 0;
        BaF2ADCPedestal[i] = 0;
        BaF2ADCGain[i] = 0;
        BaF2TDCLoThr[i] = 0;
        BaF2TDCHiThr[i] = 0;
        BaF2TDCOffset[i] = 0;
        BaF2TDCGain[i] = 0;
    }
    for(Int_t i=0; i<438; i++)
    {
        VetoADCLoThr[i] = 0;
        VetoADCHiThr[i] = 0;
        VetoADCPedestal[i] = 0;
        VetoADCGain[i] = 0;
        VetoTDCLoThr[i] = 0;
        VetoTDCHiThr[i] = 0;
        VetoTDCOffset[i] = 0;
    }
}

GTreeSetupParameters::~GTreeSetupParameters()
{

}

void    GTreeSetupParameters::SetBranchAdresses()
{
    if(inputTree->GetBranch("nTagger")) inputTree->SetBranchAddress("nTagger", &nTagger);
    if(inputTree->GetBranch("TaggerGlobalOffset")) inputTree->SetBranchAddress("TaggerGlobalOffset", &TaggerGlobalOffset);
    if(inputTree->GetBranch("TaggerTDCLoThr")) inputTree->SetBranchAddress("TaggerTDCLoThr", TaggerTDCLoThr);
    if(inputTree->GetBranch("TaggerTDCHiThr")) inputTree->SetBranchAddress("TaggerTDCHiThr", TaggerTDCHiThr);
    if(inputTree->GetBranch("TaggerTDCOffset")) inputTree->SetBranchAddress("TaggerTDCOffset", TaggerTDCOffset);
    if(inputTree->GetBranch("TaggerElectronEnergy")) inputTree->SetBranchAddress("TaggerElectronEnergy", TaggerElectronEnergy);
    if(inputTree->GetBranch("TaggerPhotonEnergy")) inputTree->SetBranchAddress("TaggerPhotonEnergy", TaggerPhotonEnergy);
    if(inputTree->GetBranch("TaggerEnergyWidth"))
    {
        inputTree->SetBranchAddress("TaggerEnergyWidth", TaggerEnergyWidth);
        hasOverlaps = true;
    }

    if(inputTree->GetBranch("nNaI")) inputTree->SetBranchAddress("nNaI", &nNaI);
    if(inputTree->GetBranch("NaIGlobalOffset")) inputTree->SetBranchAddress("NaIGlobalOffset", &NaIGlobalOffset);
    if(inputTree->GetBranch("NaIGlobalScale")) inputTree->SetBranchAddress("NaIGlobalScale", &NaIGlobalScale);
    if(inputTree->GetBranch("NaIMaxClusters")) inputTree->SetBranchAddress("NaIMaxClusters", &NaIMaxClusters);
    if(inputTree->GetBranch("NaIClusterThr")) inputTree->SetBranchAddress("NaIClusterThr", &NaIClusterThr);
    if(inputTree->GetBranch("NaIADCLoThr")) inputTree->SetBranchAddress("NaIADCLoThr", NaIADCLoThr);
    if(inputTree->GetBranch("NaIADCHiThr")) inputTree->SetBranchAddress("NaIADCHiThr", NaIADCHiThr);
    if(inputTree->GetBranch("NaIADCGain")) inputTree->SetBranchAddress("NaIADCGain", NaIADCGain);
    if(inputTree->GetBranch("NaITDCLoThr")) inputTree->SetBranchAddress("NaITDCLoThr", NaITDCLoThr);
    if(inputTree->GetBranch("NaITDCHiThr")) inputTree->SetBranchAddress("NaITDCHiThr", NaITDCHiThr);
    if(inputTree->GetBranch("NaITDCOffset")) inputTree->SetBranchAddress("NaITDCOffset", NaITDCOffset);

    if(inputTree->GetBranch("nPID")) inputTree->SetBranchAddress("nPID", &nPID);
    if(inputTree->GetBranch("PIDGlobalOffset")) inputTree->SetBranchAddress("PIDGlobalOffset", &PIDGlobalOffset);
    if(inputTree->GetBranch("PIDADCLoThr")) inputTree->SetBranchAddress("PIDADCLoThr", PIDADCLoThr);
    if(inputTree->GetBranch("PIDADCHiThr")) inputTree->SetBranchAddress("PIDADCHiThr", PIDADCHiThr);
    if(inputTree->GetBranch("PIDADCPedestal")) inputTree->SetBranchAddress("PIDADCPedestal", PIDADCPedestal);
    if(inputTree->GetBranch("PIDADCGain")) inputTree->SetBranchAddress("PIDADCGain", PIDADCGain);
    if(inputTree->GetBranch("PIDTDCLoThr")) inputTree->SetBranchAddress("PIDTDCLoThr", PIDTDCLoThr);
    if(inputTree->GetBranch("PIDTDCHiThr")) inputTree->SetBranchAddress("PIDTDCHiThr", PIDTDCHiThr);
    if(inputTree->GetBranch("PIDTDCOffset")) inputTree->SetBranchAddress("PIDTDCOffset", PIDTDCOffset);
    if(inputTree->GetBranch("PIDPhi")) inputTree->SetBranchAddress("PIDPhi", PIDPhi);

    if(inputTree->GetBranch("nBaF2")) inputTree->SetBranchAddress("nBaF2", &nBaF2);
    if(inputTree->GetBranch("BaF2GlobalOffset")) inputTree->SetBranchAddress("BaF2GlobalOffset", &BaF2GlobalOffset);
    if(inputTree->GetBranch("BaF2GlobalScale")) inputTree->SetBranchAddress("BaF2GlobalScale", &BaF2GlobalScale);
    if(inputTree->GetBranch("BaF2Distance")) inputTree->SetBranchAddress("BaF2Distance", &BaF2Distance);
    if(inputTree->GetBranch("BaF2MaxClusters")) inputTree->SetBranchAddress("BaF2MaxClusters", &BaF2MaxClusters);
    if(inputTree->GetBranch("BaF2ClusterThr")) inputTree->SetBranchAddress("BaF2ClusterThr", &BaF2ClusterThr);
    if(inputTree->GetBranch("BaF2ADCLoThr")) inputTree->SetBranchAddress("BaF2ADCLoThr", BaF2ADCLoThr);
    if(inputTree->GetBranch("BaF2ADCHiThr")) inputTree->SetBranchAddress("BaF2ADCHiThr", BaF2ADCHiThr);
    if(inputTree->GetBranch("BaF2ADCPedestal")) inputTree->SetBranchAddress("BaF2ADCPedestal", BaF2ADCPedestal);
    if(inputTree->GetBranch("BaF2ADCGain")) inputTree->SetBranchAddress("BaF2ADCGain", BaF2ADCGain);
    if(inputTree->GetBranch("BaF2TDCLoThr")) inputTree->SetBranchAddress("BaF2TDCLoThr", BaF2TDCLoThr);
    if(inputTree->GetBranch("BaF2TDCHiThr")) inputTree->SetBranchAddress("BaF2TDCHiThr", BaF2TDCHiThr);
    if(inputTree->GetBranch("BaF2TDCOffset")) inputTree->SetBranchAddress("BaF2TDCOffset", BaF2TDCOffset);
    if(inputTree->GetBranch("BaF2TDCGain")) inputTree->SetBranchAddress("BaF2TDCGain", BaF2TDCGain);

    if(inputTree->GetBranch("nVeto")) inputTree->SetBranchAddress("nVeto", &nVeto);
    if(inputTree->GetBranch("VetoGlobalOffset")) inputTree->SetBranchAddress("VetoGlobalOffset", &VetoGlobalOffset);
    if(inputTree->GetBranch("VetoDistance")) inputTree->SetBranchAddress("VetoDistance", &VetoDistance);
    if(inputTree->GetBranch("VetoADCLoThr")) inputTree->SetBranchAddress("VetoADCLoThr", VetoADCLoThr);
    if(inputTree->GetBranch("VetoADCHiThr")) inputTree->SetBranchAddress("VetoADCHiThr", VetoADCHiThr);
    if(inputTree->GetBranch("VetoADCPedestal")) inputTree->SetBranchAddress("VetoADCPedestal", VetoADCPedestal);
    if(inputTree->GetBranch("VetoADCGain")) inputTree->SetBranchAddress("VetoADCGain", VetoADCGain);
    if(inputTree->GetBranch("VetoTDCLoThr")) inputTree->SetBranchAddress("VetoTDCLoThr", VetoTDCLoThr);
    if(inputTree->GetBranch("VetoTDCHiThr")) inputTree->SetBranchAddress("VetoTDCHiThr", VetoTDCHiThr);
    if(inputTree->GetBranch("VetoTDCOffset")) inputTree->SetBranchAddress("VetoTDCOffset", VetoTDCOffset);
}

void    GTreeSetupParameters::SetBranches()
{
    outputTree = inputTree->CloneTree(0);
}
