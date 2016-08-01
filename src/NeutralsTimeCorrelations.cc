#include "NeutralsTimeCorrelations.h"

NeutralsTimeCorrelations::NeutralsTimeCorrelations(){ 
    nTracks = new TH1F("nTracks","PreSelected events",11,-0.5,10.5);
    nTracks->GetXaxis()->SetTitle("Number of Tracks");

    nParticles = new TH1F("nParticles","PreSelected events",11,-0.5,10.5);
    nParticles->GetXaxis()->SetTitle("Number of Particles");

    TimeDiffBetweenNeutral = new TH1F("TimeDiffBetweenNeutral","Time correlation between the two neutral particles",201,-100.5,100.5);
    TimeDiffBetweenNeutral->GetXaxis()->SetTitle("time_1 - time_2 [ns]");

    TimeDiffSelectionBetweenNeutral = new TH1F("TimeDiffSelectionBetweenNeutral","Time correlation between the two charged particles",201,-100.5,100.5);
    TimeDiffSelectionBetweenNeutral->GetXaxis()->SetTitle("time_1 - time_2 [ns]");

    nIncomingPhotonsAll = new TH1F("nIncomingPhotonsAll","Tagger - All",101,-0.5,100.5);
    nIncomingPhotonsAll->GetXaxis()->SetTitle("Number of #gamma");

    nIncomingPhotonsInPromptPeak = new TH1F("nIncomingPhotonsInPromptPeak","Tagger - Prompt Peak",51,-0.5,50.5);
    nIncomingPhotonsInPromptPeak->GetXaxis()->SetTitle("Number of #gamma");

    timeIncomingPhotons = new TH1F("timeIncomingPhotons","Tagger - All",201,-100.5,100.5);
    timeIncomingPhotons->GetXaxis()->SetTitle("time  of #gamma [ns]");

    timeCorrelationIncomingPhotonVsNeutralParticlesAll = new TH2F("timeCorrelationIncomingPhotonVsNeutralParticlesAll"," Timing between incoming photons and final state neutral particles - All",301,-150.5,150.5,301,-150.5,150.5);
    timeCorrelationIncomingPhotonVsNeutralParticlesAll->GetXaxis()->SetTitle("time_#gamma - time_1 [ns]");
    timeCorrelationIncomingPhotonVsNeutralParticlesAll->GetYaxis()->SetTitle("time_#gamma - time_2 [ns]");

    energyIncomingPhotonsAll = new TH1F("energyIncomingPhotonsAll","Tagger - All",751,-0.5,1500.5);
    energyIncomingPhotonsAll->GetXaxis()->SetTitle("Energy [MeV]");

    CoplanarityAll = new TH1F("CoplanarityAll","Azimuthal correlation between Proton and PiNot",721.,-360.5,360.5);
    CoplanarityAll->GetXaxis()->SetTitle("#phi_#pi^0 - #phi_P [deg]");

    CoplanarityVsPhiProtonAll = new TH2F("CoplanarityVsPhiProtonAll","Azimuthal correlation between Proton and PiNot",361,-180.5,180.5,721.,-360.5,360.5);
    CoplanarityVsPhiProtonAll->GetXaxis()->SetTitle("#phi_P [deg]");
    CoplanarityVsPhiProtonAll->GetYaxis()->SetTitle("#phi_#pi^0 - #phi_P [deg]");

    CoplanarityVsInvariantMassAll = new TH2F("CoplanarityVsInvarianMassAll","Coplanarity (#pi^0 - P) [deg] Vs M(#gamma_1,#gamma_2) [MeV]",1500,0.5,1500.5,721,-360.5,360.5);
    CoplanarityVsInvariantMassAll->GetYaxis()->SetTitle("#phi_#pi^0 - #phi_P [deg]");
    CoplanarityVsInvariantMassAll->GetXaxis()->SetTitle("M(#gamma_1,#gamma_2) [MeV]");

    AzimuthalAnglesPhotonsAll = new TH2F("AzimuthalAnglesPhotons","#phi_1 - #phi_2 [deg] Vs #phi_1 [deg]", 361,-180.5,180.5,721.,-360.5,360.5);
    AzimuthalAnglesPhotonsAll->GetXaxis()->SetTitle("#phi_1 [deg]");
    AzimuthalAnglesPhotonsAll->GetYaxis()->SetTitle("#phi_1 - #phi_2 [deg]");

    EnergyPhoton1VsInvariantMassAll = new TH2F("EnergyPhoton1VsInvariantMassAll","E_#gamma_1 [MeV] Vs M(#gamma_1,#gamma_2) [MeV]",1500,0.5,1500.5,1500,0.5,1500.5);
    EnergyPhoton1VsInvariantMassAll->GetXaxis()->SetTitle("M(#gamma_1,#gamma_2) [MeV]");
    EnergyPhoton1VsInvariantMassAll->GetYaxis()->SetTitle("E_#gamma_1 [MeV]");

    EnergyPhoton2VsInvariantMassAll = new TH2F("EnergyPhoton2VsInvariantMassAll","E_#gamma_2 [MeV] Vs M(#gamma_1,#gamma_2) [MeV]",1500,0.5,1500.5,1500,0.5,1500.5);
    EnergyPhoton2VsInvariantMassAll->GetXaxis()->SetTitle("M(#gamma_1,#gamma_2) [MeV]");
    EnergyPhoton2VsInvariantMassAll->GetYaxis()->SetTitle("E_#gamma_2 [MeV]");

    DeltaEnergyPhotonsVsInvariantMassAll = new TH2F("DeltaEnergyPhotonsVsInvariantMassAll","E_#gamma_1 - E_#gamma_2 [MeV] Vs M(#gamma_1,#gamma_2) [MeV]",1001,-1001.,1001,1500,0.5,1500.5);
    DeltaEnergyPhotonsVsInvariantMassAll->GetYaxis()->SetTitle("E_#gamma_1 - E_#gamma_2 [MeV]");
    EnergyPhoton2VsInvariantMassAll->GetXaxis()->SetTitle("M(#gamma_1,#gamma_2) [MeV]");

    CoplanarityEGamma1Good = new TH1F("CoplanarityEGamma1Good","Azimuthal correlation between Proton and PiNot",721.,-360.5,360.5);
    CoplanarityEGamma1Good->GetXaxis()->SetTitle("#phi_#pi^0 - #phi_P [deg]");

    CoplanarityVsPhiProtonEGamma1Good = new TH2F("CoplanarityVsPhiProtonEGamma1Good","Azimuthal correlation between Proton and PiNot",361,-180.5,180.5,721.,-360.5,360.5);
    CoplanarityVsPhiProtonEGamma1Good->GetXaxis()->SetTitle("#phi_P [deg]");
    CoplanarityVsPhiProtonEGamma1Good->GetYaxis()->SetTitle("#phi_#pi^0 - #phi_P [deg]");

    CoplanarityVsInvariantMassEGamma1Good = new TH2F("CoplanarityVsInvarianMassEGamma1Good","Coplanarity (#pi^0 - P) [deg] Vs M(#gamma_1,#gamma_2) [MeV]",1500,0.5,1500.5,721,-360.5,360.5);
    CoplanarityVsInvariantMassEGamma1Good->GetYaxis()->SetTitle("#phi_#pi^0 - #phi_P [deg]");
    CoplanarityVsInvariantMassEGamma1Good->GetXaxis()->SetTitle("M(#gamma_1,#gamma_2) [MeV]");

    AzimuthalAnglesPhotonsEGamma1Good = new TH2F("AzimuthalAnglesPhotons","#phi_1 - #phi_2 [deg] Vs #phi_1 [deg]", 361,-180.5,180.5,721.,-360.5,360.5);
    AzimuthalAnglesPhotonsEGamma1Good->GetXaxis()->SetTitle("#phi_1 [deg]");
    AzimuthalAnglesPhotonsEGamma1Good->GetYaxis()->SetTitle("#phi_1 - #phi_2 [deg]");

    EnergyPhoton1VsInvariantMassEGamma1Good = new TH2F("EnergyPhoton1VsInvariantMassEGamma1Good","E_#gamma_1 [MeV] Vs M(#gamma_1,#gamma_2) [MeV]",1500,0.5,1500.5,1500,0.5,1500.5);
    EnergyPhoton1VsInvariantMassEGamma1Good->GetXaxis()->SetTitle("M(#gamma_1,#gamma_2) [MeV]");
    EnergyPhoton1VsInvariantMassEGamma1Good->GetYaxis()->SetTitle("E_#gamma_1 [MeV]");

    EnergyPhoton2VsInvariantMassEGamma1Good = new TH2F("EnergyPhoton2VsInvariantMassEGamma1Good","E_#gamma_2 [MeV] Vs M(#gamma_1,#gamma_2) [MeV]",1500,0.5,1500.5,1500,0.5,1500.5);
    EnergyPhoton2VsInvariantMassEGamma1Good->GetXaxis()->SetTitle("M(#gamma_1,#gamma_2) [MeV]");
    EnergyPhoton2VsInvariantMassEGamma1Good->GetYaxis()->SetTitle("E_#gamma_2 [MeV]");

    DeltaEnergyPhotonsVsInvariantMassEGamma1Good = new TH2F("DeltaEnergyPhotonsVsInvariantMassEGamma1Good","E_#gamma_1 - E_#gamma_2 [MeV] Vs M(#gamma_1,#gamma_2) [MeV]",1001,-1001.,1001,1500,0.5,1500.5);
    DeltaEnergyPhotonsVsInvariantMassEGamma1Good->GetYaxis()->SetTitle("E_#gamma_1 - E_#gamma_2 [MeV]");
    EnergyPhoton2VsInvariantMassEGamma1Good->GetXaxis()->SetTitle("M(#gamma_1,#gamma_2) [MeV]");

    CoplanarityEGamma1Bad = new TH1F("CoplanarityEGamma1Bad","Azimuthal correlation between Proton and PiNot",721.,-360.5,360.5);
    CoplanarityEGamma1Bad->GetXaxis()->SetTitle("#phi_#pi^0 - #phi_P [deg]");

    CoplanarityVsPhiProtonEGamma1Bad = new TH2F("CoplanarityVsPhiProtonEGamma1Bad","Azimuthal correlation between Proton and PiNot",361,-180.5,180.5,721.,-360.5,360.5);
    CoplanarityVsPhiProtonEGamma1Bad->GetXaxis()->SetTitle("#phi_P [deg]");
    CoplanarityVsPhiProtonEGamma1Bad->GetYaxis()->SetTitle("#phi_#pi^0 - #phi_P [deg]");

    CoplanarityVsInvariantMassEGamma1Bad = new TH2F("CoplanarityVsInvarianMassEGamma1Bad","Coplanarity (#pi^0 - P) [deg] Vs M(#gamma_1,#gamma_2) [MeV]",1500,0.5,1500.5,721,-360.5,360.5);
    CoplanarityVsInvariantMassEGamma1Bad->GetYaxis()->SetTitle("#phi_#pi^0 - #phi_P [deg]");
    CoplanarityVsInvariantMassEGamma1Bad->GetXaxis()->SetTitle("M(#gamma_1,#gamma_2) [MeV]");

    AzimuthalAnglesPhotonsEGamma1Bad = new TH2F("AzimuthalAnglesPhotons","#phi_1 - #phi_2 [deg] Vs #phi_1 [deg]", 361,-180.5,180.5,721.,-360.5,360.5);
    AzimuthalAnglesPhotonsEGamma1Bad->GetXaxis()->SetTitle("#phi_1 [deg]");
    AzimuthalAnglesPhotonsEGamma1Bad->GetYaxis()->SetTitle("#phi_1 - #phi_2 [deg]");

    EnergyPhoton1VsInvariantMassEGamma1Bad = new TH2F("EnergyPhoton1VsInvariantMassEGamma1Bad","E_#gamma_1 [MeV] Vs M(#gamma_1,#gamma_2) [MeV]",1500,0.5,1500.5,1500,0.5,1500.5);
    EnergyPhoton1VsInvariantMassEGamma1Bad->GetXaxis()->SetTitle("M(#gamma_1,#gamma_2) [MeV]");
    EnergyPhoton1VsInvariantMassEGamma1Bad->GetYaxis()->SetTitle("E_#gamma_1 [MeV]");

    EnergyPhoton2VsInvariantMassEGamma1Bad = new TH2F("EnergyPhoton2VsInvariantMassEGamma1Bad","E_#gamma_2 [MeV] Vs M(#gamma_1,#gamma_2) [MeV]",1500,0.5,1500.5,1500,0.5,1500.5);
    EnergyPhoton2VsInvariantMassEGamma1Bad->GetXaxis()->SetTitle("M(#gamma_1,#gamma_2) [MeV]");
    EnergyPhoton2VsInvariantMassEGamma1Bad->GetYaxis()->SetTitle("E_#gamma_2 [MeV]");

    DeltaEnergyPhotonsVsInvariantMassEGamma1Bad = new TH2F("DeltaEnergyPhotonsVsInvariantMassEGamma1Bad","E_#gamma_1 - E_#gamma_2 [MeV] Vs M(#gamma_1,#gamma_2) [MeV]",1001,-1001.,1001,1500,0.5,1500.5);
    DeltaEnergyPhotonsVsInvariantMassEGamma1Bad->GetYaxis()->SetTitle("E_#gamma_1 - E_#gamma_2 [MeV]");
    EnergyPhoton2VsInvariantMassEGamma1Bad->GetXaxis()->SetTitle("M(#gamma_1,#gamma_2) [MeV]");

}
NeutralsTimeCorrelations::~NeutralsTimeCorrelations(){
}

