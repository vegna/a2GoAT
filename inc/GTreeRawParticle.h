#ifndef __GTreeRawParticle_h__
#define __GTreeRawParticle_h__


#include <TLorentzVector.h>

#include "GTree.h"


#define GTreeRawParticle_MAX 256

class  GTreeRawParticle : public GTree
{
public:
    enum
    {
        APPARATUS_NONE  = 0,
        APPARATUS_CB    = 1,
        APPARATUS_TAPS  = 2
    };
private:
    Int_t		nParticles;
    Double_t	clusterEnergy[GTreeRawParticle_MAX];
    Double_t 	theta[GTreeRawParticle_MAX];
    Double_t 	phi[GTreeRawParticle_MAX];
    Double_t	time[GTreeRawParticle_MAX];
    UChar_t     clusterSize[GTreeRawParticle_MAX];
    Int_t       centralCrystal[GTreeRawParticle_MAX];
    Int_t       centralVeto[GTreeRawParticle_MAX];
    UChar_t 	apparatus[GTreeRawParticle_MAX];
    //Charged detector energies
    Double_t	vetoEnergy[GTreeRawParticle_MAX];
    Double_t	MWPC0Energy[GTreeRawParticle_MAX];
    Double_t	MWPC1Energy[GTreeRawParticle_MAX];

protected:
    virtual void    SetBranchAdresses();
    virtual void    SetBranches();

public:
    GTreeRawParticle(GTreeManager *Manager);
    virtual ~GTreeRawParticle();

    virtual void    Clear()     {nParticles = 0;}

    const	UChar_t*        GetApparatus()                      const	{return apparatus;}
            UChar_t         GetApparatus(const Int_t index)     const	{return apparatus[index];}
    const	UChar_t*        GetClusterSize()                      const	{return clusterSize;}
            UChar_t         GetClusterSize(const Int_t index)   const 	{return clusterSize[index];}
    const	Int_t*          GetCentralCrystal()                   const	{return centralCrystal;}
            Int_t           GetCentralCrystal(const Int_t index)  const {return centralCrystal[index];}
    const	Int_t*          GetCentralVeto()                      const	{return centralVeto;}
            Int_t           GetCentralVeto(const Int_t index)   const 	{return centralVeto[index];}
    const	Double_t*       GetVetoEnergy()                     const	{return vetoEnergy;}
            Double_t        GetVetoEnergy(const Int_t index)    const	{return vetoEnergy[index];}
    const	Double_t*       GetClusterEnergy()                  const	{return clusterEnergy;}
            Double_t        GetClusterEnergy(const Int_t index) const	{return clusterEnergy[index];}
    inline  Int_t           GetNCB()                            const;
            Int_t           GetNParticles()                     const	{return nParticles;}
    inline  Int_t           GetNTAPS()                          const;
    const	Double_t*       GetPhi()                            const	{return phi;}
            Double_t        GetPhi(const Int_t index)           const	{return phi[index];}
            Double_t        GetPhiRad(const Int_t index)        const	{return theta[index] * TMath::DegToRad();}
    const	Double_t*       GetTheta()                          const	{return theta;}
            Double_t        GetTheta(const Int_t index)         const	{return theta[index];}
            Double_t        GetThetaRad(const Int_t index)      const	{return theta[index] * TMath::DegToRad();}
    const	Double_t*       GetTime()                           const	{return time;}
            Double_t        GetTime(const Int_t index)          const	{return time[index];}
    inline  TLorentzVector	GetVector(const Int_t index)        const;
    inline  TLorentzVector	GetVector(const Int_t index, const Double_t mass)   const;
    const	Double_t*       GetMWPC0Energy()                          const	{return MWPC0Energy;}
            Double_t        GetMWPC0Energy(const Int_t index)         const	{return MWPC0Energy[index];}
    const	Double_t*       GetMWPC1Energy()                          const	{return MWPC1Energy;}
            Double_t        GetMWPC1Energy(const Int_t index)         const	{return MWPC1Energy[index];}
    virtual void            Print(const Bool_t All = kFALSE)    const;
};

TLorentzVector	GTreeRawParticle::GetVector(const Int_t index) const
{
    Double_t th = theta[index] * TMath::DegToRad();
    Double_t ph = phi[index]   * TMath::DegToRad();

    Double_t Px = clusterEnergy[index]* sin(th)*cos(ph);
    Double_t Py = clusterEnergy[index]* sin(th)*sin(ph);
    Double_t Pz = clusterEnergy[index]* cos(th);

    return TLorentzVector(Px, Py, Pz, clusterEnergy[index]);
}

TLorentzVector	GTreeRawParticle::GetVector(const Int_t index, const Double_t mass) const
{
    Double_t th = theta[index] * TMath::DegToRad();
    Double_t ph = phi[index]   * TMath::DegToRad();

    Double_t E 	= clusterEnergy[index] + mass;
    Double_t P 	= TMath::Sqrt(E*E - mass*mass);
    Double_t Px = P* sin(th)*cos(ph);
    Double_t Py = P* sin(th)*sin(ph);
    Double_t Pz = P* cos(th);

    return TLorentzVector(Px, Py, Pz, E);
}

Int_t		GTreeRawParticle::GetNCB()	const
{
    Int_t NCB = 0;
    for(Int_t i = 0; i < nParticles; i++)
    {
        if (apparatus[i] == APPARATUS_CB) NCB++;
    }
    return NCB;
}
Int_t		GTreeRawParticle::GetNTAPS()	const
{
    Int_t NTAPS = 0;
    for(Int_t i = 0; i < nParticles; i++)
    {
        if (apparatus[i] == APPARATUS_TAPS) NTAPS++;
    }
    return NTAPS;
}
#endif
