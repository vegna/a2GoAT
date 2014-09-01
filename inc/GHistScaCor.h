#ifndef __GHistScaCor_h__
#define __GHistScaCor_h__


#include <TROOT.h>
#include <TObjArray.h>

#include "GHistManager.h"





class   GHistScaCor : public GHistLinked
{
private:
    TH1D        accumulated;
    TH1D        accumulatedCorrected;
    TObjArray   singleScalerReads;
    TObjArray   singleScalerReadsCorrected;
    Bool_t      corrected;

    void    CreateSingleScalerRead();

protected:
    static  TDirectory* GetCreateDirectory(const char* name);

public:
    GHistScaCor();
    GHistScaCor(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Bool_t linkHistogram = kTRUE);
    virtual ~GHistScaCor();

    virtual Bool_t	Add(const GHistScaCor* h, Double_t c = 1);
    virtual void    Reset(Option_t* option = "");
            Int_t   GetNScalerReadCorrections() const   {return singleScalerReads.GetEntriesFast();}
    virtual void    ScalerReadCorrection(const Double_t CorrectionFactor, const Bool_t CreateHistogramsForSingleScalerReads = kFALSE);
    virtual Int_t   Write(const char* name = 0, Int_t option = 0, Int_t bufsize = 0);
};


#endif
