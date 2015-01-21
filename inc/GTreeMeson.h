#ifndef __GTreeMeson_h__
#define __GTreeMeson_h__


#include <TClonesArray.h>
#include <TLorentzVector.h>

#include "GTreeParticle.h"


#define MASS_PI0    134.9766
#define MASS_ETA    547.853
#define MASS_ETAP   957.78
#define MASS_PROTON 938.272046


using namespace std;

class  GTreeMeson   : public GTreeParticle
{
private:
    UChar_t             nSubParticles[GTreeParticle_MAX];
    UChar_t             nSubRootinos[GTreeParticle_MAX];
    UChar_t             nSubPhotons[GTreeParticle_MAX];
    UChar_t             nSubChargedPions[GTreeParticle_MAX];
    TClonesArray*       subRootinos;
    TClonesArray*       subPhotons;
    TClonesArray*       subChargedPions;

protected:
    virtual void    SetBranchAdresses();
    virtual void    SetBranches();

public:
    GTreeMeson(GTreeManager *Manager, const TString& _Name);
    virtual ~GTreeMeson();

            void            AddParticle(Int_t subParticle_index0, const TLorentzVector& subParticle0, const Int_t pdg0, Int_t subParticle_index1, const TLorentzVector& subParticle1, const Int_t pdg1);
            void            AddParticle(const Int_t _NSubRootinos, Int_t* subRootinos_index, TLorentzVector** subRootinos_list, const Int_t _NSubPhotons, Int_t* subPhotons_index, TLorentzVector** subPhotons_list, const Int_t _NSubChargedPions, Int_t* subChargedPions_index, TLorentzVector** subChargedPions_list);
    //        void            AddParticle(const TLorentzVector& subParticle0, const TLorentzVector& subParticle1, const Int_t pdg0, const Int_t pdg1);
    //        void            AddParticle(const Int_t _NSubPhotons, TLorentzVector** subPhotons_list, const Int_t _NSubChargedPions, TLorentzVector** subChargedPions_list);
    virtual void            Clear();
            UInt_t          GetNMesons()                            const	{return GetNParticles();}
            UInt_t          GetNSubParticles(const Int_t meson)     const	{return nSubParticles[meson];}
            UInt_t          GetNSubRootinos(const Int_t meson)      const	{return nSubRootinos[meson];}
            UInt_t          GetNSubPhotons(const Int_t meson)       const	{return nSubPhotons[meson];}
            UInt_t          GetNSubChargedPi(const Int_t meson)     const	{return nSubChargedPions[meson];}
            TLorentzVector& Meson(const Int_t meson)             {return Particle(meson);}
    const   TLorentzVector& Meson(const Int_t meson) const       {return Particle(meson);}
    virtual void            Print() const;
            TLorentzVector& SubRootinos(const Int_t meson, const Int_t subParticle)       {return *((TLorentzVector*)(((TClonesArray*)subRootinos->At(meson))->At(subParticle)));}
    const   TLorentzVector& SubRootinos(const Int_t meson, const Int_t subParticle) const {return *((TLorentzVector*)(((TClonesArray*)subRootinos->At(meson))->At(subParticle)));}
            TLorentzVector& SubPhotons(const Int_t meson, const Int_t subParticle)       {return *((TLorentzVector*)(((TClonesArray*)subPhotons->At(meson))->At(subParticle)));}
    const   TLorentzVector& SubPhotons(const Int_t meson, const Int_t subParticle) const {return *((TLorentzVector*)(((TClonesArray*)subPhotons->At(meson))->At(subParticle)));}
            TLorentzVector& SubChargedPions(const Int_t meson, const Int_t subParticle)       {return *((TLorentzVector*)(((TClonesArray*)subChargedPions->At(meson))->At(subParticle)));}
    const   TLorentzVector& SubChargedPions(const Int_t meson, const Int_t subParticle) const {return *((TLorentzVector*)(((TClonesArray*)subChargedPions->At(meson))->At(subParticle)));}
            TLorentzVector& SubParticles(const Int_t meson, const Int_t subParticle)       {if(subParticle<nSubRootinos[meson]) return SubRootinos(meson, subParticle); if(subParticle<(nSubPhotons[meson]+nSubRootinos[meson])) return SubPhotons(meson, subParticle); return SubChargedPions(meson, subParticle);}
    const   TLorentzVector& SubParticles(const Int_t meson, const Int_t subParticle) const {if(subParticle<nSubRootinos[meson]) return SubRootinos(meson, subParticle); if(subParticle<(nSubPhotons[meson]+nSubRootinos[meson])) return SubPhotons(meson, subParticle); return SubChargedPions(meson, subParticle);}
};



#endif
