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
    SetDirectory(0);
    accumulated.SetDirectory(0);
    accumulatedCorrected.SetDirectory(0);

    singleScalerReads.SetOwner();
    singleScalerReadsCorrected.SetOwner();
}

GHistScaCor::GHistScaCor(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Bool_t linkHistogram) :
    GHistLinked(name, title, nbinsx, xlow, xup, linkHistogram),
    accumulated(TString(name).Append("_Acc").Data(),
                TString(title).Append(" Accumulated"),
                nbinsx, xlow, xup),
    accumulatedCorrected(TString(name).Append("_AccCor").Data(),
                         TString(title).Append(" Accumulated and Corrected").Data(),
                         nbinsx, xlow, xup),
    singleScalerReads(128),
    singleScalerReadsCorrected(128),
    corrected(kFALSE)
{
    SetDirectory(0);
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
    TH1D::Add(h, c);
    accumulated.Add(&h->accumulated, c);
    accumulatedCorrected.Add(&h->accumulatedCorrected, c);
    for(int i=0; i<h->GetNScalerReadCorrections(); i++)
    {
        if(i>=GetNScalerReadCorrections())
            CreateSingleScalerRead();
        else
        {
            ((GHistLinked*)singleScalerReads.At(i))->Add((GHistLinked*)h->singleScalerReads.At(i), c);
            ((GHistLinked*)singleScalerReadsCorrected.At(i))->Add(((GHistLinked*)h->singleScalerReadsCorrected.At(i)), c);
        }
    }
    corrected = h->corrected;
}

void    GHistScaCor::CreateSingleScalerRead()
{
    TH1D*    uncor   = new TH1D(TString(GetName()).Append("_UnCor_ScaRead").Append(TString::Itoa(singleScalerReads.GetEntriesFast(), 10)),
                                TString(GetTitle()).Append(" Uncorrected Scaler Read ").Append(TString::Itoa(singleScalerReads.GetEntriesFast(), 10)),
                                GetNbinsX(),
                                GetXaxis()->GetXmin(),
                                GetXaxis()->GetXmax());
    uncor->SetDirectory(0);
    uncor->Sumw2();
    singleScalerReads.Add(uncor);

    TH1D*    cor     = new TH1D(TString(GetName()).Append("_ScaRead").Append(TString::Itoa(singleScalerReadsCorrected.GetEntriesFast(), 10)),
                                TString(GetTitle()).Append(" Scaler Read ").Append(TString::Itoa(singleScalerReadsCorrected.GetEntriesFast(), 10)),
                                GetNbinsX(),
                                GetXaxis()->GetXmin(),
                                GetXaxis()->GetXmax());
    cor->SetDirectory(0);
    cor->Sumw2();
    singleScalerReadsCorrected.Add(cor);
}

void    GHistScaCor::Reset(Option_t* option)
{
    accumulated.Reset(option);
    accumulatedCorrected.Reset(option);
    singleScalerReads.Clear();
    singleScalerReadsCorrected.Clear();
    TH1D::Reset(option);
    corrected   = kFALSE;
}

void	GHistScaCor::Scale(Double_t c1, Option_t* option)
{
    GHistLinked::Scale(c1, option);
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
    accumulated.Add(this);

    if(CreateHistogramsForSingleScalerReads)
        CreateSingleScalerRead();
    else
        Scale(CorrectionFactor);

    accumulatedCorrected.Add(this);
    TH1D::Reset();
    corrected   = kTRUE;
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

Int_t   GHistScaCor::Write(const char* name, Int_t option, Int_t bufsize)
{
    if(corrected==kFALSE)
    {
        return TH1D::Write(name, option, bufsize);
    }

    TString     nameBuffer;
    if(name)
        nameBuffer  = name;
    else
        nameBuffer  = GetName();
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
            nameBuffer  = GetName();
        nameBuffer.Append("_UnCor_ScalerRead");
        nameBuffer.Append(TString::Itoa(i, 10));
        ret += singleScalerReads.At(i)->Write(nameBuffer.Data(), option, bufsize);
        if(name)
            nameBuffer  = name;
        else
            nameBuffer  = GetName();
        nameBuffer.Append("_Cor_ScalerRead");
        nameBuffer.Append(TString::Itoa(i, 10));
        ret += singleScalerReadsCorrected.At(i)->Write(nameBuffer.Data(), option, bufsize);
    }

    parentDir->cd();
    if(name)
        nameBuffer  = name;
    else
        nameBuffer  = GetName();
    ret += accumulatedCorrected.Write(nameBuffer.Data(), option, bufsize);
    return ret;
}




