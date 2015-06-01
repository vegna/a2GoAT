#ifndef __PTaggEff_h__
#define __PTaggEff_h__

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>

#include "GTreeManager.h"
#include "PPhysics.h"

class	PTaggEff  : public PPhysics
{
private:
    TH1*	TaggerAllHits;
    TH1*	TaggerSingles;
    TH1*	TaggerDoubles;
    TH1*	TaggerAccScal;
    TH1*	TaggEffAllHits;
    TH1*	TaggEffSingles;
    TH1*	TaggEffDoubles;

protected:
    virtual Bool_t  Start();
    virtual void    ProcessEvent();
    virtual void	ProcessScalerRead();
    virtual Bool_t    Write();
			
public:
    PTaggEff();
    virtual ~PTaggEff();
    virtual Bool_t  Init();

};
#endif
