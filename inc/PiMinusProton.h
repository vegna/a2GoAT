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

    TH1* tracks;
    TH1* particles;
    TH2* coplanarity;
    TH2* coplanarity_tagliato;
    TH1* timediff;
    TH1* timediff_tagliato;

    Int_t evtNum;
    Int_t nIncompatibleWithGoat;
    Int_t nBadCoplanarity;
    Int_t nBadTimeCorrelationBetweenChargedParticles;

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