Bool_t NeutralsTimeCorrelations::Init(){
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
  nBadTimeCorrelationBetweenNeutralParticles = 0;


  nEneG1TooLow=0;

  IndexIncomingPhoton = -999; // negative index has no meaning

  return kTRUE;
}

Bool_t NeutralsTimeCorrelations::Start(){
  cout << "=== NeutralsTimeCorrelations::Start() " << endl;
  if(!IsGoATFile()){
    cout << "ERROR: Input File is not a GoAT file." << endl;
    return kFALSE;
  }
  SetAsPhysicsFile();
  TraverseValidEvents();
  return kTRUE;
}

void NeutralsTimeCorrelations::ProcessEvent(){
    if(CheckInitialConditions()){
	if((GetPhotons()->GetNParticles()==2)&&(GetRootinos()->GetNParticles()==1)){
// inizia l'analisi del pi0 p 
	    Bool_t IsEGammma1Good = BuildPiNot();
	    FindRecoilProton();
	    CoplanarityAll->Fill((lvInvariantSystem.Phi()-lvRecoilProton.Phi())*TMath::RadToDeg());
	    CoplanarityVsPhiProtonAll->Fill(lvRecoilProton.Phi()*TMath::RadToDeg(),(lvInvariantSystem.Phi()-lvRecoilProton.Phi())*TMath::RadToDeg());
	    CoplanarityVsInvariantMassAll->Fill(lvInvariantSystem.M(),(lvInvariantSystem.Phi()-lvRecoilProton.Phi())*TMath::RadToDeg());
	    if (IsEGammma1Good){
		CoplanarityEGamma1Good->Fill((lvInvariantSystem.Phi()-lvRecoilProton.Phi())*TMath::RadToDeg());
		CoplanarityVsPhiProtonEGamma1Good->Fill(lvRecoilProton.Phi()*TMath::RadToDeg(),(lvInvariantSystem.Phi()-lvRecoilProton.Phi())*TMath::RadToDeg());
		CoplanarityVsInvariantMassEGamma1Good->Fill(lvInvariantSystem.M(),(lvInvariantSystem.Phi()-lvRecoilProton.Phi())*TMath::RadToDeg());
		AzimuthalAnglesPhotonsEGamma1Good->Fill((lvGamma1.Phi()-lvGamma2.Phi())*TMath::RadToDeg(),lvGamma1.Phi()*TMath::RadToDeg());
		EnergyPhoton1VsInvariantMassEGamma1Good->Fill(lvInvariantSystem.M(),lvGamma1.E());
		EnergyPhoton2VsInvariantMassEGamma1Good->Fill(lvInvariantSystem.M(),lvGamma2.E());
		DeltaEnergyPhotonsVsInvariantMassEGamma1Good->Fill(lvInvariantSystem.M(),lvGamma1.E()-lvGamma2.E());
	    } else {
		CoplanarityEGamma1Bad->Fill((lvInvariantSystem.Phi()-lvRecoilProton.Phi())*TMath::RadToDeg());
		CoplanarityVsPhiProtonEGamma1Bad->Fill(lvRecoilProton.Phi()*TMath::RadToDeg(),(lvInvariantSystem.Phi()-lvRecoilProton.Phi())*TMath::RadToDeg());
		CoplanarityVsInvariantMassEGamma1Bad->Fill(lvInvariantSystem.M(),(lvInvariantSystem.Phi()-lvRecoilProton.Phi())*TMath::RadToDeg());
		AzimuthalAnglesPhotonsEGamma1Bad->Fill((lvGamma1.Phi()-lvGamma2.Phi())*TMath::RadToDeg(),lvGamma1.Phi()*TMath::RadToDeg());
		EnergyPhoton1VsInvariantMassEGamma1Bad->Fill(lvInvariantSystem.M(),lvGamma1.E());
		EnergyPhoton2VsInvariantMassEGamma1Bad->Fill(lvInvariantSystem.M(),lvGamma2.E());
		DeltaEnergyPhotonsVsInvariantMassEGamma1Bad->Fill(lvInvariantSystem.M(),lvGamma1.E()-lvGamma2.E());


	    }
	    if (CheckNeutralCorrelation(1,3)){
		TimeDiffSelectionBetweenNeutral->Fill(GetPhotons()->GetTime(0) - GetPhotons()->GetTime(1));
		if (CheckTagger()){
//		    FillHistograms();
		    evtNum++;
		}  // close CheckTagger
	    } // close CheckNeutralCorrelation
	} // fine analis del pi0 p
    } // close Check GoAT preselection
}  



