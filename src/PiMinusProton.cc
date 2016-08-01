#include "PiMinusProton.h"

PiMinusProton::PiMinusProton(){ 
    nTracks = new TH1F("nTracks","PreSelected events",11,-0.5,10.5);
    nTracks->GetXaxis()->SetTitle("Number of Tracks");
//    nTracks->GetYAxis()->SetTitle("counts");

    nParticles = new TH1F("nParticles","PreSelected events",11,-0.5,10.5);
    nParticles->GetXaxis()->SetTitle("Number of Particles");
//    nParticles->GetYAxis()->SetTitle("counts");

    Coplanarity = new TH2F("CoplanarityVsPhi1","Azimuthal correlation between the 2 charged particles",361,-180.5,180.5,721.,-360.5,360.5);
    Coplanarity->GetXaxis()->SetTitle("#phi_2 [deg]");
    Coplanarity->GetYaxis()->SetTitle("#phi_1 - #phi_2 [deg]");

    CoplanaritySelection = new TH2F("CoplanaritySelectionVsPhi1","Azimuthal correlation between the 2 charged particles",361,-180.5,180.5,721.,-360.5,360.5);
    CoplanaritySelection->GetXaxis()->SetTitle("#phi_2 [deg]");
    CoplanaritySelection->GetYaxis()->SetTitle("#phi_1 - #phi_2 [deg]");


    TimeDiffBetweenCharged = new TH1F("TimeDiffBetweenCharged","Time correlation between the two charged particles",201,-100.5,100.5);
    TimeDiffBetweenCharged->GetXaxis()->SetTitle("time_1 - time_2 [ns]");

    TimeDiffSelectionBetweenCharged = new TH1F("TimeDiffSelectionBetweenCharged","Time correlation between the two charged particles",201,-100.5,100.5);
    TimeDiffSelectionBetweenCharged->GetXaxis()->SetTitle("time_1 - time_2 [ns]");

    nIncomingPhotonsAll = new TH1F("nIncomingPhotonsAll","Tagger - All",101,-0.5,100.5);
    nIncomingPhotonsAll->GetXaxis()->SetTitle("Number of #gamma");

    nIncomingPhotonsInPromptPeak = new TH1F("nIncomingPhotonsInPromptPeak","Tagger - Prompt Peak",51,-0.5,50.5);
    nIncomingPhotonsInPromptPeak->GetXaxis()->SetTitle("Number of #gamma");

    timeIncomingPhotons = new TH1F("timeIncomingPhotons","Tagger - All",201,-100.5,100.5);
    timeIncomingPhotons->GetXaxis()->SetTitle("time  of #gamma [ns]");

    timeCorrelationIncomingPhotonVsChargedParticlesAll = new TH2F("timeCorrelationIncomingPhotonVsChargedParticlesAll"," Timing between incoming photons and final state charged particles - All",301,-150.5,150.5,301,-150.5,150.5);
    timeCorrelationIncomingPhotonVsChargedParticlesAll->GetXaxis()->SetTitle("time_#gamma - time_1 [ns]");
    timeCorrelationIncomingPhotonVsChargedParticlesAll->GetYaxis()->SetTitle("time_#gamma - time_2 [ns]");

    timeCorrelationIncomingPhotonVsChargedParticlesSelected = new TH2F("timeCorrelationIncomingPhotonVsChargedParticlesSelected"," Timing between incoming photons and final state charged particles - Selected",81,-40.5,40.5,81,-40.5,40.5);
    timeCorrelationIncomingPhotonVsChargedParticlesSelected->GetXaxis()->SetTitle("time_#gamma - time_1 [ns]");
    timeCorrelationIncomingPhotonVsChargedParticlesSelected->GetXaxis()->SetTitle("time_#gamma - time_2 [ns]");

    energyIncomingPhotonsAll = new TH1F("energyIncomingPhotonsAll","Tagger - All",751,-0.5,1500.5);
    energyIncomingPhotonsAll->GetXaxis()->SetTitle("Energy [MeV]");

    energyIncomingPhotonSelected = new TH1F("energyIncomingPhotonSelected","Tagger - Selected (only 1 #gamma in Prompt Peak)",751,-0.5,1500.5);
    energyIncomingPhotonSelected->GetXaxis()->SetTitle("Energy [MeV]");

    PCalcDenum1VsPCalcDenum2 = new TH2F("PCalcDenum2VsPCalcDenum1","Checks formula for momenta P1 and P2 calculation",2.1,-1.05,1.05,101,-10.05,10.05);
    PCalcDenum1VsPCalcDenum2->GetYaxis()->SetTitle("Denum2 = cos(#theta_2) - cos(#theta_1)*sin(#theta_2)*cos(#phi_2)/(Denum1)");
    PCalcDenum1VsPCalcDenum2->GetXaxis()->SetTitle("Denum1 = sin(#theta_1)*cos(#phi_11)");

    
    PYConservation = new TH1F("PYConservation","Momentum conservation along Y-Axis",801,-400.5,400.5);
    PYConservation->GetXaxis()->SetTitle("P^y_Tot = P^y_P + P^y_#pi [MeV]");

    ChargedParticleHypothesis = new TH2F("ChargedParticleHypothesis","Calculated Mass of the Target Particle",751,-1.,3001.,751,-1.,3001);
    ChargedParticleHypothesis->GetXaxis()->SetTitle("M_T [MeV] (if Proton = charged1 and Pion = charged2)");
    ChargedParticleHypothesis->GetYaxis()->SetTitle("M _T[MeV] (if Proton = charged2 and Pion = charged1)");

    ProtonAnglesGCut = new TH2F("ProtonAnglesGCut","Selection through graphical cut - Proton",361,-180.5,180.5,181,-0.5,180.5);
    ProtonAnglesGCut->GetXaxis()->SetTitle("#phi_P [deg]");
    ProtonAnglesGCut->GetXaxis()->SetTitle("#theta_P [deg]");

    PionAnglesGCut = new TH2F("PionAnglesGCut","Selection through graphical cut - Pion",361,-180.5,180.5,181,-0.5,180.5);
    PionAnglesGCut->GetXaxis()->SetTitle("#phi_#pi [deg]");
    PionAnglesGCut->GetYaxis()->SetTitle("#theta_#pi [deg]");

    ProtonMomentumVsThetaGCut = new TH2F("ProtonMomentumVsThetaGCut","Selection through graphical cut - Proton",1001,-1.,2001.,181,-0.5,180.5);
    ProtonMomentumVsThetaGCut->GetXaxis()->SetTitle("momentum_P [MeV]");
    ProtonMomentumVsThetaGCut->GetYaxis()->SetTitle("#theta_P [deg]");

    PionMomentumVsThetaGCut = new TH2F("PionMomentumVsThetaGCut","Selection through graphical cut - Pion",1001,-1.,2001.,181,-0.5,180.5);
    PionMomentumVsThetaGCut->GetYaxis()->SetTitle("momentum_#pi [MeV]");
    PionMomentumVsThetaGCut->GetYaxis()->SetTitle("#theta_#pi [deg]");

    TargetMassGCut = new TH1F("TargetMassGCut","Calculated Mass of the Target Particle",751,-1.,3001.);
    TargetMassGCut->GetXaxis()->SetTitle("M_T [MeV] (if P and #pi selected with graphical cut)");

    InvariantMassVSTargetMassGCut = new TH2F("InvariantMassVSTargetMassGCut","Mass of the Proton-Pion System [MeV] Vs Target Mass [MeV]",751,-1.,3001.,751,-1.,3001.);
    InvariantMassVSTargetMassGCut->GetXaxis()->SetTitle("M_T [MeV] (if P and #pi selected with graphical cut)");
    InvariantMassVSTargetMassGCut->GetYaxis()->SetTitle("M(P,#pi) [MeV]");

    InvariantMassVSEGammaGCut = new TH2F("InvariantMassVSEGammaGCut","Mass of the Proton-Pion System [MeV] Vs  Incoming Photon Energy [MeV]",751,-1.,3001.,751,-1.,3001.);
    InvariantMassVSEGammaGCut->GetXaxis()->SetTitle("Incoming Photon Energy E_#gamma [MeV]");
    InvariantMassVSEGammaGCut->GetYaxis()->SetTitle("M(P,#pi) [MeV]");

    TargetMassVSEGammaGCut = new TH2F("TargetMassVSEGammaGCut","Target Mass [MeV] Vs  Incoming Photon Energy [MeV]",751,-1.,3001.,751,-1.,3001.);
    TargetMassVSEGammaGCut->GetXaxis()->SetTitle("Incoming Photon Energy E_#gamma [MeV]");
    TargetMassVSEGammaGCut->GetYaxis()->SetTitle("M_T [MeV] (if P and #pi selected with graphical cut)");

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
		    FillHistograms();
		    evtNum++;
		}  // close CalcMomenta
	    }  // close CheckTagger
	} // close CheckChargedCorrelation
    } // close Check GoAT preselection
}  



