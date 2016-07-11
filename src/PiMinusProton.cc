#include "PiMinusProton.h"

PiMinusProton::PiMinusProton(){ 
    nTracks = new TH1F("nTracks","Number of tracks",11,-0.5,10.5);
    nParticles = new TH1F("nParticles","Number of particles",11,-0.5,10.5);
    Coplanarity = new TH2F("CoplanarityVsPhi1","(#phi_0 - #phi_1) [deg] Vs #phi_1 [deg]",361,-180.5,180.5,721.,-360.5,360.5);
    CoplanaritySelection = new TH2F("CoplanaritySelectionVsPhi1","(#phi_0 - #phi_1) [deg] Vs #phi_1 [deg]",361,-180.5,180.5,721.,-360.5,360.5);
    TimeDiffBetweenCharged = new TH1F("TimeDiffBetweenCharged","Time difference between the two charged particles [ns]",201,-100.5,100.5);
    TimeDiffSelectionBetweenCharged = new TH1F("TimeDiffSelectionBetweenCharged","Time difference between the two charged particles [ns]",201,-100.5,100.5);
    
    nIncomingPhotonsAll = new TH1F("nIncomingPhotonsAll","Number of incoming photons - All",101,-0.5,100.5);
    nIncomingPhotonsInPromptPeak = new TH1F("nIncomingPhotonsInPromptPeak","Number of incoming photons - Only in Prompt Peak",51,-0.5,50.5);
    timeIncomingPhotons = new TH1F("timeIncomingPhotons","time of incoming photons [ns]",201,-100.5,100.5);
    timeCorrelationIncomingPhotonVsChargedParticlesAll = new TH2F("timeCorrelationIncomingPhotonVsChargedParticlesAll"," Timing between incoming photons and final state charged particles - All",301,-150.5,150.5,301,-150.5,150.5);
    timeCorrelationIncomingPhotonVsChargedParticlesSelected = new TH2F("timeCorrelationIncomingPhotonVsChargedParticlesSelected"," Timing between incoming photons and final state charged particles - Selected",81,-40.5,40.5,81,-40.5,40.5);
    energyIncomingPhotonsAll = new TH1F("energyIncomingPhotonsAll","Incoming Photons Spectrum [MeV] - All Tagged Photons",751,-0.5,1500.5);
    energyIncomingPhotonSelected = new TH1F("energyIncomingPhotonSelected","Incoming Photond Spectrum [MeV] - Selected Events (Only 1 inc #gamma)",751,-0.5,1500.5);

    PCalcDenum1VsPCalcDenum2 = new TH2F("PCalcDenum1VsPCalcDenum2","Denum2 Vs Denum1 - Formulas for momentum P2 calculation",2.1,-1.05,1.05,101,-10.05,10.05);
    PYConservation = new TH1F("PYConservation","Momentum conservation along Y-Axis (P_Y^{Tot}) [MeV]",801,-400.5,400.5);
    ChargedParticleHypothesis = new TH2F("ChargedParticleHypothesis","Energy conservation",751,-1.,3001.,751,-1.,3001);
}

PiMinusProton::~PiMinusProton(){
}

Bool_t PiMinusProton::Init(){
  cout << "Initialising physics analysis..." << endl;
  cout << "--------------------------------------------------" << endl << endl;

  if(!InitBackgroundCuts()) return kFALSE;
  if(!InitTargetMass()) return kFALSE;
// erano gia' commentati da Susanna. Devo ancora capire a cosa servono
  //   if(!InitTaggerChannelCuts()) return kFALSE;
  //   if(!InitTaggerScalers()) return kFALSE;
  if(!PPhysics::Init()) return kFALSE;
  cout << "--------------------------------------------------" << endl;

  evtNum = 0;

  nIncompatibleWithGoat = 0;

  // correlation between the 2 charged particles
  nBadCoplanarity = 0;
  nBadTimeCorrelationBetweenChargedParticles = 0;
  // number of candidate incoming photons
  nNoPhotonsInPromptPeak = 0;
  nTooManyPhotonsInPromptPeak = 0;
  nBadTimeCorrelationIncomingPhotonWithChargedParticles = 0;

  nAlgebraicalFailInCalcMomenta = 0;


  IndexIncomingPhoton = -999; // negative index has no meaning

  return kTRUE;
}

