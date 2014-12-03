#include "GParticleReconstruction.h"


using namespace std;

GParticleReconstruction::GParticleReconstruction() :
    Identified(new Int_t[GTreeRawEvent_MAX]),
    Charge(new Int_t[GTreeRawEvent_MAX]),
    Hadron(new Int_t[GTreeRawEvent_MAX]),
    DoScalerCorrection(kFALSE),
    DoTrigger(kFALSE),
    E_Sum(50),
    multiplicity(1),
    charged_theta_min(0),
    charged_theta_max(180),
    charge_ignore_PID(kFALSE),
    charge_ignore_WC0(kFALSE),
    charge_ignore_WC1(kFALSE),
    charge_ignore_VETO(kFALSE)    
{
    CBTimeCut[0] = -1000000.0;
    CBTimeCut[1] = 1000000.0;
    TAPSTimeCut[0] = -1000000.0;
    TAPSTimeCut[1] = 1000000.0;
}

GParticleReconstruction::~GParticleReconstruction()
{
}

Bool_t GParticleReconstruction::Trigger()
{
    if(trigger->GetESum() < E_Sum)
        return kFALSE;
    if(trigger->GetMult() < multiplicity)
        return kFALSE;
    return kTRUE;
}


Bool_t GParticleReconstruction::Start()
{
    rootinos->CloseForInput();
    photons->CloseForInput();
    electrons->CloseForInput();
    chargedPi->CloseForInput();
    protons->CloseForInput();
    neutrons->CloseForInput();

    if(!TraverseValidEvents())		return kFALSE;

    return kTRUE;
}

