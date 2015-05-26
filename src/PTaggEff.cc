#include "PTaggEff.h"

PTaggEff::PTaggEff()
{ 
    TaggerHits    = new TH1D("TaggerHits","TaggerHits",352,0,352);
    TaggerAccScal = new TH1D("TaggerAccScal","TaggerAccScal",352,0,352);
}

PTaggEff::~PTaggEff()
{
}

Bool_t	PTaggEff::Init()
{
    cout << "Initialising physics analysis..." << endl;
	cout << "--------------------------------------------------" << endl << endl;

	if(!InitBackgroundCuts()) return kFALSE;
	if(!InitTargetMass()) return kFALSE;
	if(!InitTaggerChannelCuts()) return kFALSE;
	if(!InitTaggerScalers()) return kFALSE;
	cout << "--------------------------------------------------" << endl;
	return kTRUE;
}

Bool_t	PTaggEff::Start()
{
    if(!IsAcquFile())
    {
        cout << "ERROR: Input File is not an Acqu file." << endl;
        return kFALSE;
    }
    SetAsGoATFile();

    TraverseValidEvents();

    return kTRUE;
}

void	PTaggEff::ProcessEvent()
{
    // Uncomment the following line to decode double hits in the tagger
    //GetTagger()->DecodeDoubles();

    for (Int_t i = 0; i < GetTagger()->GetNTagged(); i++)
    {
        if(RejectTagged(i)) continue;
        TaggerHits->Fill(GetTagger()->GetTaggedChannel(i));
    }
}

void	PTaggEff::ProcessScalerRead()
{
	// Fill Tagger Scalers
	FillScalers(GetTC_scaler_min(),GetTC_scaler_max(),TaggerAccScal);
}

Bool_t	PTaggEff::Write()
{
    // Write all GH1's and TObjects defined in this class
    return GTreeManager::Write();
}
