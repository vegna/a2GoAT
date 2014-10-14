#ifndef __GTreeLinPol_h__
#define __GTreeLinPol_h__


#include <TLorentzVector.h>

#include "GTree.h"


#define GTreeLinPol_MAX 4096

class  GTreeLinPol : public GTree
{
private:
    Int_t	plane;
    Double_t	edge;
    Double_t	edgeSetting;    
    Double_t	polTable[352];
    Double_t	enhTable[352];

protected:
    virtual void    SetBranchAdresses();
    virtual void    SetBranches();

public:
    GTreeLinPol(GTreeManager *Manager);
    virtual ~GTreeLinPol();

    virtual void        Clear()     {}
            Int_t 	GetPolPlane() 	const	{return plane;}
            Double_t 	GetEdge() 	const	{return edge;}
            Double_t 	GetEdgeSetting()const	{return edgeSetting;}	    
     const  Double_t*	GetPolTable() 	const	{return polTable;}
     const  Double_t	GetPolDegree(Int_t channel) const	{return polTable[channel];}
     const  Double_t*	GetEnhTable() 	const	{return enhTable;}
     const  Double_t	GetEnhTable(Int_t channel) const	{return enhTable[channel];}

};


#endif
