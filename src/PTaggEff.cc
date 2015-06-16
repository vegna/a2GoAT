#include "PTaggEff.h"

PTaggEff::PTaggEff()
{ 
    TaggerAllHits = new TH1D("TaggerAllHits","Tagger - All Hits",352,0,352);
    TaggerSingles = new TH1D("TaggerSingles","Tagger - Single Hits",352,0,352);
    TaggerDoubles = new TH1D("TaggerDoubles","Tagger - Double Hits",352,0,352);
    TaggEffAllHits = new TH1D("TaggEffAllHits","Tagging Efficiency - All Hits",352,0,352);
    TaggEffSingles = new TH1D("TaggEffSingles","Tagging Efficiency - Single Hits",352,0,352);
    TaggEffDoubles = new TH1D("TaggEffDoubles","Tagging Efficiency - Double Hits",352,0,352);
}

PTaggEff::~PTaggEff()
{
}

Bool_t	PTaggEff::Init()
{
    cout << "Initialising tagging efficiency analysis..." << endl;
	cout << "--------------------------------------------------" << endl << endl;

    if(!InitBackgroundCuts()) return kFALSE;

    if(!PPhysics::Init()) return kFALSE;

    TaggerAccScal = GetScalerHist("TaggerAccScal");
    if(!TaggerAccScal)
    {
        cout << "No tagger scaler histogram available" << endl;
        return kFALSE;
    }

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
        if(RejectDouble(i)) continue;
        TaggerDoubles->Fill(GetTagger()->GetDoubleRandom(i));
    }
}

void	PTaggEff::ProcessScalerRead()
{
    PPhysics::ProcessScalerRead();
}

Bool_t	PTaggEff::Write()
{
    // Write all GH1's and TObjects defined in this class
    return GTreeManager::Write();
}
