#ifndef __CINT__

#include "PPhysics.h"

PPhysics::PPhysics() 
{
	TC_cut_min = 0;
	TC_cut_max = 352;
}

PPhysics::~PPhysics()
{
}

Bool_t	PPhysics::Init(const Char_t *configfile)
{
	return kTRUE;
}

void	PPhysics::Reconstruct()
{
}

// ----------------------------------------------------------------------------------------
// TH1 routines
// ----------------------------------------------------------------------------------------
void PPhysics::FillScalers(Int_t low_scaler_number, Int_t high_scaler_number, TH1* hist)
{	
	// To properly accumulate, create a histogram for this scaler read
	// cloning input histogram means the axis will be equivalent
	TH1* hist_current_SR = (TH1D*) hist->Clone();
	hist_current_SR->Reset();

	// Loop over scaler range, don't pull anything higher than the real # scalers
	if (low_scaler_number  < 0)
	{
		cout << "FillScalers given scaler number outside range: " << low_scaler_number << endl;
		cout << "Setting lower limit to zero and continuing" << endl;
		low_scaler_number = 0;
	}
	if (high_scaler_number > scalers->GetNScaler())
	{
		cout << "FillScalers given scaler number outside range: " << high_scaler_number << endl;
		cout << "Setting upper limit to "<< high_scaler_number << " and continuing" << endl;	
		high_scaler_number = scalers->GetNScaler();
	}

	for (int i = low_scaler_number; i <= high_scaler_number; i++) 
	{
		Int_t bin = hist_current_SR->GetXaxis()->FindBin(i);
		hist_current_SR->SetBinContent(bin,scalers->GetScaler(i));
	}

	// Add to accumulated
	hist->Add(hist_current_SR);
}	

void PPhysics::FillMissingMass(const GTreeParticle& tree, TH1* Hprompt, TH1* Hrandom)
{
    for (Int_t i = 0; i < tree.GetNParticles(); i++)
    {
	for (Int_t j = 0; j < tagger->GetNTagged(); j++)
	{
        	FillMissingMass(tree, i, j, Hprompt, Hrandom);
	}
    }
}

void PPhysics::FillMissingMass(const GTreeParticle& tree, Int_t particle_index, TH1* Hprompt, TH1* Hrandom)
{
    for (Int_t i = 0; i < tagger->GetNTagged(); i++)
	{
        	FillMissingMass(tree, particle_index, i, Hprompt, Hrandom);
	}
}

void PPhysics::FillMissingMass(const GTreeParticle& tree, Int_t particle_index, Int_t tagger_index, TH1* Hprompt, TH1* Hrandom)
{
	time = tagger->GetTagged_t(tagger_index) - tree.GetTime(particle_index);
	missingp4 = CalcMissingP4(tree, particle_index,tagger_index);

	if (GHistBGSub::IsPrompt(time)) Hprompt->Fill(missingp4.M());
	if (GHistBGSub::IsRandom(time)) Hrandom->Fill(missingp4.M());						
}

void PPhysics::FillTime(const GTreeParticle& tree, TH1* Hist)
{
    for (Int_t i = 0; i < tree.GetNParticles(); i++)
	{
        for (Int_t j = 0; j < tagger->GetNTagged(); j++)
		{
			// Is tagger channel rejected by user?
			if(tagger->GetTagged_ch(j) < TC_cut_min) continue;
			if(tagger->GetTagged_ch(j) > TC_cut_max) continue;

           		time = tagger->GetTagged_t(j) - tree.GetTime(i);
			Hist->Fill(time);
		}
	}
}

void PPhysics::FillTime(const GTreeParticle& tree, Int_t particle_index, TH1* Hist)
{
	for (Int_t j = 0; j < tagger->GetNTagged(); j++)
	{
	// Is tagger channel rejected by user?
		if(tagger->GetTagged_ch(j) < TC_cut_min) continue;
		if(tagger->GetTagged_ch(j) > TC_cut_max) continue;
	
		time = tagger->GetTagged_t(j) - tree.GetTime(particle_index);
	Hist->Fill(time);
	}
}

void PPhysics::FillTimeCut(const GTreeParticle& tree, TH1* Hist)
{
    for (Int_t i = 0; i < tree.GetNParticles(); i++)
	{
        for (Int_t j = 0; j < tagger->GetNTagged(); j++)
		{
			// Is tagger channel rejected by user?
			if(tagger->GetTagged_ch(j) < TC_cut_min) continue;
			if(tagger->GetTagged_ch(j) > TC_cut_max) continue;

            		time = tagger->GetTagged_t(j) - tree.GetTime(i);
			if((GHistBGSub::IsPrompt(time)) || (GHistBGSub::IsRandom(time))) Hist->Fill(time);
		}
	}
}

