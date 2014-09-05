#include "GHistScaCor.h"

#include <iostream>


GHistScaCor::GHistScaCor() :
    GHistLinked(),
    accumulated(),
    accumulatedCorrected(),
    singleScalerReads(),
    singleScalerReadsCorrected(),
    corrected(kFALSE)
{
    buffer.SetDirectory(0);
    accumulated.SetDirectory(0);
    accumulatedCorrected.SetDirectory(0);

    singleScalerReads.SetOwner();
    singleScalerReadsCorrected.SetOwner();
}

GHistScaCor::GHistScaCor(const char* name, const char* title, const Int_t nbinsx, const Double_t xlow, const Double_t xup, const Bool_t linkHistogram) :
    GHistLinked(linkHistogram),
    buffer(TString(name).Append("_Buffer").Data(),
           TString(title).Append(" Buffer"),
           nbinsx, xlow, xup),
    accumulated(TString(name).Append("_NoScaCor").Data(),
                TString(title).Append(" NoScaCor"),
                nbinsx, xlow, xup),
    accumulatedCorrected(name, title, nbinsx, xlow, xup),
    singleScalerReads(128),
    singleScalerReadsCorrected(128),
    corrected(kFALSE)
{
    buffer.SetDirectory(0);
    accumulated.SetDirectory(0);
    accumulatedCorrected.SetDirectory(0);

    singleScalerReads.SetOwner();
    singleScalerReadsCorrected.SetOwner();
}

GHistScaCor::~GHistScaCor()
{
}

Bool_t	GHistScaCor::Add(const GHistScaCor *h, Double_t c)
{
    if(corrected!=h->corrected)
    {
        std::cout << "ERROR: GHistScaCor::Add. Tried to add a corrected and an uncorrected GHistScaCor" << std::endl;
        return kFALSE;
    }

    if(corrected==kFALSE)
    {
        buffer.Add(&h->buffer, c);
        return kTRUE;
    }

    buffer.Add(&h->buffer, c);
    accumulated.Add(&h->accumulated, c);
    accumulatedCorrected.Add(&h->accumulatedCorrected, c);
    for(int i=0; i<h->GetNScalerReadCorrections(); i++)
    {
        if(i>=GetNScalerReadCorrections())
            CreateSingleScalerRead();
        else
        {
            ((TH1D*)singleScalerReads.At(i))->Add((TH1D*)h->singleScalerReads.At(i), c);
            ((TH1D*)singleScalerReadsCorrected.At(i))->Add(((TH1D*)h->singleScalerReadsCorrected.At(i)), c);
        }
    }
    return kTRUE;
}

void    GHistScaCor::CreateSingleScalerRead()
{
    TH1D*    uncor   = new TH1D(TString(accumulatedCorrected.GetName()).Append("_NoScaCor_ScaRead").Append(TString::Itoa(singleScalerReads.GetEntriesFast(), 10)),
                                TString(accumulatedCorrected.GetTitle()).Append(" Uncorrected Scaler Read ").Append(TString::Itoa(singleScalerReads.GetEntriesFast(), 10)),
                                accumulatedCorrected.GetNbinsX(),
                                accumulatedCorrected.GetXaxis()->GetXmin(),
                                accumulatedCorrected.GetXaxis()->GetXmax());
    uncor->SetDirectory(0);
    singleScalerReads.Add(uncor);

    TH1D*    cor     = new TH1D(TString(accumulatedCorrected.GetName()).Append("_ScaRead").Append(TString::Itoa(singleScalerReadsCorrected.GetEntriesFast(), 10)),
                                TString(accumulatedCorrected.GetTitle()).Append(" Scaler Read ").Append(TString::Itoa(singleScalerReadsCorrected.GetEntriesFast(), 10)),
                                accumulatedCorrected.GetNbinsX(),
                                accumulatedCorrected.GetXaxis()->GetXmin(),
                                accumulatedCorrected.GetXaxis()->GetXmax());
    cor->SetDirectory(0);
    singleScalerReadsCorrected.Add(cor);
}

void    GHistScaCor::Reset(Option_t* option)
{
    buffer.Reset(option);
    accumulated.Reset(option);
    accumulatedCorrected.Reset(option);
    singleScalerReads.Clear();
    singleScalerReadsCorrected.Clear();
    corrected   = kFALSE;
}