Bool_t PiMinusProton::Start(){
  cout << "=== PiMinusProton::Start() " << endl;
  if(!IsGoATFile()){
    cout << "ERROR: Input File is not a GoAT file." << endl;
    return kFALSE;
  }
  SetAsPhysicsFile();
  TraverseValidEvents();
  return kTRUE;
}

void PiMinusProton::ProcessEvent(){
    if(CheckInitialConditions()){
	if (CheckChargedCorrelation(1,3)){
	    CoplanaritySelection->Fill(GetRootinos()->GetPhi(1),GetRootinos()->GetPhi(0)-GetRootinos()->GetPhi(1));
	    TimeDiffSelectionBetweenCharged->Fill(GetRootinos()->GetTime(0) - GetRootinos()->GetTime(1));
	    if (CheckTagger()){
		lvIncomingPhoton.SetPxPyPzE(0.,0.,GetTagger()->GetTaggedEnergy(IndexIncomingPhoton),GetTagger()->GetTaggedEnergy(IndexIncomingPhoton));
		if(CalcMomenta()){
		    evtNum++;
		}  // close CalcMomenta
	    }  // close CheckTagger
	} // close CheckChargedCorrelation
    } // close Check GoAT preselection
}  



void	PiMinusProton::ProcessScalerRead(){
/*
  // Fill Tagger Scalers
  //  FillScalers(GetTC_scaler_min(),GetTC_scaler_max(),TaggerAccScal);
*/
  PPhysics::ProcessScalerRead();
}

Bool_t	PiMinusProton::Write(){
    cout << "PiMinusProton::Write() " << endl;
  // Write all GH1's and TObjects defined in this class
    return GTreeManager::Write();
//    cout << " ----------------------------- " << endl;
//    cout << " Summary of the counters: " << endl;
//    cout << " ----------------------------- " << endl;
//    cout << " Number of events analysed: " << evtNum++ << endl;
//    cout << " Number of events rejected for incompatibility with GoAT preselection: " << nIncompatibleWithGoat << endl;
//    cout << "Number of event rejected for bad coplanarity condition: " << NBadCoplanarity << endl;
}


// *********************************************************
Bool_t PiMinusProton::CheckInitialConditions(){
    Int_t NTracks = GetTracks()->GetNTracks();
    if (NTracks <2){
	cout << " EvtNumber: " << evtNum  <<  " Number of Tracks : " <<  NTracks  << endl;
	nIncompatibleWithGoat++;
	return kFALSE;
    } else {
	nTracks->Fill(NTracks);
    }

    Int_t NChargedParticles = GetRootinos()->GetNParticles();
    if (NChargedParticles != 2){
	cout << " EvtNumber: " << evtNum  <<  " NChargedParticles = " << NChargedParticles << endl;
	nIncompatibleWithGoat++;
	return kFALSE;
    } else {
	nParticles->Fill(NChargedParticles);
    }
    return kTRUE;
}


Bool_t PiMinusProton::CheckChargedCorrelation(Int_t NSigmaCoplanarity, Int_t NSigmaTime){
    Double_t copl = GetRootinos()->GetPhi(0) - GetRootinos()->GetPhi(1);
    Coplanarity->Fill(GetRootinos()->GetPhi(1),copl);
    Double_t sigma_copl = 25.; // Fissato ad occhio. Cerca di ottimizzarlo con un fit!!!
    if ((TMath::Abs(copl)>180.-1.*NSigmaCoplanarity*sigma_copl)&&(TMath::Abs(copl)<180.+NSigmaCoplanarity*sigma_copl)){
	Double_t TimeDiff = GetRootinos()->GetTime(0) - GetRootinos()->GetTime(1);
	TimeDiffBetweenCharged->Fill(TimeDiff);
	Double_t sigma_time = 25.; // Fissato ad occhio. Cerca di ottimizzarlo con un fit!!!
	if (TMath::Abs(TimeDiff) < NSigmaTime*sigma_time){
	    return kTRUE;
	} else {
	    nBadTimeCorrelationBetweenChargedParticles++;
	    return kFALSE;
	}
    } else {
	nBadCoplanarity++;
	return kFALSE;
    }
}

