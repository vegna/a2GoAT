#ifndef __GTreePluto_h__
#define __GTreePluto_h__


#include "GTree.h"

#include "TClonesArray.h"


class  GTreePluto : public GTree
{
private:
    TClonesArray*   PlutoMCTrue;

   protected:
    virtual void    SetBranchAdresses();
    virtual void    SetBranches();

public:
    GTreePluto(GTreeManager *Manager);
    virtual ~GTreePluto();


    virtual void                Clear()                 { PlutoMCTrue->Clear(); }
    virtual TClonesArray* 		GetMCTrue()        		{ return PlutoMCTrue; }


};

#endif
