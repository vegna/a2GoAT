#include "PTaggEff.h"

PTaggEff::PTaggEff()
{ 
    TaggerAllHits = new TH1D("TaggerAllHits","Tagger - All Hits",352,0,352);
    TaggerSingles = new TH1D("TaggerSingles","Tagger - Single Hits",352,0,352);
    TaggerDoubles = new TH1D("TaggerDoubles","Tagger - Double Hits",352,0,352);
    TaggerAccScal = new TH1D("TaggerAccScal","Tagger - Accumulated Scalers",352,0,352);
    TaggEffAllHits = new TH1D("TaggEffAllHits","Tagging Efficiency - All Hits",352,0,352);
    TaggEffSingles = new TH1D("TaggEffSingles","Tagging Efficiency - Single Hits",352,0,352);
    TaggEffDoubles = new TH1D("TaggEffDoubles","Tagging Efficiency - Double Hits",352,0,352);
    LiveTimeScal  = new TH1D("LiveTimeScal","Live Time Scalers",2,0,2);
}

PTaggEff::~PTaggEff()
{
}

Bool_t	PTaggEff::Init()
{
    cout << "Initialising tagging efficiency analysis..." << endl;
	cout << "--------------------------------------------------" << endl << endl;

    if(!InitDecodeDoubles()) return kFALSE;
    if(!InitBackgroundCuts()) return kFALSE;
	if(!InitTaggerScalers()) return kFALSE;
    if(!InitLiveTimeScalers()) return kFALSE;
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

    GoosyScalers(TaggerAccScal);

    TaggEffAllHits->Sumw2();
    TaggEffAllHits->Divide(TaggerAllHits,TaggerAccScal);

    TaggEffSingles->Sumw2();
    TaggEffSingles->Divide(TaggerSingles,TaggerAccScal);

    TaggEffDoubles->Sumw2();
    TaggEffDoubles->Divide(TaggerDoubles,TaggerAccScal);

    LiveTimeScal->GetXaxis()->SetBinLabel(1,"Clock");
    LiveTimeScal->GetXaxis()->SetBinLabel(2,"Inhibited");

    return kTRUE;
}

void	PTaggEff::ProcessEvent()
{
    if(GetDecodeDoubles()) GetTagger()->DecodeDoubles();

    for (Int_t i = 0; i < GetTagger()->GetNTagged(); i++)
    {
        TaggerAllHits->Fill(GetTagger()->GetTaggedChannel(i));
        if(RejectTagged(i)) continue;
        TaggerSingles->Fill(GetTagger()->GetTaggedChannel(i));
        TaggerDoubles->Fill(GetTagger()->GetTaggedChannel(i));
    }
    for (Int_t i = 0; i < GetTagger()->GetNDouble(); i++)
    {
        TaggerDoubles->Fill(GetTagger()->GetDoubleRandom(i));
    }
}

void	PTaggEff::ProcessScalerRead()
{
	// Fill Tagger Scalers
	FillScalers(GetTC_scaler_min(),GetTC_scaler_max(),TaggerAccScal);
    // Fill Live Time Scalers
    FillScalers(GetLT_scaler_clock(),GetLT_scaler_inhib(),LiveTimeScal);
}

Bool_t	PTaggEff::Write()
{
    // Write all GH1's and TObjects defined in this class
    return GTreeManager::Write();
}