void PPhysics::FillTimeCut(const GTreeParticle& tree, Int_t particle_index, TH1* Hist)
{
	for (Int_t j = 0; j < tagger->GetNTagged(); j++)
	{
		// Is tagger channel rejected by user?
		if(tagger->GetTagged_ch(j) < TC_cut_min) continue;
		if(tagger->GetTagged_ch(j) > TC_cut_max) continue;

		time = tagger->GetTagged_t(j) - tree.GetTime(particle_index);
		if((GHistBGSub::IsPrompt(time)) || (GHistBGSub::IsRandom(time))) Hist->Fill(time);
	}
}

void PPhysics::FillBeamAsymmetry(const GTreeParticle& tree, Int_t particle_index, TH1* Hprompt, TH1* Hrandom, Double_t MM_min, Double_t MM_max)
{
    for (Int_t i = 0; i < tagger->GetNTagged(); i++)
    {
        FillBeamAsymmetry(tree, particle_index, i, Hprompt, Hrandom, MM_min, MM_max);
    }

}

void PPhysics::FillBeamAsymmetry(const GTreeParticle& tree, Int_t particle_index, Int_t tagger_index, TH1* Hprompt, TH1* Hrandom, Double_t MM_min, Double_t MM_max)
{
    // Is tagger channel rejected by user?
//    cout << tagger->GetTagged_ch(tagger_index) << " " << TC_cut_min << " " << TC_cut_max << endl;
    if(tagger->GetTagged_ch(tagger_index) < TC_cut_min) return;
    if(tagger->GetTagged_ch(tagger_index) > TC_cut_max) return;

    // calc particle time diff
    time = tagger->GetTagged_t(tagger_index) - tree.GetTime(particle_index);
//    cout << "time " << time << endl; 
    // calc missing p4
    missingp4 = CalcMissingP4(tree, particle_index,tagger_index);
 //   cout << "MM " << missingp4.M() << endl;     
    if((missingp4.M() < MM_min) || (missingp4.M() > MM_max)) return;

   // Calc phi
   double phi = tree.Particle(particle_index).Phi() * TMath::RadToDeg();
//    cout << "phi " << phi << endl;     
   
   if (GHistBGSub::IsPrompt(time)) Hprompt->Fill(phi); //cout << "prompt" << endl;}
   if (GHistBGSub::IsRandom(time)) Hrandom->Fill(phi);	//cout << "random" << endl;}
}

Double_t PPhysics::CalcCoplanarity(const GTreeParticle& tree1, Int_t particle_index1, const GTreeParticle& tree2, Int_t particle_index2)
{
   double phi1 = tree1.Particle(particle_index1).Phi() * TMath::RadToDeg();
   double phi2 = tree2.Particle(particle_index2).Phi() * TMath::RadToDeg();
   double phidiff = TMath::Abs(phi1 - phi2);

   return phidiff;
}

// ----------------------------------------------------------------------------------------
// GH1 routines
// ----------------------------------------------------------------------------------------

void PPhysics::FillMissingMass(const GTreeParticle& tree, GH1* gHist, Bool_t TaggerBinning)
{
	for (Int_t i = 0; i < tree.GetNParticles(); i++)
	{
		for (Int_t j = 0; j < tagger->GetNTagged(); j++)
		{
			FillMissingMass(tree, i, j, gHist, TaggerBinning);
		}
	}
}

void PPhysics::FillMissingMass(const GTreeParticle& tree, Int_t particle_index, GH1* gHist, Bool_t TaggerBinning)
{
    for (Int_t i = 0; i < tagger->GetNTagged(); i++)
	{
        FillMissingMass(tree, particle_index, i, gHist, TaggerBinning);
	}
}

void PPhysics::FillMissingMass(const GTreeParticle& tree, Int_t particle_index, Int_t tagger_index, GH1* gHist, Bool_t TaggerBinning)
{
    // Is tagger channel rejected by user?
    if(tagger->GetTagged_ch(tagger_index) < TC_cut_min) return;
    if(tagger->GetTagged_ch(tagger_index) > TC_cut_max) return;

    // calc particle time diff
    time = tagger->GetTagged_t(tagger_index) - tree.GetTime(particle_index);
    
    // calc missing p4
    missingp4 = CalcMissingP4(tree, particle_index,tagger_index);

   // Fill GH1
   if(TaggerBinning)   gHist->Fill(missingp4.M(),time, tagger->GetTagged_ch(tagger_index));
   else gHist->Fill(missingp4.M(),time);

}

Double_t PPhysics::CalcMissingMass(const GTreeParticle& tree, Int_t particle_index, Int_t tagger_index)
{
    missingp4 	= CalcMissingP4(tree, particle_index, tagger_index);

	return missingp4.M();
}

Double_t PPhysics::CalcMissingEnergy(const GTreeParticle& tree, Int_t particle_index, Int_t tagger_index)
{
    missingp4 	= CalcMissingP4(tree,particle_index, tagger_index);

	return missingp4.T();
}

