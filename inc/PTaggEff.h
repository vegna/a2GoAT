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
    TH1*	TaggerHits;
    TH1*	TaggerAccScal;

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
