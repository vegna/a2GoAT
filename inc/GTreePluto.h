#ifndef __GTreePluto_h__
#define __GTreePluto_h__


#include "GTree.h"

#include "TClonesArray.h"


class  GTreePluto : public GTree
{
private:
    TClonesArray*   PlutoMCTrue;
    Long64_t        plutoID;
    Long64_t        plutoRandomID;

   protected:
    virtual void    SetBranchAdresses();
    virtual void    SetBranches();

public:
    GTreePluto(GTreeManager *Manager);
    virtual ~GTreePluto();


    virtual void                Clear()                 { PlutoMCTrue->Clear(); plutoID=-1; plutoRandomID=1; }
    virtual TClonesArray* 		GetMCTrue()        		{ return PlutoMCTrue; }
    virtual Long64_t            GetPlutoID()            { return plutoID; }
    virtual Long64_t            GetPlutoRandomID()      { return plutoRandomID; }

};

#endif