void NeutralsTimeCorrelations::ProcessScalerRead(){
/*
  // Fill Tagger Scalers
  //  FillScalers(GetTC_scaler_min(),GetTC_scaler_max(),TaggerAccScal);
*/
  PPhysics::ProcessScalerRead();
}

Bool_t	NeutralsTimeCorrelations::Write(){
    cout << "NeutralsTimeCorrelations::Write() " << endl;
    return GTreeManager::Write();
}


// *********************************************************
Bool_t NeutralsTimeCorrelations::CheckInitialConditions(){
    Int_t NTracks = GetTracks()->GetNTracks();
    if (NTracks <2){
	cout << " EvtNumber: " << evtNum  <<  " Number of Tracks : " <<  NTracks  << endl;
	nIncompatibleWithGoat++;
	return kFALSE;
    } else {
	nTracks->Fill(NTracks);
    }

    Int_t NNeutralParticles = GetPhotons()->GetNParticles();
    if (NNeutralParticles <2){
	cout << " EvtNumber: " << evtNum  <<  " NNeutralParticles = " << NNeutralParticles << endl;
	nIncompatibleWithGoat++;
	return kFALSE;
    } else {
	nParticles->Fill(NNeutralParticles);
    }
    return kTRUE;
}


Bool_t NeutralsTimeCorrelations::CheckNeutralCorrelation(Int_t Index1, Int_t Index2){
    Double_t TimeDiff = GetPhotons()->GetTime(0) - GetPhotons()->GetTime(1);
	TimeDiffBetweenNeutral->Fill(TimeDiff);
	return kTRUE;
}

