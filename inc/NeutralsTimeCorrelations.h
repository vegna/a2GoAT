#ifndef __NeutralsTimeCorrelations_h__
#define __NeutralsTimeCorrelations_h__

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>

#include "GTreeManager.h"
#include "PPhysics.h"
#include "TH2.h"
//#include "TH3.h"
//#include "TRandom3.h"
#include <TCutG.h>

class	NeutralsTimeCorrelations  : public PPhysics
{
private:

    TH1* nTracks;
    TH1* nParticles;
    TH1* TimeDiffBetweenNeutral;
    TH1* TimeDiffSelectionBetweenNeutral;

    TH1* nIncomingPhotonsAll;
    TH1* nIncomingPhotonsInPromptPeak;
    TH1* timeIncomingPhotons;
    TH2* timeCorrelationIncomingPhotonVsNeutralParticlesAll;
    TH1* energyIncomingPhotonsAll;

// All events
    TH1* CoplanarityAll;
    TH2* CoplanarityVsPhiProtonAll;
    TH2* CoplanarityVsInvariantMassAll;
    TH2* AzimuthalAnglesPhotonsAll;
    TH2* EnergyPhoton1VsInvariantMassAll;
    TH2* EnergyPhoton2VsInvariantMassAll;
    TH2* DeltaEnergyPhotonsVsInvariantMassAll;
// Only for E_gamma1 > = 70. MeV;
    TH1* CoplanarityEGamma1Good;
    TH2* CoplanarityVsPhiProtonEGamma1Good;
    TH2* CoplanarityVsInvariantMassEGamma1Good;
    TH2* AzimuthalAnglesPhotonsEGamma1Good;
    TH2* EnergyPhoton1VsInvariantMassEGamma1Good;
    TH2* EnergyPhoton2VsInvariantMassEGamma1Good;
    TH2* DeltaEnergyPhotonsVsInvariantMassEGamma1Good;
// Only for E_gamma1 < 70. MeV;
    TH1* CoplanarityEGamma1Bad;
    TH2* CoplanarityVsPhiProtonEGamma1Bad;
    TH2* CoplanarityVsInvariantMassEGamma1Bad;
    TH2* AzimuthalAnglesPhotonsEGamma1Bad;
    TH2* EnergyPhoton1VsInvariantMassEGamma1Bad;
    TH2* EnergyPhoton2VsInvariantMassEGamma1Bad;
    TH2* DeltaEnergyPhotonsVsInvariantMassEGamma1Bad;

//    TCutG* Proton;
//    TCutG* Pion;

//  counters to perform checks at the end of the analysis
    Int_t evtNum;
    Int_t nIncompatibleWithGoat;
    Int_t nBadTimeCorrelationBetweenNeutralParticles;

    Int_t nNoPhotonsInPromptPeak;
    Int_t nTooManyPhotonsInPromptPeak;

    Int_t nEneG1TooLow;

    Int_t IndexIncomingPhoton;

    Double_t ProtonMass = 938.272046;
//    TLorentzVector lvIncomingPhoton;
//    TLorentzVector lvTarget;
    TLorentzVector lvRecoilProton;
//    TLorentzVector lvPiMinus;
    TLorentzVector lvInvariantSystem;
    TLorentzVector lvGamma1;
    TLorentzVector lvGamma2;

protected:
    virtual Bool_t  Start();
    virtual void    ProcessEvent();
    virtual void    ProcessScalerRead();
    virtual Bool_t  Write();
  
public:
    NeutralsTimeCorrelations();
    virtual ~NeutralsTimeCorrelations();
    virtual Bool_t  Init();

    Bool_t CheckInitialConditions();
    Bool_t CheckNeutralCorrelation(Int_t NSigmaCoplanarity, Int_t NSigmaTime);
    Bool_t CheckTagger();
    void FillHistograms();
    Bool_t BuildPiNot();
    void FindRecoilProton();

//    void FillTracks(const GTreeTrack& tree, TH1* Hist);
//    void FillParticles(const GTreeTrack& tree, TH1* Hist);
/*
    void        FillTime(const GTreeTrack& tree, TH1* Hist);
    void        FillNTracks(const GTreeTrack& tree, TH1* Hist, TH1* HistN, TH1* HistC);
    void        FillFPD_TI(const GTreeTrack& tree, GH1* gHist0, GH1* gHist1, 
			   GH1* gCBHist0, GH1* gCBHist1, GH1* gTAPSHist0, GH1* gTAPSHist1);

    void        FillEsum(const GTreeTrack& tree, GH1* gHist0, GH1* gHist1, GH1* gHist2);
*/
};
#endif
