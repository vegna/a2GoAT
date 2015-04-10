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
        pairInd1[i]      = 0;
        pairInd2[i]      = 0;
        pairTime[i]      = 0;
        pairDiff[i]      = 0;
        pairOrder[i]     = 0;
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

void    GTreeTagger::DecodeDoubles(const Double_t timingRes, const Bool_t decodeChain)
{
    // Reset variables for this event
    nDouble = 0;
    nChain = 0;
    for(Int_t i=0; i<nTagged; i++)
    {
        taggedOrder[i] = 0;
        taggedDouble[i] = false;
        pairInd1[i] = 0;
        pairInd2[i] = 0;
        pairTime[i] = 0;
        pairDiff[i] = 0;
        pairOrder[i] = 0;
    }

    // Local variables for search
    Int_t nPairs = 0;
    Double_t timeDiff;

    // Sort channel list into ascending order to make the search easier
    TMath::Sort(nTagged, taggedChannel, taggedOrder, false);

    // Loop over new ordered list
    for(Int_t i=0; i<nTagged; i++)
    {
        for(Int_t j=i+1; j<nTagged; j++)
        {
            // Skip if multi-hit of same channel
            if(taggedChannel[taggedOrder[j]] == taggedChannel[taggedOrder[i]]) continue;

            // Break if beyond neighbor
            if(taggedChannel[taggedOrder[j]] > (taggedChannel[taggedOrder[i]] + 1)) break;

            // Check if neighboring channel is within timing resolution
            timeDiff = (TMath::Abs(taggedTime[taggedOrder[j]]-taggedTime[taggedOrder[i]]));
            if(timeDiff < timingRes)
            {
                pairInd1[nPairs] = taggedOrder[i];
                pairInd2[nPairs] = taggedOrder[j];
                pairTime[nPairs] = ((taggedTime[taggedOrder[i]]+taggedTime[taggedOrder[j]])/2.0);
                pairDiff[nPairs] = timeDiff;
                nPairs++;
            }
        }
    }

    // Look for neighboring pairs to form chain
    if(decodeChain)
    {
        // Loop over pairs, looking for multiples that represent a chain
        for(Int_t i=0; i<nPairs; i++)
        {
            for(Int_t j=i+1; j<nPairs; j++)
            {
                // Skip if multi-hit of same channel
                if(taggedChannel[pairInd1[j]] == taggedChannel[pairInd1[i]]) continue;

                // Break if beyond neighbor
                if(taggedChannel[pairInd1[j]] != taggedChannel[pairInd2[i]]) break;

                // Check if neighboring pair is within timing resolution
                timeDiff = (TMath::Abs(pairTime[j]-pairTime[i]));
                if(timeDiff < timingRes)
                {
                    // Increment number of chains if first pair not already part of a chain
                    if(!taggedDouble[pairInd1[i]] && !taggedDouble[pairInd2[i]]) nChain++;

                    // Denote both pairs as belonging to a chain
                    taggedDouble[pairInd1[i]] = true;
                    taggedDouble[pairInd2[i]] = true;

                    taggedDouble[pairInd1[j]] = true;
                    taggedDouble[pairInd2[j]] = true;
                }
            }

            // Skip if already part of a chain
            if(taggedDouble[pairInd1[i]]) continue;
            if(taggedDouble[pairInd2[i]]) continue;

            // Otherwise call this pair a double
            taggedDouble[pairInd1[i]] = true;
            taggedDouble[pairInd2[i]] = true;

            doubleTime[nDouble] = pairTime[i];
            doubleEnergy[nDouble] = ((GetTaggedEnergy(pairInd1[i])+GetTaggedEnergy(pairInd2[i]))/2.0);
            nDouble++;
        }
    }
    // Otherwise choose best pairs
    else
    {
        // Reorder pairs by timing difference
        TMath::Sort(nPairs, pairDiff, pairOrder, false);

        // Loop over pairs, removing from list as we go
        for(Int_t i=0; i<nPairs; i++)
        {
            // Skip if already paired as a double
            if(taggedDouble[pairInd1[pairOrder[i]]]) continue;
            if(taggedDouble[pairInd2[pairOrder[i]]]) continue;

            // Otherwise call this pair a double
            taggedDouble[pairInd1[pairOrder[i]]] = true;
            taggedDouble[pairInd2[pairOrder[i]]] = true;

            doubleTime[nDouble] = pairTime[pairOrder[i]];
            doubleEnergy[nDouble] = ((GetTaggedEnergy(pairInd1[pairOrder[i]])+GetTaggedEnergy(pairInd2[pairOrder[i]]))/2.0);
            nDouble++;
        }
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