void PiMinusProton::ProcessScalerRead(){
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
    
    Double_t MProton = 938.272013;  // Proton Mass  in MeV
    Double_t MPion = 139.57018; // Pion Mass in MeV

    Double_t Theta1 = GetRootinos()->GetTheta(0)*TMath::DegToRad();
    Double_t Phi1   = GetRootinos()->GetPhi(0)*TMath::DegToRad();
    Double_t Theta2 = GetRootinos()->GetTheta(1)*TMath::DegToRad();
    Double_t Phi2   = GetRootinos()->GetPhi(1)*TMath::DegToRad();

    Int_t NProtonsInCut = 0;
    Int_t NPionsInCut = 0;

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
    Double_t Ene1_A = TMath::Sqrt(P1*P1 + MProton*MProton); // charged 1 = proton
    Double_t Ene2_A = TMath::Sqrt(P2*P2 + MPion*MPion); // charged 2 = pion

    // hypothesis B) charged 1 = pion; charged 2 = proton
    Double_t Ene1_B = TMath::Sqrt(P1*P1 + MPion*MPion); // charged 2 = pion
    Double_t Ene2_B = TMath::Sqrt(P2*P2 + MProton*MProton); // charged 1 = proton

    ChargedParticleHypothesis->Fill(Ene1_A+Ene2_A-lvIncomingPhoton.E(),Ene1_B+Ene2_B-lvIncomingPhoton.E());

    // hypothesis on the base of the graphical cut for the central detector

    TCutG* IsItAProton;
    TCutG* IsItAPion;

    Int_t IndexProton, IndexPion;

    TFile ProtonCut("/hsag/maritozzo/vale/Mainz/data/outPreSelection/proton.root","READ");
    TFile PionCut("/hsag/maritozzo/vale/Mainz/data/outPreSelection/pion.root","READ");

    if(!ProtonCut.IsOpen()){
        cerr << "Can't open ProtonCut file! " << endl;
    } else {
	ProtonCut.GetObject("CUTG",IsItAProton);
    }
    if(!PionCut.IsOpen()){
        cerr << "Can't open PionCut file! " << endl;
    } else {
	PionCut.GetObject("CUTG",IsItAPion);
    }
//    cout << "Charged particle number 1: ClEnergy: " << GetRootinos()->GetClusterEnergy(0) << "    Veto Energy : " << GetRootinos()->GetVetoEnergy(0) << endl;

    if(IsItAProton->IsInside(GetRootinos()->GetClusterEnergy(0),GetRootinos()->GetVetoEnergy(0))){
	NProtonsInCut++;
	IndexProton=0;
    } else {
	if(IsItAPion->IsInside(GetRootinos()->GetClusterEnergy(0),GetRootinos()->GetVetoEnergy(0))){
	    NPionsInCut++;
	    IndexPion = 0;
	}
    }

    if(IsItAProton->IsInside(GetRootinos()->GetClusterEnergy(1),GetRootinos()->GetVetoEnergy(1))){
	NProtonsInCut++;
	IndexProton=1;
    } else { 
	if(IsItAPion->IsInside(GetRootinos()->GetClusterEnergy(1),GetRootinos()->GetVetoEnergy(1))){
	    NPionsInCut++;
	    IndexPion=1;
	}
    }

//    cout << "According with graphical cuts: NProtons = " << NProtonsInCut <<"     , NPions = " << NPionsInCut << endl;

    if((NProtonsInCut==1)&&(NPionsInCut==1)){
	Double_t ThetaProton = GetRootinos()->GetTheta(IndexProton)*TMath::DegToRad();
	Double_t PhiProton = GetRootinos()->GetPhi(IndexProton)*TMath::DegToRad();
	Double_t ThetaPion = GetRootinos()->GetTheta(IndexPion)*TMath::DegToRad();
	Double_t PhiPion = GetRootinos()->GetPhi(IndexPion)*TMath::DegToRad();
 
// same algorithm as before. Now we call Proton what before was particle 2 and pion what before was particle 1

	Double_t Factor1 = TMath::Sin(ThetaPion)*TMath::Cos(PhiPion);
	Double_t Factor2 = TMath::Cos(ThetaProton) - TMath::Cos(ThetaPion)*TMath::Sin(ThetaProton)*TMath::Cos(PhiProton)/(Factor1);

	Double_t PProton = lvIncomingPhoton.E()/Factor2;
	Double_t PPion = -1. * PProton * TMath::Sin(ThetaProton)*TMath::Cos(PhiProton)/Denum1;

	lvRecoilProton.SetPxPyPzE(PProton*TMath::Sin(ThetaProton)*TMath::Cos(PhiProton),
				  PProton*TMath::Sin(ThetaProton)*TMath::Sin(PhiProton),
				  PProton*TMath::Cos(ThetaProton),
				  TMath::Sqrt(PProton*PProton+MProton*MProton));
	lvPiMinus.SetPxPyPzE(PPion*TMath::Sin(ThetaPion)*TMath::Cos(PhiPion),
			     PPion*TMath::Sin(ThetaPion)*TMath::Sin(PhiPion),
			     PPion*TMath::Cos(ThetaPion),
			     TMath::Sqrt(PPion*PPion+MPion*MPion));
	lvTarget = lvRecoilProton + lvPiMinus - lvIncomingPhoton;
	lvInvariantSystem = lvRecoilProton + lvPiMinus;


    }

    return kTRUE;
}


void PiMinusProton::FillHistograms(){

	ProtonAnglesGCut->Fill(lvRecoilProton.Phi()*TMath::RadToDeg(),lvRecoilProton.Theta()*TMath::RadToDeg());
	PionAnglesGCut->Fill(lvPiMinus.Phi()*TMath::RadToDeg(),lvPiMinus.Theta()*TMath::RadToDeg());
	ProtonMomentumVsThetaGCut->Fill(lvRecoilProton.P(),lvRecoilProton.Theta()*TMath::RadToDeg());
	PionMomentumVsThetaGCut->Fill(lvPiMinus.P(),lvPiMinus.Theta()*TMath::RadToDeg());
	TargetMassGCut->Fill(lvTarget.M());
	InvariantMassVSTargetMassGCut->Fill(lvTarget.M(),lvInvariantSystem.M());
	InvariantMassVSEGammaGCut->Fill(lvIncomingPhoton.E(),lvInvariantSystem.M());
	TargetMassVSEGammaGCut->Fill(lvIncomingPhoton.E(),lvTarget.M());
}