Bool_t PiMinusProton::CheckTagger(){

    Int_t NPhotonsAll = GetTagger()->GetNTagged();
    Int_t NPhotonsInTime = 0;

    nIncomingPhotonsAll->Fill(NPhotonsAll);
    for (Int_t i=0; i<NPhotonsAll; i++){
	timeIncomingPhotons->Fill(GetTagger()->GetTaggedTime(i));
	energyIncomingPhotonsAll->Fill(GetTagger()->GetTaggedEnergy(i));
	if (((GetTagger()->GetTaggedTime(i))>-10.)&&((GetTagger()->GetTaggedTime(i)<30.))){  // values decided just looking at the plot... to be optimized
	    IndexIncomingPhoton = i;
	    NPhotonsInTime = NPhotonsInTime + 1;
	}
    }
    nIncomingPhotonsInPromptPeak->Fill(NPhotonsInTime);
    if (NPhotonsInTime==1){
	Double_t XValue = GetTagger()->GetTaggedTime(IndexIncomingPhoton)-GetRootinos()->GetTime(0); // time correlation IncomingPhoton - Charged0
	Double_t YValue = GetTagger()->GetTaggedTime(IndexIncomingPhoton)-GetRootinos()->GetTime(1); // time correlation IncomingPhoton - Charged1
	timeCorrelationIncomingPhotonVsChargedParticlesAll->Fill(XValue,YValue);
	if((TMath::Abs(XValue)<=40.)&&(TMath::Abs(YValue)<=40.)&&((25.+XValue)>YValue)&&(YValue>(-24.+XValue))){ // values just looking at the histo... to be optimized
	    timeCorrelationIncomingPhotonVsChargedParticlesSelected->Fill(XValue,YValue);
	    energyIncomingPhotonSelected->Fill(GetTagger()->GetTaggedEnergy(IndexIncomingPhoton));
	    return kTRUE;
	} else {
	    nBadTimeCorrelationIncomingPhotonWithChargedParticles++;
	    return kFALSE;
	}
    } else {
	if(NPhotonsInTime<1){
	    nNoPhotonsInPromptPeak++;
	} else {
	    nTooManyPhotonsInPromptPeak++;
	}
	return kFALSE;
    }
}


Bool_t PiMinusProton::CalcMomenta(){

    Double_t P1 = -999.;  // magnitude of the 3-momentum of charged particle 0 --> it can not be negative!!!
    Double_t P2 = -999.;  // magnitude of the 3-momenutm of charged particle 1 --> it can not be negative!!!

    Double_t Theta1 = GetRootinos()->GetTheta(0)*TMath::DegToRad();
    Double_t Phi1   = GetRootinos()->GetPhi(0)*TMath::DegToRad();
    Double_t Theta2 = GetRootinos()->GetTheta(1)*TMath::DegToRad();
    Double_t Phi2   = GetRootinos()->GetPhi(1)*TMath::DegToRad();

    Double_t Denum1 = TMath::Sin(Theta1)*TMath::Cos(Phi1);
    if (Denum1 ==0){
	nAlgebraicalFailInCalcMomenta++;
	return kFALSE;
    }
    Double_t Denum2 = TMath::Cos(Theta2) - TMath::Cos(Theta1)*TMath::Sin(Theta2)*TMath::Cos(Phi2)/(Denum1);
    if (Denum2 ==0){
	nAlgebraicalFailInCalcMomenta++;
	return kFALSE;
    }
 
    PCalcDenum1VsPCalcDenum2->Fill(Denum1,Denum2);

    P2 = lvIncomingPhoton.E()/Denum2;
    P1 = -1. * P2 * TMath::Sin(Theta2)*TMath::Cos(Phi2)/Denum1;

    Double_t DeltaPY = P1 * TMath::Sin(Theta1)*TMath::Sin(Phi1) + P2 * TMath::Sin(Theta2)*TMath::Sin(Phi2);
    PYConservation->Fill(DeltaPY);

    // hypothesis A) charged 1 = proton; charged 2 = pion
    Double_t Ene1_A = TMath::Sqrt(P1*P1 + 938*938); // charged 1 = proton
    Double_t Ene2_A = TMath::Sqrt(P2*P2 + 139*139); // charged 2 = pion

    // hypothesis B) charged 1 = pion; charged 2 = proton
    Double_t Ene1_B = TMath::Sqrt(P1*P1 + 139*139); // charged 2 = pion
    Double_t Ene2_B = TMath::Sqrt(P2*P2 + 938*938); // charged 1 = proton

    ChargedParticleHypothesis->Fill(Ene1_A+Ene2_A-lvIncomingPhoton.E(),Ene1_B+Ene2_B-lvIncomingPhoton.E());

    return kTRUE;

}
