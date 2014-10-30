#include "GHistScaCor.h"

#include <iostream>


#define GHSC_folderName                  "ScalerCorrection"
#define GHSC_singleScalerReadFolderName  "SingleScalerRead_"
#define GHSC_bufferNameSuffix            "_Buffer"
#define GHSC_bufferTitleSuffix           ""
#define GHSC_accumulatedNameSuffix       "_NoScaCor"
#define GHSC_accumulatedTitleSuffix      " NoScaCor"
#define GHSC_singleScalerReadNameSuffix              "_NoScaCor_ScaRead"
#define GHSC_singleScalerReadTitleSuffix             " NoScaCor ScaRead "
#define GHSC_singleScalerReadCorrectedNameSuffix     "_ScaRead"
#define GHSC_singleScalerReadCorrectedTitleSuffix    " ScaRead "



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
    buffer(TString(name).Append(GHSC_bufferNameSuffix).Data(),
           TString(title).Append(GHSC_bufferTitleSuffix).Data(),
           nbinsx, xlow, xup),
    accumulated(TString(name).Append(GHSC_accumulatedNameSuffix).Data(),
                TString(title).Append(GHSC_accumulatedTitleSuffix).Data(),
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
        if(buffer.GetEntries()>0)
        {
            std::cout << "ERROR: GHistScaCor::Add. Tried to add a corrected and an uncorrected GHistScaCor" << std::endl;
            return kFALSE;
        }
        corrected   = h->corrected;
    }

    if(h->corrected==kFALSE)
    {
        buffer.Add(&h->buffer, c);
        return kTRUE;
    }

    buffer.Add(&h->buffer, c);
    accumulated.Add(&h->accumulated, c);
    accumulatedCorrected.Add(&h->accumulatedCorrected, c);
    buffer.SetDirectory(0);
    accumulated.SetDirectory(0);
    accumulatedCorrected.SetDirectory(0);
    for(int i=0; i<h->GetNScalerReadCorrections(); i++)
    {
        if(i>=GetNScalerReadCorrections())
            CreateSingleScalerRead();
        else
        {
            ((TH1D*)singleScalerReads.At(i))->Add((TH1D*)h->singleScalerReads.At(i), c);
            ((TH1D*)singleScalerReadsCorrected.At(i))->Add(((TH1D*)h->singleScalerReadsCorrected.At(i)), c);
            ((TH1D*)singleScalerReads.At(i))->SetDirectory(0);
            ((TH1D*)singleScalerReadsCorrected.At(i))->SetDirectory(0);
        }
    }
    return kTRUE;
}

void    GHistScaCor::CreateSingleScalerRead()
{
    TH1D*    uncor   = new TH1D(TString(accumulatedCorrected.GetName()).Append(GHSC_singleScalerReadNameSuffix).Append(TString::Itoa(singleScalerReads.GetEntriesFast(), 10)),
                                TString(accumulatedCorrected.GetTitle()).Append(GHSC_singleScalerReadTitleSuffix).Append(TString::Itoa(singleScalerReads.GetEntriesFast(), 10)),
                                accumulatedCorrected.GetNbinsX(),
                                accumulatedCorrected.GetXaxis()->GetXmin(),
                                accumulatedCorrected.GetXaxis()->GetXmax());
    uncor->SetDirectory(0);
    singleScalerReads.Add(uncor);

    TH1D*    cor     = new TH1D(TString(accumulatedCorrected.GetName()).Append(GHSC_singleScalerReadCorrectedNameSuffix).Append(TString::Itoa(singleScalerReadsCorrected.GetEntriesFast(), 10)),
                                TString(accumulatedCorrected.GetTitle()).Append(GHSC_singleScalerReadCorrectedTitleSuffix).Append(TString::Itoa(singleScalerReadsCorrected.GetEntriesFast(), 10)),
                                accumulatedCorrected.GetNbinsX(),
                                accumulatedCorrected.GetXaxis()->GetXmin(),
                                accumulatedCorrected.GetXaxis()->GetXmax());
    cor->SetDirectory(0);
    singleScalerReadsCorrected.Add(cor);
}

