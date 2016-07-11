#ifndef __PiMinusProton_h__
#define __PiMinusProton_h__

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>

#include "GTreeManager.h"
#include "PPhysics.h"
#include "TH2.h"
#include "TH3.h"
#include "TRandom3.h"

class	PiMinusProton  : public PPhysics
{
private:

    TH1* nTracks;
    TH1* nParticles;
    TH2* Coplanarity;
    TH2* CoplanaritySelection;
    TH1* TimeDiffBetweenCharged;
    TH1* TimeDiffSelectionBetweenCharged;

    TH1* nIncomingPhotonsAll;
    TH1* nIncomingPhotonsInPromptPeak;
    TH1* timeIncomingPhotons;
    TH2* timeCorrelationIncomingPhotonVsChargedParticlesAll;
    TH2* timeCorrelationIncomingPhotonVsChargedParticlesSelected;
    TH1* energyIncomingPhotonsAll;
    TH1* energyIncomingPhotonSelected;

    TH2* PCalcDenum1VsPCalcDenum2;
    TH1* PYConservation;
    TH2* ChargedParticleHypothesis;


//  counters to perform checks at the end of the analysis
    Int_t evtNum;
    Int_t nIncompatibleWithGoat;
    Int_t nBadCoplanarity;
    Int_t nBadTimeCorrelationBetweenChargedParticles;

    Int_t nNoPhotonsInPromptPeak;
    Int_t nTooManyPhotonsInPromptPeak;
    Int_t nBadTimeCorrelationIncomingPhotonWithChargedParticles;

    Int_t nAlgebraicalFailInCalcMomenta;

    Int_t IndexIncomingPhoton;

    TLorentzVector lvIncomingPhoton;
    TLorentzVector lvTarget;
    TLorentzVector lvRecoilProton;
    TLorentzVector lvPiMinus;

protected:
    virtual Bool_t  Start();
    virtual void    ProcessEvent();
    virtual void    ProcessScalerRead();
    virtual Bool_t  Write();
  
public:
    PiMinusProton();
    virtual ~PiMinusProton();
    virtual Bool_t  Init();

    Bool_t CheckInitialConditions();
    Bool_t CheckChargedCorrelation(Int_t NSigmaCoplanarity, Int_t NSigmaTime);
    Bool_t CheckTagger();
    Bool_t CalcMomenta();
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
