#ifndef __PPi0Example_h__
#define __PPi0Example_h__

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string> 

#include "GTreeManager.h"
#include "GH1.h"

class	PPi0Example : public GTreeManager
{
private:
    GH1*	time;
    GH1*	time_2g;   
     
    GH1*	IM;
    GH1*	IM_2g;
    
    GH1*	MM;
    GH1*	MM_2g; 
    
protected:
    virtual Bool_t  Start();

    virtual void    ProcessEvent();
    virtual void	ProcessScalerRead();
			
public:
    PPi0Example();
    virtual ~PPi0Example();

    //virtual Bool_t	Init(const char* configfile);

};
#endif
