void RenameGoAT(TString sFile){
  
  TFile fOld(sFile,"READ");

  // Acqu Trees
  TTree *taggerOld = (TTree*)fOld.Get("treeTagger");
  TTree *tracksOld = (TTree*)fOld.Get("treeRawEvent");
  TTree *detectorHitsOld = (TTree*)fOld.Get("treeDetectorHits");
  TTree *linPolOld = (TTree*)fOld.Get("treeLinPol");
  TTree *triggerOld = (TTree*)fOld.Get("treeTrigger");
  TTree *scalerOld = (TTree*)fOld.Get("treeScaler");

  // GoAT Trees
  TTree *eventParametersOld = (TTree*)fOld.Get("treeEventParameters");
  TTree *rootinosOld = (TTree*)fOld.Get("rootino");
  TTree *photonsOld = (TTree*)fOld.Get("gamma");
  TTree *electronsOld = (TTree*)fOld.Get("e-");
  TTree *chargedPionsOld = (TTree*)fOld.Get("pi+");
  TTree *protonsOld = (TTree*)fOld.Get("proton");
  TTree *neutronsOld = (TTree*)fOld.Get("neutron");
  TTree *neutralPionsOld = (TTree*)fOld.Get("pi0");
  TTree *etasOld = (TTree*)fOld.Get("eta");
  TTree *etaPrimesOld = (TTree*)fOld.Get("eta'");

  sFile.ReplaceAll(".root","_renamed.root");
  TFile fNew(sFile,"RECREATE");

  if(taggerOld){
    Int_t nTagged = 0;
    Double_t *taggedEnergy  = new Double_t[1024];
    Int_t *taggedChannel    = new Int_t[1024];
    Double_t *taggedTime    = new Double_t[1024];

    TTree *tagger = new TTree("tagger", "tagger");

    if(taggerOld->GetBranch("nTagged")){
      taggerOld->SetBranchAddress("nTagged", &nTagged);
      tagger->Branch("nTagged", &nTagged,"nTagged/I");
      if(taggerOld->GetBranch("photonbeam_E")){
	taggerOld->SetBranchAddress("photonbeam_E", taggedEnergy);
	tagger->Branch("taggedEnergy", taggedEnergy, "taggedEnergy[nTagged]/D");
      }
      if(taggerOld->GetBranch("tagged_ch")){
	taggerOld->SetBranchAddress("tagged_ch", taggedChannel);
	tagger->Branch("taggedChannel", taggedChannel, "taggedChannel[nTagged]/I");
      }
      if(taggerOld->GetBranch("tagged_t")){
	taggerOld->SetBranchAddress("tagged_t", taggedTime);
	tagger->Branch("taggedTime", taggedTime, "taggedTime[nTagged]/D");
      }
    }

    for(Int_t i=0; i<taggerOld->GetEntries(); i++){
      taggerOld->GetEvent(i);
      tagger->Fill();
    }
    tagger->Write();
  }

  if(tracksOld){
    Int_t nTracks = 0;
    Double_t *clusterEnergy = new Double_t[128];
    Double_t *theta         = new Double_t[128];
    Double_t *phi           = new Double_t[128];
    Double_t *time          = new Double_t[128];
    UChar_t *clusterSize    = new UChar_t[128];
    Int_t *centralCrystal   = new Int_t[128];
    Int_t *centralVeto      = new Int_t[128];
    UChar_t *apparatus      = new UChar_t[128];
    Double_t *vetoEnergy    = new Double_t[128];
    Double_t *MWPC0Energy   = new Double_t[128];
    Double_t *MWPC1Energy   = new Double_t[128];

    TTree *tracks = new TTree("tracks", "tracks");

    if(tracksOld->GetBranch("nParticles")){
      tracksOld->SetBranchAddress("nParticles", &nTracks);
      tracks->Branch("nTracks", &nTracks, "nTracks/I");
      if(tracksOld->GetBranch("Ek")){
	tracksOld->SetBranchAddress("Ek", clusterEnergy);
	tracks->Branch("clusterEnergy", clusterEnergy, "clusterEnergy[nTracks]/D");
      }
      if(tracksOld->GetBranch("Theta")){
	tracksOld->SetBranchAddress("Theta", theta);
	tracks->Branch("theta", theta, "theta[nTracks]/D");
      }
      if(tracksOld->GetBranch("Phi")){
	tracksOld->SetBranchAddress("Phi", phi);
	tracks->Branch("phi", phi, "phi[nTracks]/D");
      }
      if(tracksOld->GetBranch("time")){
	tracksOld->SetBranchAddress("time", time);
	tracks->Branch("time", time, "time[nTracks]/D");
      }
      if(tracksOld->GetBranch("clusterSize")){
	tracksOld->SetBranchAddress("clusterSize", clusterSize);
	tracks->Branch("clusterSize", clusterSize, "clusterSize[nTracks]/b");
      }
      if(tracksOld->GetBranch("centralCrys")){
	tracksOld->SetBranchAddress("centralCrys", centralCrystal);
	tracks->Branch("centralCrystal", centralCrystal, "centralCrystal[nTracks]/I");
      }
      if(tracksOld->GetBranch("centralVeto")){
	tracksOld->SetBranchAddress("centralVeto", centralVeto);
	tracks->Branch("centralVeto", centralVeto, "centralVeto[nTracks]/I");
      }
      if(tracksOld->GetBranch("Apparatus")){
	tracksOld->SetBranchAddress("Apparatus", apparatus);
	tracks->Branch("apparatus", apparatus, "apparatus[nTracks]/b");
      }
      if(tracksOld->GetBranch("d_E")){
	tracksOld->SetBranchAddress("d_E", vetoEnergy);
	tracks->Branch("vetoEnergy", vetoEnergy, "vetoEnergy[nTracks]/D");
      }
      if(tracksOld->GetBranch("WC0_E")){
	tracksOld->SetBranchAddress("WC0_E", MWPC0Energy);
	tracks->Branch("MWPC0Energy", MWPC0Energy, "MWPC0Energy[nTracks]/D");
      }
      if(tracksOld->GetBranch("WC1_E")){
	tracksOld->SetBranchAddress("WC1_E", MWPC1Energy);
	tracks->Branch("MWPC1Energy", MWPC1Energy, "MWPC1Energy[nTracks]/D");
      }
    }

    for(Int_t i=0; i<tracksOld->GetEntries(); i++){
      tracksOld->GetEvent(i);
      tracks->Fill();
    }
    tracks->Write();
  }

  if(detectorHitsOld){
    Int_t nNaIHits = 0;
    Int_t *NaIHits	  = new Int_t[860];
    Int_t *NaICluster       = new Int_t[860];
    Int_t nPIDHits = 0;
    Int_t *PIDHits	  = new Int_t[860];
    Int_t nMWPCHits = 0;
    Int_t *MWPCHits	  = new Int_t[860];
    Int_t nBaF2PbWO4Hits = 0;
    Int_t *BaF2PbWO4Hits	  = new Int_t[860];
    Int_t *BaF2PbWO4Cluster = new Int_t[860];
    Int_t nVetoHits = 0;
    Int_t *VetoHits         = new Int_t[860];
	
    TTree *detectorHits = new TTree("detectorHits", "detectorHits");

    if(detectorHitsOld->GetBranch("nNaI_Hits")){
      detectorHitsOld->SetBranchAddress("nNaI_Hits", &nNaIHits);
      detectorHits->Branch("nNaIHits", &nNaIHits, "nNaIHits/I");
      if(detectorHitsOld->GetBranch("NaI_Hits")){
	detectorHitsOld->SetBranchAddress("NaI_Hits", NaIHits);
	detectorHits->Branch("NaIHits", NaIHits, "NaIHits[nNaIHits]/I");
      }
      if(detectorHitsOld->GetBranch("NaI_Cluster")){
	detectorHitsOld->SetBranchAddress("NaI_Cluster", NaICluster);
	detectorHits->Branch("NaICluster", NaICluster, "NaICluster[nNaIHits]/I");
      }
    }
    if(detectorHitsOld->GetBranch("nPID_Hits")){
      detectorHitsOld->SetBranchAddress("nPID_Hits", &nPIDHits);
      detectorHits->Branch("nPIDHits", &nPIDHits, "nPIDHits/I");
      if(detectorHitsOld->GetBranch("PID_Hits")){
	detectorHitsOld->SetBranchAddress("PID_Hits", PIDHits);
	detectorHits->Branch("PIDHits", PIDHits, "PIDHits[nPIDHits]/I");
      }
    }
    if(detectorHitsOld->GetBranch("nWC_Hits")){
      detectorHitsOld->SetBranchAddress("nWC_Hits", &nMWPCHits);
      detectorHits->Branch("nMWPCHits", &nMWPCHits, "nMWPCHits/I");
      if(detectorHitsOld->GetBranch("WC_Hits")){
	detectorHitsOld->SetBranchAddress("WC_Hits", MWPCHits);
	detectorHits->Branch("MWPCHits", MWPCHits, "MWPCHits[nMWPCHits]/I");
      }
    }
    if(detectorHitsOld->GetBranch("nBaF2_PbWO4_Hits")){
      detectorHitsOld->SetBranchAddress("nBaF2_PbWO4_Hits", &nBaF2PbWO4Hits);
      detectorHits->Branch("nBaF2PbWO4Hits", &nBaF2PbWO4Hits, "nBaF2PbWO4Hits/I");
      if(detectorHitsOld->GetBranch("BaF2_PbWO4_Hits")){
	detectorHitsOld->SetBranchAddress("BaF2_PbWO4_Hits", BaF2PbWO4Hits);
	detectorHits->Branch("BaF2PbWO4Hits", BaF2PbWO4Hits, "BaF2PbWO4Hits[nBaF2PbWO4Hits]/I");
      }
      if(detectorHitsOld->GetBranch("BaF2_PbWO4_Cluster")){
	detectorHitsOld->SetBranchAddress("BaF2_PbWO4_Cluster", BaF2PbWO4Cluster);
	detectorHits->Branch("BaF2PbWO4Cluster", BaF2PbWO4Cluster, "BaF2PbWO4Cluster[nBaF2PbWO4Hits]/I");
      }
    }
    if(detectorHitsOld->GetBranch("nVeto_Hits")){
      detectorHitsOld->SetBranchAddress("nVeto_Hits", &nVetoHits);
      detectorHits->Branch("nVetoHits", &nVetoHits, "nVetoHits/I");
      if(detectorHitsOld->GetBranch("Veto_Hits")){
	detectorHitsOld->SetBranchAddress("Veto_Hits", VetoHits);
	detectorHits->Branch("VetoHits", VetoHits, "VetoHits[nVetoHits]/I");
      }
    }

    for(Int_t i=0; i<detectorHitsOld->GetEntries(); i++){
      detectorHitsOld->GetEvent(i);
      detectorHits->Fill();
    }
    detectorHits->Write();
  }

  if(linPolOld){
    Int_t plane = 0;
    Double_t edge = 0;
    Double_t edgeSetting = 0;
    Double_t *polarizationTable = new Double_t[352];
    Double_t *enhancementTable  = new Double_t[352];

    TTree *linPol = new TTree("linPol", "linPol");

    if(linPolOld->GetBranch("plane")){
      linPolOld->SetBranchAddress("plane", &plane);
      linPol->Branch("plane", &plane, "plane/I");
    }
    if(linPolOld->GetBranch("edge")){
      linPolOld->SetBranchAddress("edge", &edge);
      linPol->Branch("edge", &edge, "edge/D");
    }
    if(linPolOld->GetBranch("edgeSetting")){
      linPolOld->SetBranchAddress("edgeSetting", &edgeSetting);
      linPol->Branch("edgeSetting", &edgeSetting, "edgeSetting/D");
    }
    if(linPolOld->GetBranch("polTable")){
      linPolOld->SetBranchAddress("polTable", polarizationTable);
      linPol->Branch("polarizationTable", polarizationTable, "polarizationTable[352]/D");
    }
    if(linPolOld->GetBranch("enhTable")){
      linPolOld->SetBranchAddress("enhTable", enhancementTable);
      linPol->Branch("enhancementTable", enhancementTable, "enhancementTable[352]/D");
    }

    for(Int_t i=0; i<linPolOld->GetEntries(); i++){
      linPolOld->GetEvent(i);
      linPol->Fill();
    }
    linPol->Write();
  }

  if(triggerOld){
    Double_t energySum = 0;
    Int_t multiplicity = 0;
    Bool_t helicity = false;
    Int_t nErrors = 0;
    Int_t nErrors = 0;
    Int_t *errorModuleID    = new Int_t[300];
    Int_t *errorModuleIndex = new Int_t[300];
    Int_t *errorCode        = new Int_t[300];
    Int_t nTriggerPattern = 0;
    Int_t *triggerPattern   = new Int_t[32];

    TTree *trigger = new TTree("trigger", "trigger");

    if(triggerOld->GetBranch("ESum")){
      triggerOld->SetBranchAddress("ESum", &energySum);
      trigger->Branch("energySum", &energySum, "energySum/D");
    }
    if(triggerOld->GetBranch("Mult")){
      triggerOld->SetBranchAddress("Mult", &multiplicity);
      trigger->Branch("multiplicity", &multiplicity, "multiplicity/I");
    }
    if(triggerOld->GetBranch("Helicity")){
      triggerOld->SetBranchAddress("Helicity", &helicity);
      trigger->Branch("helicity", &helicity, "helicity/O");
    }
    if(triggerOld->GetBranch("nError")){
      triggerOld->SetBranchAddress("nError", &nErrors);
      trigger->Branch("nErrors", &nErrors, "nErrors/I");
      if(triggerOld->GetBranch("ErrModID")){
	triggerOld->SetBranchAddress("ErrModID", errorModuleID);
	trigger->Branch("errorModuleID", errorModuleID, "errorModuleID[nErrors]/I");
      }
      if(triggerOld->GetBranch("ErrModIndex")){
	triggerOld->SetBranchAddress("ErrModIndex", errorModuleIndex);
	trigger->Branch("errorModuleIndex", errorModuleIndex, "errorModuleIndex[nErrors]/I");
      }
      if(triggerOld->GetBranch("ErrCode")){
	triggerOld->SetBranchAddress("ErrCode", errorCode);
	trigger->Branch("errorCode", errorCode, "errorCode[nErrors]/I");
      }
    }
    if(triggerOld->GetBranch("nTriggerPattern")){
      triggerOld->SetBranchAddress("nTriggerPattern", &nTriggerPattern);
      trigger->Branch("nTriggerPattern", &nTriggerPattern, "nTriggerPattern/I");
      if(triggerOld->GetBranch("TriggerPattern")){
	triggerOld->SetBranchAddress("TriggerPattern", triggerPattern);
	trigger->Branch("triggerPattern", triggerPattern, "triggerPattern[nTriggerPattern]/I");
      }
    }

    for(Int_t i=0; i<triggerOld->GetEntries(); i++){
      triggerOld->GetEvent(i);
      trigger->Fill();
    }
    trigger->Write();
  }

  if(scalerOld){
    TString sScaler = scalerOld->GetBranch("Scaler")->GetTitle();
    sScaler.Remove(0,sScaler.First("[")+1);
    sScaler.Remove(sScaler.First("]"));
    const Int_t nScaler = sScaler.Atoi();
    Char_t str[256];
    sprintf(str, "scalers[%d]/i", nScaler);

    Int_t eventNumber = 0;
    Int_t eventID = 0;
    UInt_t *scalers = new UInt_t[nScaler];

    TTree *scaler = new TTree("scaler", "scaler");
    
    if(scalerOld->GetBranch("eventNumber")){
      scalerOld->SetBranchAddress("eventNumber", &eventNumber);
      scaler->Branch("eventNumber", &eventNumber, "eventNumber/I");
    }
    if(scalerOld->GetBranch("eventID")){
      scalerOld->SetBranchAddress("eventID", &eventID);
      scaler->Branch("eventID", &eventID, "eventID/I");
    }
    if(scalerOld->GetBranch("Scaler")){
      scalerOld->SetBranchAddress("Scaler", scalers);
      scaler->Branch("scalers", scalers, str);
    }

    for(Int_t i=0; i<scalerOld->GetEntries(); i++){
      scalerOld->GetEvent(i);
      scaler->Fill();
    }
    scaler->Write();
  }

  if(eventParametersOld){
    UInt_t eventNumber2 = 0;
    UChar_t nReconstructed = 0;

    TTree *eventParameters = new TTree("eventParameters", "eventParameters");

    if(eventParametersOld->GetBranch("EventNumber")){
      eventParametersOld->SetBranchAddress("EventNumber", &eventNumber2);
      eventParameters->Branch("eventNumber", &eventNumber2, "eventNumber/i");
    }
    if(eventParametersOld->GetBranch("nReconstructed")){
      eventParametersOld->SetBranchAddress("nReconstructed", &nReconstructed);
      eventParameters->Branch("nReconstructed", &nReconstructed, "nReconstructed/b");
    }

    for(Int_t i=0; i<eventParametersOld->GetEntries(); i++){
      eventParametersOld->GetEvent(i);
      eventParameters->Fill();
    }
    eventParameters->Write();
  }

  if(rootinosOld){
    rootinosOld->SetName("rootinos");
    rootinosOld->SetTitle("rootinos");
    TTree *rootinos = (TTree*)rootinosOld->CloneTree();
    rootinos->Write();
  }

  if(photonsOld){
    photonsOld->SetName("photons");
    photonsOld->SetTitle("photons");
    TTree *photons = (TTree*)photonsOld->CloneTree();
    photons->Write();
  }

  if(electronsOld){
    electronsOld->SetName("electrons");
    electronsOld->SetTitle("electrons");
    TTree *electrons = (TTree*)electronsOld->CloneTree();
    electrons->Write();
  }

  if(chargedPionsOld){
    chargedPionsOld->SetName("chargedPions");
    chargedPionsOld->SetTitle("chargedPions");
    TTree *chargedPions = (TTree*)chargedPionsOld->CloneTree();
    chargedPions->Write();
  }

  if(protonsOld){
    protonsOld->SetName("protons");
    protonsOld->SetTitle("protons");
    TTree *protons = (TTree*)protonsOld->CloneTree();
    protons->Write();
  }

  if(neutronsOld){
    neutronsOld->SetName("neutrons");
    neutronsOld->SetTitle("neutrons");
    TTree *neutrons = (TTree*)neutronsOld->CloneTree();
    neutrons->Write();
  }

  if(neutralPionsOld){
    neutralPionsOld->SetName("neutralPions");
    neutralPionsOld->SetTitle("neutralPions");
    TTree *neutralPions = (TTree*)neutralPionsOld->CloneTree();
    neutralPions->Write();
  }

  if(etasOld){
    etasOld->SetName("etas");
    etasOld->SetTitle("etas");
    TTree *etas = (TTree*)etasOld->CloneTree();
    etas->Write();
  }

  if(etaPrimesOld){
    etaPrimesOld->SetName("etaPrimes");
    etaPrimesOld->SetTitle("etaPrimes");
    TTree *etaPrimes = (TTree*)etaPrimesOld->CloneTree();
    etaPrimes->Write();
  }

  if(fOld.GetListOfKeys()->Contains("CheckCB")){
    fNew.mkdir("CheckCB");
    fNew.cd("CheckCB");

    TH2F *Check_CBdE_E = (TH2F*)fOld.Get("CheckCB/Check_CBdE_E");
    Check_CBdE_E->Write();
    TH2F *Check_CBPhiCorr = (TH2F*)fOld.Get("CheckCB/Check_CBPhiCorr");	
    Check_CBPhiCorr->Write();
    TH2F *Check_CBdE_E_1PID = (TH2F*)fOld.Get("CheckCB/Check_CBdE_E_1PID");	
    Check_CBdE_E_1PID->Write();
    TH2F *Check_CBPhiCorr_1PID = (TH2F*)fOld.Get("CheckCB/Check_CBPhiCorr_1PID");	
    Check_CBPhiCorr_1PID->Write();
    TH2F *Check_CBdE_E_pi0 = (TH2F*)fOld.Get("CheckCB/Check_CBdE_E_pi0");	
    Check_CBdE_E_pi0->Write();
    TH2F *Check_CBPhiCorr_pi0 = (TH2F*)fOld.Get("CheckCB/Check_CBPhiCorr_pi0");	
    Check_CBPhiCorr_pi0->Write();

    fNew.cd();
  }

  if(fOld.GetListOfKeys()->Contains("CheckTAPS")){
    fNew.mkdir("CheckTAPS");
    fNew.cd("CheckTAPS");

    TH2F *Check_TAPSdE_E = (TH2F*)fOld.Get("CheckTAPS/Check_TAPSdE_E");
    Check_TAPSdE_E->Write();
    TH2F *Check_TAPSPhiCorr = (TH2F*)fOld.Get("CheckTAPS/Check_TAPSPhiCorr");
    Check_TAPSPhiCorr->Write();
    TH2F *Check_TAPSdE_E_1Veto = (TH2F*)fOld.Get("CheckTAPS/Check_TAPSdE_E_1PID");
    Check_TAPSdE_E_1Veto->SetName("Check_TAPSdE_E_1Veto");
    Check_TAPSdE_E_1Veto->Write();
    TH2F *Check_TAPSPhiCorr_1Veto = (TH2F*)fOld.Get("CheckTAPS/Check_TAPSPhiCorr_1Veto");
    Check_TAPSPhiCorr_1Veto->Write();

    fNew.cd();
  }

  if(fOld.GetListOfKeys()->Contains("CheckHitPatterns")){
    fNew.mkdir("CheckHitPatterns");
    fNew.cd("CheckHitPatterns");	

    TH2F *Check_CBHits = (TH2F*)fOld.Get("CheckHitPatterns/Check_CBHits");
    Check_CBHits->Write();
    TH2F *Check_CBADCHits = (TH2F*)fOld.Get("CheckHitPatterns/Check_CBADCHits");
    Check_CBADCHits->Write();
    TH2F *Check_CBTDCHits = (TH2F*)fOld.Get("CheckHitPatterns/Check_CBTDCHits");
    Check_CBTDCHits->Write();

    TH2F *Check_PIDHits = (TH2F*)fOld.Get("CheckHitPatterns/Check_PIDHits");
    Check_PIDHits->Write();
    TH2F *Check_PIDADCHits = (TH2F*)fOld.Get("CheckHitPatterns/Check_PIDADCHits");
    Check_PIDADCHits->Write();
    TH2F *Check_PIDTDCHits = (TH2F*)fOld.Get("CheckHitPatterns/Check_PIDTDCHits");
    Check_PIDTDCHits->Write();

    TH2F *Check_TAPSHits = (TH2F*)fOld.Get("CheckHitPatterns/Check_TAPSHits");
    Check_TAPSHits->Write();
    TH2F *Check_TAPSADCHits = (TH2F*)fOld.Get("CheckHitPatterns/Check_TAPSADCHits");
    Check_TAPSADCHits->Write();
    TH2F *Check_TAPSTDCHits = (TH2F*)fOld.Get("CheckHitPatterns/Check_TAPSTDCHits");
    Check_TAPSTDCHits->Write();

    TH2F *Check_VetoHits = (TH2F*)fOld.Get("CheckHitPatterns/Check_VetoHits");
    Check_VetoHits->Write();
    TH2F *Check_VetoADCHits = (TH2F*)fOld.Get("CheckHitPatterns/Check_VetoADCHits");
    Check_VetoADCHits->Write();
    TH2F *Check_VetoTDCHits = (TH2F*)fOld.Get("CheckHitPatterns/Check_VetoTDCHits");
    Check_VetoTDCHits->Write();

    fNew.cd();
  }

  if(fOld.GetListOfKeys()->Contains("GoAT_File")){
    TNamed *GoAT_File = (TNamed*)fOld.Get("GoAT_File");
    GoAT_File->Write();
  }

  if(fOld.GetListOfKeys()->Contains("CountScalerValid")){
    TH1I *CountScalerValid = (TH1I*)fOld.Get("CountScalerValid");
    CountScalerValid->Write();
  }

  fNew.Close();
  fOld.Close();

}