Bool_t	GParticleReconstruction::Init()
{		
    GDataChecks::Init();

	cout << endl << "Particle Reconstruction turned ON" << endl;
    
    //CB
    // set default reconstruction (none)
    CB_type = Recon_None;

    config = ReadConfig("Cut-dE-E-CB-Proton");
    if (strcmp(config.c_str(), "nokey") != 0)
    {
        if(sscanf( config.c_str(), "%s %s\n", cutfilename,cutname) == 2)
        {
            CB_type = ReconType(Recon_dE_Proton | CB_type);
            if(!(Cut_CB_proton = OpenCutFile(cutfilename,cutname)))
            {
                cerr << "Failed to load cut! Terminating..." << endl;
                exit(1);
            }
        }
        else
        {
            cout << "ERROR: Cut-dE-E-CB-Proton set improperly" << endl;
            return kFALSE;
        }
    }

    config = ReadConfig("Cut-dE-E-CB-Pion");
    if (strcmp(config.c_str(), "nokey") != 0)
    {
        if(sscanf( config.c_str(), "%s %s\n", cutfilename,cutname) == 2)
        {
            CB_type = ReconType(Recon_dE_Pion | CB_type);
            if(!(Cut_CB_pion = OpenCutFile(cutfilename,cutname)))
            {
                cerr << "Failed to load cut! Terminating..." << endl;
                exit(1);
            }
        }
        else
        {
            cout << "ERROR: Cut-dE-E-CB-Pion set improperly" << endl;
            return kFALSE;
        }
    }

    config = ReadConfig("Cut-dE-E-CB-Electron");
    if (strcmp(config.c_str(), "nokey") != 0)
    {
        if(sscanf( config.c_str(), "%s %s\n", cutfilename,cutname) == 2)
        {
            CB_type = ReconType(Recon_dE_Electron | CB_type);
            if(!(Cut_CB_electron = OpenCutFile(cutfilename,cutname)))
            {
                cerr << "Failed to load cut! Terminating..." << endl;
                exit(1);
            }
        }
        else
        {
            cout << "ERROR: Cut-dE-E-CB-Electron set improperly" << endl;
            return kFALSE;
        }
    }

    config = ReadConfig("Cut-CB-TOF");
    if (strcmp(config.c_str(), "nokey") != 0)
    {
        if(sscanf( config.c_str(), "%s %s\n", cutfilename,cutname) == 2)
        {
            CB_type = ReconType(Recon_TOF | CB_type);
            if(!(Cut_CB_TOF = OpenCutFile(cutfilename,cutname)))
            {
                cerr << "Failed to load cut! Terminating..." << endl;
                exit(1);
            }
        }
        else
        {
            cout << "ERROR: Cut-CB-TOF set improperly" << endl;
            return kFALSE;
        }
    }

    config = ReadConfig("Cut-CB-ClustSize");
    if (strcmp(config.c_str(), "nokey") != 0)
    {
        if(sscanf( config.c_str(), "%s %s\n", cutfilename,cutname) == 2)
        {
            CB_type = ReconType(Recon_ClustSize | CB_type);
            if(!(Cut_CB_ClustSize = OpenCutFile(cutfilename,cutname)))
            {
                cerr << "Failed to load cut! Terminating..." << endl;
                exit(1);
            }
        }
        else
        {
            cout << "ERROR: Cut-CB-ClustSize set improperly" << endl;
            return kFALSE;
        }
    }

    // check for optional "all photon" reconstruction
    config = ReadConfig("CB-all-photons");
    if (strcmp(config.c_str(), "nokey") != 0)
    {
        CB_type = Recon_AllPhotons;
        cout << "Setting all CB particles to photons" << endl;
    }

    // check for optional "all proton" reconstruction
    config = ReadConfig("CB-all-protons");
    if (strcmp(config.c_str(), "nokey") != 0)
    {
        CB_type = Recon_AllProtons;
        cout << "Setting all CB particles to protons" << endl;
    }

    //TAPS
    // set default reconstruction (none)
    TAPS_type = Recon_None;

    config = ReadConfig("Cut-dE-E-TAPS-Proton");
    if (strcmp(config.c_str(), "nokey") != 0)
    {
        if(sscanf( config.c_str(), "%s %s\n", cutfilename,cutname) == 2)
        {
            TAPS_type = ReconType(Recon_dE_Proton | TAPS_type);
            if(!(Cut_TAPS_proton = OpenCutFile(cutfilename,cutname)))
            {
                cerr << "Failed to load cut! Terminating..." << endl;
                exit(1);
            }
        }
        else
        {
            cout << "ERROR: Cut-dE-E-TAPS-Proton set improperly" << endl;
            return kFALSE;
        }
    }

    config = ReadConfig("Cut-dE-E-TAPS-Pion");
    if (strcmp(config.c_str(), "nokey") != 0)
    {
        if(sscanf( config.c_str(), "%s %s\n", cutfilename,cutname) == 2)
        {
            TAPS_type = ReconType(Recon_dE_Pion | TAPS_type);
            if(!(Cut_TAPS_pion = OpenCutFile(cutfilename,cutname)))
            {
                cerr << "Failed to load cut! Terminating..." << endl;
                exit(1);
            }
        }
        else
        {
            cout << "ERROR: Cut-dE-E-TAPS-Pion set improperly" << endl;
            return kFALSE;
        }
    }

    config = ReadConfig("Cut-dE-E-TAPS-Electron");
    if (strcmp(config.c_str(), "nokey") != 0)
    {
        if(sscanf( config.c_str(), "%s %s\n", cutfilename,cutname) == 2)
        {
            TAPS_type = ReconType(Recon_dE_Electron | TAPS_type);
            if(!(Cut_TAPS_electron  = OpenCutFile(cutfilename,cutname)))
            {
                cerr << "Failed to load cut! Terminating..." << endl;
                exit(1);
            }
        }
        else
        {
            cout << "ERROR: Cut-dE-E-TAPS-Electron set improperly" << endl;
            return kFALSE;
        }
    }

    config = ReadConfig("Cut-TAPS-TOF");
    if (strcmp(config.c_str(), "nokey") != 0)
    {
        if(sscanf( config.c_str(), "%s %s\n", cutfilename,cutname) == 2)
        {
            TAPS_type = ReconType(Recon_TOF | TAPS_type);
            if(!(Cut_TAPS_TOF = OpenCutFile(cutfilename,cutname)))
            {
                cerr << "Failed to load cut! Terminating..." << endl;
                exit(1);
            }
        }
        else
        {
            cout << "ERROR: Cut-TAPS-TOF set improperly" << endl;
            return kFALSE;
        }
    }

    config = ReadConfig("Cut-TAPS-ClustSize");
    if (strcmp(config.c_str(), "nokey") != 0)
    {
        if(sscanf( config.c_str(), "%s %s\n", cutfilename,cutname) == 2)
        {
            TAPS_type = ReconType(Recon_ClustSize | TAPS_type);
            if(!(Cut_TAPS_ClustSize = OpenCutFile(cutfilename,cutname)))
            {
                cerr << "Failed to load cut! Terminating..." << endl;
                exit(1);
            }
        }
        else
        {
            cout << "ERROR: Cut-TAPS-ClustSize set improperly" << endl;
            return kFALSE;
        }
    }

    // check for optional "all photon" reconstruction
    config = ReadConfig("TAPS-all-photons");
    if (strcmp(config.c_str(), "nokey") != 0)
    {
        TAPS_type = Recon_AllPhotons;
        cout << "Setting all TAPS particles to photons" << endl;
    }

    // check for optional "all proton" reconstruction
    config = ReadConfig("TAPS-all-protons");
    if (strcmp(config.c_str(), "nokey") != 0)
    {
        TAPS_type = Recon_AllProtons;
        cout << "Setting all TAPS particles to protons" << endl;
    }

    // Option to ignore energy deposit in detectors when determining charge
    config = ReadConfig("charge-ignore-PID");
    if (strcmp(config.c_str(), "nokey") != 0) charge_ignore_PID = kTRUE;

    config = ReadConfig("charge-ignore-WC0");
    if (strcmp(config.c_str(), "nokey") != 0) charge_ignore_WC0 = kTRUE;
    
    config = ReadConfig("charge-ignore-WC1");
    if (strcmp(config.c_str(), "nokey") != 0) charge_ignore_WC1 = kTRUE;
    
    config = ReadConfig("charge-ignore-VETO");
    if (strcmp(config.c_str(), "nokey") != 0) charge_ignore_VETO = kTRUE;
    
    
	// Particle timing cuts
    config = ReadConfig("CB-PARTICLE-TIME-CUT");
    if (strcmp(config.c_str(), "nokey") != 0)
    {
        if(sscanf( config.c_str(), "%lf %lf\n", &CBTimeCut[0], &CBTimeCut[1]) != 2)
        {
            cout << "ERROR: CB-PARTICLE-TIME-CUT set improperly" << endl;
            return kFALSE;
        }
    }

    config = ReadConfig("TAPS-PARTICLE-TIME-CUT");
    if (strcmp(config.c_str(), "nokey") != 0)
    {
        if(sscanf( config.c_str(), "%lf %lf\n", &TAPSTimeCut[0], &TAPSTimeCut[1]) != 2)
        {
            cout << "ERROR: TAPS-PARTICLE-TIME-CUT set improperly" << endl;
            return kFALSE;
        }
    }
	
	return kTRUE;
}

