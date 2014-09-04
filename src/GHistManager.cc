#include "GHistManager.h"



GHistManager*   gGHistManager = 0;


GHistManager::GHistManager()    :
    histList()
{
    gGHistManager   = this;
    histList.SetOwner(kFALSE);
}

GHistManager::~GHistManager()
{
    gGHistManager   = 0;
}

void    GHistManager::AddHistogramToList(GHistLinked* hist)
{
    histList.AddAtFree(hist);
}

void    GHistManager::RemoveHistogramFromList(GHistLinked* hist)
{
    histList.Remove(hist);
}

void GHistManager::ClearLinkedHistograms()
{
    TIter   iter(&histList);
    GHistLinked*    hist;
    while(hist=(GHistLinked*)iter.Next())
        hist->Reset();
}

void GHistManager::WriteLinkedHistograms(TDirectory* dir)
{
    std::cout << "Prepare Write." << std::endl;
    {
        TIter   iter(&histList);
        GHistLinked*    hist;
        while(hist=(GHistLinked*)iter.Next())
            hist->PrepareWrite();
    }

    std::cout << "Write." << std::endl;
    {
        TIter   iter(&histList);
        GHistLinked*    hist;
        while(hist=(GHistLinked*)iter.Next())
            hist->Write(0, TObject::kWriteDelete);
    }
}





GHistLinked::GHistLinked(Bool_t linkHistogram) :
    TObject(),
    linked(linkHistogram)
{
    if(linked == kTRUE)
        Link();
}

GHistLinked::~GHistLinked()
{
    Unlink();
}

void    GHistLinked::Link()
{
    if(linked)
        Unlink();
    if(gGHistManager)
    {
        gGHistManager->AddHistogramToList(this);
        linked = kTRUE;
    }
}

void    GHistLinked::Unlink()
{
    linked = kFALSE;
    if(gGHistManager)
        gGHistManager->RemoveHistogramFromList(this);
}
