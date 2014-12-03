#ifndef __GParticleReconstruction_h__
#define __GParticleReconstruction_h__

#include <TCutG.h>


#include "GDataChecks.h"

#define	pdg_rootino 0

class	GParticleReconstruction : public GDataChecks
{
public:
    enum ReconType
    {
        Recon_None         = 0,
        Recon_dE_Proton    = 1,
        Recon_dE_Pion      = 2,
        Recon_dE_Electron  = 4,
        Recon_TOF          = 8,
        Recon_ClustSize    = 16,
        Recon_AllPhotons   = 32,
        Recon_AllProtons   = 64
    };

private:
	std::string config;

    ReconType   CB_type;
    ReconType   TAPS_type;

    char 		cutfilename[256];
    char 		cutname[256];

    TFile* 		CutFile;
    TCutG* 		Cut;
    TCutG* 		Cut_CB_proton;
    TCutG* 		Cut_CB_pion;
    TCutG*		Cut_CB_electron;
    TCutG* 		Cut_TAPS_proton;
    TCutG* 		Cut_TAPS_pion;
    TCutG*		Cut_TAPS_electron;

    TCutG* 		Cut_CB_TOF;
    TCutG* 		Cut_CB_ClustSize;
    TCutG* 		Cut_TAPS_TOF;
    TCutG* 		Cut_TAPS_ClustSize;

    Double_t	charged_theta_min;
    Double_t	charged_theta_max;

    Int_t* 		Identified;
    Int_t* 		Charge;
    Int_t* 		Hadron;

    Bool_t 		charge_ignore_PID;
    Bool_t 		charge_ignore_WC0;
    Bool_t 		charge_ignore_WC1;
    Bool_t 		charge_ignore_VETO;    

    Double_t    CBTimeCut[2];
    Double_t    TAPSTimeCut[2];

    Bool_t      DoScalerCorrection;
    Bool_t      DoTrigger;
    Double_t    E_Sum;
    Int_t       multiplicity;

    TCutG*	OpenCutFile(Char_t* filename, Char_t* cutname);
    Bool_t  Trigger();

protected:
            Bool_t  ProcessEventWithoutFilling();
    virtual void    ProcessEvent();
    virtual Bool_t  Start();

public:
    GParticleReconstruction();
    virtual ~GParticleReconstruction();

    Bool_t	Init();
    void    SetCBTimeCut(const Double_t min, const Double_t max)    {CBTimeCut[0]=min; CBTimeCut[1]=max;}
    void    SetTAPSTimeCut(const Double_t min, const Double_t max)  {TAPSTimeCut[0]=min; TAPSTimeCut[1]=max;}
    void    SetScalerCorrection(const Bool_t value)                 {DoScalerCorrection = value;}
    void    SetTrigger(const Double_t esum, const Int_t mult)       {DoTrigger = kTRUE; E_Sum = esum; multiplicity = mult;}
    void    SetThetaRangeChargedParticles(const Double_t min, const Double_t max)  {charged_theta_min = min; charged_theta_max = max;}
};

#endif