void    GHistScaCor::Reset(Option_t* option)
{
    buffer.SetDirectory(0);
    accumulated.SetDirectory(0);
    accumulatedCorrected.SetDirectory(0);

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
    {
        CreateSingleScalerRead();
        ((TH1D*)singleScalerReads.Last())->Add(&buffer);
        buffer.Scale(CorrectionFactor);
        ((TH1D*)singleScalerReadsCorrected.Last())->Add(&buffer);
    }
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

void    GHistScaCor::PrepareWriteList(GHistWriteList* arr, const char *name)
{
    if(!arr)
        return;

    TString     nameBuffer;
    if(name)
    {
        if(corrected==kFALSE)
            return  arr->AddHistogram(&buffer, name);
        arr->AddHistogram(&accumulatedCorrected, name);
    }
    else
    {
        if(corrected==kFALSE)
            return  arr->AddHistogram(&buffer, accumulatedCorrected.GetName());
        arr->AddHistogram(&accumulatedCorrected, accumulatedCorrected.GetName());
    }

    GHistWriteList* ScalerCorrection    = arr->GetDirectory(TString(GHSC_folderName));
    if(name)
    {
        nameBuffer  = name;
        nameBuffer.Append(GHSC_accumulatedNameSuffix);
        ScalerCorrection->AddHistogram(&accumulated, nameBuffer);
    }
    else
        ScalerCorrection->AddHistogram(&accumulated, accumulated.GetName());

    for(int i=0; i<singleScalerReads.GetEntriesFast(); i++)
    {
        GHistWriteList* SingleScalerRead    = ScalerCorrection->GetDirectory(TString(GHSC_singleScalerReadFolderName).Append(TString::Itoa(i, 10)));
        if(name)
        {
            nameBuffer  = name;
            nameBuffer.Append(GHSC_singleScalerReadNameSuffix).Append(TString::Itoa(i, 10)),
            SingleScalerRead->AddHistogram((TH1D*)singleScalerReads.At(i), nameBuffer);
        }
        else
            SingleScalerRead->AddHistogram((TH1D*)singleScalerReads.At(i), ((TH1D*)singleScalerReads.At(i))->GetName());
        if(name)
        {
            nameBuffer  = name;
            nameBuffer.Append(GHSC_singleScalerReadCorrectedNameSuffix).Append(TString::Itoa(i, 10)),
            SingleScalerRead->AddHistogram((TH1D*)singleScalerReadsCorrected.At(i), nameBuffer);
        }
        else
            SingleScalerRead->AddHistogram((TH1D*)singleScalerReadsCorrected.At(i), ((TH1D*)singleScalerReadsCorrected.At(i))->GetName());
    }
}

Int_t   GHistScaCor::WriteWithoutCalcResult(const char* name, Int_t option, Int_t bufsize)
{
    if(corrected==kFALSE)
    {
        if(name)
            return buffer.Write(name, option, bufsize);
        else
            return buffer.Write(accumulatedCorrected.GetName(), option, bufsize);
    }

    Int_t   ret = 0;
    if(name)
        ret += accumulatedCorrected.Write(name, option, bufsize);
    else
        ret += accumulatedCorrected.Write(0, option, bufsize);

    TDirectory* parentDir   = gDirectory;
    TDirectory* dir         = GetCreateDirectory(GHSC_folderName);
    dir->cd();

    TString     nameBuffer;
    if(name)
    {
        nameBuffer  = name;
        nameBuffer.Append(GHSC_accumulatedNameSuffix);
        ret += accumulated.Write(nameBuffer.Data(), option, bufsize);
    }
    else
        ret += accumulated.Write(0, option, bufsize);

    for(int i=0; i<singleScalerReads.GetEntriesFast(); i++)
    {
        dir->cd();
        GetCreateDirectory(TString(GHSC_singleScalerReadFolderName).Append(TString::Itoa(i, 10)).Data())->cd();
        if(name)
        {
            nameBuffer  = name;
            nameBuffer.Append(GHSC_singleScalerReadNameSuffix);
            nameBuffer.Append(TString::Itoa(i, 10));
            ret += singleScalerReads.At(i)->Write(nameBuffer.Data(), option, bufsize);
        }
        else
            ret += singleScalerReads.At(i)->Write(0, option, bufsize);
        ((TH1D*)singleScalerReads.At(i))->SetDirectory(0);

        if(name)
        {
            nameBuffer  = name;
            nameBuffer.Append(GHSC_singleScalerReadCorrectedNameSuffix);
            nameBuffer.Append(TString::Itoa(i, 10));
            ret += singleScalerReadsCorrected.At(i)->Write(nameBuffer.Data(), option, bufsize);
        }
        else
            ret += singleScalerReadsCorrected.At(i)->Write(0, option, bufsize);
        ((TH1D*)singleScalerReadsCorrected.At(i))->SetDirectory(0);
    }
    buffer.SetDirectory(0);
    accumulated.SetDirectory(0);
    accumulatedCorrected.SetDirectory(0);
    parentDir->cd();
    return ret;
}




