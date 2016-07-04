#include "PiMinusProton.h"

PiMinusProton::PiMinusProton(){ 
    tracks = new TH1F("Number of tracks","tracks",11,-0.5,10.5);
    particles = new TH1F("Number of particles","particles",11,-0.5,10.5);
    coplanarity = new TH2F("CoplanarityVsPhi1","(#phi_0 - #phi_1) [deg] Vs #phi_1 [deg]",361,-180.5,180.5,721.,-360.5,360.5);
    coplanarity_tagliato = new TH2F("CoplanarityVsPhi1_Tagliato","(#phi_0 - #phi_1) [deg] Vs #phi_1 [deg]",361,-180.5,180.5,721.,-360.5,360.5);
    timediff = new TH1F("timediff","Time difference between the two charged particles [ns]",201,-100.5,100.5);
    timediff_tagliato = new TH1F("timediff_tagliato","Time difference between the two charged particles [ns]",201,-100.5,100.5);
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
  nBadCoplanarity = 0;
  nBadTimeCorrelationBetweenChargedParticles = 0;

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
	    coplanarity_tagliato->Fill(GetRootinos()->GetPhi(1),GetRootinos()->GetPhi(0)-GetRootinos()->GetPhi(1));
	    timediff_tagliato->Fill(GetRootinos()->GetTime(0) - GetRootinos()->GetTime(1));
	    evtNum++;
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
	tracks->Fill(NTracks);
    }

    Int_t NChargedParticles = GetRootinos()->GetNParticles();
    if (NChargedParticles != 2){
	cout << " EvtNumber: " << evtNum  <<  " NChargedParticles = " << NChargedParticles << endl;
	nIncompatibleWithGoat++;
	return kFALSE;
    } else {
	particles->Fill(NChargedParticles);
    }
    return kTRUE;
}


/*Bool_t PiMinusProton::CheckCoplanarity(Int_t NSigma)
{
    Double_t copl = GetRootinos()->GetPhi(0) - GetRootinos()->GetPhi(1);
    coplanarity->Fill(GetRootinos()->GetPhi(1),copl);
    Double_t sigma_copl = 25.; // Fissato ad occhio. Cerca di ottimizzarlo con un fit!!!
    cout << " printami il taglio " << NSigma*sigma_copl << endl;
    if ((TMath::Abs(copl)>180.-1.*NSigma*sigma_copl)&&(TMath::Abs(copl)<180.+NSigma*sigma_copl)){
	return kTRUE;
    } else {
	return kFALSE;
    }
}
*/

Bool_t PiMinusProton::CheckChargedCorrelation(Int_t NSigmaCoplanarity, Int_t NSigmaTime){
    Double_t copl = GetRootinos()->GetPhi(0) - GetRootinos()->GetPhi(1);
    coplanarity->Fill(GetRootinos()->GetPhi(1),copl);
    Double_t sigma_copl = 25.; // Fissato ad occhio. Cerca di ottimizzarlo con un fit!!!
    if ((TMath::Abs(copl)>180.-1.*NSigmaCoplanarity*sigma_copl)&&(TMath::Abs(copl)<180.+NSigmaCoplanarity*sigma_copl)){
	Double_t TimeDiff = GetRootinos()->GetTime(0) - GetRootinos()->GetTime(1);
	timediff->Fill(TimeDiff);
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