Bool_t	GParticleReconstruction::ProcessEventWithoutFilling()
{
    if(DoTrigger)
    {
        if(!Trigger())
            return kFALSE;
    }

    rootinos->Clear();
    photons->Clear();
    electrons->Clear();
    chargedPi->Clear();
    protons->Clear();
    neutrons->Clear();

    for(Int_t i=0; i<rawEvent->GetNParticles(); i++)
    {
        if(rawEvent->GetApparatus(i) == GTreeRawEvent::APPARATUS_CB)
        {
            if(rawEvent->GetTime(i)<CBTimeCut[0] || rawEvent->GetTime(i)>CBTimeCut[1])
                return kFALSE;

            Identified[i] = pdg_rootino;
            Charge[i] = 0;
            Hadron[i] = 0;

            if(CB_type & Recon_AllPhotons)
            {
                Identified[i] = pdgDB->GetParticle("gamma")->PdgCode();
                continue;
            }

            if(CB_type & Recon_AllProtons)
            {
                Identified[i] = pdgDB->GetParticle("proton")->PdgCode();
                continue;
            }

            if ((!charge_ignore_PID) && (rawEvent->Get_dE(i) > 0.0))	Charge[i] = 1;
            if ((!charge_ignore_WC0) && (rawEvent->GetWC0_E(i) > 0.0))	Charge[i] = 1;
            if ((!charge_ignore_WC1) && (rawEvent->GetWC1_E(i) > 0.0))	Charge[i] = 1;

            if(CB_type & Recon_TOF)
            {
                if(Cut_CB_TOF->IsInside(rawEvent->GetEk(i),rawEvent->GetTime(i)))
                    Hadron[i] = 1;
            }

            if(CB_type & Recon_ClustSize)
            {
                if(Cut_CB_ClustSize->IsInside(rawEvent->GetEk(i),rawEvent->GetClusterSize(i)))
                    Hadron[i] = 1;
            }

            if (Charge[i] == 0)
            {
                if(Hadron[i] == 0) Identified[i] = pdgDB->GetParticle("gamma")->PdgCode();
                else Identified[i] = pdgDB->GetParticle("neutron")->PdgCode();
                continue;
            }

            if (rawEvent->GetTheta(i) < charged_theta_min) break; // user rejected theta region
            if (rawEvent->GetTheta(i) > charged_theta_max) break; // user rejected theta region

            if(Hadron[i] == 1)
            {
                Identified[i] = pdgDB->GetParticle("proton")->PdgCode();
                continue;
            }

            if(CB_type & Recon_dE_Proton)
            {
                if(Cut_CB_proton->IsInside(rawEvent->GetEk(i),rawEvent->Get_dE(i)))
                    Identified[i] = pdgDB->GetParticle("proton")->PdgCode();
            }
            if(CB_type & Recon_dE_Pion)
            {
                if(Cut_CB_pion->IsInside(rawEvent->GetEk(i),rawEvent->Get_dE(i)))
                    Identified[i] = pdgDB->GetParticle("pi+")->PdgCode();
            }

            if(CB_type & Recon_dE_Electron)
            {
                if(Cut_CB_electron->IsInside(rawEvent->GetEk(i),rawEvent->Get_dE(i)))
                    Identified[i] = pdgDB->GetParticle("e-")->PdgCode();
            }

        }

        if(rawEvent->GetApparatus(i) == GTreeRawEvent::APPARATUS_TAPS)
        {
            if(rawEvent->GetTime(i)<TAPSTimeCut[0] || rawEvent->GetTime(i)>TAPSTimeCut[1])
                return kFALSE;

            Identified[i] = pdg_rootino;
            Charge[i] = 0;
            Hadron[i] = 0;

            if(TAPS_type & Recon_AllPhotons)
            {
                Identified[i] = pdgDB->GetParticle("gamma")->PdgCode();
                continue;
            }

            if(TAPS_type & Recon_AllProtons)
            {
                Identified[i] = pdgDB->GetParticle("proton")->PdgCode();
                continue;
            }

            if ((!charge_ignore_VETO) && (rawEvent->Get_dE(i) > 0.0))	Charge[i] = 1;

            if(TAPS_type & Recon_TOF)
            {
                if(Cut_TAPS_TOF->IsInside(rawEvent->GetEk(i),rawEvent->GetTime(i)))
                    Hadron[i] = 1;
            }

            if(TAPS_type & Recon_ClustSize)
            {
                if(Cut_TAPS_ClustSize->IsInside(rawEvent->GetEk(i),rawEvent->GetClusterSize(i)))
                    Hadron[i] = 1;
            }

            if (Charge[i] == 0)
            {
                if(Hadron[i] == 0) Identified[i] = pdgDB->GetParticle("gamma")->PdgCode();
                else Identified[i] = pdgDB->GetParticle("neutron")->PdgCode();
                continue;
            }

            if (rawEvent->GetTheta(i) < charged_theta_min) break; // user rejected theta region
            if (rawEvent->GetTheta(i) > charged_theta_max) break; // user rejected theta region

            if(Hadron[i] == 1)
            {
                Identified[i] = pdgDB->GetParticle("proton")->PdgCode();
                continue;
            }

            if(TAPS_type & Recon_dE_Proton)
            {
                if(Cut_TAPS_proton->IsInside(rawEvent->GetEk(i),rawEvent->Get_dE(i)))
                    Identified[i] = pdgDB->GetParticle("proton")->PdgCode();
            }
            if(TAPS_type & Recon_dE_Pion)
            {
                if(Cut_TAPS_pion->IsInside(rawEvent->GetEk(i),rawEvent->Get_dE(i)))
                    Identified[i] = pdgDB->GetParticle("pi+")->PdgCode();
            }

            if(TAPS_type & Recon_dE_Electron)
            {
                if(Cut_TAPS_electron->IsInside(rawEvent->GetEk(i),rawEvent->Get_dE(i)))
                    Identified[i] = pdgDB->GetParticle("e-")->PdgCode();
            }

        }
    }

    for (int i = 0; i < rawEvent->GetNParticles(); i++)
    {
        // Finally add particles which were temporarily identified
        if (Identified[i] == pdgDB->GetParticle("proton")->PdgCode())
            protons->AddParticle(rawEvent->GetVector(i, pdgDB->GetParticle("proton")->Mass()*1000), rawEvent->GetApparatus(i), rawEvent->Get_dE(i), rawEvent->GetWC0_E(i), rawEvent->GetWC1_E(i), rawEvent->GetTime(i), rawEvent->GetClusterSize(i));
        else if (Identified[i] == pdgDB->GetParticle("pi+")->PdgCode())
            chargedPi->AddParticle(rawEvent->GetVector(i, pdgDB->GetParticle("pi+")->Mass()*1000), rawEvent->GetApparatus(i), rawEvent->Get_dE(i), rawEvent->GetWC0_E(i), rawEvent->GetWC1_E(i), rawEvent->GetTime(i), rawEvent->GetClusterSize(i));
        else if (Identified[i] == pdgDB->GetParticle("e-")->PdgCode())
            electrons->AddParticle(rawEvent->GetVector(i, pdgDB->GetParticle("e-")->Mass()*1000), rawEvent->GetApparatus(i), rawEvent->Get_dE(i), rawEvent->GetWC0_E(i), rawEvent->GetWC1_E(i), rawEvent->GetTime(i), rawEvent->GetClusterSize(i));
        else if (Identified[i] == pdgDB->GetParticle("neutron")->PdgCode())
            neutrons->AddParticle(rawEvent->GetVector(i, pdgDB->GetParticle("neutron")->Mass()*1000), rawEvent->GetApparatus(i), rawEvent->Get_dE(i), rawEvent->GetWC0_E(i), rawEvent->GetWC1_E(i), rawEvent->GetTime(i), rawEvent->GetClusterSize(i));
        else if (Identified[i] == pdgDB->GetParticle("gamma")->PdgCode())
            photons->AddParticle(rawEvent->GetVector(i), rawEvent->GetApparatus(i), rawEvent->Get_dE(i), rawEvent->GetWC0_E(i), rawEvent->GetWC1_E(i), rawEvent->GetTime(i), rawEvent->GetClusterSize(i));
        else if (Identified[i] == pdg_rootino)
            rootinos->AddParticle(rawEvent->GetVector(i), rawEvent->GetApparatus(i), rawEvent->Get_dE(i), rawEvent->GetWC0_E(i), rawEvent->GetWC1_E(i), rawEvent->GetTime(i), rawEvent->GetClusterSize(i));
    }

    return kTRUE;
}

