#include "GTreeTagger.h"
#include "GTreeManager.h"

GTreeTagger::GTreeTagger(GTreeManager *Manager)    :
    GTree(Manager, TString("tagger")),
    nTagged(0),
    nDouble(0),
    nChain(0),
    hasEnergy(0)
{
    for(Int_t i=0; i<GTreeTagger_MAX; i++)
    {
        taggedChannel[i] = 0;
        taggedTime[i]    = 0;
        taggedEnergy[i]  = 0;
        taggedOrder[i]   = 0;
        taggedDouble[i]  = 0;
        doubleTime[i]    = 0;
        doubleEnergy[i]  = 0;
    }
    for(Int_t i=0; i<352; i++) calibration[i] = 0;
}

GTreeTagger::~GTreeTagger()
{

}

void    GTreeTagger::SetBranchAdresses()
{
    inputTree->SetBranchAddress("nTagged", 	   &nTagged);
    inputTree->SetBranchAddress("taggedChannel", taggedChannel);
    inputTree->SetBranchAddress("taggedTime",    taggedTime);
    if(inputTree->GetBranch("taggedEnergy"))
    {
        inputTree->SetBranchAddress("taggedEnergy",  taggedEnergy);
        hasEnergy = true;
    }

}

void    GTreeTagger::SetBranches()
{
    outputTree->Branch("nTagged",       &nTagged,      "nTagged/I");
    outputTree->Branch("taggedChannel", taggedChannel, "taggedChannel[nTagged]/I");
    outputTree->Branch("taggedTime",    taggedTime,    "taggedTime[nTagged]/D");
    if(hasEnergy) outputTree->Branch("taggedEnergy",  taggedEnergy,  "taggedEnergy[nTagged]/D");
}

void    GTreeTagger::DecodeDoubles(const Double_t timingRes)
{
    // Reset variables for this event
    nDouble = 0;
    nChain = 0;
    for(Int_t i=0; i<nTagged; i++)
    {
        taggedOrder[i] = 0;
        taggedDouble[i] = false;
    }

    // Local variables for search
    Int_t nNeighbors;
    Int_t lastChan;
    Double_t timeDiff;
    Double_t timeAvg;
    Double_t energyAvg;

    // Sort channel list into ascending order to make the search easier
    TMath::Sort(nTagged, taggedChannel, taggedOrder, false);

    // Loop over new ordered list
    for(Int_t i=0; i<nTagged; i++)
    {
        // Skip if already counted as a double
        if(taggedDouble[taggedOrder[i]]) continue;

        nNeighbors = 0;
        lastChan = taggedChannel[taggedOrder[i]];

        timeDiff = 0;
        timeAvg = taggedTime[taggedOrder[i]];
        energyAvg = GetTaggedEnergy(taggedOrder[i]);

        for(Int_t j=i; j<nTagged; j++)
        {
            // Skip if already counted as a double
            if(taggedDouble[taggedOrder[j]]) continue;

            // Skip if multi-hit of same channel
            if(taggedChannel[taggedOrder[j]] == taggedChannel[taggedOrder[i]]) continue;

            // Break if beyond string of channels
            if(taggedChannel[taggedOrder[j]] > (lastChan + 1)) break;

            // Check if neighboring channel is within timing resolution
            timeDiff = (TMath::Abs(taggedTime[taggedOrder[j]]-taggedTime[taggedOrder[i]]));
            if(timeDiff < timingRes)
            {
                nNeighbors++;
                lastChan = taggedChannel[taggedOrder[j]];
                timeAvg += taggedTime[taggedOrder[j]];
                energyAvg += GetTaggedEnergy(taggedOrder[j]);

                // Denote both as being parts of a double
                taggedDouble[taggedOrder[i]] = true;
                taggedDouble[taggedOrder[j]] = true;
            }
        }

        // For actual double (two neighboring channels in coincidence) add to double list
        if(nNeighbors == 1)
        {
            doubleTime[nDouble] = (timeAvg/(nNeighbors+1));
            doubleEnergy[nDouble] = (energyAvg/(nNeighbors+1));
            nDouble++;
        }
        // For chain of hits, ignore for now
        else if(nNeighbors > 1) nChain++;
    }
    /*
    cout << "New Event - nDouble = " << nDouble << " - nChain = " << nChain << endl << endl;
    for(Int_t i=0; i<nTagged; i++)
    {
        cout << i << "\t" << taggedChannel[i] << "\t" << taggedTime[i] << "   \t" << taggedOrder[i] << "\t" << taggedChannel[taggedOrder[i]] << "\t" << taggedTime[taggedOrder[i]] << "   \t" << taggedDouble[taggedOrder[i]] << endl;
    }
    cout << endl;
    */
}

void    GTreeTagger::SetCalibration(const Int_t nChan, const Double_t *energy)
{
    for(Int_t i=0; i<nChan; i++) calibration[i] = energy[i];
}

TLorentzVector  GTreeTagger::GetVectorProtonTarget(const Int_t index)    const
{
    return TLorentzVector(0, 0, taggedEnergy[index], taggedEnergy[index] + (manager->pdgDB->GetParticle("proton")->Mass()*1000));
}
