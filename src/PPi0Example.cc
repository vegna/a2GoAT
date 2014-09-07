#include "PPi0Example.h"

PPi0Example::PPi0Example()
{ 
    //GHistBGSub::InitCuts(-20, 15, -100, -40);
    //GHistBGSub::AddRandCut(35, 95);
        
    time 	= new GH1("time", 	"time", 	1400, -700,	700);

    IM 		= new GH1("IM", 	"IM", 		400,   0,	400);
  
    MM		= new GH1("MM", 	"MM", 	 	400,   800, 1200);
}

PPi0Example::~PPi0Example()
{
}

Bool_t	PPi0Example::Start()
{
    if(!IsGoATFile())
    {
        cout << "ERROR: Input File is not a GoAT file." << endl;
        return kFALSE;
    }
    SetAsPhysicsFile();

    TraverseValidEvents();

	return kTRUE;
}

void	PPi0Example::ProcessEvent()
{
    for (Int_t i = 0; i < eta->GetNParticles(); i++)
    {
        for(int t=0; t<tagger->GetNTagged(); t++)
        {
            time->Fill(tagger->GetTagged_t(t));
            MM->Fill((tagger->GetVectorProtonTarget(t)-eta->Particle(i)).M(), tagger->GetTagged_ch(t));
        }
        IM->Fill(eta->Particle(i).M(), *tagger);
	}
	
}

void	PPi0Example::ProcessScalerRead()
{
    time->ScalerReadCorrection(5);

    IM->ScalerReadCorrection(5);

    MM->ScalerReadCorrection(5);
}