Bool_t NeutralsTimeCorrelations::CheckTagger(){

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
	Double_t XValue = GetTagger()->GetTaggedTime(IndexIncomingPhoton)-GetPhotons()->GetTime(0); // time correlation IncomingPhoton - Charged0
	Double_t YValue = GetTagger()->GetTaggedTime(IndexIncomingPhoton)-GetPhotons()->GetTime(1); // time correlation IncomingPhoton - Charged1
	timeCorrelationIncomingPhotonVsNeutralParticlesAll->Fill(XValue,YValue);
	return kTRUE;
    } else {
	if(NPhotonsInTime<1){
	    nNoPhotonsInPromptPeak++;
	} else {
	    nTooManyPhotonsInPromptPeak++;
	}
	return kFALSE;
    }
    
}

void NeutralsTimeCorrelations::FillHistograms(){
/*
	ProtonAnglesGCut->Fill(lvRecoilProton.Phi()*TMath::RadToDeg(),lvRecoilProton.Theta()*TMath::RadToDeg());
	PionAnglesGCut->Fill(lvPiMinus.Phi()*TMath::RadToDeg(),lvPiMinus.Theta()*TMath::RadToDeg());
	ProtonMomentumVsThetaGCut->Fill(lvRecoilProton.P(),lvRecoilProton.Theta()*TMath::RadToDeg());
	PionMomentumVsThetaGCut->Fill(lvPiMinus.P(),lvPiMinus.Theta()*TMath::RadToDeg());
	TargetMassGCut->Fill(lvTarget.M());
	InvariantMassVSTargetMassGCut->Fill(lvTarget.M(),lvInvariantSystem.M());
	InvariantMassVSEGammaGCut->Fill(lvIncomingPhoton.E(),lvInvariantSystem.M());
	TargetMassVSEGammaGCut->Fill(lvIncomingPhoton.E(),lvTarget.M());
*/
}