void	GParticleReconstruction::ProcessEvent()
{    
    if(!ProcessEventWithoutFilling())   return;

    eventParameters->SetNReconstructed(GetNReconstructed());
    eventParameters->Fill();

    rootinos->Fill();
    photons->Fill();
    electrons->Fill();
    chargedPi->Fill();
    protons->Fill();
    neutrons->Fill();
    FillReadList();
}

/**
 * @brief Load a cut from a ROOT file
 * @param filename The ROOT file to open
 * @param cutname The name of the TCutG object to load
 * @return Pointer to the cut
 * @throw bool false on any error
 */
TCutG*	GParticleReconstruction::OpenCutFile(Char_t* filename, Char_t* cutname)
{
	CutFile 	= new TFile(filename, "READ");

    if( !CutFile || !CutFile->IsOpen() ) {
        cerr << "Can't open cut file: " << filename << endl;
        throw false;
    }


    // Try to find a TCutG with the name we want
    // GetObject checks the type to be TCutG,
    // see http://root.cern.ch/root/html534/TDirectory.html#TDirectory:GetObject
    CutFile->GetObject(cutname, Cut);

    if( !Cut ) {
        cerr << "Could not find a TCutG with the name " << cutname << " in " << filename << endl;
        throw false;
    }

    TCutG* Cut_clone = Cut;
    CutFile->Close();

    cout << "cut file " << filename << 	" opened (Cut-name = " << cutname << ")"<< endl;
    return Cut_clone;
}