void	GHistScaCor::Scale(Double_t c1, Option_t* option)
{
    buffer.Scale(c1, option);
    accumulated.Scale(c1, option);
    accumulatedCorrected.Scale(c1, option);
    for(int i=0; i<singleScalerReads.GetEntriesFast(); i++)
    {
        ((TH1D*)singleScalerReads.At(i))->Scale(c1, option);
        ((TH1D*)singleScalerReadsCorrected.At(i))->Scale(c1, option);
    }
}

void    GHistScaCor::ScalerReadCorrection(const Double_t CorrectionFactor, const Bool_t CreateHistogramsForSingleScalerReads)
{
    accumulated.Add(&buffer);

    if(CreateHistogramsForSingleScalerReads)
        CreateSingleScalerRead();
    else
        buffer.Scale(CorrectionFactor);

    accumulatedCorrected.Add(&buffer);
    buffer.Reset();
    corrected   = kTRUE;
}

void	GHistScaCor::SetBins(Int_t nx, Double_t xmin, Double_t xmax)
{
    buffer.SetBins(nx, xmin, xmax);
    accumulated.SetBins(nx, xmin, xmax);
    accumulatedCorrected.SetBins(nx, xmin, xmax);
    for(int i=0; i<singleScalerReads.GetEntriesFast(); i++)
    {
        ((TH1D*)singleScalerReads.At(i))->SetBins(nx, xmin, xmax);
        ((TH1D*)singleScalerReadsCorrected.At(i))->SetBins(nx, xmin, xmax);
    }
}

TDirectory* GHistScaCor::GetCreateDirectory(const char* name)
{
    TDirectory* ret = gDirectory->GetDirectory(name);
    if(!ret)
    {
        ret = gDirectory->mkdir(name);
        if(!ret)
            ret = gDirectory;
    }
    return ret;
}

void    GHistScaCor::PrepareWrite()
{
    if(corrected==kFALSE)
        return;

    TDirectory* parentDir   = gDirectory;
    TDirectory* dir         = GetCreateDirectory("ScalerCorrection");

    for(int i=0; i<singleScalerReads.GetEntriesFast(); i++)
    {
        dir->cd();
        GetCreateDirectory(TString("SingleScalerRead").Append(TString::Itoa(i, 10)).Data())->cd();
    }

    parentDir->cd();
}

Int_t   GHistScaCor::Write(const char* name, Int_t option, Int_t bufsize)
{
    if(corrected==kFALSE)
    {
        return buffer.Write(name, option, bufsize);
    }

    TString     nameBuffer;
    if(name)
        nameBuffer  = name;
    else
        nameBuffer  = accumulatedCorrected.GetName();
    nameBuffer.Append("_UnCor");

    TDirectory* parentDir   = gDirectory;
    TDirectory* dir         = GetCreateDirectory("ScalerCorrection");
    dir->cd();

    Int_t   ret = accumulated.Write(nameBuffer.Data(), option, bufsize);

    for(int i=0; i<singleScalerReads.GetEntriesFast(); i++)
    {
        dir->cd();
        GetCreateDirectory(TString("SingleScalerRead").Append(TString::Itoa(i, 10)).Data())->cd();
        if(name)
            nameBuffer  = name;
        else
            nameBuffer  = accumulatedCorrected.GetName();
        nameBuffer.Append("_UnCor_ScalerRead");
        nameBuffer.Append(TString::Itoa(i, 10));
        ret += singleScalerReads.At(i)->Write(nameBuffer.Data(), option, bufsize);
        if(name)
            nameBuffer  = name;
        else
            nameBuffer  = accumulatedCorrected.GetName();
        nameBuffer.Append("_Cor_ScalerRead");
        nameBuffer.Append(TString::Itoa(i, 10));
        ret += singleScalerReadsCorrected.At(i)->Write(nameBuffer.Data(), option, bufsize);
    }

    parentDir->cd();
    if(name)
        nameBuffer  = name;
    else
        nameBuffer  = accumulatedCorrected.GetName();
    ret += accumulatedCorrected.Write(nameBuffer.Data(), option, bufsize);
    return ret;
}