Bool_t NeutralsTimeCorrelations::BuildPiNot(){

    Double_t Ene1 = GetPhotons()->GetClusterEnergy(0);
    Double_t Theta1 = GetPhotons()->GetTheta(0)*TMath::DegToRad();
    Double_t Phi1 = GetPhotons()->GetPhi(0)*TMath::DegToRad();
    
    Double_t Ene2 = GetPhotons()->GetClusterEnergy(1);
    Double_t Theta2 = GetPhotons()->GetTheta(1)*TMath::DegToRad();
    Double_t Phi2 = GetPhotons()->GetPhi(1)*TMath::DegToRad();

    lvGamma1.SetPxPyPzE(Ene1*TMath::Sin(Theta1)*TMath::Cos(Phi1),
			Ene1*TMath::Sin(Theta1)*TMath::Sin(Phi1),
			Ene1*TMath::Cos(Theta1),Ene1);

    lvGamma2.SetPxPyPzE(Ene2*TMath::Sin(Theta2)*TMath::Cos(Phi2),
			Ene2*TMath::Sin(Theta2)*TMath::Sin(Phi2),
			Ene2*TMath::Cos(Theta2),Ene2);

    lvInvariantSystem = lvGamma1 + lvGamma2;

    AzimuthalAnglesPhotonsAll->Fill((lvGamma1.Phi()-lvGamma2.Phi())*TMath::RadToDeg(),lvGamma1.Phi()*TMath::RadToDeg());
    
    EnergyPhoton1VsInvariantMassAll->Fill(lvInvariantSystem.M(),lvGamma1.E());
    EnergyPhoton2VsInvariantMassAll->Fill(lvInvariantSystem.M(),lvGamma2.E());
    DeltaEnergyPhotonsVsInvariantMassAll->Fill(lvInvariantSystem.M(),lvGamma1.E()-lvGamma2.E());

    if(lvGamma1.E()<70.){
	nEneG1TooLow++;
	return kFALSE;
    } else {
	return kTRUE;
    }

}

void NeutralsTimeCorrelations::FindRecoilProton(){
    Double_t TKin = GetRootinos()->GetClusterEnergy(0);
    Double_t Theta = GetRootinos()->GetTheta(0)*TMath::DegToRad();
    Double_t Phi = GetRootinos()->GetPhi(0)*TMath::DegToRad();
    Double_t Ene = TKin + ProtonMass;
    Double_t Momentum = TMath::Sqrt(Ene*Ene - ProtonMass*ProtonMass);
    lvRecoilProton.SetPxPyPzE(Momentum*TMath::Sin(Theta)*TMath::Cos(Phi),
			Momentum*TMath::Sin(Theta)*TMath::Sin(Phi),
			Momentum*TMath::Cos(Theta),Ene);
    
}
