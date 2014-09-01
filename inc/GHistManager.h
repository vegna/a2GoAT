#ifndef __GHistManager_h__
#define __GHistManager_h__


#include <iostream>

#include <TH1.h>
#include <TObjArray.h>
#include <TDirectory.h>



class   GHistLinked;

class   GHistManager
{
private:
    TObjArray   histList;

    void        AddHistogramToList(GHistLinked* hist);
    virtual     TDirectory* GetOutputDirectory() = 0;
    void        RemoveHistogramFromList(GHistLinked* hist);

protected:

public:
    GHistManager();
    virtual ~GHistManager();

    void    ClearLinkedHistograms();
    void    WriteLinkedHistograms(TDirectory* dir);

    friend  class   GHistLinked;
};





class   GHistLinked : public TH1D
{
private:
    Bool_t  linked;

    void    Link();
    void    Unlink();

protected:

public:
    GHistLinked();
    GHistLinked(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Bool_t linkHistogram = kTRUE);
    virtual ~GHistLinked();

    virtual Int_t   Write(const char* name = 0, Int_t option = 0, Int_t bufsize = 0) = 0;
};


#endif
