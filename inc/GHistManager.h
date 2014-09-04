#ifndef __GHistManager_h__
#define __GHistManager_h__


#include <iostream>

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





class   GHistLinked : public TObject
{
private:
    Bool_t  linked;

protected:
    virtual void    PrepareWriteList(TObjArray& arr) = 0;

public:
    GHistLinked(Bool_t linkHistogram = kTRUE);
    virtual ~GHistLinked();

    virtual Int_t	Fill(Double_t x) = 0;
            void    Link();
    virtual void    Reset(Option_t* option = "") = 0;
            void    Unlink();
    virtual Int_t   Write(const char* name = 0, Int_t option = 0, Int_t bufsize = 0) = 0;
};





#endif