TLorentzVector PPhysics::CalcMissingP4(const GTreeParticle& tree, Int_t particle_index, Int_t tagger_index)
{
    particle	= tree.Particle(particle_index);
    beam 		= TLorentzVector(0.,0.,tagger->GetPhotonBeam_E(tagger_index),tagger->GetPhotonBeam_E(tagger_index));
	missingp4 	= beam + target - particle;						

	return missingp4;
}

void PPhysics::FillBeamAsymmetry(const GTreeParticle& tree, Int_t particle_index, GH1* gHist, Bool_t TaggerBinning, Double_t MM_min, Double_t MM_max)
{
    for (Int_t i = 0; i < tagger->GetNTagged(); i++)
    {
        FillBeamAsymmetry(tree, particle_index, i, gHist, TaggerBinning);
    }

}

void PPhysics::FillBeamAsymmetry(const GTreeParticle& tree, Int_t particle_index, Int_t tagger_index, GH1* gHist, Bool_t TaggerBinning, Double_t MM_min, Double_t MM_max)
{
    // Is tagger channel rejected by user?
    if(tagger->GetTagged_ch(tagger_index) < TC_cut_min) return;
    if(tagger->GetTagged_ch(tagger_index) > TC_cut_max) return;

    // calc particle time diff
    time = tagger->GetTagged_t(tagger_index) - tree.GetTime(particle_index);
    
    // calc missing p4
    missingp4 = CalcMissingP4(tree, particle_index,tagger_index);
    if((missingp4.M() < MM_min) || (missingp4.M() > MM_max)) return;

   // Calc phi and Fill GH1
   double phi = tree.Particle(particle_index).Phi() * TMath::RadToDeg();
   
   if(TaggerBinning)   gHist->Fill(phi,time,tagger->GetTagged_ch(tagger_index));
   else gHist->Fill(phi,time);

}

void PPhysics::FillTime(const GTreeParticle& tree, GH1* gHist)
{
    for (Int_t i = 0; i < tree.GetNParticles(); i++)
	{
        for (Int_t j = 0; j < tagger->GetNTagged(); j++)
		{
			// Is tagger channel rejected by user?
			if(tagger->GetTagged_ch(j) < TC_cut_min) continue;
			if(tagger->GetTagged_ch(j) > TC_cut_max) continue;

           		time = tagger->GetTagged_t(j) - tree.GetTime(i);
			gHist->Fill(time);
		}
	}
}

void PPhysics::FillTime(const GTreeParticle& tree, Int_t particle_index, GH1* gHist)
{
	for (Int_t j = 0; j < tagger->GetNTagged(); j++)
	{
		// Is tagger channel rejected by user?
		if(tagger->GetTagged_ch(j) < TC_cut_min) continue;
		if(tagger->GetTagged_ch(j) > TC_cut_max) continue;
	
		time = tagger->GetTagged_t(j) - tree.GetTime(particle_index);
		gHist->Fill(time);
	}
}

void PPhysics::FillTimeCut(const GTreeParticle& tree, GH1* gHist)
{
    for (Int_t i = 0; i < tree.GetNParticles(); i++)
	{
        for (Int_t j = 0; j < tagger->GetNTagged(); j++)
		{
			// Is tagger channel rejected by user?
			if(tagger->GetTagged_ch(j) < TC_cut_min) continue;
			if(tagger->GetTagged_ch(j) > TC_cut_max) continue;

            		time = tagger->GetTagged_t(j) - tree.GetTime(i);
			if((GHistBGSub::IsPrompt(time)) || (GHistBGSub::IsRandom(time))) gHist->Fill(time);
		}
	}
}

void PPhysics::FillTimeCut(const GTreeParticle& tree, Int_t particle_index, GH1* gHist)
{
	for (Int_t j = 0; j < tagger->GetNTagged(); j++)
	{
		// Is tagger channel rejected by user?
		if(tagger->GetTagged_ch(j) < TC_cut_min) continue;
		if(tagger->GetTagged_ch(j) > TC_cut_max) continue;

		time = tagger->GetTagged_t(j) - tree.GetTime(particle_index);
		if((GHistBGSub::IsPrompt(time)) || (GHistBGSub::IsRandom(time))) gHist->Fill(time);
	}
}

void PPhysics::FillMass(const GTreeParticle& tree, GH1* gHist)
{
    for (Int_t i = 0; i < tree.GetNParticles(); i++)
	{
		gHist->Fill(tree.Particle(i).M());
	}
}

void PPhysics::FillMass(const GTreeParticle& tree, Int_t particle_index, GH1* gHist)
{
	gHist->Fill(tree.Particle(particle_index).M());
}

Bool_t 	PPhysics::Write()
{
	return kTRUE;
}
#endif
