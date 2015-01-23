#ifndef __GTreeParameters_h__
#define __GTreeParameters_h__


#include "GTree.h"


class  GTreeParameters : public GTree
{
private:
    Int_t		nNaI;
    Int_t		NaIA0[720];
    Int_t		NaIA1[720];
    Int_t		NaIA2[720];
    Int_t		NaIT0[720];
    Int_t		NaIT1[720];
    Int_t		NaIT2[720];
    Int_t		nPID;
    Int_t		PIDA0[24];
    Int_t		PIDA1[24];
    Int_t		PIDA2[24];
    Int_t		PIDT0[24];
    Int_t		PIDT1[24];
    Int_t		PIDT2[24];
    Int_t		nMWPC;
    Int_t		MWPC[860];
    Int_t		nBaF2PbWO4;
    Int_t		BaF2PbWO4A0[438];
    Int_t		BaF2PbWO4A1[438];
    Int_t		BaF2PbWO4A2[438];
    Int_t		BaF2PbWO4T0[438];
    Int_t		BaF2PbWO4T1[438];
    Int_t		BaF2PbWO4T2[438];
    Int_t		nVeto;
    Int_t		VetoA0[438];
    Int_t		VetoA1[438];
    Int_t		VetoA2[438];
    Int_t		VetoT0[438];
    Int_t		VetoT1[438];
    Int_t		VetoT2[438];
    Int_t		nTagger;
    Double_t	TaggerElectronEnergy[352];
    Double_t	TaggerPhotonEnergy[352];
    Double_t    TaggerEnergyWidth[352];
    Int_t		TaggerT0[352];
    Int_t		TaggerT1[352];
    Int_t		TaggerT2[352];

protected:
    virtual void    SetBranchAdresses();
    virtual void    SetBranches();

public:
    GTreeParameters(GTreeManager *Manager);
    virtual ~GTreeParameters();

    virtual void    Clear()             {}

            Int_t           GetNTagger()                               const	{return nTagger;}
    const	Double_t*       GetTaggerElectronEnergy()                  const	{return TaggerPhotonEnergy;}
            Double_t        GetTaggerElectronEnergy(const Int_t index) const	{return TaggerPhotonEnergy[index];}
    const	Double_t*       GetTaggerPhotonEnergy()                    const	{return TaggerPhotonEnergy;}
            Double_t        GetTaggerPhotonEnergy(const Int_t index)   const	{return TaggerPhotonEnergy[index];}
    const	Double_t*       GetTaggerEnergyWidth()                     const	{return TaggerEnergyWidth;}
            Double_t        GetTaggerEnergyWidth(const Int_t index)    const	{return TaggerEnergyWidth[index];}
};

#endif
