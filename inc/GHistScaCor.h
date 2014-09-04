#ifndef __GHistScaCor_h__
#define __GHistScaCor_h__


#include <TROOT.h>
#include <TH1.h>
#include <TObjArray.h>

#include "GHistManager.h"





class   GHistScaCor : public GHistLinked
{
private:
    TH1D        buffer;
    TH1D        accumulated;
    TH1D        accumulatedCorrected;
    TObjArray   singleScalerReads;
    TObjArray   singleScalerReadsCorrected;
    Bool_t      corrected;

    void    CreateSingleScalerRead();

protected:
    static  TDirectory* GetCreateDirectory(const char* name);
    virtual Int_t   PrepareWriteList();

public:
    GHistScaCor();
    GHistScaCor(const char* name, const char* title, const Int_t nbinsx, const Double_t xlow, const Double_t xup, const Bool_t linkHistogram = kTRUE);
    virtual ~GHistScaCor();

    virtual Bool_t	Add(const GHistScaCor* h, Double_t c = 1);
    virtual Int_t	Fill(Double_t x)    {return buffer.Fill(x);}
    const   TH1D&   GetAccumulated()            const   {return accumulated;}
    const   TH1D&   GetAccumulatedCorrected()   const   {return accumulatedCorrected;}
            Int_t   GetNScalerReadCorrections() const   {return singleScalerReads.GetEntriesFast();}
    virtual void    Reset(Option_t* option = "");
    virtual void	Scale(Double_t c1 = 1, Option_t* option = "");
    virtual void    ScalerReadCorrection(const Double_t CorrectionFactor, const Bool_t CreateHistogramsForSingleScalerReads = kFALSE);
    virtual void	SetBins(Int_t nx, Double_t xmin, Double_t xmax);
    virtual Int_t   Write(const char* name = 0, Int_t option = 0, Int_t bufsize = 0);
};


#endif
