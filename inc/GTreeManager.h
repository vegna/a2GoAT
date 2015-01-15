#ifndef __GTreeManager_h__
#define __GTreeManager_h__


#include <TLorentzVector.h>
#include <TH1.h>
#include <TDatabasePDG.h>

#include "GConfigFile.h"
#include "GTreeRawParticle.h"
#include "GTreeTagger.h"
#include "GTreeLinPol.h"
#include "GTreeScaler.h"
#include "GTreeParticle.h"
#include "GTreeMeson.h"
#include "GTreeTrigger.h"
#include "GTreeDetectorHits.h"
#include "GTreeEventParameters.h"
#include "GHistManager.h"

#ifdef hasPluto
#include "GTreePluto.h"
#endif
#include "GTreeA2Geant.h"

#include <stdio.h>
#include <TSystem.h>


class  GTreeManager : public GHistManager, public GConfigFile
{
private:
    TFile*      inputFile;
    TObjArray   treeList;
    TObjArray   treeCorreleatedToScalerReadList;
    TObjArray   readList;
    TObjArray   readCorreleatedToScalerReadList;
    TObjArray   writeList;
    Bool_t      isWritten;

    UInt_t  currentScalerEntry;

    Int_t   countReconstructed;

            Bool_t      TraverseValidEvents_AcquTreeFile();
            Bool_t      TraverseValidEvents_GoATTreeFile();

protected:
    TFile*          outputFile;

private:
    virtual TDirectory* GetOutputDirectory()    {return outputFile;}

protected:
    GTreeRawParticle*   rawParticles;
    GTreeTagger*        tagger;
    GTreeLinPol*        linpol;
    GTreeTrigger*       trigger;
    GTreeScaler*        scalers;

    GTreeEventParameters* eventParameters;
    GTreeDetectorHits*  detectorHits;
    GTreeParticle*      rootinos;
    GTreeParticle*      photons;
    GTreeParticle*      electrons;
    GTreeParticle*      chargedPions;
    GTreeParticle*      protons;
    GTreeParticle*      neutrons;
    GTreeMeson*         neutralPions;
    GTreeMeson*         etas;
    GTreeMeson*         etaPrimes;

#ifdef hasPluto
    GTreePluto*         pluto;
#endif
    GTreeA2Geant*       geant;

    TDatabasePDG *pdgDB;

            void    FillReadList()      {for(int l=0; l<readList.GetEntriesFast(); l++) ((GTree*)readList[l])->Fill();}
    const   TObjArray&  GetTreeList()    const   {return treeList;}
    virtual void    ProcessEvent() = 0;
    virtual void    ProcessScalerRead() {}
            void    SetAsGoATFile();
            void    SetAsPhysicsFile();
    virtual Bool_t  Start() = 0;
            Bool_t  TraverseEntries(const UInt_t min, const UInt_t max);
            Bool_t  TraverseScalerEntries(const UInt_t min, const UInt_t max);
            Bool_t  TraverseValidEvents()   {if(IsAcquFile()) return TraverseValidEvents_AcquTreeFile(); return TraverseValidEvents_GoATTreeFile();}
    virtual Bool_t  Write();
            Bool_t  Write(const TNamed* object);

public:
    GTreeManager();
    virtual ~GTreeManager();

    static  Int_t   CheckInput(const char* input_filename);
            UInt_t  GetEventNumber()    const   {return eventParameters->GetEventNumber();}
            UInt_t  GetNEntries()       const;
            UInt_t  GetNReconstructed() const   {return countReconstructed;}
            UInt_t  GetNScalerEntries() const;
            Bool_t  IsAcquFile()    const;
            Bool_t  IsGoATFile()    const;
            Bool_t  IsPhysicsFile()    const;
            Bool_t  TraverseFiles();
            Bool_t  StartFile(const char* inputFileName, const char* outputFileName);

    friend  class GTree;
    friend  class GTreeParticle;
    friend  class GTreeMeson;
    friend  class GTreeTagger;
};

#endif
