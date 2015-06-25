#include "PTaggEff.h"

PTaggEff::PTaggEff()
{ 
    TaggerAllHits = new GH1("TaggerAllHits","Tagger - All Hits",352,0,352);
    TaggerSingles = new GH1("TaggerSingles","Tagger - Single Hits",352,0,352);
    TaggerDoubles = new GH1("TaggerDoubles","Tagger - Double Hits",352,0,352);
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

    GoosyTagger(TaggerAccScal);

    return kTRUE;
}

void	PTaggEff::ProcessEvent()
{
    if(GetDecodeDoubles()) GetTagger()->DecodeDoubles();

    for (Int_t i = 0; i < GetTagger()->GetNTagged(); i++)
    {
        TaggerAllHits->Fill(GetTagger()->GetTaggedChannel(i),GetTagger()->GetTaggedTime(i));
        if(RejectTagged(i)) continue;
        TaggerSingles->Fill(GetTagger()->GetTaggedChannel(i),GetTagger()->GetTaggedTime(i));
        TaggerDoubles->Fill(GetTagger()->GetTaggedChannel(i),GetTagger()->GetTaggedTime(i));
    }
    for (Int_t i = 0; i < GetTagger()->GetNDouble(); i++)
    {
        if(RejectDouble(i)) continue;
        TaggerDoubles->Fill(GetTagger()->GetDoubleRandom(i),GetTagger()->GetDoubleTime(i));
    }
}

void	PTaggEff::ProcessScalerRead()
{
    PPhysics::ProcessScalerRead();
}

Bool_t	PTaggEff::Write()
{
    TH1D *TempScal = (TH1D*)TaggerAccScal->Clone("TempScal");

    // Write all GH1's and TObjects defined in this class
    if(!(GTreeManager::Write())) return false;

    TH1D *TempAllHits = (TH1D*)TaggerAllHits->GetSum()->GetResult()->GetBuffer()->Clone("TempAllHits");
    TH1D *TempSingles = (TH1D*)TaggerSingles->GetSum()->GetResult()->GetBuffer()->Clone("TempSingles");
    TH1D *TempDoubles = (TH1D*)TaggerDoubles->GetSum()->GetResult()->GetBuffer()->Clone("TempDoubles");

    TH1D *TaggEffAllHits = new TH1D("TaggEffAllHits","Tagging Efficiency - All Hits",352,0,352);
    TH1D *TaggEffSingles = new TH1D("TaggEffSingles","Tagging Efficiency - Single Hits",352,0,352);
    TH1D *TaggEffDoubles = new TH1D("TaggEffDoubles","Tagging Efficiency - Double Hits",352,0,352);

    TaggEffAllHits->Sumw2();
    TaggEffAllHits->Divide(TempAllHits,TempScal);

    TaggEffSingles->Sumw2();
    TaggEffSingles->Divide(TempSingles,TempScal);

    TaggEffDoubles->Sumw2();
    TaggEffDoubles->Divide(TempDoubles,TempScal);

    TaggEffAllHits->Write();
    TaggEffSingles->Write();
    TaggEffDoubles->Write();

    delete TempScal;

    delete TempAllHits;
    delete TempSingles;
    delete TempDoubles;

    delete TaggEffAllHits;
    delete TaggEffSingles;
    delete TaggEffDoubles;

    return true;
}
